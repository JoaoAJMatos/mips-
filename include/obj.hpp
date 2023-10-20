/**
 * @file    obj.hpp
 * @author  JoaoAJMatos
 *
 * @brief   This header file dictates the MIPS++ executable file format and
 *          defines helper functions for interacting with it.
 *
 * @date    2023-10-19
 * 
 * @copyright Copyright (c) 2023 JoaoAJMatos
 */

#ifndef MIPS_OBJ_HPP
#define MIPS_OBJ_HPP

/** C++ Includes */
#include <string>

/** Local Includes */
#include "common.hpp"
#include "memory.hpp"

namespace mips
{
      constexpr int MIPS_VERSION = 1;
      constexpr int MIPS_HEADER_SIZE_BYTES = 8;

      /** The file header is used to describe the binary file. */
      struct MIPS_file_header {
            byte_t magic[4];        // MIPS
            byte_t endianess;       // 0 = little endian, 1 = big endian
            byte_t version;         // 1
            byte_t shnum;           // Number of sections
            byte_t padding[1];      // Padding
      };

      /** The section header is used to describe the sections of the binary file. */
      struct MIPS_section_header {
            byte_t segment;         // 0 = text, 1 = data
            byte_t padding[3];      // Padding
            word_t offset;          // Offset
            word_t size;            // Size
      };

      /**
       * @brief Loads a MIPS binary file into memory
       * 
       * @param[i] filename 
       * @param[i] memory 
       * @throw std::runtime_error If the file is not found
       * @throw std::runtime_error If the file is not a valid MIPS binary file
       */
      void load_mips_binary(std::string filename, Memory* memory);

      /**
       * @brief Saves a MIPS binary file
       * 
       * @param[i] filename
       * @param[i] binary
       * @throw std::runtime_error If the file fails to open
       */
      void save_mips_binary(std::string filename, std::vector<byte_t> binary);

      /**
       * @brief Dumps the MIPS binary file
       * 
       * @param[i] filename 
       */
      void objdump(std::string filename);
} // namespace mips

#endif // MIPSPP_OBJ_HPP

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