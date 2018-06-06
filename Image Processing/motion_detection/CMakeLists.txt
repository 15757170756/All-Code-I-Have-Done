# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
# 项目信息
project (motion_detection)
# 设置编译选项
set( CMAKE_BUILD_TYPE Release )
set( CMAKE_C_FLAGS "-std=c99" )

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(./src LIB_SRCS)
aux_source_directory(./testUtil EXE_SRCS)

# 包含文件.h
include_directories(./inc)

# 共享库
add_library(motion_detection_shared SHARED ${LIB_SRCS})
# 静态库
add_library( motion_detection ${LIB_SRCS})

# 指定生成目标
add_executable(testUtil ${EXE_SRCS})

target_link_libraries(testUtil motion_detection_shared)



