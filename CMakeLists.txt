cmake_minimum_required(VERSION 2.6)

# Set new cmake module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")

# Projet name
project("PaciWar")

cmake_policy(SET CMP0015 NEW)

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

# Version configuration
set (PaciWar_VERSION_MAJOR "0")
set (PaciWar_VERSION_MINOR "1")
set (PaciWar_VERSION_PATCH "1")

include(GetGitRevisionDescription)
git_describe(PaciWar_VERSION_SHA --always --long)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/version.hpp.in
               ${CMAKE_CURRENT_SOURCE_DIR}/src/version.hpp)


option(GODMODE "Enable/Disable god mode" FALSE)
if(GODMODE)
	add_definitions(-DGOD_MODE)
endif()

find_package(SFML QUIET COMPONENTS system window graphics audio)
if (NOT SFML_FOUND) # Let's try to find it ourselves
    set(TMP_NEED_COMPILE_SFML FALSE)
    if (WIN32)
        if (MSVC)
            if (CMAKE_SIZEOF_VOID_P EQUAL 8)
                set(TMP_ARCH "x64")
            elseif (CMAKE_SIZEOF_VOID_P EQUAL 4)
                set(TMP_ARCH "Win32")
            else()
                set(TMP_ARCH "UNKNOWN")
                set(TMP_NEED_COMPILE_SFML TRUE)
            endif()

            if (MSVC10) # Visual C++ 2010
                set(TMP_TOOLSET "v100")
            elseif (MSVC11) # Visual C++ 2012
                set(TMP_TOOLSET "v110")
            elseif (MSVC12) # Visual C++ 2013
                set(TMP_TOOLSET "v120")
            else()
                set(TMP_TOOLSET "UNSUPPORTED")
                set(TMP_NEED_COMPILE_SFML TRUE)
            endif()

            set(TMP_TOOLSET "msvc_${TMP_TOOLSET}-${TMP_ARCH}")
        else() # Certainly mingw
            # Assume mingw
            if (CMAKE_SIZEOF_VOID_P EQUAL 4)
                set(TMP_ARCH "i686")
            else()
                set(TMP_ARCH "UNKNOWN")
                set(TMP_NEED_COMPILE_SFML TRUE)
            endif()

            set(TMP_TOOLSET "mingw-${TMP_ARCH}")
        endif()
    else() # Not Windows
        set(TMP_NEED_COMPILE_SFML TRUE)

        # RPATH configuration
        SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
        SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
        SET(CMAKE_INSTALL_RPATH "./lib")
        SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)
    endif()

    # Try to compile
    if (TMP_NEED_COMPILE_SFML)
        message("SFML will be compiled")
        set(SFML_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/deps/SFML-2.3.source")

        add_subdirectory(${SFML_PREFIX} EXCLUDE_FROM_ALL)

        set(SFML_INCLUDE_DIR "${SFML_PREFIX}/include")
        set(SFML_LIBRARY_DIR "${SFML_PREFIX}/lib")
    else()
        set(SFML_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/deps/SFML-2.3.bin")
        set(SFML_LIBRARY_DIR "${SFML_PREFIX}/lib-${TMP_TOOLSET}")
    endif()
    set(SFML_INCLUDE_DIR "${SFML_PREFIX}/include")

    link_directories(${SFML_LIBRARY_DIR})

    # Clean up after ourselves
    unset(TMP_TOOLSET)
    unset(TMP_ARCH)

    if (WIN32)
        set(SFML_LIBRARIES sfml-main sfml-system sfml-graphics sfml-window sfml-audio)
        if (MINGW)
            # I should use find_library
            set(SFML_LIBRARIES ${SFML_LIBRARY_DIR}/libsfml-main.a ${SFML_LIBRARY_DIR}/libsfml-system.a ${SFML_LIBRARY_DIR}/libsfml-graphics.a ${SFML_LIBRARY_DIR}/libsfml-window.a ${SFML_LIBRARY_DIR}/libsfml-audio.a)
        endif()
    else()
        set(SFML_LIBRARIES sfml-system sfml-graphics sfml-window sfml-audio)
    endif()
endif()

add_executable(
        "PaciWar"
        ${source_files}
)

target_link_libraries(PaciWar ${SFML_LIBRARIES})
include_directories(${SFML_INCLUDE_DIR}
                    ./include/
                    ./src/)

# Installation
install(TARGETS PaciWar 
        RUNTIME DESTINATION .)

if (WIN32)
    file(GLOB dllFiles "${SFML_LIBRARY_DIR}/*.dll")
    foreach(dll ${dllFiles})
            install(FILES ${dll} DESTINATION .)
    endforeach()
else()
    install(DIRECTORY ${SFML_LIBRARY_DIR}
            DESTINATION .
            FILES_MATCHING PATTERN "*.so*")
endif()

# Resources file installation
file(GLOB dataFiles "./data/*")
foreach(data ${dataFiles})
        install(FILES ${data} DESTINATION ./data)
endforeach()

# CPack part
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Pacifism mode remake from Geometry Wars 2")
SET(CPACK_PACKAGE_VENDOR "LittleWhite")
SET(CPACK_PACKAGE_EXECUTABLES "PaciWar" "PaciWar")
set(CPACK_PACKAGE_VERSION_MAJOR ${PaciWar_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PaciWar_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PaciWar_VERSION_PATCH})
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
else()
    set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH} - ${PaciWar_VERSION_SHA}")
endif()

include(CPack)
