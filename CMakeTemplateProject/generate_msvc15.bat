mkdir build_x86
cd build_x86
mkdir Debug
mkdir Release
cmake ..\ -G "Visual Studio 15 2017"
cd ..
mkdir build_x64
cd build_x64
mkdir Debug
mkdir Release
cmake ..\ -G "Visual Studio 15 2017 Win64"
cd %~dp0



copy "include\SDL2-2.0.9\lib\x64\SDL2.dll" "build_x64\Debug\SDL2.dll"
copy "include\SDL2-2.0.9\lib\x64\SDL2.dll" "build_x64\Release\SDL2.dll"
copy "include\SDL2-2.0.9\lib\x86\SDL2.dll" "build_x86\Debug\SDL2.dll"
copy "include\SDL2-2.0.9\lib\x86\SDL2.dll" "build_x86\Release\SDL2.dll"

pause