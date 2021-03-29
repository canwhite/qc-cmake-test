#CMake允许为项目增加编译选项,从而可以根据用户的环境和需求选择最合适的编译方案
#例如可以将MathFunctions库设为一个可选的库，如果该选项为ON，就使用该库定义的数学函数来进行运算
#否则就调用标准库中的数学函数库

#CMake最低版本号要求
cmake_minimum_required(VERSION 2.8)

#项目信息
project(Demo4)

#加入一个配置文件config.h,这个文件由CMake从config.h.in生成
#通过这样的机制，可以预定义一些参数和变量来控制代码的生成
configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_SOURCE_DIR}/config.h"
)

#是否使用自己的MathFucntions库
option(USE_MYMATH
       "Use provided math implementation" ON)


#是否加入MathFuntions库
#根据 USE_MYMATH 变量的值来决定是否使用我们自己编写的 MathFunctions 库。
#因为头文件引入过了，所以USE_MYMATH变量可以直接使用
if(USE_MYMATH)
    include_directories("${PROJECT_SOURCE_DIR}/math")
    add_subdirectory(math)
    set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif(USE_MYMATH)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable(Demo ${DIR_SRCS})
target_link_libraries (Demo  ${EXTRA_LIBS})