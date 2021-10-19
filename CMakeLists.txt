cmake_minimum_required(VERSION 3.5)

project (TemplateCopy)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tc src/main.cpp src/parse_cmd.cpp src/file_operation.cpp src/text_editor.cpp src/tem_file_operation.cpp src/variable_operation.cpp)

target_include_directories(tc
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/src
)

option(ENABLE_TEST "Enable or disable testing" OFF)
option(ENABLE_DEBUG "Enable or disable debug message" OFF)

# For Windows GTest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) 

if(ENABLE_TEST)
    message("Enable the testing")
    configure_file(${PROJECT_SOURCE_DIR}/test/text_editor_test.cpp.in ${PROJECT_SOURCE_DIR}/test/text_editor_test.cpp)
    configure_file(${PROJECT_SOURCE_DIR}/test/tem_file_operation_test.cpp.in ${PROJECT_SOURCE_DIR}/test/tem_file_operation_test.cpp)
    add_subdirectory(test/thirdparty)
    enable_testing()

    add_executable(parse_cmd_test test/parse_cmd_test.cpp src/parse_cmd.cpp)
    target_include_directories(parse_cmd_test PRIVATE ${PROJECT_SOURCE_DIR}/src)
    target_link_libraries(parse_cmd_test gtest_main)
    add_test(parse_cmd_test parse_cmd_test)

    add_executable(text_editor_test test/text_editor_test.cpp src/text_editor.cpp)
    target_include_directories(text_editor_test PRIVATE ${PROJECT_SOURCE_DIR}/src)
    target_link_libraries(text_editor_test gtest_main)
    add_test(text_editor_test text_editor_test)

    add_executable(variable_operation_test test/variable_operation_test.cpp src/variable_operation.cpp src/text_editor.cpp)
    target_include_directories(variable_operation_test PRIVATE ${PROJECT_SOURCE_DIR}/src)
    target_link_libraries(variable_operation_test gtest_main)
    add_test(variable_operation_test variable_operation_test)

    add_executable(tem_file_operation_test
        test/tem_file_operation_test.cpp src/tem_file_operation.cpp src/text_editor.cpp src/variable_operation.cpp)
    target_include_directories(tem_file_operation_test PRIVATE ${PROJECT_SOURCE_DIR}/src)
    target_link_libraries(tem_file_operation_test gtest_main)
    add_test(tem_file_operation_test tem_file_operation_test)
    

endif(ENABLE_TEST)

if(!ENABLE_DEBUG)
    target_compile_definitions(TC PUBLIC NDEBUG)
endif(!ENABLE_DEBUG)
