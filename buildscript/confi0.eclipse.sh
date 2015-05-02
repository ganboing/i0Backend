#!/bin/sh
current_dir=$(dirname "$0")
llvm_source_dir=$(realpath "$current_dir/llvm.i0")
llvm_eclipse_dir=$(realpath "$current_dir/llvm.i0.eclipse")
cd $llvm_eclipse_dir
cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_ECLIPSE_VERSION=4.2 -DCMAKE_CXX_COMPILER_ARG1=-std=c++11 -DCMAKE_BUILD_TYPE=Debug -DLLVM_TARGETS_TO_BUILD=i0  $llvm_source_dir
