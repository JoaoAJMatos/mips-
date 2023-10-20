//
// Created by JoaoAJMatos on 2023-10-19
//

/** C++ Includes */
#include <iostream>

/** Mips Includes */
#include <cpu.hpp>
#include <instruction.hpp>

/** 
 * @brief Constructor
 */
mips::CPU::CPU(Memory* memory) {
      reset();
      this->memory = memory;
}

/** 
 * @brief Resets the CPU 
 * 
 * @details This function resets the CPU by setting all registers to 0
 */
void mips::CPU::reset() {
      pc = 0;
      hi = 0;
      lo = 0;
      for (int i = 0; i < 32; i++) {
            registers[i] = 0;
      }
}

/** 
 * @brief Steps the CPU
 * 
 * @details This function goes through one fetch-decode-execute cycle
 */
void mips::CPU::step() {
      instruction_t instruction = fetch();
      opcode_t opcode = decode(instruction);
      execute(instruction, opcode);
}

/**
 * @brief Gets the string representation of the CPU state
 * 
 * @return std::string 
 */
std::string mips::CPU::state() {
      std::string state = "PC: " + std::to_string(pc) + "\n";
      state += "Registers:\n";
      for (int i = 0; i < 32; i++) {
            state += "$" + std::to_string(i) + ": " + std::to_string(registers[i]) + "\n";
      }
      state += "HI: " + std::to_string(hi) + "\n";
      state += "LO: " + std::to_string(lo) + "\n";
      return state;
}

/** 
 * @brief Fetches instruction
 * 
 * @details This function fetches the next instruction from memory and increments
 *          the program counter
 */
mips::instruction_t mips::CPU::fetch() {
      instruction_t instruction = memory->read_word(pc);
      pc += sizeof(instruction_t);
      return instruction;
}

/** 
 * @brief Decodes the instruction 
 * 
 * @details This function decodes the instruction and returns the opcode
 */
mips::opcode_t mips::CPU::decode(instruction_t instruction) {
      return get_opcode(instruction);
}

/** 
 * @brief Executes the instruction 
 * 
 * @details This function executes the instruction according to its opcode
 *          and instruction type.
 */
void mips::CPU::execute(instruction_t instruction, opcode_t opcode) {
      switch (opcode) {
            case R_TYPE: // R-type
                  execute_r(instruction);
                  break;
            case SYSCALL: // syscall
                  execute_syscall();
                  break;
            default:
                  execute_i(instruction);
                  execute_j(instruction);
                  break;
      }
}

/** 
 * @brief Executes the R-type instruction
 * 
 * @details In R-type instructions, the opcode is 0x00
 *          and the funct field determines the operation.
 */
void mips::CPU::execute_r(instruction_t instruction) {
      /** Extract the fileds from the instruction */
      byte_t rs = get_rs(instruction);
      byte_t rt = get_rt(instruction);
      byte_t rd = get_rd(instruction);
      [[maybe_unused]] byte_t shamt = get_shamt(instruction);
      byte_t funct = get_funct(instruction);

      switch (funct) {
            case 0x20: // add
                  registers[rd] = registers[rs] + registers[rt];
                  break;
            case 0x22: // sub
                  registers[rd] = registers[rs] - registers[rt];
                  break;
            case 0x24: // and
                  registers[rd] = registers[rs] & registers[rt];
                  break;
            case 0x25: // or
                  registers[rd] = registers[rs] | registers[rt];
                  break;
            default:
                  throw std::runtime_error("Invalid funct for R-type instruction");
      }
}

/** 
 * @brief Executes the J-type instruction 
 * 
 * @details In J-type instructions, the opcode is 0x02 or 0x03
 *          and the address field determines the target address.
 */
void mips::CPU::execute_j(instruction_t instruction) {
      /** Extract the fields from the instruction */
      byte_t opcode = get_opcode(instruction);
      address_t address = get_address(instruction);

      switch (opcode) {
            case 0x02: // j (jumps to the target address)
                  pc = address;
                  break;
            case 0x03: // jal (jumps to the target address and stores the return address in $ra)
                  registers[31] = pc;
                  pc = address;
                  break;
            default:
                  throw std::runtime_error("Invalid opcode for J-type instruction");
      }
}

/** 
 * @brief Executes the I-type instruction 
 * 
 * @details In I-type instructions, the opcode is not 0x00, 0x02 or 0x03
 *          and the immediate field determines the operation.
 */
void mips::CPU::execute_i(instruction_t instruction) {
      /** Extract the fields from the instruction */
      byte_t opcode = get_opcode(instruction);
      byte_t rs = get_rs(instruction);
      byte_t rt = get_rt(instruction);
      halfword_t immediate = get_immediate(instruction);

      switch (opcode) {
            case 0x23: // lw (loads a word from memory)
                  registers[rt] = memory->read_word(registers[rs] + immediate);
                  break;
            case 0x2B: // sw (stores a word in memory)
                  memory->write_word(registers[rs] + immediate, registers[rt]);
                  break;
            case 0x0F: // lui (loads a word in the upper half of a register)
                  registers[rt] = immediate << 16;
                  break;
            case 0x0C: // andi (bitwise and with immediate)
                  registers[rt] = registers[rs] & immediate;
                  break;
            case 0x0D: // ori (bitwise or with immediate)
                  registers[rt] = registers[rs] | immediate;
                  break;
            case 0x0E: // nori (bitwise nor with immediate)
                  registers[rt] = ~(registers[rs] | immediate);
                  break;
            case 0x0A: // slti (set less than immediate)
                  registers[rt] = registers[rs] < immediate;
                  break;
            case 0x04: // beq (branch if equal)
                  if (registers[rs] == registers[rt]) {
                        pc += immediate << 2;
                  }
                  break;
            case 0x05: // bne (branch if not equal)
                  if (registers[rs] != registers[rt]) {
                        pc += immediate << 2;
                  }
                  break;
            case 0x07: // bgtz (branch if greater than zero)
                  if (registers[rs] > 0) {
                        pc += immediate << 2;
                  }
                  break;
            default:
                  throw std::runtime_error("Invalid opcode for I-type instruction");
      }
}

/** 
 * @brief Executes the syscall instruction 
 */
void mips::CPU::execute_syscall() {
      /** Grab the syscall code from $v0 */
      byte_t syscall_code = get_syscall_code();

      switch (syscall_code) {
            case 1: // print_int (print an integer to stdout)
                  std::cout << registers[4];
                  break;
            case 4: // print_string (print a string to stdout)
                  std::cout << memory->read_string(registers[4]);
                  break;
            case 5: // read_int (read an integer from stdin)
                  std::cin >> registers[2];
                  break;
            case 8: // read_string (read a string from stdin)
                  //std::cin >> memory->read_string(registers[4]);
                  break;
            // TODO: Add support for sbrk
            /*case 9: // sbrk (allocate memory on the heap)
                  registers[2] = memory->allocate(registers[4]);
                  break; */
            case 10: // exit (exit the program)
                  exit(registers[4]);
                  break;
            case 11: // print_char (print a character to stdout)
                  std::cout << static_cast<char>(registers[4]);
                  break;
            case 12: // read_char (read a character from stdin)
                  //std::cin >> static_cast<char>(registers[2]);
                  break;
            default:
                  throw std::runtime_error("Invalid syscall code");
      }
}

// MIT License
// 
// Copyright (c) 2023 João Matos
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.