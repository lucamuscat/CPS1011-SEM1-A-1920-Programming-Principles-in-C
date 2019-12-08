echo off
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug --build -Bbuild -H.
cd build
make -s
cd ..
