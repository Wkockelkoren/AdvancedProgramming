cd ext
git init
git submodule add https://github.com/wjakob/nanogui.git nanogui
git submodule update --init --recursive
cd nanogui

mkdir build_x86
cd build_x86
cmake ..\ -G "Visual Studio 15 2017"
cmake --build . --target nanogui --config Release
cd ..
mkdir build_x64
cd build_x64
cmake ..\ -G "Visual Studio 15 2017 Win64"
cmake --build . --target nanogui --config Release
cd %~dp0

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

copy "ext\SDL2-2.0.9\lib\x64\SDL2.dll" "build_x64\Debug\SDL2.dll"
copy "ext\SDL2-2.0.9\lib\x64\SDL2.dll" "build_x64\Release\SDL2.dll"
copy "ext\SDL2-2.0.9\lib\x86\SDL2.dll" "build_x86\Debug\SDL2.dll"
copy "ext\SDL2-2.0.9\lib\x86\SDL2.dll" "build_x86\Release\SDL2.dll"

copy "ext\nanogui\build_x64\Release\nanogui.dll" "build_x64\Debug\nanogui.dll"
copy "ext\nanogui\build_x64\Release\nanogui.dll" "build_x64\Release\nanogui.dll"
copy "ext\nanogui\build_x86\Release\nanogui.dll" "build_x86\Debug\nanogui.dll"
copy "ext\nanogui\build_x86\Release\nanogui.dll" "build_x86\Release\nanogui.dll"

pause