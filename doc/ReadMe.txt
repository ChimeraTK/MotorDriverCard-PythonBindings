How to compile:

You need the MotorDriverCard library, boost-python and the mtca4u python bindings. Either install the debian packages
$ sudo apt-get install dev-mtca4u-motordrivercard python-mtca4upy libboost-python-dev
or manually install them from the source code.

1. Create a build directory, usually direcly inside the checkout directory.
~/MotorDriverCard_python$ mkdir build && cd build

2. Run CMake
~/MotorDriverCard_python/build$ cmake ..
If you have installed mtca4u-deviceaccess manually you might have to set mtca4u-deviceaccess_DIR.

3. Fixme: There is no proper installation or building of a python module yet.
You need the steppermotor.so in the directory where you start python.
