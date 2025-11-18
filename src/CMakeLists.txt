set(SRC_EXECUTABLE_NAME "SecretNumberDilemma")

file(GLOB_RECURSE SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_executable(${SRC_EXECUTABLE_NAME} ${SOURCES})
target_include_directories(${SRC_EXECUTABLE_NAME} PRIVATE ${INCLUDE_DIR})