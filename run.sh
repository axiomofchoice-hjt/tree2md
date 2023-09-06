mkdir -p build
cd build
cmake .. && make
sudo cp ./tree2md /usr/bin
cd ../../study-notes
tree2md