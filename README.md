# camrem
[![Build Status](https://travis-ci.org/Silberschleier/camrem.svg?branch=master)](https://travis-ci.org/Silberschleier/camrem)
## Requirements
* CMake (>= 2.8.4)
* libboost (>= 1.54)
* libmicrohttpd (>= 0.9)

## Build
### Debian Jessie / Ubuntu Trusty
*  **Clone repository:** ```git clone https://github.com/Silberschleier/camrem.git```
*  **Clone submodules:** ```cd camrem``` and ```git submodule init``` and ```git submodule update```
*  **Install required dependencies:**```apt-get install cmake libmicrohttpd-dev libgphoto2-dev g++ libboost-test-dev libboost-log-dev```
*  **Generate Makefiles:** ```cmake .```
*  **Build:** ```make```
