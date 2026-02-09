cmake_minimum_required(VERSION 3.16)
project(Halsu_LensEffects VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)

# Manual paths support
if(LIBOBS_INCLUDE_DIR AND LIBOBS_LIB)
    # LIBOBS_INCLUDE_DIR may contain semicolon-separated paths
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

add_library(Halsu_LensEffects MODULE
    plugin_main.cpp
)

target_link_libraries(Halsu_LensEffects PRIVATE ${LIBOBS_TARGET})

if(EXTRA_INCLUDES)
    target_include_directories(Halsu_LensEffects PRIVATE ${EXTRA_INCLUDES})
endif()

file(COPY Halsu_LensEffects.effect DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
