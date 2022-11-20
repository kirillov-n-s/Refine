cmake_minimum_required(VERSION 3.23)
project(Refine)

set(CMAKE_CXX_STANDARD 17)

add_executable(Refine
        main.cpp
        Demo.h Demo.cpp

        Refine/Common/Common.cpp Refine/Common/Common.h
        Refine/Common/Debug.cpp Refine/Common/Debug.h

        Refine/Geometry/Adjacency.cpp Refine/Geometry/Adjacency.h
        Refine/Geometry/Common.cpp Refine/Geometry/Common.h
        Refine/Geometry/MeshPoly.cpp Refine/Geometry/MeshPoly.h
        Refine/Geometry/MeshTri.cpp Refine/Geometry/MeshTri.h

        Refine/IO/Obj.cpp Refine/IO/Obj.h

        Refine/Rendering/Camera.cpp Refine/Rendering/Camera.h
        Refine/Rendering/Common.cpp Refine/Rendering/Common.h
        Refine/Rendering/GlMesh.cpp Refine/Rendering/GlMesh.h
        Refine/Rendering/GlShader.cpp Refine/Rendering/GlShader.h

        Refine/PBD/ProblemPositional.cpp Refine/PBD/ProblemPositional.h Refine/PBD/Forces.cpp Refine/PBD/Forces.h Refine/PBD/Constraints.cpp Refine/PBD/Constraints.h)

target_link_libraries(Refine GL)
target_link_libraries(Refine GLEW)
target_link_libraries(Refine glfw)
