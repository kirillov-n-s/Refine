cmake_minimum_required(VERSION 3.23)
project(Refine)

set(CMAKE_CXX_STANDARD 17)

add_executable(Refine
        main.cpp
        Demo.h Demo.cpp

        Refine/Common/Common.h Refine/Common/Common.cpp
        Refine/Common/Debug.h Refine/Common/Debug.cpp
        Refine/Common/FlatTable.h

        Refine/Geometry/Adjacency.h Refine/Geometry/Adjacency.cpp
        Refine/Geometry/Common.h Refine/Geometry/Common.cpp
        Refine/Geometry/MeshPoly.h Refine/Geometry/MeshPoly.cpp
        Refine/Geometry/MeshTri.h Refine/Geometry/MeshTri.cpp

        Refine/IO/Obj.h Refine/IO/Obj.cpp

        Refine/Rendering/Camera.h Refine/Rendering/Camera.cpp
        Refine/Rendering/Common.h Refine/Rendering/Common.cpp
        Refine/Rendering/GlMesh.h Refine/Rendering/GlMesh.cpp
        Refine/Rendering/GlShader.h Refine/Rendering/GlShader.cpp)

target_link_libraries(Refine GL)
target_link_libraries(Refine GLEW)
target_link_libraries(Refine glfw)
