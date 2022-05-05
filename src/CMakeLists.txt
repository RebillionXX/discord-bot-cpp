project(discord_bot LANGUAGES CXX)

file(GLOB INCLUDE_FILES
    *.h
    discord_bot/*.h
    discord_bot/structure/*.h
    utils/*.h
)
file(GLOB SOURCE_FILES
    *.cpp
    discord_bot/*.cpp
    discord_bot/structure/*.cpp
    utils/*.cpp
)

add_executable(${PROJECT_NAME}
    ${INCLUDE_FILES}
    ${SOURCE_FILES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    C_STANDARD 11
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    NOMINMAX
    WIN32_LEAN_AND_MEAN
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/DPP/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/fmt/include
)

target_link_libraries(${PROJECT_NAME}
    dpp
    fmt
)
