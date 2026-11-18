cmake_minimum_required(VERSION 3.14)

# Use Intel's compiler for C++ if found
find_program(ICPX_PATH icpx)
if(ICPX_PATH)
    message(STATUS "Intel icpx found. Using: ${ICPX_PATH} for C++ compilation")
    set(CMAKE_CXX_COMPILER ${ICPX_PATH})
    set(MKL_INTERFACE_LAYER "-lmkl_intel_lp64")
else()
    message(STATUS "Intel icx compiler not found! (Did you run source setvars.sh?) Falling back to default system compiler.")
    set(MKL_INTERFACE_LAYER "-lmkl_gf_lp64")
endif()

# Use Intel's compiler for C
find_program(ICX_PATH icx)
if (ICX_PATH)
    message(STATUS "Intel icx found. Using: ${ICX_PATH} for C compilation")
    set(CMAKE_C_COMPILER ${ICX_PATH})
endif()

project(Thesis-SuperRes LANGUAGES C CXX)

# Use C++17 or newer
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set output folders (same layout as Cpp-Project)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib) # For libSuperRes_lib.a
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib) # For *.so or *.dll
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin) # For executables (bin/main)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Include folders (all headers inside inc/ are automatically visible)
include_directories(
    $ENV{MKLROOT}/include
    ${OpenCV_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/inc
)

# Create STATIC extension library from your SR src files
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp src/*.c)
add_library(SuperRes_lib STATIC
    ${SRC_FILES}
)

# Link Intel's MKL (uses the interface layer detected above)
set(MKL_LIBS "${MKL_INTERFACE_LAYER} -lmkl_sequential -lmkl_core -lpthread -lm -ldl")

# Automatically add executables from app/ (replaces tests/ from Cpp-Project)
file(GLOB APP_FILES CONFIGURE_DEPENDS app/*.cpp)
foreach(APP_FILE ${APP_FILES})
    get_filename_component(APP_NAME ${APP_FILE} NAME_WE)

    add_executable(${APP_NAME} ${APP_FILE})

    # Order matters for static libraries: SuperRes_lib -> Cpp-Project_lib -> OpenCV -> MKL
    target_link_libraries(${APP_NAME}
        SuperRes_lib
        Cpp-Project_lib
        ${OpenCV_LIBS}
        ${MKL_LIBS}
    )
endforeach()