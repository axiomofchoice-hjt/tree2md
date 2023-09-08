mkdir build
cd build
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
cmake .. -GNinja &&^
ninja tree2md
xcopy tree2md.exe C:\Apps\Links