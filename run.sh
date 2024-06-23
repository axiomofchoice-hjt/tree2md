if [[ $1 == "test" ]]; then
    cd test && sh ./test.sh
elif [[ $1 == "install" ]]; then
    pip install .
fi
