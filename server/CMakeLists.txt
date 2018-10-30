add_executable(server server.cpp Caculator.cpp main.cpp)

#add dynamic linked libraries
target_link_libraries (server ${CMAKE_THREAD_LIBS_INIT})
