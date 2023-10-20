//
// Created by JoaoAJMatos on 2023-10-19
//

/** C++ Includes */
//#include <map>

/** R-type instruction opcodes binary mappping */
/*static std::map<std::string, std::string> r_type_instructions = {
      {"add", "100000"}, {"addu", "100001"}, {"and", "100100"}, {"break", "001101"},
      {"div", "011010"}, {"divu", "011011"}, {"jalr", "001001"}, {"jr", "001000"},
      {"mfhi", "010000"}, {"mflo", "010010"}, {"mthi", "010001"}, {"mtlo", "010011"},
      {"mult", "011000"}, {"multu", "011001"}, {"nor", "100111"}, {"or", "100101"},
      {"sll", "000000"}, {"sllv", "000100"}, {"slt", "101010"}, {"sltu", "101011"},
      {"sra", "000011"}, {"srav", "000111"}, {"srl", "000010"}, {"srlv", "000110"},
      {"sub", "100010"}, {"subu", "100011"}, {"syscall", "001100"}, {"xor", "100110"}
};*/

/** I-type instruction opcodes binary mappping */
/*std::map<std::string, std::string> i_type_instructions = {
      {"addi", "001000"}, {"addiu", "001001"}, {"andi", "001100"}, {"beq", "000100"},
      {"bgez", "000001"}, {"bgezal", "000001"}, {"bgtz", "000111"}, {"blez", "000110"},
      {"bltz", "000001"}, {"bltzal", "000001"}, {"bne", "000101"}, {"lb", "100000"},
      {"lbu", "100100"}, {"lh", "100001"}, {"lhu", "100101"}, {"lui", "001111"},
      {"lw", "100011"}, {"lwc1", "110001"}, {"ori", "001101"}, {"sb", "101000"},
      {"sh", "101001"}, {"slti", "001010"}, {"sltiu", "001011"}, {"sw", "101011"},
      {"swc1", "111001"}, {"xori", "001110"}
};*/

/** J-type instruction opcodes binary mappping */
/*std::map<std::string, std::string> j_type_instructions = {
      {"j", "000010"},
      {"jal", "000011"}
};*/

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