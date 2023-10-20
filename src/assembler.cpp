//
// Created by JoaoAJMatos on 2023-10-19
//

/** C++ Includes */
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cassert>
#include <algorithm>
#include <array>
#include <map>

/** MIPS Includes */
#include <assembler.hpp> 
#include <instruction.hpp>
#include <common.hpp>
#include <obj.hpp>
#include <except.hpp>

//////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Throw syntax error if the number of arguments is not the expected
 *        number of arguments for the given instruction.
 */
#define ASSERT_ARG_COUNT(count, line, instruction) if (tokens.size() != count) \
      throw mips::SyntaxException("Invalid number of arguments in line " + std::to_string(line) + " for instruction '" + instruction + \
      "' (expected " + std::to_string(count) + ", got " + std::to_string(tokens.size()) + ")");

//////////////////////////////////////////////////////////////////////////////////////////

#define SHOW_FIRST_PASS_BANNER()  std::cout << "===============================" << std::endl; \
                                  std::cout << "          First pass           " << std::endl; \
                                  std::cout << "===============================" << std::endl;

#define SHOW_SECOND_PASS_BANNER() std::cout << "===============================" << std::endl; \
                                  std::cout << "          Second pass          " << std::endl; \
                                  std::cout << "===============================" << std::endl;

#define SHOW_LABELS_BANNER()      std::cout << "===============================" << std::endl; \
                                  std::cout << "            Labels             " << std::endl; \
                                  std::cout << "===============================" << std::endl;

//////////////////////////////////////////////////////////////////////////////////////////

#define SHOW_LABELS() \
      for (auto label : this->labels) { \
            std::cout << label.name << " -> " << label.address << std::endl; \
      }

#define SHOW_TOKENS() \
      std::cout << "Tokens: " << std::endl; \
      std::cout << "Line " << i << ": ["; \
      for (auto token : tokens) { \
            if (token == tokens.back()) std::cout << token; \
            else std::cout << token << ", "; \
      } \
      std::cout << "]" << std::endl;

#define SHOW_CURRENT_LINE() std::cout << "Line " << i << ": " << line << std::endl;
#define SHOW_R_TYPE_INSTRUCTION() std::cout << "R-Type Instruction: " << tokens[0] << " " << tokens[1] << " " << tokens[2] << " " << tokens[3] << std::endl;
#define SHOW_I_TYPE_INSTRUCTION() std::cout << "I-Type Instruction: " << tokens[0] << " " << tokens[1] << " " << tokens[2] << " " << tokens[3] << std::endl;
#define SHOW_J_TYPE_INSTRUCTION() std::cout << "J-Type Instruction: " << tokens[0] << " " << tokens[1] << std::endl;

//////////////////////////////////////////////////////////////////////////////////////////

/** Constants */
constexpr int MAX_IMMEDIATE = 32767;
constexpr int MIN_IMMEDIATE = -32768;

/** Opcode mappings */
static std::map<std::string, mips::byte_t> r_opcode_map = {
      {"add", 0x20}, {"addu", 0x21}, {"and", 0x24}, {"break", 0x0D},
      {"div", 0x1A}, {"divu", 0x1B}, {"jalr", 0x09}, {"jr", 0x08},
      {"mfhi", 0x10}, {"mflo", 0x12}, {"mthi", 0x11}, {"mtlo", 0x13},
      {"mult", 0x18}, {"multu", 0x19}, {"nor", 0x27}, {"or", 0x25},
      {"sll", 0x00}, {"sllv", 0x04}, {"slt", 0x2A}, {"sltu", 0x2B},
      {"sra", 0x03}, {"srav", 0x07}, {"srl", 0x02}, {"srlv", 0x06},
      {"sub", 0x22}, {"subu", 0x23}, {"syscall", 0x0C}, {"xor", 0x26}
};

static std::map<std::string, mips::byte_t> i_opcode_map = {
      {"addi", 0x08}, {"addiu", 0x09}, {"andi", 0x0C}, {"beq", 0x04},
      {"bgez", 0x01}, {"bgezal", 0x01}, {"bgtz", 0x07}, {"blez", 0x06},
      {"bltz", 0x01}, {"bltzal", 0x01}, {"bne", 0x05}, {"lb", 0x20},
      {"lbu", 0x24}, {"lh", 0x21}, {"lhu", 0x25}, {"lui", 0x0F},
      {"lw", 0x23}, {"lwc1", 0x31}, {"ori", 0x0D}, {"sb", 0x28},
      {"sh", 0x29}, {"slti", 0x0A}, {"sltiu", 0x0B}, {"sw", 0x2B},
      {"swc1", 0x39}, {"xori", 0x0E}
};

static std::map<std::string, mips::byte_t> j_opcode_map = {
      {"j", 0x02},
      {"jal", 0x03}
};

//////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Checks if a given instruction is a R-type instruction
 * 
 * @param[i] instruction
 * @return true/false
 */
static inline bool is_r_type_instruction(std::string instruction) {
      return r_opcode_map.find(instruction) != r_opcode_map.end();
}

