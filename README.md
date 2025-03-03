# Satellite Command Scheduler

Contains a C++ library for parsing JSON command structures with C interoperability. This is exported a shared library which can be mofidified in the build and is portable.

The scheduler is not complete yet.

## Overview

This library provides functionality to parse JSON command structures into C++ objects and C-compatible structures. It's designed to be used in both C++ applications and from other languages like Python through a C-compatible interface.

## Features

- Parse JSON command structures into C++ objects
- C-compatible interface for interoperability with other languages
- Error handling with descriptive error codes
- Memory management utilities for C-compatible structures
- Cross-platform compatibility (Windows, Linux, macOS)

## Requirements

- C++11 or later
- RapidJSON library
- CMake 3.10 or later (for building)

## Building the Library

```bash
mkdir build
cd build
cmake ..
cmake --build .
```
Additionally, the zip file in /package needs to be extracted in the src directory for it to compile.