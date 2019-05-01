cmake_minimum_required(VERSION 3.9)
project(Raytracer)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)
link_directories(../lib/)
include_directories(../shared ../shared/include ../shared/gl3w ../shared/imgui)



add_executable(Raytracer
        Raytracer.cpp
        Raytracer.hpp
        GeometryNode.cpp
        GeometryNode.hpp
        Image.cpp
        Image.hpp
        JointNode.cpp
        JointNode.hpp
        Light.cpp
        Light.hpp
        lua488.hpp
        Main.cpp
        Material.cpp
        Material.hpp
        Mesh.cpp
        Mesh.hpp
        PhongMaterial.cpp
        PhongMaterial.hpp
        polyroots.cpp
        polyroots.hpp
        Primitive.cpp
        Primitive.hpp
        scene_lua.cpp
        scene_lua.hpp
        SceneNode.cpp
        SceneNode.hpp BoolNode.cpp BoolNode.hpp Lego.cpp Lego.hpp ProcLegoNode.cpp ProcLegoNode.hpp)

set(CMAKE_SHARED_LINKER_FLAGS  "${CMAKE_SHARED_LINKER_FLAGS} -Wl,../../lib/" )

target_link_libraries(Raytracer -lcs488-framework -limgui -lglfw3 -llua -llodepng -lGL -lXinerama -lXcursor -lXxf86vm -lXi -lXrandr -lX11 -lstdc++ -ldl -lpthread)