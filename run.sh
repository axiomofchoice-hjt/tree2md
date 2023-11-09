if [[ $1 == "clean" ]]; then
    rm build -rf
    exit 0
fi

mkdir -p build

if [[ $1 == "test" ]]; then
    cd test && bash ./test.sh
elif [[ $1 == "install" ]]; then
    cmake -B build . && cmake --build build -- tree2md && sudo cp build/tree2md /usr/bin
fi
