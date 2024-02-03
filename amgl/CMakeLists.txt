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