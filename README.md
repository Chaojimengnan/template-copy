# TemplateCopy

[中文](./doc/README_chs.md)

## Introduce

This is a template copying program that copies files in a directory to another directory and replaces `${variable}` in a text file with the suffix `.tem`. Finally, the `tem` suffix is removed

For example, if I have a `1.txt.tem` file and I have a custom `You` variable with a value of "lomekragow" :

```text
Hello ${You}
```

TemplateCopy will look for the string variable named `You` in the `variable.txt` file and replace it. When copied to the destination directory, the file is suffixed with `1.txt` and looks like this

```text
Hello lomekragow
```

Inspiration comes from CMake。

## Usage

### Help

```text
tc help
```

This command lists all available tc commands and their usage.

### Copy directory

```text
tc SourceDirectory:TargetDirectory
```

Copy the source directory under the tc executable directory to the target directory of the current working directory (if not, it will be created automatically).  


### Lists the directories to copy


```text
tc list
```

List the source directories that the tc can copy


### Set a variable

```text
tc variable=value
```
This variable will be stored in a `variable.txt` file in the directory of the executable, which means you can modify the `variable.txt` file yourself(Prefer the former). 

## Build

The program is built using [CMake](https://cmake.org/), or you can build it using another tool or IDE.  

```text
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

## Note

You need to add the directory of the tc to the environment variable to call it from the command line.