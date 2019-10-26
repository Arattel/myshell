cmake_minimum_required(VERSION 3.15)
project(Mycat)

set(CMAKE_CXX_STANDARD 14)


find_package( Boost REQUIRED COMPONENTS filesystem )
include_directories( ${Boost_INCLUDE_DIRS} )




#add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/external_programs/mycat)
file(GLOB src
        "*.cpp"
        "*.h"
        )
add_executable(mycat ${src})
target_link_libraries(mycat  ${Boost_LIBRARIES})
# create executable

# link libraries
