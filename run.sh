mkdir -p build
cd build
cmake .. "-DCMAKE_TOOLCHAIN_FILE=/home/ax/repos/vcpkg/scripts/buildsystems/vcpkg.cmake" && \
    make -j
cd ../../study-notes
../tree2md/build/tree2md