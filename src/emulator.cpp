//
// Created by JoaoAJMatos on 2023-10-19
//

/** C++ Includes */
#include <iostream>
#include <sstream>

/** Mips Includes */
#include <emulator.hpp>

/** 
 * @brief Constructor 
 */
mips::Emulator::Emulator() {
      this->memory = new Memory();
      this->cpu = new CPU(this->memory);
}

/** 
 * @brief Destructor 
 */
mips::Emulator::~Emulator() {
      delete this->cpu;
      delete this->memory;
}

/** 
 * @brief Runs the emulator 
 * 
 * @details This function runs the emulator
 * 
 * @param[i] filename 
 */
void mips::Emulator::run() {
      while (true) {
            try {
                  this->step();
            }
            catch(const std::exception& e) {
                  std::cerr << e.what() << '\n';
                  break;
            }
            
      }
}

/**
 * @brief Prepare program and hold
 * 
 * @details Loads the program into memory, resets the CPU and holds the emulator.
 * 
 * @param[i] filename 
 */
void mips::Emulator::prepare_and_hold([[maybe_unused]] std::string filename) {
      //this->memory->load_program(filename);
      this->cpu->reset();
}

/**
 * @brief Steps through a CPU cycle
 */
void mips::Emulator::step() {
      try {
            this->cpu->step();
      }
      catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
      }
      
}

/**
 * @brief Returns the string representation of the emulator state
 * 
 * @param[i] show_memory
 * @return std::string 
 */
std::string mips::Emulator::state(bool show_memory) {
      std::string state = this->cpu->state();
      std::stringstream ss;

      if (show_memory) {
            state += "\n\nMemory:\n";
            memory->dump(ss);
      }
      return state;
}

void mips::Emulator::cli() {

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