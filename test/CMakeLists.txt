## Authors: first_name1 last_name1, first_name2 last_name2
########################################################################################################################

# clone and build gtest
include(FetchContent)
FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG v1.14.0
        GIT_SHALLOW TRUE
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# add testing executable
add_executable(example_test gtest_main.cpp test.cpp)
target_link_libraries(example_test PUBLIC GTest::gtest_main GTest::gmock ${LIBRARY_NAME})

# make tests available for ctest
include(GoogleTest)
gtest_add_tests(TARGET example_test WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/test)
