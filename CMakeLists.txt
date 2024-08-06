#需求的最低cmake程序版本
cmake_minimum_required(VERSION 3.12)

#本工程的名字
project(OpenGL)


#将资源文件夹assets打包到变量ASSETS下，然后拷贝到二进制执行目录里面
file(GLOB ASSETS "./assets")

file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})

#规定头文件搜索路径
include_directories(system ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/include)

#规定链接器搜索路径
link_directories(system ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/lib)

#加入关联文件夹
add_subdirectory(wrapper)
add_subdirectory(application)
add_subdirectory(glframework)


#本工程支持的C++版本
set(CMAKE_CXX_STANDARD 17)

#add_definitions(-DDEBUG)

#搜索所有的cpp，加入SRCS变量中
aux_source_directory(. SRCS)

#本工程所有cpp文件编译链接，生成exe
add_executable(OpenGLStudy "OpenGL.cpp""glad.c" )

#将链接库连接到exe里面合成一个程序
target_link_libraries(OpenGLStudy glfw3.lib wrapper app fw)