/**
 * @brief Checks if a given instruction is a I-type instruction
 * 
 * @param[i] instruction
 * @return true/false
 */
static inline bool is_i_type_instruction(std::string instruction) {
      return i_opcode_map.find(instruction) != i_opcode_map.end();
}

/**
 * @brief Checks if a given instruction is a J-type instruction
 * 
 * @param[i] instruction
 * @return true/false
 */
static inline bool is_j_type_instruction(std::string instruction) {
      return j_opcode_map.find(instruction) != j_opcode_map.end();
}

/**
 * @brief Checks if a given line contains a label
 * 
 * @param[i] instruction
 * @return true/false
 */
static inline bool is_label(std::string line) {
      return line.find(":") != std::string::npos;
}

/**
 * @brief Checks if a given line is a comment
 * 
 * @param[i] instruction
 * @return true/false
 */
static inline bool is_comment(std::string line) {
      return line.find("#") != std::string::npos;
}

/**
 * @brief Checks if a given line is empty
 * 
 * @param[i] line 
 * @return true/false
 */
static inline bool is_empty_line(std::string line) {
      return line == "" || line == "\n";
}

/**
 * @brief Checks if the given register is valid
 * 
 * @param[i] reg 
 * @return true/false
 */
static inline bool is_valid_register(std::string reg) {
      return reg[0] == '$' && reg.size() == 3 && reg[1] == 't' && reg[2] >= '0' && reg[2] <= '9';
}

/**
 * @brief Checks if a given immediate value is valid
 * 
 * @param[i] immediate 
 * @return true/false
 */
static inline bool is_valid_immediate(std::string immediate) {
      if (immediate[0] == '-') {
            immediate = immediate.substr(1);
      }
      for (size_t i = 0; i < immediate.size(); i++) {
            if (immediate[i] < '0' || immediate[i] > '9') return false;
      }
      int imm = std::stoi(immediate);
      return imm >= MIN_IMMEDIATE && imm <= MAX_IMMEDIATE;
}

/**
 * @brief Checks if the given address is valid
 * 
 * @param address 
 * @return true/false
 */
static inline bool is_valid_address(std::string address) {
      for (size_t i = 0; i < address.size(); i++) {
            if (address[i] < '0' || address[i] > '9') return false;
      }
      return true;
}

/** 
 * @brief Trims a string
 * @details Removes leading and trailing spaces from a string
 * 
 * @param[i/o] line 
 */
static void trim(std::string &str) {
      str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch) {
            return !std::isspace(ch);
      }));
      str.erase(std::find_if(str.rbegin(), str.rend(), [](int ch) {
            return !std::isspace(ch);
      }).base(), str.end());
}

/** 
 * @brief Tokenizes a string 
 * 
 * @param[i] line
 * @return std::vector<std::string>
 * 
 * @example "add $t0, $t1, $t2" -> ["add", "$t0", "$t1", "$t2"]
 */
static std::vector<std::string> tokenize(std::string line) {
      std::vector<std::string> tokens;
      std::string token;
      std::istringstream token_stream(line);

      std::getline(token_stream, token, ' ');
      trim(token);
      tokens.push_back(token);

      while (std::getline(token_stream, token, ',')) {
            trim(token);
            tokens.push_back(token);
      }

      return tokens;
}

/**
 * @brief Assembles a R-type instruction from the given tokens
 * 
 * @param instruction 
 * @param rd 
 * @param rs 
 * @param rt 
 * @return mips::instruction_t 
 */
static mips::instruction_t assemble_r_type_instruction(std::string instruction, std::string rd, std::string rs, std::string rt) {
      mips::byte_t opcode = r_opcode_map[instruction];
      mips::byte_t funct = 0x0;
      mips::byte_t rd_reg = std::stoi(rd.substr(2));
      mips::byte_t rs_reg = std::stoi(rs.substr(2));
      mips::byte_t rt_reg = std::stoi(rt.substr(2));
      return mips::create_r_instruction(opcode, rs_reg, rt_reg, rd_reg, 0x0, funct);
}

/**
 * @brief Assembles a I-type instruction from the given tokens
 * 
 * @param instruction 
 * @param rt 
 * @param rs 
 * @param immediate 
 * @return mips::instruction_t 
 */
static mips::instruction_t assemble_i_type_instruction(std::string instruction, std::string rt, std::string rs, std::string immediate) {
      mips::byte_t opcode = i_opcode_map[instruction];
      mips::byte_t rt_reg = std::stoi(rt.substr(2));
      mips::byte_t rs_reg = std::stoi(rs.substr(2));
      mips::word_t imm = std::stoi(immediate);
      return mips::create_i_instruction(opcode, rs_reg, rt_reg, imm);
}

/**
 * @brief Assembles a J-type instruction from the given tokens
 * 
 * @param instruction 
 * @param address 
 * @return mips::instruction_t 
 */
