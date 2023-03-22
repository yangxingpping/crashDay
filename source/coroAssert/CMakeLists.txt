# Adds convenience methods, see cmake/cleanCppExtensions.cmake
include(cleanCppExtensions)

# Creates options to turn on sanitizers, see cmake/sanitizers.cmake
include(sanitizers)

include_directories(..)

# Enable helpfull warnings and C++14 for all files
if(MSVC)
    add_compile_options(/std:c++20 /W3 /WX )
else()
    add_compile_options(-std=c++20 -fcoroutines -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wunused -pedantic)
endif()

# configure version.cpp.in with selected version
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/../version.cpp.in"
  "${CMAKE_CURRENT_BINARY_DIR}/version.cpp"
  )



#------------------------------------------------------------------------------
# Libraries dependencies
find_package (Threads REQUIRED) #threading


#-------------------------------------------------------------------------------
# exampleApp executable setup

set(ICON_RESOURCE "")
if(WIN32) #windows icon resource file, provided from /packaging directory
    set(ICON_RESOURCE "${PROJECT_BINARY_DIR}/exampleApp.icon.rc")
elseif (APPLE) #osx icon ressource file, provided from /packaging directory
    set(ICON_RESOURCE "${PROJECT_SOURCE_DIR}/packaging/exampleApp.icns")
endif()

add_executable(coroAssert MACOSX_BUNDLE
    ${ICON_RESOURCE}
    ${CMAKE_CURRENT_BINARY_DIR}/version.cpp
    SomeClass.cpp
    SomeClass.h
    main.cpp)
add_dependencies(coroAssert versionFileTouchForRebuild) # We want precise time of build in version
target_include_directories(coroAssert PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries (coroAssert PRIVATE Threads::Threads PRIVATE asio)


install(TARGETS coroAssert
    BUNDLE DESTINATION "."
    RUNTIME DESTINATION bin)

# Using macro from cmake/cleanCpppExtensions.cpp included on the top
# Provides exampleApp-run and exampleApp-dbg
addRunAndDebugTargets(coroAssert)

# short convenience target from cmake/cleanCpppExtensions.cpp
#add_custom_target(run DEPENDS coroAssert-run)

#-------------------------------------------------------------------------------
# Copy MINGW needed libraries for building on windows

if(MINGW)
    message(STATUS "MinGW detected")
    get_filename_component(GCC_PATH ${CMAKE_C_COMPILER} PATH)
    if(${GCC_PATH} MATCHES "mingw64/bin")
        set(libgcc "libgcc_s_seh-1.dll") #64bit
        message(STATUS "  64bit dlls is building")
    else()
        set(libgcc "libgcc_s_dw2-1.dll") #32bit
        message(STATUS "  32bit dlls is building")
    endif()

    install(FILES ${GCC_PATH}/${libgcc}
        ${GCC_PATH}/libwinpthread-1.dll
        ${GCC_PATH}/libstdc++-6.dll
        DESTINATION ./bin/
    )
endif(MINGW)


#------------------------------------------------------------------------------
# Other MISC targets



