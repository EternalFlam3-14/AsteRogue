cmake_minimum_required(VERSION 3.0.0)
project(Engine VERSION 0.0.7)
set(CMAKE_CXX_STANDARD 20)

set(ENGINE_DIR ${CMAKE_SOURCE_DIR}/engine)
set(ENGINE_HEADERS_DIR ${ENGINE_DIR}/headers)
set(COMPONENTS_HEADER_DIR ${ENGINE_HEADER_DIR}/components)
set(STATES_HEADER_DIR ${ENGINE_HEADER_DIR}/states)
set(ENGINE_SOURCE_DIR src)

include_directories(
    ${ENGINE_HEADERS_DIR}
    ${COMPONENTS_HEADER_DIR}
    ${STATES_HEADER_DIR}
)

aux_source_directory(${ENGINE_SOURCE_DIR} ENGINE_SRCS)

add_library(${PROJECT_NAME} STATIC ${ENGINE_SRCS})

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${ENGINE_HEADERS_DIR}
    ${COMPONENTS_HEADER_DIR}
    ${STATES_HEADER_DIR}
)

