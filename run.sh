mkdir -p build
cd build
cmake .. "-DCMAKE_TOOLCHAIN_FILE=/home/ax/repos/vcpkg/scripts/buildsystems/vcpkg.cmake" && \
    make -j
sudo cp ./tree2md /usr/local/bin
cd ../../study-notes
tree2md