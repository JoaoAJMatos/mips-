/**
 * @file    except.hpp
 * @author  JoaoAJMatos
 *
 * @brief   This file contains the MIPS++ exceptions.         
 * 
 * @date    2023-10-19
 * 
 * @copyright Copyright (c) 2023 JoaoAJMatos
 */

#ifndef MIPS_EXCEPT_HPP
#define MIPS_EXCEPT_HPP

/** C++ Includes */
#include <exception>
#include <string>

namespace mips
{
      /**
       * @brief MIPS++ exception class
       *
       * @details This class is used to throw MIPS++ exceptions.
       */
      class Exception : public std::exception
      {
      public:
            Exception(std::string message) : message(message) {}

            virtual const char* what() const throw() {
                  return message.c_str();
            }
      private:
            std::string message;
      };

      /**
       * @brief MIPS++ runtime exception class
       *
       * @details This class is used to throw MIPS++ runtime exceptions.
       */
      class RuntimeException : public Exception
      {
      public:
            RuntimeException(std::string message) : Exception(message) {}
      };

      /**
       * @brief MIPS++ syntax exception class
       *
       * @details This class is used to throw MIPS++ syntax exceptions.
       */
      class SyntaxException : public Exception
      {
      public:
            SyntaxException(std::string message) : Exception(message) {}
      };

      /**
       * @brief MIPS++ file exception class
       *
       * @details This class is used to throw MIPS++ file exceptions.
       */
      class FileException : public Exception
      {
      public:
            FileException(std::string message) : Exception(message) {}
      };
} // namespace mips
      
#endif // MIPS_EXCEPT_HPP

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