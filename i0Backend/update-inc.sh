#!/bin/sh
i0_build_dir=$(dirname $0)/../../../../objs/llvm.i0.build/lib/Target/i0
echo "copying tablegen inc from $(realpath $i0_build_dir)"
cp $i0_build_dir/*.inc $(dirname $0)/

