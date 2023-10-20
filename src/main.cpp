//
// Created by JoaoAJMatos on 2023-10-19
//

/** C++ Includes */
#include <iostream>

/** MIPS++ Includes */
#include <assembler.hpp>
#include <emulator.hpp>
#include <except.hpp>

#define DEBUG 1
#define VERSION "0.0.1"

//////////////////////////////////////////////////////////////////////////////////////////

void print_help() {
      std::cout << "Usage: mips++ [options] <filename> ..." << std::endl;
      std::cout << "Options:" << std::endl;
      std::cout << "  -h, --help\t\t\tPrints this help message" << std::endl;
      std::cout << "  -c, --compile\t\t\tCompiles the given file" << std::endl;
      std::cout << "  -r, --run\t\t\tRuns the given file" << std::endl;
      std::cout << "  -d, --debug\t\t\tDebugs the given file" << std::endl;
      std::cout << "  -v, --version\t\t\tPrints the version" << std::endl;
      std::cout << std::endl;
      std::cout << "Examples:" << std::endl;
      std::cout << "  Assembling a file:" << std::endl;
      std::cout << "    mips++ -c <filename> <output>" << std::endl << std::endl;
      std::cout << "  Running a MIPS executable:" << std::endl;
      std::cout << "    mips++ -r <filename>" << std::endl << std::endl;
      std::cout << "  Debugging a MIPS executable:" << std::endl;
      std::cout << "    mips++ -d <filename>" << std::endl << std::endl;
      exit(0);
}

//////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief MIPS++ Entry point
 * 
 * @param argc 
 * @param argv 
 * @return int 
 * 
 * @example
 * 
 *    Assembling a file:
 *    ./mips++ <filename> -o <output>
 * 
 *    Running a MIPS executable:
 *    ./mips++ -r <filename>
 * 
 *    Debugging a MIPS executable:
 *    ./mips++ -d <filename>
 */
int main(int argc, char** argv) {
      if (argc < 2) {
            print_help();
      }

      if (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help") {
            print_help();
      }
      else if (std::string(argv[1]) == "-v" || std::string(argv[1]) == "--version") {
            std::cout << "MIPS++ version " << VERSION << std::endl;
            exit(0);
      }
      else if (std::string(argv[1]) == "-r" || std::string(argv[1]) == "--run") {
            if (argc < 3) {
                  std::cout << "Error: No file specified" << std::endl;
                  exit(1);
            }

            try {
                  mips::Emulator emulator;
                  emulator.prepare_and_hold(argv[2]);
                  emulator.run();
            }
            catch(const mips::SyntaxException& e) {
                  std::cout << "Syntax error: " << e.what() << std::endl;
                  return 1;
            }
            catch(const mips::RuntimeException& e) {
                  std::cout << "Runtime error: " << e.what() << std::endl;
                  return 1;
            }
            catch(const std::exception& e) {
                  std::cout << "Error: " << e.what() << std::endl;
                  return 1;
            }
            
            return 0;
      }
      else if (std::string(argv[1]) == "-d" || std::string(argv[1]) == "--debug") {
            if (argc < 3) {
                  std::cout << "Error: No file specified" << std::endl;
                  exit(1);
            }

            try {
                  mips::Emulator emulator;
                  emulator.prepare_and_hold(argv[2]);
                  emulator.cli();
            }
            catch(const mips::SyntaxException& e) {
                  std::cout << "Syntax error: " << e.what() << std::endl;
                  return 1;
            }
            catch(const mips::RuntimeException& e) {
                  std::cout << "Runtime error: " << e.what() << std::endl;
                  return 1;
            }
            catch(const std::exception& e) {
                  std::cout << "Error: " << e.what() << std::endl;
                  return 1;
            }
            
            return 0;
      }
      else if (std::string(argv[1]) == "-c" || std::string(argv[1]) == "--compile") {
            if (argc < 4) {
                  std::cout << "Error: No file specified" << std::endl;
                  exit(1);
            }

            try {
                  mips::Assembler assembler;
                  assembler.assemble(argv[2], argv[3]);
            }
            catch(const mips::SyntaxException& e) {
                  std::cout << "Syntax error: " << e.what() << std::endl;
                  return 1;
            }
            catch(const mips::RuntimeException& e) {
                  std::cout << "Runtime error: " << e.what() << std::endl;
                  return 1;
            }
            catch(const std::exception& e) {
                  std::cout << "Error: " << e.what() << std::endl;
                  return 1;
            }
            
            return 0;
      }
      else {
            std::cout << "Error: Invalid option" << std::endl;
            exit(1);
      }
      
      return 0;
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