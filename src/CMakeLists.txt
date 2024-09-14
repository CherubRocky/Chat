add_subdirectory(Modelo)
add_subdirectory(Controlador)

add_executable(Servidor CorreServidor.cpp)
target_link_libraries(Servidor modelo)
target_link_libraries(Servidor controlador)

add_executable(Chat Chat.cpp)
target_link_libraries(Chat modelo)
target_link_libraries(Servidor controlador)
