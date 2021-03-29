#多个目录，多个文件
#对于这种情况，需要在项目根目录demo3和math目录里各自编写CMakeLists.txt文件
#为了方便，我们可以先将math目录里的文件编译成静态库再由main函数调用

#CMake最低版本号要求
cmake_minimum_required(VERSION 2.8)

#项目信息,这个项目名称是自定义的
project(Demo3)

#查找当前目录下的所有源文件，并将名称保存到DIR_SRCS变量
aux_source_directory(. DIR_SRCS)

#添加math子目录
add_subdirectory(math)

#指定生成目标
add_executable(Demo main.cc)

#添加链接库
target_link_libraries(Demo MathFunctions)


