cmake_minimum_required(VERSION 3.26.0 FATAL_ERROR)

project(sandbox)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(TARGET_ARCHITECTURE "x64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(TARGET_ARCHITECTURE "x86")
else ()
    message(FATAL_ERROR "Unknown architecture")
endif()

message("\nTARGET_ARCHITECTURE = ${TARGET_ARCHITECTURE}\n")


file(GLOB_RECURSE SANDBOX_SRC CONFIGURE_DEPENDS 
    ${CMAKE_CURRENT_LIST_DIR}/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/*.c
)

add_executable(${PROJECT_NAME} ${SANDBOX_SRC})

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
set(SDL2_PATH ${CMAKE_CURRENT_LIST_DIR}/thirdparty/SDL2/2.28.5)

find_package(SDL2 REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARY})
target_link_libraries(${PROJECT_NAME} PUBLIC amgl)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy_if_different
       ${CMAKE_CURRENT_LIST_DIR}/thirdparty/SDL2/2.28.5/lib/${TARGET_ARCHITECTURE}/SDL2.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>)