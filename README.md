# tree2md

将项目里的 markdown 文件以树的形式嵌入 README.md 里，并提供链接

## 快速开始

```sh
mkdir -p build
cd build
cmake .. && make
sudo cp ./tree2md /usr/bin
```

在项目根目录执行 `tree2md`

`<!-- tree2md -->` 标记了嵌入位置，若没有则在末尾嵌入
