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

## License
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.