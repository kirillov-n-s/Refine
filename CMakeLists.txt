cmake_minimum_required(VERSION 3.23)
project(Refine)

set(CMAKE_CXX_STANDARD 17)

add_executable(Refine
        main.cpp
        Refine/Common/Common.h Refine/Common/Common.cpp
        Refine/Common/Debug.h Refine/Common/Debug.cpp
        Refine/Common/FlatTable.h
        Refine/Geometry/PolyMesh.h Refine/Geometry/PolyMesh.cpp
        Refine/Geometry/TriMesh.h Refine/Geometry/TriMesh.cpp
        Refine/IO/Obj.h Refine/IO/Obj.cpp)
