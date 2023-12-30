    cmake_minimum_required(VERSION 3.0.0)
    project(AsteRogue VERSION 0.1.1)
    set(CMAKE_CXX_STANDARD 20)

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/AsteRogue)

    set(ENGINE_DIR ${CMAKE_SOURCE_DIR}/engine)
    set(ENGINE_HEADER_DIR ${ENGINE_DIR}/headers)
    set(COMPONENTS_HEADER_DIR ${ENGINE_HEADER_DIR}/components)
    set(STATES_HEADER_DIR ${ENGINE_HEADER_DIR}/states)
    set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/external)
    set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

    #SFML build options
    option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

    #Fetch SFML
    include(FetchContent)
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
    FetchContent_MakeAvailable(SFML)
    
    add_subdirectory(${ENGINE_DIR})

    include_directories(
        ${ENGINE_HEADERS_DIR}
        ${COMPONENTS_HEADER_DIR}
        ${STATES_HEADER_DIR}
    )

    # Gather source files and build executable from them
    aux_source_directory(${SOURCE_DIR}  DIR_SRCS)
    add_executable(${PROJECT_NAME} ${DIR_SRCS})

    #Link libraries to project
    target_link_libraries(${PROJECT_NAME} PUBLIC Engine)
    target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
    target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)


    
    if (NOT EXISTS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/saves)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory(${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/saves)
    )
    endif()

    if (NOT EXISTS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory(${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data)
    )
endif()

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/data  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data
    )