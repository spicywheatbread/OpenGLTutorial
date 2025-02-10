add_library(mylib Mesh.cpp Model.cpp Shader.cpp)

target_link_libraries(mylib PUBLIC glm::glm)
target_include_directories(mylib
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR})
