cmake_minimum_required(VERSION 3.8)
project(myls)



find_package( Boost REQUIRED COMPONENTS filesystem system regex)


include_directories(${Boost_INCLUDE_DIRS})
file(GLOB config_src
       "config/*.cpp"
        "config/*.h"
        )
file(GLOB filesystem_classes
        "filesystem_classes/*"
        )

file(GLOB console_helpers
        "../../../helpers/filesystem/*")
add_executable(myls main.cpp ${config_src} ${filesystem_classes} ${console_helpers} outputter/output.cpp outputter/output.h outputter/Outputter.cpp outputter/Outputter.h outputter/split_into_groups.cpp outputter/split_into_groups.h outputter/sorters.cpp outputter/sorters.h outputter/filename_formats.cpp outputter/filename_formats.h)


target_link_libraries(myls ${Boost_LIBRARIES})
