set(EXECUTABLE_NAME "SecretNumberDilemma")
set(SOURCES
        main.cpp
        csp/variable.cpp
        csp/constraint/binaryConstraint.cpp
        csp/constraint/allDifferenceConstraint.cpp
        csp/constraint/constraint.cpp
)

add_executable(${EXECUTABLE_NAME} ${SOURCES})

target_include_directories(${EXECUTABLE_NAME} PRIVATE ${INCLUDE_DIR})