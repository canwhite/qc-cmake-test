#多个目录，多个文件
#对于这种情况，需要在项目根目录demo3和math目录里各自编写CMakeLists.txt文件
#为了方便，我们可以先将math目录里的文件编译成静态库再由main函数调用

#CMake最低版本号要求
cmake_minimum_required(VERSION 2.8)

#项目信息,这个项目名称是自定义的
project(Demo3)

#查找当前目录下的所有源文件，并将名称保存到DIR_SRCS变量
aux_source_directory(. DIR_SRCS)

#添加math子目录，并执行子目录中的CMakeLists.txt
#注意子目录中生成静态文件的方法是add_library(名字 路径)
add_subdirectory(math)

#PS：SET命令可以显式的定义变量
#SET(CMAKE_INSTALL_PREFIX /usr/local)  

#指定生成目标（名称，文件）
add_executable(Demo main.cc)

#添加链接库，再math中生成了MathFunction，这里建立了链接
target_link_libraries(Demo MathFunctions)


