#查找当前目录下的所有源文件
#并将名称保存在 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)

#生成静态链接库
add_library(MathFunctions ${DIR_LIB_SRCS})

#指定MathFunctions库的安装路径
install(TARGETS MathFunctions DESTINATION lib)
install(FILES MathFunctions.h DESTINATION include)