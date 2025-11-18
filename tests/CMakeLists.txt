set(TESTS_EXECUTABLE_NAME "SecretNumberDilemma_tests")

file(GLOB_RECURSE SOURCES
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

list(REMOVE_ITEM SOURCES "${PROJECT_SOURCE_DIR}/src/main.cpp")

file(GLOB_RECURSE TEST_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_executable(${TESTS_EXECUTABLE_NAME} ${SOURCES} ${TEST_SOURCES})
target_include_directories(${TESTS_EXECUTABLE_NAME} PRIVATE ${INCLUDE_DIR})