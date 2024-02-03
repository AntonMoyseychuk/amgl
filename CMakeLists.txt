cmake_minimum_required(VERSION 3.26.0 FATAL_ERROR)

project(amgl)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (AMGL_DIR ${PROJECT_SOURCE_DIR}/amgl)

file(GLOB_RECURSE AMGL_SRC CONFIGURE_DEPENDS 
    ${AMGL_DIR}/src/*.cpp
    ${AMGL_DIR}/src/*.c
)

add_library(${PROJECT_NAME} STATIC ${AMGL_SRC})

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${AMGL_DIR}/include
    
    PRIVATE ${AMGL_DIR}/src
    PRIVATE ${AMGL_DIR}/thirdparty/debugbreak
)

target_precompile_headers(${PROJECT_NAME} PRIVATE ${AMGL_DIR}/src/pch.hpp)

set(CFG_BUILD_TESTS ON CACHE BOOL "Build tests" FORCE)
if (CFG_BUILD_TESTS)
    add_subdirectory(${PROJECT_SOURCE_DIR}/tests)
endif()

set(CFG_DISABLE_ERROR_FLAGS OFF CACHE BOOL "Disable error flags" FORCE)
set(CFG_DISABLE_DEBUG_LAYER OFF CACHE BOOL "Disable debug layer" FORCE)

set(CFG_INITIAL_BUFF_COUNT "1024" CACHE STRING "Precreated buffers count" FORCE)


target_compile_definitions(${PROJECT_NAME} PRIVATE "AM_BUILD_DEBUG=$<CONFIG:Debug>")
target_compile_definitions(${PROJECT_NAME} PRIVATE "AM_BUILD_RELEASE=$<CONFIG:Release>")
target_compile_definitions(${PROJECT_NAME} PRIVATE "AM_BUILD_RELEASE_MIN_SIZE=$<CONFIG:MinSizeRel>")
target_compile_definitions(${PROJECT_NAME} PRIVATE "AM_BUILD_RELEASE_WITH_DEBUG_INFO=$<CONFIG:RelWithDebInfo>")

target_compile_definitions(${PROJECT_NAME} PRIVATE AM_INIT_BUFF_COUNT=${CFG_INITIAL_BUFF_COUNT})

target_compile_definitions(${PROJECT_NAME} PRIVATE AM_DISABLE_ERROR_FLAGS=${CFG_DISABLE_ERROR_FLAGS})
target_compile_definitions(${PROJECT_NAME} PRIVATE AM_DISABLE_DEBUG_LAYER=${CFG_DISABLE_DEBUG_LAYER})