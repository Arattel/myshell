cmake_minimum_required(VERSION 3.8)
project(myshell)


set(CMAKE_CXX_STANDARD 14)
set( CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})


find_package(Readline REQUIRED)
find_package( Boost REQUIRED COMPONENTS filesystem system regex)


include_directories(${Boost_INCLUDE_DIRS})
include_directories(${Readline_INCLUDE_DIRS})
include_directories(${Docopt_INCLUDE_DIRS})
include_directories(docopt)


link_libraries(${READLINE_LIBRARY})


file(GLOB helpers_src
        "helpers/*/*.h"
        "helpers/*/*.cpp"
        "internal_programs/*.h"
        "internal_programs/*/*.h"
        "internal_programs/*/*.cpp"
        )
file(GLOB docopt_src
        "docopt/*")
file(GLOB external_programs_src
        "external_programs/*.cpp"
        "external_programs/*.h"
        )



set(SOURCE_FILES main.cpp helpers/io/console_io.h helpers/io/console_io.cpp
        ${helpers_src} ${docopt_src} ${external_programs_src} internal_programs/mcd/mcd.h internal_programs/mcd/mcd.cpp
        internal_programs/mexit/mexit.cpp internal_programs/mexit/mexit.h
        internal_programs/mexit/mexit.cpp internal_programs/mecho/mecho.h
        internal_programs/mexit/mexit.cpp internal_programs/mecho/mecho.cpp
        internal_programs/mexit/mexit.cpp internal_programs/mexport/mexport.cpp
        internal_programs/mexit/mexit.cpp internal_programs/mexport/mexport.h
        )

add_executable(myshell ${SOURCE_FILES})


target_link_libraries(myshell ${Boost_LIBRARIES})


