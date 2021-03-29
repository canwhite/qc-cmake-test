#区别于安装，这里是生成安装包
#主要是文件最后几句的实现

#在生成项目之后，我们可以
#生成二进制安装包：cpack -C CPackConfig.cmake
#生成源码安装包：cpack -C CPackSourceConfig.cmake



#CMake最低版本号要求
cmake_minimum_required(VERSION 2.8)

#项目信息
project(Demo8)
#设置主版本号
set(Demo_VERSION_MAJOR 1)
#设置副版本号
set(Demo_VERSION_MINOR 0)




#CMAKE_INCLUDE_CURRENT_DIR equal to INCLUDE_DIRECTORY(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
#拿到CMAKE当前所在环境
set (CMAKE_INCLUDE_CURRENT_DIR ON)


#检查系统是否支持pow函数
include(${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)#引入check*函数
#调用函数验证
check_function_exists(pow HAVE_POW)



#加入一个配置文件config.h,这个文件由CMake从config.h.in生成
#通过这样的机制，可以预定义一些参数和变量来控制代码的生成
configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_SOURCE_DIR}/config.h"
)

#是否使用自己的MathFucntions库
# option(USE_MYMATH
#        "Use provided math implementation" ON)


#是否加入MathFuntions库
#根据 USE_MYMATH 变量的值来决定是否使用我们自己编写的 MathFunctions 库。
#因为头文件引入过了，所以USE_MYMATH变量可以直接使用
if(NOT HAVE_POW)
    include_directories("${PROJECT_SOURCE_DIR}/math")
    add_subdirectory(math)
    set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif(HAVE_POW)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
# aux是辅助的意思
aux_source_directory(. DIR_SRCS)

# 指定生成目标
add_executable(Demo ${DIR_SRCS})
target_link_libraries (Demo  ${EXTRA_LIBS})


#指定安装目录
#以下内容意味着生成的demo文件会被复制到/usr/local/bin
#config.h文件会被赋值到/usr/local/include文件
#math中类同
install (TARGETS Demo DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/config.h"
         DESTINATION include)


#启用测试和add_test
enable_testing()

# 测试程序是否成功运行
add_test (test_run Demo 5 2)

# 测试帮助信息是否可以正常提示
add_test (test_usage Demo)
#PASS_REGULAR_EXPRESSION 用来测试输出是否包含后面跟着的字符串。
#现有add_test，后边这个是写断言的set_tests_properties
set_tests_properties (test_usage
  PROPERTIES PASS_REGULAR_EXPRESSION "Usage: .* base exponent")

# 测试 2 的 10 次方
# add_test (test_2_10 Demo 2 10)

# set_tests_properties (test_2_10
#  PROPERTIES PASS_REGULAR_EXPRESSION "is 1024")


#测试总结：add_test和断言set_tests_properties一般会成对存在
#所以我们可以定义宏方法，方便使用，这个估计还要重新再打一遍包


# 定义一个宏，用来简化测试工作
macro (do_test arg1 arg2 result)
  add_test (test_${arg1}_${arg2} Demo ${arg1} ${arg2})
  set_tests_properties (test_${arg1}_${arg2}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test)

# 利用 do_test 宏，测试一系列数据
do_test (5 2 "is 25")
do_test (10 5 "is 100000")
do_test (2 10 "is 1024")


# 构建一个 CPack 安装包
#导入 InstallRequiredSystemLibraries 模块，以便之后导入 CPack 模块；
include (InstallRequiredSystemLibraries)
#设置一些 CPack 相关变量，包括版权信息和版本信息，其中版本信息用了上一节定义的版本号
set (CPACK_RESOURCE_FILE_LICENSE
  "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set (CPACK_PACKAGE_VERSION_MAJOR "${Demo_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${Demo_VERSION_MINOR}")
#导入CPack模块
include (CPack)
