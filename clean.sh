#!/bin/bash 


tmp=`find ./ -name *~`
echo "will clean $tmp"
rm $tmp

#rm *~
#rm hz_libc/*~
