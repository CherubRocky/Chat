add_library(controlador STATIC GeneradorJSON.cpp)
find_package(nlohmann_json REQUIRED)
target_link_libraries(controlador PRIVATE nlohmann_json::nlohmann_json)
