# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
SET(CMAKE_USE_RELETIVE_PATH ON)
SET(CMAKE_SUPPRESS_REGENERATION 1)
# 项目信息
#set (DIR_SRCS ./src)
project (crack_merge)
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(./src/utility DLL_SRCS)
#aux_source_directory(./src/test TEST_SRCS)
# 指定生成目标

#link_directories 应该在 add_executable 之前
LINK_DIRECTORIES(
./Debug
./Release
${CMAKE_SOURCE_DIR}/lib
)



#add_executable(Demo ${TEST_SRCS})
ADD_LIBRARY(crack_merge SHARED ${DLL_SRCS})

#SET_TARGET_PROPERTIES(Demo PROPERTIES LINKER_LANGUAGE CXX)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( ${CMAKE_SOURCE_DIR}/inc/TinyVLib )
include_directories( ${CMAKE_SOURCE_DIR}/inc)
# target_link_libraries( Demo 
# ${OpenCV_LIBS} 
# crack_merge.lib
# )
target_link_libraries( crack_merge 
stitchImgs
getwidthDll
${OpenCV_LIBS} 
)
