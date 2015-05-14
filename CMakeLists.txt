cmake_minimum_required(VERSION 2.6)

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

add_executable(
        "PaciWar"
        ${source_files}
)

# Set new cmake module path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

# Look after SFML
if (MSYS OR MINGW) # Give CMake a little hint
	set(SFML_ROOT "./")
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
                set(TMP_NEED_COMPILE_SFML "true")
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
            if (CMAKE_SIZEOF_VOID_P EQUAL 8)
                set(TMP_ARCH "x86_64")
            elseif (CMAKE_SIZEOF_VOID_P EQUAL 4)
                set(TMP_ARCH "i686")
            else()
                set(TMP_ARCH "UNKNOWN")
                set(TMP_NEED_COMPILE_SFML TRUE)
            endif()

            set(TMP_TOOLSET "mingw-${TMP_ARCH}")
        endif()
    else()
        set(TMP_NEED_COMPILE_SFML TRUE)
    endif()

    # Try to compile
    if (TMP_NEED_COMPILE_SFML)
        message("SFML will be compiled")
        set(SFML_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/deps/SFML-2.3.source")
        add_subdirectory(${SFML_PREFIX} EXCLUDE_FROM_ALL)

        set(SFML_INCLUDE_DIR "${SFML_PREFIX}/include" PATH "Path to SFML headers")
        set(SFML_LIBRARY_DIR "${SFML_PREFIX}/lib" PATH "Path to SFML libraries")
    else()
        set(SFML_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/deps/SFML-2.3.bin")
        set(SFML_LIBRARY_DIR "${SFML_PREFIX}/lib-${TMP_TOOLSET}" PATH "Path to SFML libraries")
    endif()
    set(SFML_INCLUDE_DIR "${SFML_PREFIX}/include" PATH "Path to SFML headers")

    message("Link lib dir : ${SFML_LIBRARY_DIR}")
    link_directories(${SFML_LIBRARY_DIR})

    # Clean up after ourselves
    unset(TMP_TOOLSET)
    unset(TMP_ARCH)

    if (WIN32)
        set(SFML_LIBRARIES sfml-main sfml-system sfml-graphics sfml-window sfml-audio)
    else()
        set(SFML_LIBRARIES sfml-system sfml-graphics sfml-window sfml-audio)
    endif()
endif()

target_link_libraries(PaciWar ${SFML_LIBRARIES})
include_directories(${SFML_INCLUDE_DIR}
                    ./include/
                    ./src/)

# Installation
install(TARGETS PaciWar
        RUNTIME
        DESTINATION bin)

if (WIN32)
    file(GLOB dllFiles "${SFML_LIBRARY_DIR}/*.dll")
    foreach(dll ${dllFiles})
            install(FILES ${dll} DESTINATION bin)
    endforeach()
endif()

# Resources file installation
file(GLOB dataFiles "./data/*")
foreach(data ${dataFiles})
	install(FILES ${data} DESTINATION bin/data)
endforeach()

# CPack part
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Pacifism mode remake from Geometry Wars 2")
SET(CPACK_PACKAGE_VENDOR "LittleWhite")
SET(CPACK_PACKAGE_EXECUTABLES "PaciWar" "PaciWar")

include(CPack)
