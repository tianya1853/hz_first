#!/bin/bash 

#tmp=`find ./ -name *~`
#find: paths must precede expression: README.md~
#出现这个提示是因为星号被展开为当前目录下所有的文件,想要星号不被展开就需要加上括号或者反斜杠转义，知道了这些我们就知道该怎么find了
tmp=`find ./ -name '*~'`
echo "will clean $tmp"
rm $tmp

#rm *~
#rm hz_libc/*~
