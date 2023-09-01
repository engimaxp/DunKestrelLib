# SPDX-License-Identifier: Unlicense

target_sources( ${PROJECT_NAME}
    PRIVATE
        GraphNode.h
        GraphNode.cpp
        GraphEdge.h
        GraphEdge.cpp
        Graph.h
        Graph.cpp
        example.h
        example.cpp
        register_types.h
        register_types.cpp

)

target_include_directories( ${PROJECT_NAME}
    PRIVATE
        "src"
)