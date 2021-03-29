#案例一 : 同一目录，单个文件


#CMake 最低版本号要求
cmake_minimum_required(VERSION 2.8)

#项目信息,给当前项目起个名字
project(Demo1)

#指定生成目标,将main.cc源文件编译为一个名为Demo的可执行文件
add_executable(Demo main.cc)

