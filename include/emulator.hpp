/**
 * @file    emulator.hpp
 * @author  JoaoAJMatos
 *
 * @brief   This header file contains the MIPS++ emulator.
 *          The emulator orchestrates the interaction between the CPU and the
 *          memory. It's like an abstraction of a virtual computer.
 *
 * @date    2023-10-19
 * 
 * @copyright Copyright (c) 2023 JoaoAJMatos
 */

#ifndef MIPS_EMULATOR_HPP
#define MIPS_EMULATOR_HPP

/** Local Includes */
#include "common.hpp"
#include "cpu.hpp"
#include "memory.hpp"

namespace mips
{
      class Emulator
      {
      public:
            Emulator();
            ~Emulator();

            /**
             * @brief Runs the emulator
             *
             * @throw std::runtime_error If the program fails to run
             */
            void run();

            /**
             * @brief Loads the binary file and holds the emulator
             *
             * @details This function loads the binary file and holds the emulator,
             *          used for initializing the emulator in debug mode.
             *
             * @param[i] filename The filename
             * @throw std::runtime_error If the program fails to load
             */
            void prepare_and_hold(std::string filename);

            /**
             * @brief Steps the emulator
             *
             * @details Used for stepping through the emulator in debug mode.
             */
            void step();

            /**
             * @brief Gets the state of the emulator
             *
             * @details This function returns the string representation of the
             *          emulator state (CPU + [Memory]).
             *
             * @param[i] show_memory Whether to add the memory dump to the state
             * @return The state of the emulator
             */
            std::string state(bool show_memory = false);

            /**
             * @brief Laucnhes the CLI for the debuger (GDB style)
             * 
             * @details The user can interact with the emulator through the CLI
             *          when running in debug mode. This function is called when
             *          the emulator is ready to be debugged (after loading the
             *          binary file) after calling prepare_and_hold().
             * 
             *          Check the documentation for the list of available debug
             *          commands.
             */
            void cli();

      private:
            CPU *cpu;
            Memory *memory;
      };
} // namespace mips

#endif // MIPS_EMULATOR_HPP

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