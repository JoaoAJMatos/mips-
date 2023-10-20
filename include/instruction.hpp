/**
 * @file    instructions.hpp
 * @author  JoaoAJMatos
 *
 * @brief   This header file contains macros and functions
 *          for dealing with MIPS instructions.
 *
 * @date    2023-10-19
 * 
 * @copyright Copyright (c) 2023 JoaoAJMatos
 */

#ifndef MIPS_INSTRUCTIONS_HPP
#define MIPS_INSTRUCTIONS_HPP

/** Local Includes */
#include "common.hpp"

namespace mips
{
      /** Instruction types */
      enum InstructionType { R, I, J };

      /** R-Type Indicator */
      constexpr opcode_t R_TYPE = 0x00;

      /** Instruction masks */
      /**
       * These are useful for extracting the fields from an instruction
       * and stand out in the code.
       */
      constexpr word_t OPCODE_MASK = 0xFC000000;
      constexpr word_t RS_MASK = 0x03E00000;
      constexpr word_t RT_MASK = 0x001F0000;
      constexpr word_t RD_MASK = 0x0000F800;
      constexpr word_t SHAMT_MASK = 0x000007C0;
      constexpr word_t FUNCT_MASK = 0x0000003F;
      constexpr word_t IMMEDIATE_MASK = 0x0000FFFF;
      constexpr word_t ADDRESS_MASK = 0x03FFFFFF;

      /** Instruction shifts */
      constexpr word_t OPCODE_SHIFT = 26;
      constexpr word_t RS_SHIFT = 21;
      constexpr word_t RT_SHIFT = 16;
      constexpr word_t RD_SHIFT = 11;
      constexpr word_t SHAMT_SHIFT = 6;
      constexpr word_t FUNCT_SHIFT = 0;
      constexpr word_t IMMEDIATE_SHIFT = 0;
      constexpr word_t ADDRESS_SHIFT = 0;

      /** Syscall id */
      constexpr word_t SYSCALL = 0x0C;

      /**
       * @brief Get the opcode of an instruction
       * 
       * @param[i] instruction 
       * @return opcode_t 
       */
      inline opcode_t get_opcode(instruction_t instruction) {
            return static_cast<opcode_t>((instruction & OPCODE_MASK) >> OPCODE_SHIFT);
      }

      /**
       * @brief Get the instruction type of an opcode
       * 
       * @param[i] opcode 
       * @return InstructionType 
       */
      /*InstructionType get_instruction_type(opcode_t opcode) {
            switch (opcode) {
                  case 0x00: return InstructionType::R;
                  case 0x02: return InstructionType::J;
                  case 0x03: return InstructionType::J;
                  default: return InstructionType::I;
            }
      }*/

      /**
       * @brief Get the rs field of an instruction
       * 
       * @param[i] instruction 
       * @return byte_t 
       */
      inline byte_t get_rs(instruction_t instruction) {
            return (instruction & RS_MASK) >> RS_SHIFT;
      }

      /**
       * @brief Get the rt field of an instruction
       * 
       * @param[i] instruction 
       * @return byte_t 
       */
      inline byte_t get_rt(instruction_t instruction) {
            return (instruction & RT_MASK) >> RT_SHIFT;
      }

      /**
       * @brief Get the rd field of an instruction
       * 
       * @param[i] instruction 
       * @return byte_t 
       */
      inline byte_t get_rd(instruction_t instruction) {
            return (instruction & RD_MASK) >> RD_SHIFT;
      }

      /**
       * @brief Get the shamt field of an instruction
       * 
       * @param[i] instruction 
       * @return byte_t 
       */
      inline byte_t get_shamt(instruction_t instruction) {
            return (instruction & SHAMT_MASK) >> SHAMT_SHIFT;
      }

      /**
       * @brief Get the funct field of an instruction
       * 
       * @param[i] instruction 
       * @return byte_t
       */
      inline byte_t get_funct(instruction_t instruction) {
            return (instruction & FUNCT_MASK) >> FUNCT_SHIFT;
      }

      /**
       * @brief Get the immediate field of an instruction
       * 
       * @param[i] instruction 
       * @return halfword_t 
       */
      inline halfword_t get_immediate(instruction_t instruction) {
            return static_cast<halfword_t>((instruction & IMMEDIATE_MASK) >> IMMEDIATE_SHIFT);
      }

      /**
       * @brief Get the address field of an instruction
       * 
       * @param[i] instruction 
       * @return word_t 
       */
      inline word_t get_address(instruction_t instruction) {
            return (instruction & ADDRESS_MASK) >> ADDRESS_SHIFT;
      }

      /**
       * @brief Create a r instruction
       * 
       * @param[i] opcode
       * @param[i] rs
       * @param[i] rt
       * @param[i] rd
       * @param[i] shamt
       * @param[i] funct
       * @return instruction_t 
       */
      inline instruction_t create_r_instruction(opcode_t opcode, byte_t rs, byte_t rt, byte_t rd, byte_t shamt, byte_t funct) {
            return (opcode << OPCODE_SHIFT) | (rs << RS_SHIFT) | (rt << RT_SHIFT) | (rd << RD_SHIFT) | (shamt << SHAMT_SHIFT) | (funct << FUNCT_SHIFT);
      }

      /**
       * @brief Create a i instruction
       * 
       * @param[i] opcode
       * @param[i] rs
       * @param[i] rt
       * @param[i] immediate
       * @return instruction_t 
       */
      inline instruction_t create_i_instruction(opcode_t opcode, byte_t rs, byte_t rt, word_t immediate) {
            return (opcode << OPCODE_SHIFT) | (rs << RS_SHIFT) | (rt << RT_SHIFT) | (immediate << IMMEDIATE_SHIFT);
      }

      /**
       * @brief Create a j instruction
       * 
       * @param[i] opcode
       * @param[i] address
       * @return instruction_t 
       */
      inline instruction_t create_j_instruction(opcode_t opcode, word_t address) {
            return (opcode << OPCODE_SHIFT) | (address << ADDRESS_SHIFT);
      }
} // namespace mips

#endif // MIPS_INSTRUCTIONS_HPP

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