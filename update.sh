#!/bin/bash

echo -e '\033[1;36m***** RE-INSTALLING 2501LIB *****\033[0m'
echo -e '\033[1;36m - Uninstalling library\033[0m'
sudo rm /usr/local/include/2501 -rf
sudo rm /usr/local/lib/lib2501.a
cd src
make clean
echo -e '\033[1;36m - Building library\033[0m'
make
echo -e '\033[1;36m - Installing library\033[0m'
sudo make install
