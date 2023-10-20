/**
 * @file    common.hpp
 * @author  JoaoAJMatos
 *
 * @brief   This file contains a set of common definitions used throughout the
 *          MIPS++ project.         
 * 
 * @date    2023-10-19
 * 
 * @copyright Copyright (c) 2023 JoaoAJMatos
 */

#ifndef MIPS_COMMON_HPP
#define MIPS_COMMON_HPP

/** C++ Includes */
#include <cstdint>

namespace mips
{
      /** Type Aliases */
      using byte_t = uint8_t;         // 1 byte
      using halfword_t = uint16_t;    // 2 bytes
      using word_t = uint32_t;        // 4 bytes

      using register_t = word_t;
      using instruction_t = word_t;
      using opcode_t = byte_t;
      using address_t = word_t;

      /** Returns the string representation of a byte */
      std::string to_hex_string(byte_t value);

      /** Dumps the given bytes to the given stream in a formatted manner */
      void dump_bytes(std::ostream& stream, byte_t* bytes, size_t size);
} // namespace mips
      
#endif // MIPS_COMMON_HPP

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