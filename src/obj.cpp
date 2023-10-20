//
// Created by JoaoAJMatos on 2023-10-19
//

/** C++ Includes */
#include <fstream>

/** Mips Includes */
#include <obj.hpp>

//////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Checks if the given header is a valid MIPS header
 * 
 * @param[i] header
 * @return true/false
 */
static bool is_mips_header(mips::MIPS_file_header header) {
      /** Check the magic */
      if (header.magic[0] != 'M' || header.magic[1] != 'I' || header.magic[2] != 'P' || header.magic[3] != 'S') {
            return false;
      }

      /** Check the version */
      if (header.version != mips::MIPS_VERSION) {
            return false;
      }

      return true;
}

//////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Loads a MIPS binary file into memory
 * 
 * @param[i] filename 
 * @param[o] memory 
 * @throw std::runtime_error If the file is not found
 * @throw std::runtime_error If the file is not a valid MIPS binary file
 */
void mips::load_mips_binary(std::string filename, mips::Memory* memory) {
      std::ifstream file(filename, std::ios::binary);
      if (!file.is_open()) throw std::runtime_error("Failed to open file");

      /** Check the file headers */
      MIPS_file_header header;
      file.read((char*)&header, MIPS_HEADER_SIZE_BYTES);
      if (!is_mips_header(header)) throw std::runtime_error("Invalid MIPS header");

      for (int i = 0; i < header.shnum; i++) {
            MIPS_section_header section_header;
            file.read((char*)&section_header, sizeof(MIPS_section_header));

            if (section_header.segment == 0) {
                  memory->load_text_section(file, section_header.offset, section_header.size);
            } else if (section_header.segment == 1) {
                  memory->load_data_section(file, section_header.offset, section_header.size);
            }
      }
}

/**
 * @brief Save the MIPS bytecode to a file
 * 
 * @param[i] filename 
 * @param[i] binary 
 * @throw std::runtime_error If the file fails to open
 */
void mips::save_mips_binary(std::string filename, std::vector<byte_t> binary) {
      std::ofstream file(filename, std::ios::binary);
      if (!file.is_open()) throw std::runtime_error("Failed to open file");

      /** Write the header */
      MIPS_file_header header;
      header.magic[0] = 'M';
      header.magic[1] = 'I';
      header.magic[2] = 'P';
      header.magic[3] = 'S';
      header.endianess = 0;
      header.version = MIPS_VERSION;
      header.shnum = 1;
      header.padding[0] = 0;
      file.write((char*)&header, MIPS_HEADER_SIZE_BYTES);

      /** Write the text section */
      MIPS_section_header text_section;
      text_section.segment = 0;
      text_section.padding[0] = 0;
      text_section.padding[1] = 0;
      text_section.padding[2] = 0;
      text_section.offset = 0;
      text_section.size = binary.size();
      file.write((char*)&text_section, sizeof(MIPS_section_header));

      /** Write the binary */
      for (size_t i = 0; i < binary.size(); i++) {
            file.write((char*)&binary[i], sizeof(byte_t));
      }

      file.close();
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