static mips::instruction_t assemble_j_type_instruction(std::string instruction, std::string address) {
      mips::byte_t opcode = j_opcode_map[instruction];
      mips::word_t addr = std::stoi(address);
      return mips::create_j_instruction(opcode, addr);
}

/**
 * @brief Appends an instruction to the binary
 * 
 * @details This function appends an instruction to the binary in big endian
 * 
 * @param instruction 
 * @param binary 
 */
static void append_instruction(mips::instruction_t instruction, std::vector<mips::byte_t> &binary) {
      /** Shift the instruction to the right to get the most significant byte */
      binary.push_back(instruction >> 24);
      binary.push_back(instruction >> 16);
      binary.push_back(instruction >> 8);
      binary.push_back(instruction);
}

//////////////////////////////////////////////////////////////////////////////////////////

/** 
 * @brief Load the assembly file into memory
 * 
 * @param[i] filename
 * @throw std::runtime_error If the file is not found
 */
void mips::Assembler::load_file(std::string filename) {
      std::ifstream file(filename);
      if (!file.is_open()) throw std::runtime_error("Could not open file");

      std::string line;
      while (std::getline(file, line)) {
            this->file_contents.push_back(line);
      }
      file.close();
}

/**
 * @brief Makes the first pass of the assembler
 */
void mips::Assembler::first_pass() {
#if DEBUG
      SHOW_FIRST_PASS_BANNER();
#endif // DEBUG

      for (size_t i = 0; i < this->file_contents.size(); i++) {
            std::string line = this->file_contents[i];
            trim(line);
#if DEBUG
            SHOW_CURRENT_LINE();
#endif // DEBUG

            /** Ignore empty lines and comments */
            if (is_empty_line(line)) continue;
            if (is_comment(line)) continue;

            /** Map labels */
            if (is_label(line)) {
                  std::string label = line.substr(0, line.find(":"));
                  this->labels.push_back(Symbol(label, i));
            }
      }
#if DEBUG
      SHOW_LABELS_BANNER();
      SHOW_LABELS();
#endif // DEBUG
}

/** Second pass of the assembler. Assemble the binary. */
void mips::Assembler::second_pass() {
#if DEBUG
      SHOW_SECOND_PASS_BANNER();
#endif // DEBUG

      for (size_t i = 0; i < this->file_contents.size(); i++) {
            std::string line = this->file_contents[i];

            /** Ignore empty lines, comments and labels */
            if (is_empty_line(line) || is_comment(line) || is_label(line)) continue;

            /** Tokenize the line */
            std::vector<std::string> tokens = tokenize(line);
#if DEBUG
            SHOW_TOKENS();
#endif // DEBUG
            if (is_r_type_instruction(tokens[0])) {
                  ASSERT_ARG_COUNT(4, i, tokens[0]);
#if DEBUG
                  SHOW_R_TYPE_INSTRUCTION();
#endif // DEBUG
                  /** Check if the registers are valid */
                  if (!is_valid_register(tokens[1]) || !is_valid_register(tokens[2]) || !is_valid_register(tokens[3])) throw std::runtime_error("Invalid register");

                  /** Assemble the instruction and append it to the binary */
                  instruction_t instruction = assemble_r_type_instruction(tokens[0], tokens[1], tokens[2], tokens[3]);
                  append_instruction(instruction, this->binary);

                  this->text_size += 4;
                  this->line++;
                  continue;
            }
            else if (is_i_type_instruction(tokens[0])) {
                  ASSERT_ARG_COUNT(4, i, tokens[0]);
#if DEBUG
                  SHOW_I_TYPE_INSTRUCTION();
#endif // DEBUG
                  /** Validate the registers and immediate */
                  if (!is_valid_register(tokens[1]) || !is_valid_register(tokens[2])) throw std::runtime_error("Invalid register");
                  if (!is_valid_immediate(tokens[3])) throw std::runtime_error("Invalid immediate");

                  /** Assemble the instruction and append it to the binary */
                  instruction_t instruction = assemble_i_type_instruction(tokens[0], tokens[1], tokens[2], tokens[3]);
                  append_instruction(instruction, this->binary);

                  this->text_size += 4;
                  this->line++;
                  continue;
            }
            else if (is_j_type_instruction(tokens[0])) {
                  ASSERT_ARG_COUNT(2, i, tokens[0]);
#if DEBUG
                  SHOW_J_TYPE_INSTRUCTION();
#endif // DEBUG
                  /** Check if the address is valid */
                  if (!is_valid_address(tokens[1])) throw std::runtime_error("Invalid address");

                  /** Assemble the instruction and append it to the binary */
                  instruction_t instruction = assemble_j_type_instruction(tokens[0], tokens[1]);
                  append_instruction(instruction, this->binary);

                  this->text_size += 4;
                  this->line++;
                  continue;
            }
      }
}

/** Assembles MIPS code into a binary file */
void mips::Assembler::assemble(std::string filename, std::string output) {
      this->load_file(filename);
      this->first_pass();
      this->second_pass();

      /** Use save function from obj.hpp to save */
      mips::save_mips_binary(output, this->binary);
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