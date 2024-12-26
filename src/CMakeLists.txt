add_executable(particel_system
"main.cpp"
"stb_image.cpp"
"shader.cpp"
"object.cpp"
) #列所有的cpp
target_link_libraries(particel_system
glfw
glm::glm
glad
)