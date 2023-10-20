//
// Created by JoaoAJMatos on 2023-10-19
//

/** C++ Includes */
#include <string>
#include <iostream>

/** Mips Includes */
#include <common.hpp>

/**
 * @brief Returns the string representation of the given byte
 * 
 * @param value 
 * @return std::string 
 */
std::string mips::to_hex_string(mips::byte_t value) {
      std::string str = "";
      if (value < 16) {
            str += "0";
      }
      str += std::to_string(value);
      return str;
}

/**
 * @brief Dumps the given bytes to the given stream
 * 
 * @details Formats the bytes in hexadecimal and ASCII, showing 16 bytes per line.
 *          Just like in an hex editor.
 * 
 * @param stream 
 * @param bytes 
 * @param size 
 */
void mips::dump_bytes(std::ostream& stream, byte_t* bytes, size_t size) {
      for (size_t i = 0; i < size; i++) {
            if (i % 16 == 0) {
                  stream << to_hex_string(i) << " | ";
            }
            stream << to_hex_string(bytes[i]) << " ";
            if (i % 16 == 15) {
                  stream << " | ";
                  for (size_t j = i - 15; j <= i; j++) {
                        if (bytes[j] >= 32 && bytes[j] <= 126) {
                              stream << bytes[j];
                        } else {
                              stream << ".";
                        }
                  }
                  stream << std::endl;
            }
            if (i == size - 1) {
                  if (i % 16 != 15) {
                        for (size_t j = 0; j < 15 - (i % 16); j++) {
                              stream << "   ";
                        }
                        stream << " | ";
                        for (size_t j = i - (i % 16); j <= i; j++) {
                              if (bytes[j] >= 32 && bytes[j] <= 126) {
                                    stream << bytes[j];
                              } else {
                                    stream << ".";
                              }
                        }
                        stream << std::endl;
                  }
            }
      }
      stream << std::endl;
}