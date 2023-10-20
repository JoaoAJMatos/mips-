/**
 * @file    memory.hpp
 * @author  JoaoAJMatos
 *
 * @brief   This header file contains the MIPS++ memory abstraction.
 *          The memory is used to store the MIPS++ program and data.
 *          It's like an abstraction of the RAM.
 * 
 *          The Memory class offers an interface for interacting with the
 *          virtual memory.
 *          
 *          Memory map:
 * 
 *           +------------------------+ <- 0x00000000
 *           |       Text Segment     |
 *           +------------------------+ <- 0x00400000
 *           |                        | 
 *           |      Program Code      | (The text segment is where the program code is stored)
 *           |                        |
 *           +------------------------+
 *           |       Data Segment     |
 *           +------------------------+ <- 0x10010000
 *           |                        |
 *           |    Initialized Data    | (The data segment is where the initialized data is stored (global, static))
 *           |                        |
 *           +------------------------+
 *           |  Heap (Dynamic Data)   | (The heap is where the dynamic data is stored (malloc, new))
 *           +------------------------+
 *           |       Stack Segment    |
 *           +------------------------+ <- 0x7FFFFFFFC
 *           |                        |
 *           |   Stack (Grows Down)   | (The stack is where the stack is stored (local variables, function calls))
 *           |                        |
 *           +-------------------------+
 *
 * @date    2023-10-19
 * 
 * @copyright Copyright (c) 2023 JoaoAJMatos
 */

#ifndef MIPS_MEMORY_HPP
#define MIPS_MEMORY_HPP

/** C++ Includes */
#include <iostream>
#include <vector>

/** Local Includes */
#include "common.hpp"

namespace mips
{
      /** Some memory offsets */
      /** 0x0 to 0x3FFFFFFF are reserved */
      constexpr long MAX_MEMORY  = 0x100000000;    // 4GB
      constexpr int TEXT_OFFSET  = 0x00400000;     // Start of the text segment
      constexpr int DATA_OFFSET  = 0x10000000;     // Start of the data segment (data segment grows up)
      constexpr int STACK_OFFSET = 0x7FFFFFFF;     // End of the stack segment (stack grows down)

      class Memory
      {
      public:
            Memory();
            ~Memory() {}

            /** Read functions */
            byte_t read_byte(address_t address);
            halfword_t read_halfword(address_t address);
            word_t read_word(address_t address);

            /** Write functions */
            void write_byte(byte_t value, address_t address);
            void write_halfword(halfword_t value, address_t address);
            void write_word(word_t value, address_t address);

            /** Load functions */
            void load_text_section(std::ifstream& file, word_t offset, word_t size);
            void load_data_section(std::ifstream& file, word_t offset, word_t size);

            /** Read string */
            std::string read_string(address_t address);

            /**
             * @brief Dumps the memory
             * @details This function dumps the memory to a string.
             *
             * @param[i] The stream to dump to
             */
            void dump(std::ostream& stream);

            /**
             * @brief Dumps the memory on a given range
             * @details This function dumps the memory to a string on a given
             *
             * @param[i] The stream to dump to
             * @param[i] start The start address
             * @param[i] finish The finish address
             */
            void dump_offset(std::ostream& stream, address_t start, address_t finish);

      private:
            /**
             * @brief Checks if the address is valid
             *
             * @param[i] address The address to check
             * @return true/false
             */
            bool check_address(address_t address);

            /** @brief Zeroes the memory */
            void zero_memory();
            
            /** Memory array */
            std::vector<byte_t> memory = std::vector<byte_t>(MAX_MEMORY);
      };
} // namespace mipspp

#endif // MIPSPP_MEMORY_HPP

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