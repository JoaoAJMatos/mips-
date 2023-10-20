//
// Created by JoaoAJMatos on 2023-10-19
//

/** C++ Includes */
#include <fstream>
#include <iostream>

/** Mips Includes */
#include <memory.hpp>

/**
 * @brief Constructor
 */
mips::Memory::Memory() {
      zero_memory();
}

/**
 * @brief Zeroes the memory
 */
void mips::Memory::zero_memory() {
      for (size_t i = 0; i < MAX_MEMORY; i++) {
            memory[i] = 0;
      }
}

/**
 * @brief Checks if the given address is valid
 * 
 * @param[i] address 
 * @return true/false
 */
bool mips::Memory::check_address(address_t address) {
      if (static_cast<size_t>(address) >= MAX_MEMORY || address < 0) {
            return false;
      }
      return true;
}

/**
 * @brief Returns the byte at the given address
 * 
 * @param[i] address
 * @return byte_t
 */
mips::byte_t mips::Memory::read_byte(address_t address) {
      if (!check_address(address)) {
            throw std::runtime_error("Invalid address");
      }
      return memory[address];
}

/**
 * @brief Returns the half word at the given address
 * 
 * @param[i] address
 * @return halfword_t
 */
mips::halfword_t mips::Memory::read_halfword(address_t address) {
      if (!check_address(address) || !check_address(address + 1)) {
            throw std::runtime_error("Invalid address");
      }
      return (memory[address] << 8) | memory[address + 1];
}

/**
 * @brief Returns the word at the given address
 * 
 * @param[i] address
 * @return word_t
 */
mips::word_t mips::Memory::read_word(address_t address) {
      if (!check_address(address) || !check_address(address + 3)) {
            throw std::runtime_error("Invalid address");
      }
      return (memory[address] << 24) | (memory[address + 1] << 16) | (memory[address + 2] << 8) | memory[address + 3];
}

/**
 * @brief Writes a byte at the given address
 * 
 * @param[i] value
 * @param[i] address
 */
void mips::Memory::write_byte(byte_t value, address_t address) {
      if (!check_address(address)) {
            throw std::runtime_error("Invalid address");
      }
      memory[address] = value;
}

/**
 * @brief Writes a half word at the given address
 * 
 * @param[i] value
 * @param[i] address
 */
void mips::Memory::write_halfword(halfword_t value, address_t address) {
      if (!check_address(address) || !check_address(address + 1)) {
            throw std::runtime_error("Invalid address");
      }
      memory[address] = value >> 8;
      memory[address + 1] = value;
}

/**
 * @brief Writes a word at the given address
 * 
 * @param[i] value
 * @param[i] address
 */
void mips::Memory::write_word(word_t value, address_t address) {
      if (!check_address(address) || !check_address(address + 3)) {
            throw std::runtime_error("Invalid address");
      }
      memory[address] = value >> 24;
      memory[address + 1] = value >> 16;
      memory[address + 2] = value >> 8;
      memory[address + 3] = value;
}

void mips::Memory::load_text_section([[maybe_unused]] std::ifstream& file, [[maybe_unused]] word_t offset, [[maybe_unused]] word_t size) {
}

void mips::Memory::load_data_section([[maybe_unused]] std::ifstream& file, [[maybe_unused]] word_t offset, [[maybe_unused]] word_t size) {
}

/**
 * @brief Reads a string from memory starting at the given address
 * 
 * @param[i] address 
 * @return std::string 
 */
std::string mips::Memory::read_string(address_t address) {
      std::string str;
      while (memory[address] != 0) {
            str += memory[address];
            address++;
      }
      return str;
}

/**
 * @brief Dumps the entire memory to a formatted string
 */
void mips::Memory::dump(std::ostream& stream) {
      return dump_offset(stream, 0, 200);
}

/**
 * @brief Dumps the memory to a formatted string on a given range
 * 
 * @param[i] start 
 * @param[i] finish 
 */
void mips::Memory::dump_offset(std::ostream& stream, address_t start, address_t finish) {
      mips::dump_bytes(stream, &memory[start], finish - start);
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