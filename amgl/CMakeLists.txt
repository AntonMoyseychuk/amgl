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

option(CFG_DISABLE_ERROR_FLAGS "Disable error flags" OFF)
option(CFG_DISABLE_DEBUG_LAYER "Disable debug layer" OFF)

set(CFG_INITIAL_BUFF_COUNT 1024 STRING "Precreated buffers count")

target_compile_definitions(${PROJECT_NAME} 
    PRIVATE AM_INIT_BUFF_COUNT=${CFG_INITIAL_BUFF_COUNT}
)

if(CFG_DISABLE_ERROR_FLAGS)
    target_compile_definitions(${PROJECT_NAME} 
        PRIVATE AM_DISABLE_ERROR_FLAGS=1
    )
endif()

if(CFG_DISABLE_DEBUG_LAYER)
    target_compile_definitions(${PROJECT_NAME} 
        PRIVATE AM_DISABLE_DEBUG_LAYER=1
    )
endif()