#!/bin/sh
llvm_dir=$1
llvm_source_dir=$(realpath "$llvm_dir/llvm.Cpu0")
echo "llvm source from $llvm_source_dir"
mkdir "$llvm_dir/objs/llvm.Cpu0.build"
llvm_build_dir=$(realpath "$llvm_dir/objs/llvm.Cpu0.build")
echo "build to $llvm_build_dir"
mkdir "$llvm_dir/objs/llvm.Cpu0.install"
llvm_install_dir=$(realpath "$llvm_dir/objs/llvm.Cpu0.install")
echo "install to $llvm_install_dir"
cd $llvm_build_dir
cmake -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=$llvm_install_dir $llvm_source_dir
 
