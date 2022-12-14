cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)

set(PROJECT_NAME queue)
project(${PROJECT_NAME} CXX)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_COMPILER clang++)

cmake_path(GET PROJECT_SOURCE_DIR PARENT_PATH STACK_PATH)
include_directories(include list/include ${STACK_PATH}/stack/include)

set(SOURCE_TEST tests/tests.cpp)
set(SOURCE_STACK ${STACK_PATH}/stack/src/stack_bool.cpp)

add_library(STACK_LIB STATIC ${SOURCE_STACK})

#clang-tidy
option(CLANG_TIDY "Include clang-tidy" OFF)
find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)
    message (clang-tidy " from " ${CMAKE_SOURCE_DIR}/.clang-tidy)
    
    set (CMAKE_CXX_CLANG_TIDY
        "clang-tidy;-format-style=file:${CMAKE_SOURCE_DIR}/.clang-tidy;-checks=*"
    )
endif()

#sanitizers
option(ADD_SANITIZERS "Build with sanitizers" ON)
if (ADD_SANITIZERS)
    message ("Build with sanitizers")

    add_compile_options (-fsanitize=address -fsanitize=undefined)
    set_target_properties (STACK_LIB PROPERTIES LINK_FLAGS "-fsanitize=address -fsanitize=undefined")
endif ()

#tests
option(TESTING "Include testing" ON)
if (TESTING)
    message ("Include testing")

    find_package (GTest REQUIRED)
    include_directories (${GTEST_INCLUDE_DIRS})

    add_executable (${PROJECT_NAME}_tests ${SOURCE_TEST})
    
    option(BENCHMARKING "Include benchmarking" ON)
    #benchmarking
    if (BENCHMARKING)
        message ("Include benchmarking")
        
        set (SOURCE_BENCH benchmark/benchmark.cpp)
        find_package (benchmark REQUIRED)

        add_executable (${PROJECT_NAME}_bench ${SOURCE_BENCH})
        target_link_libraries(${PROJECT_NAME}_bench PRIVATE benchmark::benchmark)
    endif ()

    if (ADD_SANITIZERS)
        set_target_properties (${PROJECT_NAME}_tests PROPERTIES LINK_FLAGS "-fsanitize=address -fsanitize=undefined")
        set_target_properties (${PROJECT_NAME}_bench PROPERTIES LINK_FLAGS "-fsanitize=address -fsanitize=undefined")
    endif()
    
    target_link_libraries (${PROJECT_NAME}_tests PUBLIC GTest::GTest GTest::Main STACK_LIB)
    
    if (BENCHMARKING)
    target_link_libraries (${PROJECT_NAME}_bench PRIVATE benchmark::benchmark)
    endif ()

    enable_testing ()

    add_custom_target (run_${PROJECT_NAME}_tests 
        COMMENT "Running list_tests"
        COMMAND ./queue_tests
    )
    add_dependencies (run_${PROJECT_NAME}_tests ${PROJECT_NAME}_tests)

    add_custom_target (run_${PROJECT_NAME}_bench 
        COMMENT "Running list_benchmarks"
        COMMAND ./queue_bench
    )
    add_dependencies (run_${PROJECT_NAME}_bench ${PROJECT_NAME}_bench)

    add_subdirectory (list)
    #add_subdirectory (${CMAKE_SOURCE_DIR}/../stack)
endif ()

#clang-format
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    message (clang-format " from " ${CMAKE_SOURCE_DIR}/.clang-format)

    file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.hpp)
    add_custom_target(
        clang_format
        COMMAND clang-format
        -i
        -style=file:${CMAKE_SOURCE_DIR}/.clang-format
        ${ALL_SOURCE_FILES}
    )
endif()

