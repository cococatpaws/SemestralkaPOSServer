cmake_minimum_required(VERSION 3.18)
project(SemestralkaPOSServer C)

set(CMAKE_C_STANDARD 99)

add_executable(SemestralkaPOSServer main.c pos_sockets/active_socket.c pos_sockets/char_buffer.c pos_sockets/passive_socket.c)
target_link_libraries(SemestralkaPOSServer pthread)
