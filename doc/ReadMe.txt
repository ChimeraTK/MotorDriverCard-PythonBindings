Installation
============

Preferred installtion
---------------------

Install the debiab package:

$ sudo apt-get install python-chimeratk-steppermotor

Manual installation
-------------------

You need cmake, the MotorDriverCard library and boost-python. Either install the debian packages
$ sudo apt-get install cmake libmtca4u-motordrivercard-dev libboost-python-dev
or manually install them from the source code.

1. Create a build directory, usually direcly inside the checkout directory.
~/MotorDriverCard_python$ mkdir build && cd build

2. Run CMake. Configure where the library is installed, for instance ${HOME}/ChimeraTK
~/MotorDriverCard_python/build$ cmake .. -DCMAKE_INSTALL_PREFIX=${HOME}/ChimeraTK
If you have installed mtca4u-deviceaccess manually you might have to set the CMAKE_MODULE_PATH.

3. Add lib/python2.7/dist-packages in your installation directory to your python path.
For example in bash:

$ export PYHTONPATH=$PYTONPATH:${HOME}/ChimeraTK/lib/python2.7/dist-packages
