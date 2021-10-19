# TemplateCopy

[English](../README.md)

## 介绍

这是一个模板复制程序，即将目录下的文件复制到另一个目录下，并将后缀名为`.tem`的文本文件中的`${变量}`替换为自定义的值，并去除其`.tem`后缀。

如有一个`1.txt.tem`文件，并且我自定义了`You`的变量，其值为"lomekragow"：

```text
Hello ${You}
```

TemplateCopy会在自己的`variable.txt`文件中查找名为`You`的字符串变量并替换它。当拷贝到目标目录时，该文件后缀为`1.txt`，并且看起来如下

```text
Hello lomekragow
```

灵感来源自CMake。

## Usage

### 帮助

```text
TC help
```

该命令会列出TC的所有可用指令及用法。

### 复制目录

```text
TC 源目录:目标目录
```

将TC可执行文件目录下的源目录复制到当前工作目录的目标目录中(如果没有则自动创建)。


### 列出可复制目录


```text
TC list
```

将TC可进行复制的源目录列举出来


### 设置变量

```text
TC 变量名=字符串
```
该变量将存储于可执行程序所在目录的`variable.txt`文件中，这意味着你也可以自己修改`variable.txt`文件(更推荐前者)。

## 构建

该程序使用[CMake](https://cmake.org/)进行构建，你也可以使用其他工具或IDE进行构建。

```text
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

## 注意

你需要将TC所在目录加入环境变量中才能在命令行中调用它。