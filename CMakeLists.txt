cmake_minimum_required(VERSION 3.5)

project (template_copy)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tc src/main.cpp src/parse_cmd.cpp src/file_operation.cpp 
    src/text_editor.cpp src/tem_file_operation.cpp src/variable_operation.cpp)

target_include_directories(tc
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/src
)

option(ENABLE_TEST "Enable or disable testing" ON)
option(ENABLE_DEBUG "Enable or disable debug message" OFF)

# For Windows GTest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) 

if(ENABLE_TEST)
    message("Enable the testing")
    configure_file(${PROJECT_SOURCE_DIR}/test/text_editor_test.cpp.in ${PROJECT_SOURCE_DIR}/test/text_editor_test.cpp)
    configure_file(${PROJECT_SOURCE_DIR}/test/tem_file_operation_test.cpp.in ${PROJECT_SOURCE_DIR}/test/tem_file_operation_test.cpp)
    add_subdirectory(test/thirdparty)
    enable_testing()

    add_executable(template_copy_test test/parse_cmd_test.cpp src/parse_cmd.cpp
        test/text_editor_test.cpp src/text_editor.cpp
        test/variable_operation_test.cpp src/variable_operation.cpp src/text_editor.cpp
        test/tem_file_operation_test.cpp src/tem_file_operation.cpp src/text_editor.cpp src/variable_operation.cpp
        )
    target_include_directories(template_copy_test PRIVATE ${PROJECT_SOURCE_DIR}/src)
    target_link_libraries(template_copy_test gtest_main)
    add_test(template_copy_test template_copy_test)

endif(ENABLE_TEST)

if(!ENABLE_DEBUG)
    target_compile_definitions(TC PUBLIC NDEBUG)
endif(!ENABLE_DEBUG)
