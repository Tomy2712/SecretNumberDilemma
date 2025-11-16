set(EXECUTABLE_NAME "SecretNumberDilemma")
add_executable(${EXECUTABLE_NAME}
        main.cpp
)

target_include_directories(${EXECUTABLE_NAME} PRIVATE
        ${INCLUDE_DIR}
)