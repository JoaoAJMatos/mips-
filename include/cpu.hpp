/**
 * @file    cpu.hpp
 * @author  JoaoAJMatos
 *
 * @brief   This file contains the MIPS++ CPU.
 *          The CPU is used to execute MIPS assembly code.
 *
 * @date    2023-10-19
 * 
 * @copyright Copyright (c) 2023 JoaoAJMatos
 */

#ifndef MIPS_CPU_HPP
#define MIPS_CPU_HPP

/** Local Includes */
#include "common.hpp"
#include "memory.hpp"

namespace mips
{
      /**
       * @brief CPU class
       *
       * @details This structure emulates the MIPS CPU
       */
      class CPU
      {
      public:
            CPU(Memory* memory);
            ~CPU() {}

            /** @brief Resets the CPU */
            void reset();

            /**
             * @brief Steps the CPU
             *
             * @details This function goes through one fetch-decode-execute
             *          cycle.
             */
            void step();

            /**
             * @brief Gets the state of the CPU
             *
             * @details This function returns the string representation of the
             *          CPU state.
             *
             * @return The state of the CPU
             */
            std::string state();

      private:
            /**
             * @brief Fetches the next instruction from memory
             *
             * @details This function fetches the next instruction from memory
             *          and increments the program counter.
             * 
             * @return The next instruction
             */
            instruction_t fetch();

            /**
             * @brief Decodes the instruction
             *
             * @details This function decodes the instruction and returns the
             *          opcode.
             * 
             * @param[i] instruction The instruction to decode
             * 
             * @return The opcode
             */
            opcode_t decode(instruction_t instruction);

            /**
             * @brief Executes the instruction
             *
             * @details This function executes the instruction.
             * 
             * @param[i] instruction The instruction to execute
             * @param[i] opcode The opcode of the instruction
             */
            void execute(instruction_t instruction, opcode_t opcode);

            /**
             * @brief Executes the R-type instruction
             *
             * @details This function executes the R-type instruction.
             * 
             * @param[i] instruction The instruction to execute
             */
            void execute_r(instruction_t instruction);

            /**
             * @brief Executes the I-type instruction
             *
             * @details This function executes the I-type instruction.
             * 
             * @param[i] instruction The instruction to execute
             */
            void execute_i(instruction_t instruction);

            /**
             * @brief Executes the J-type instruction
             *
             * @details This function executes the J-type instruction.
             * 
             * @param[i] instruction The instruction to execute
             */
            void execute_j(instruction_t instruction);

            /**
             * @brief Executes a syscall
             * 
             * @details This function does not take any arguments because the
             *          syscall number is stored in $v0.
             */
            void execute_syscall();

            /**
             * @brief Gets the syscall code
             * 
             * @details This function gets the syscall code from $v0.
             * 
             * @return The syscall code
             */
            byte_t get_syscall_code() { return registers[2]; }

            /* Registers */
            register_t pc;             /* Program counter */
            register_t hi;             /* High register */
            register_t lo;             /* Low register */
            register_t registers[32];  /* General purpose registers */

            /* Flags */
            [[maybe_unused]] bool overflow;              /* Overflow flag */
            [[maybe_unused]] bool carry;                 /* Carry flag */
            [[maybe_unused]] bool zero;                  /* Zero flag */
            [[maybe_unused]] bool negative;              /* Negative flag */

            /* Pointer to the memory */
            Memory* memory;
      };
}

#endif // MIPS_CPU_HPP

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