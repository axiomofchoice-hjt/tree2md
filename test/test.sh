echo "# test
" > README.md
tree2md
diff STANDARD.md README.md > /dev/null
if [[ $? != 0 ]]; then
    echo test 0 failed
    cat README.md
    exit
fi

echo "# test

<!-- tree2md -->" > README.md
tree2md
diff STANDARD.md README.md > /dev/null
if [[ $? != 0 ]]; then
    echo test 1 failed
    cat README.md
    exit
fi

echo "# test

<!-- tree2md -->

- [A.md](./A.md)
  - [B.md](./B.md)
    - [C.md](./C.md)" > README.md
tree2md
diff STANDARD.md README.md > /dev/null
if [[ $? != 0 ]]; then
    echo test 2 failed
    cat README.md
    exit
fi
