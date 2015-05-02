#!/bin/sh
current_dir=$(dirname "$0")
llvm_source_dir=$(realpath "$current_dir/llvm.i0")
llvm_build_dir=$(realpath "$current_dir/llvm.i0.build")
llvm_install_dir=$(realpath "$current_dir/llvm.i0.install")
cd $llvm_build_dir
cmake -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug -DLLVM_TARGETS_TO_BUILD=i0 -DCMAKE_INSTALL_PREFIX=$llvm_install_dir $llvm_source_dir
 
