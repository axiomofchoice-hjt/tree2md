# tree2md

将项目里的 markdown 文件以树的形式嵌入 README.md 里，并提供链接

## 快速开始

```sh
pip install .
```

在项目根目录新建 `README.md`，执行 `tree2md`

`<!-- tree2md -->` 标记了嵌入位置，若没有则在末尾嵌入

## 效果

<!-- tree2md -->

- [README.md](README.md)
- test
  - [README.md](test/README.md)
  - [STANDARD.md](test/STANDARD.md)
  - test_dir0
    - [test_file0.md](test/test_dir0/test_file0.md)
  - test_dir1
    - [test_file1.md](test/test_dir1/test_file1.md)
