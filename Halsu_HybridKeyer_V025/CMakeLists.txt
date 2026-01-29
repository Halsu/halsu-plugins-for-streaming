cmake_minimum_required(VERSION 3.16)
project(Halsu_HybridKeyer_V025 VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)

# Manual paths support
if(LIBOBS_INCLUDE_DIR AND LIBOBS_LIB)
    add_library(libobs_manual UNKNOWN IMPORTED)
    set_target_properties(libobs_manual PROPERTIES
        IMPORTED_LOCATION "${LIBOBS_LIB}"
        INTERFACE_INCLUDE_DIRECTORIES "${LIBOBS_INCLUDE_DIR}"
    )
    set(LIBOBS_TARGET libobs_manual)
else()
    find_package(libobs REQUIRED)
    set(LIBOBS_TARGET OBS::libobs)
endif()

add_library(Halsu_HybridKeyer_V025 MODULE
    plugin_main.cpp
)

target_link_libraries(Halsu_HybridKeyer_V025 PRIVATE ${LIBOBS_TARGET})

if(EXTRA_INCLUDES)
    target_include_directories(Halsu_HybridKeyer_V025 PRIVATE ${EXTRA_INCLUDES})
endif()

file(COPY Halsu_HybridKeyer_V025.effect DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
