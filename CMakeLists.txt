cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(barkeshli_s22)


#. . . . . . . . . . . . . . . . . . . .
include(GNUInstallDirs)
if(MSVC)
    add_compile_options(/W4)
    add_link_options(/W4)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
    # message("compiler: MSVC")
else()
    # message("compiler: NOT MSVC")
    # add_compile_options(-Wall -Wextra -pedantic -Werror -Wl,--fatal-warnings)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()



# place binaries and libraries according to GNU standards
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})


if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()
#. . . . . . . . . . . . . . . . . . . .


option(BUILD_SHARED_LIBS "Build shared libraries" OFF)




#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#   Grab all cpp files from includes folder
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
set(INCLUDES_FOLDER includes)
FILE(GLOB_RECURSE SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}   "${INCLUDES_FOLDER}/*.cpp" )

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -




ADD_EXECUTABLE(main
    main.cpp
    ${SOURCE_FILES}
)


TARGET_COMPILE_FEATURES(main PRIVATE cxx_std_17)
INSTALL(TARGETS main)


 



 

