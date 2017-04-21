#!/bin/bash



rm -r sqlite-snapshot-201703241759
sleep 1
tar -xvf sqlite-snapshot-201703241759.tar.gz
sleep 1
cd sqlite-snapshot-201703241759

./configure
sleep 1
make
