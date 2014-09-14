cmake_minimum_required(VERSION 2.6)

# Projet name
project("PaciWar")

file(
        GLOB_RECURSE
        source_files
        src/*
)

add_executable(
        "PaciWar"
        ${source_files}
)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2.1 REQUIRED system window graphics audio)
target_link_libraries(PaciWar ${SFML_LIBRARIES})

include_directories(${SFML_INCLUDE_DIR}
					./include/)

Message(${SFML_LIBRARIES})
