#!/bin/sh
i0_dir=$(dirname $0)/../../../../../i0/i0Backend
diff -r $i0_dir/ $(dirname $0)/
