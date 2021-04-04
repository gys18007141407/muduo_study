#//	命名变量
#//	
#//	set(INC_DIR /usr/local/include) 左边变量名字，右边你的文件夹名字
#//	set(LINK_DIR /usr/local/lib) set(SOURCE_FILES main.cpp)
#//	
#//	cmakelist中的print
#//	
#//	message( "what you want to print" ${dir})
#//	
#//	Cmakelist与gcc对应系列：
#//	去哪里找头文件 相当于gcc/clang 中的-I(i的大写字母)参数
#//	
#//	include_directories(${INC_DIR}) 用${}引用变量
#//	
#//	去哪里找库文件 .so .dll .dylib 相当于gcc 中的-L参数
#//	
#//	link_directories(${LINK_DIR})
#//	
#//	要链接的库文件的名字 相当于gcc中的-l(小写的l)参数
#//	
#//	target_link_libraries(test_boost boost_filesystem boost_system) 只写库名就可以，就是libxxx.so的中间xxx的部分 也可以写成下面这样 target_link_libraries(test_boost boost_filesystem boost_system)
#//	
#//	
#//	
#//	
#//	
#//	我自己的cmakelist范例:
#//	
#//	cmake_minimum_required(VERSION 3.13)
#//	project(abc)
#//	
#//	set(CMAKE_CXX_STANDARD 11)
#//	
#//	
#//	set(INC_DIR
#//	        /usr/local/include/tf
#//	        /usr/local/include/tf/bazel-genfiles
#//	        /usr/local/include/tf/bazel-tensorflow/external/eigen_archive
#//	        /usr/local/include/tf/bazel-tensorflow/external/protobuf_archive/src)
#//	
#//	set(LINK_DIR
#//	        /usr/local/lib)
#//	
#//	include_directories(${INC_DIR})
#//	
#//	link_directories(${LINK_DIR})
#//	
#//	
#//	add_executable(abc main.cpp)
#//	target_link_libraries(abc tensorflow_cc tensorflow_framework)
#//	find_package(CUDA)
#//	if(CUDA_FOUND)
#//	    message( "cuda found"  ${CUDA_LIBRARIES})
#//	    target_link_libraries(abc ${CUDA_LIBRARIES})
#//	endif()
#
cmake_minimum_required(VERSION 3.16)
project(server)

set(CMAKE_CXX_STANDARD 11)

set(INC_DIR ../)

include_directories(${INC_DIR})

add_executable(server ../main.cpp ../echoServer.cpp ../threadPool.cpp ../timeStamp.cpp ../timerQueue.cpp ../tcpServer.cpp ../tcpConnection.cpp ../eventLoop.cpp ../epollWrap.cpp ../channel.cpp ../buffer.cpp ../acceptor.cpp)
target_link_libraries(server pthread)

