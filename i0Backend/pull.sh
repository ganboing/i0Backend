#!/bin/sh
i0_dir=$(dirname $0)
rsync -a $i0_dir/../../../../../i0/i0Backend/ $i0dir/
