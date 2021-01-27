#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

# Download and extract BCM2835 library
echo -e '\033[1;36m***** INSTALLING BCM2835 *****\033[0m'
cd /tmp
echo -e '\033[1;36m - Getting library\033[0m'
wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.68.tar.gz
echo -e '\033[1;36m - Extracting library\033[0m'
tar zxvf bcm2835-1.68.tar.gz
cd bcm2835-1.68
echo -e '\033[1;36m - Configuring library\033[0m'
./configure
echo -e '\033[1;36m - Building library\033[0m'
make
echo -e '\033[1;36m - Verifying library\033[0m'
sudo make check
echo -e '\033[1;36m - Installing library\033[0m'
sudo make install


# Download and extract RPIDMX512 library
echo -e '\033[1;36m***** INSTALLING RPIDMX512 *****\033[0m'
cd /tmp
echo -e '\033[1;36m - Getting library\033[0m'
git clone https://github.com/vanvught/rpidmx512.git
cd rpidmx512/lib-pca9685/
echo -e '\033[1;36m - Building library\033[0m'
make -f Makefile.Linux "DEF=-DRASPPI"
echo -e '\033[1;36m - Installing library\033[0m'
sudo mv include/* /usr/local/include
sudo mv lib_linux/libpca9685.a /usr/local/lib/


# Download and extract RPI_WS281X library
echo -e '\033[1;36m***** INSTALLING RPI_WS281X *****\033[0m'
cd /tmp
echo -e '\033[1;36m - Getting library\033[0m'
git clone https://github.com/jgarff/rpi_ws281x.git
cd rpi_ws281x
mkdir build
cd build
echo -e '\033[1;36m - Configuring library\033[0m'
cmake -D BUILD_SHARED=OFF -D BUILD_TEST=OFF ..
echo -e '\033[1;36m - Building library\033[0m'
cmake --build .
echo -e '\033[1;36m - Installing library\033[0m'
sudo make install


# Download and extract WiringPi library
echo -e '\033[1;36m***** INSTALLING WIRINGPI *****\033[0m'
cd /tmp
echo -e '\033[1;36m - Getting library\033[0m'
wget https://project-downloads.drogon.net/wiringpi-latest.deb
echo -e '\033[1;36m - Installing library\033[0m'
sudo dpkg -i wiringpi-latest.deb
    # Uninstall with `sudo dkpg -r wiringpi`


# Install 2501lib
echo -e '\033[1;36m***** INSTALLING 2501LIB *****\033[0m'
cd $DIR/src
echo -e '\033[1;36m - Building library\033[0m'
make
echo -e '\033[1;36m - Installing library\033[0m'
sudo make install