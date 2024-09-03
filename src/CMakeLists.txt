add_subdirectory(Modelo)

add_executable(Servidor CorreServidor.cpp)
target_link_libraries(Servidor modelo)

add_executable(Chat Chat.cpp)
target_link_libraries(Chat modelo)
