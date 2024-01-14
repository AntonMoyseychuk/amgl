project(amgl)

file(GLOB_RECURSE AMGL_SRC CONFIGURE_DEPENDS 
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/*.c
)

add_library(${PROJECT_NAME} STATIC ${AMGL_SRC})

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    
    PRIVATE ${PROJECT_SOURCE_DIR}/src
    PRIVATE ${PROJECT_SOURCE_DIR}/thirdparty/debugbreak
)

target_precompile_headers(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src/pch.hpp)

target_compile_definitions(${PROJECT_NAME} 
    PRIVATE AMGL_CFG_PREALLOCATION_SIZE=1024
    PRIVATE AMGL_CFG_KEEP_MEMORY_ALLOCATED
)