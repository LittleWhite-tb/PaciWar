cmake_minimum_required(VERSION 2.6)

# Projet name
project("PaciWar")

# Additional compiler setting
SET(CMAKE_CXX_WARNING_LEVEL 4)
if (DEFINED MSYS)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else ()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif ()

file(
        GLOB_RECURSE
        source_files
        src/*
)

add_executable(
        "PaciWar"
        ${source_files}
)

# Set new cmake module path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

# Look after SFML
if (MSYS OR MINGW) # Give CMake a little hint
	set(SFML_ROOT "./")
endif (MSYS OR MINGW)

find_package(SFML 2.1 REQUIRED system window graphics audio)
target_link_libraries(PaciWar ${SFML_LIBRARIES})

include_directories(${SFML_INCLUDE_DIR}
					./include/
					./src/)

Message(${SFML_LIBRARIES})

# Installation
install(TARGETS PaciWar
        RUNTIME
        DESTINATION bin)

IF(WIN32 AND NOT UNIX)
	# Copy DLL
	file(GLOB dllFiles "./*.dll")
	foreach(dll ${dllFiles})
		install(FILES ${dll} DESTINATION bin)
	endforeach()
#else
endif(WIN32 AND NOT UNIX)

# Resources file installation
file(GLOB dataFiles "./data/*")
foreach(data ${dataFiles})
	install(FILES ${data} DESTINATION bin/data)
endforeach()

# CPack part
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Remake of the pacific mode from Geometry Wars 2")
SET(CPACK_PACKAGE_VENDOR "LittleWhite")
SET(CPACK_PACKAGE_EXECUTABLES "PaciWar" "PaciWar")

include(CPack)
