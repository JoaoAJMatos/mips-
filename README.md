# MIPS++

MIPS++ is a cross-platform assembler, emulator and debugger for the MIPS assembly language.

## Motivation

In my academic institution, we are taught MIPS assembly language in one of our courses. The course is mainly taught using a Windows environment and some of the tools used are not available on other platforms.

For that reason, I took the opportunity to learn about MIPS and implement my own cross-platform assembler and emulator; making it open source so that other students can contribute and learn from it.

## Features

- Assembler
- Emulator
- Debugger (GDB-like)

## Installing

You can download one of the precompiled binaries from the [releases]() page.

## Building from source

Alternatively, you can compile the project yourself using CMake.

```bash
git clone https://www.github.com/JoaoAJMatos/MIPS
cd MIPS
cmake -S . -B build
cd build
make
```

## Usage

### Assembler

```bash
mips -c <input> <output>
```

### Emulator

```bash
mips -r <assembled_binary>
```

### Debugger

```bash
mips -d <assembled_binary>
```
