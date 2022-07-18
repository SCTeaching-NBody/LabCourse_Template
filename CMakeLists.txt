## Authors: first_name1 last_name1, first_name2 last_name2
########################################################################################################################

cmake_minimum_required(VERSION 3.16.3)

project("LabCourse: Solar System Simulation"
        VERSION 1.0
        LANGUAGES CXX)


########################################################################################################################
##                                            set default cmake build type                                            ##
########################################################################################################################
set(default_build_type "Release")
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif ()


########################################################################################################################
##                                                   create library                                                   ##
########################################################################################################################
## TODO: all source files (*.cpp) must be added here
set(LIBRARY_SOURCES src/labcourse/dummy.cpp)

# create library
set(LIBRARY_NAME lab_course)
add_library(${LIBRARY_NAME} STATIC ${LIBRARY_SOURCES})


########################################################################################################################
##                                                 set compiler flags                                                 ##
########################################################################################################################
# set C++17 as standard
target_compile_features(${LIBRARY_NAME} PUBLIC cxx_std_17)
# set include as include-directory
target_include_directories(${LIBRARY_NAME} PUBLIC include)
# add warning flags based on the used C++-compiler
target_compile_options(${LIBRARY_NAME} PUBLIC
        $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic -Werror>
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
)
# add math definition
target_compile_definitions(${LIBRARY_NAME} PUBLIC _USE_MATH_DEFINES)

########################################################################################################################
##                                    check for optional and necessary dependencies                                   ##
########################################################################################################################
## OpenMP and MPI are required for this LabCourse
find_package(OpenMP REQUIRED)
target_link_libraries(${LIBRARY_NAME} PUBLIC OpenMP::OpenMP_CXX)
find_package(MPI REQUIRED)
target_link_libraries(${LIBRARY_NAME} PUBLIC MPI::MPI_CXX)


## TODO: add potential optional dependencies here


# create executable
add_executable(simulate src/main.cpp)

# link library against executable
target_link_libraries(simulate PRIVATE ${LIBRARY_NAME})


########################################################################################################################
##                                                     add tests                                                      ##
########################################################################################################################
option(WITH_TESTS "Build the tests." ON)
if (WITH_TESTS)
    message(STATUS "Enable tests!")
    enable_testing()
    add_subdirectory(test)
endif ()
