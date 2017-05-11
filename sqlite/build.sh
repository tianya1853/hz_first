#!/bin/bash



rm -r sqlite-snapshot-201703241759
sleep 1
tar -xvf sqlite-snapshot-201703241759.tar.gz
sleep 1
cd sqlite-snapshot-201703241759

./configure
sleep 1
make


echo "***************************"
if [ -d ".libs" ];then	
	echo "build complete,delete file others but .libs path "
	# rm * 不会删除隐藏文件
	rm *	
else
	echo "ERROR:no generate .libs path"
fi


