cmake_minimum_required (VERSION 2.8)


project (SimpleLang)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/modules CACHE TYPE STRING FORCE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
include(CommonFunctions)

include_directories( ${PROJECT_SOURCE_DIR} )
include_directories( "${PROJECT_SOURCE_DIR}/include" )

if (MSVC)
add_definitions( "/W3 /D_CRT_SECURE_NO_WARNINGS /wd4018 /wd4005 /wd4996 /nologo /permissive-" )
endif(MSVC)

add_folder(src)
add_executable (SimpleLang ${SRCS})

find_package(LLVM REQUIRED)
#find_package(LTO REQUIRED)

#find_package(Clang CONFIG REQUIRED)
# Note: 27 target(s) were omitted.
#target_link_libraries(SimpleLang PRIVATE clangAST clangLex libclang clangEdit)

find_package(LLVM CONFIG REQUIRED)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Note: 62 target(s) were omitted.
#target_link_libraries(SimpleLang PRIVATE LTO LLVMMC ${name} LLVMLTO)
target_link_libraries(SimpleLang PRIVATE LLVMMC ${name} LLVMLTO)
