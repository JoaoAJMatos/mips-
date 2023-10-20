/**
 * @file    assembler.hpp
 * @author  JoaoAJMatos
 *
 * @brief   This header file contains the MIPS++ assembler.
 *          The assembler is used to assemble MIPS assembly code into MIPS
 *          binary code, capable of being executed by the MIPS++ emulator.
 *
 * @date    2023-10-19
 * 
 * @copyright Copyright (c) 2023 JoaoAJMatos
 */

#ifndef MIPS_ASSEMBLER_HPP
#define MIPS_ASSEMBLER_HPP

/** C++ Includes */
#include <string>
#include <vector>

/** Local Includes */
#include "common.hpp"

namespace mips
{
      /** This structure maps symbols to addresses */
      struct Symbol {
            std::string name;       /** The symbol name */
            address_t address;      /** The address */

            Symbol(std::string name, address_t address) : name(name), address(address) {}
      };

      class Assembler
      {
      public:
            Assembler() {}
            ~Assembler() {}

            /**
             * @brief Assembles a file
             *
             * @param[i] filename The filename
             * @param[i] output The output filename
             * @throw std::runtime_error If the file is not found
             * @throw std::runtime_error If the file contains syntax errors
             */
            void assemble(std::string filename, std::string output);
      
      private:
            /**
             * @brief Loads the file into memory
             *
             * @param[i] filename The filename
             * @throw std::runtime_error If the file is not found
             */
            void load_file(std::string filename);

            /**
             * @brief First pass
             *
             * @details This function parses the file and stores the labels.
             *          It also checks for syntax errors.
             * 
             * @throw std::runtime_error If the file contains syntax errors
             */
            void first_pass();

            /**
             * @brief Second pass
             *
             * @details This function parses the file and assembles the binary.
             * 
             * @throw std::runtime_error If the file contains syntax errors
             */
            void second_pass();

            /** Member Variables */
            std::vector<std::string> file_contents;  /** The file contents (assembly code) */
            std::vector<Symbol> labels;              /** The labels */
            std::vector<byte_t> binary;              /** The generated binary (executable bytecode) */
            int line = 0;                            /** The current line */
            word_t text_size = 0;                    /** The size of the text segment */
            [[maybe_unused]] word_t data_size = 0;   /** The size of the data segment */
      };
} // namespace mipspp

#endif // MIPSPP_ASSEMBLER_HPP

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