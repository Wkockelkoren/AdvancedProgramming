mkdir build_x86
cd build_x86
cmake ..\ -G "Visual Studio 15 2017"
cd ..
mkdir build_x64
cd build_x64
cmake ..\ -G "Visual Studio 15 2017 Win64"
cd %~dp0
