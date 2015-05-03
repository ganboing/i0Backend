#!/bin/sh
llvm_dir=$1
mkdir "$llvm_dir/llvm.Cpu0"
llvm_source_dir=$(realpath "$llvm_dir/llvm.Cpu0")
echo "llvm source from $llvm_source_dir"
mkdir "$llvm_dir/llvm.Cpu0.eclipse"
llvm_eclipse_dir=$(realpath "$llvm_dir/llvm.Cpu0.eclipse")
echo "llvm eclips project dir $llvm_eclipse_dir"
cd $llvm_eclipse_dir
cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_ECLIPSE_VERSION=4.2 -DCMAKE_CXX_COMPILER_ARG1=-std=c++11 -DCMAKE_BUILD_TYPE=Debug $llvm_source_dir
