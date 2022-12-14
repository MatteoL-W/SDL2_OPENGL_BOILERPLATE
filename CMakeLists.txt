# Cmake version 3.11 in for FetchContent (glm)
cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(project)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set directory paths
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# /////////////////////////////////////////////////////////////////////////////
# /////////////////////////////////// FILES ///////////////////////////////////
# /////////////////////////////////////////////////////////////////////////////

# Create executable
set(TARGET_NAME ${PROJECT_NAME})
add_executable(${TARGET_NAME})

# Get source files
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*")

# Link files to project target
target_sources(${TARGET_NAME} PRIVATE ${SRC_FILES})
target_include_directories(${TARGET_NAME} PRIVATE "src/")

# Enable C++17
set_target_properties(${TARGET_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        )

# Enable good warnings
if (MSVC)
    target_compile_options(${TARGET_NAME} PRIVATE /W3)
else()
    target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors -O2)
endif()

# Set the project folder
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER ${PROJECT_NAME})

# Set the folder where the executable will be created
set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# /////////////////////////////////////////////////////////////////////////////
# //////////////////////////////// LIBRAIRIES /////////////////////////////////
# /////////////////////////////////////////////////////////////////////////////

# Include GLM
include(${CMAKE_DIR}/LinkGLM.cmake)
LinkGLM(${TARGET_NAME} PRIVATE)

# Include OpenGL
find_package(OpenGL REQUIRED)
if (OpenGL_FOUND)
    target_include_directories(${TARGET_NAME} PRIVATE ${OPENGL_INCLUDE_DIRS})
    target_link_libraries(${TARGET_NAME} ${OPENGL_LIBRARIES})
else()
    message(FATAL_ERROR "OpenGL was not found on the system")
endif()

# Include SDL2
if (WIN32)
    #SDL2 Includes / Assumed that SDL2 lib files are installed on the Compiler
    set(SDL2_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/lib/SDL2-2.0.20/x86_64-w64-mingw32/include)
    set(SDL2IMAGE_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/lib/SDL2_image-2.0.5/x86_64-w64-mingw32/include)
    set(SDL2TTF_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/lib/SDL2_ttf-2.0.18/x86_64-w64-mingw32/include)
    set(SDL2MIXER_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/lib/SDL2_mixer-2.0.4/x86_64-w64-mingw32/include)
else ()
    # On linux (https://gitlab.com/aminosbh/sdl2-cmake-modules.git)
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

    find_package(SDL2 REQUIRED)
    target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

    find_package(SDL2_image REQUIRED)
    target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${SDL2_IMAGE_LIBRARIES})

    find_package(SDL2_ttf REQUIRED)
    target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_TTF_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${SDL2_TTF_LIBRARIES})

    find_package(SDL2_mixer REQUIRED)
    target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_MIXER_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${SDL2_MIXER_LIBRARIES})
endif ()

target_include_directories(${TARGET_NAME} PUBLIC ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS})

if (UNIX)
    target_link_libraries(${TARGET_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2MIXER_LIBRARIES})
    target_link_libraries(${TARGET_NAME} -ldl -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer)
endif ()

if (WIN32)
    # MinGW and SDL2 flags
    target_link_libraries(${TARGET_NAME} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lglu32 -lopengl32)

    # Duplicate libraries in bin/ (build a functional .exe on windows!)
#    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
#            "${PROJECT_SOURCE_DIR}/lib/SDL2-2.0.20/x86_64-w64-mingw32/lib/libSDL2.dll.a"
#            "${PROJECT_SOURCE_DIR}/lib/SDL2-2.0.20/x86_64-w64-mingw32/lib/libSDL2main.a"
#
#            "${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.5/x86_64-w64-mingw32/bin/SDL2_image.dll"
#            "${PROJECT_SOURCE_DIR}/lib/SDL2_ttf-2.0.18/x86_64-w64-mingw32/lib/libSDL2_ttf.a"
#            "${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.5/x86_64-w64-mingw32/lib/libSDL2_image.a"
#            "${PROJECT_SOURCE_DIR}/lib/SDL2_mixer-2.0.4/x86_64-w64-mingw32/bin/SDL2_mixer.dll"
#            "${PROJECT_SOURCE_DIR}/lib/SDL2_mixer-2.0.4/x86_64-w64-mingw32/lib/libSDL2_mixer.dll.a"
#            "${PROJECT_SOURCE_DIR}/lib/SDL2_mixer-2.0.4/x86_64-w64-mingw32/lib/libSDL2_mixer.a"
#
#            "${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.5/x86_64-w64-mingw32/bin/libpng16-16.dll"
#            "${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.5/x86_64-w64-mingw32/bin/libjpeg-9.dll"
#            "${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.5/x86_64-w64-mingw32/bin/zlib1.dll"
#            "${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.5/x86_64-w64-mingw32/bin/libtiff-5.dll"
#            "${PROJECT_SOURCE_DIR}/lib/SDL2_image-2.0.5/x86_64-w64-mingw32/bin/libwebp-7.dll"
#
#            "${PROJECT_SOURCE_DIR}/lib/SDL2_mixer-2.0.4/x86_64-w64-mingw32/bin/libFLAC-8.dll"
#            "${PROJECT_SOURCE_DIR}/lib/SDL2_mixer-2.0.4/x86_64-w64-mingw32/bin/libmodplug-1.dll"
#            "${PROJECT_SOURCE_DIR}/lib/SDL2_mixer-2.0.4/x86_64-w64-mingw32/bin/libmpg123-0.dll"
#            "${PROJECT_SOURCE_DIR}/lib/SDL2_mixer-2.0.4/x86_64-w64-mingw32/bin/libogg-0.dll"
#            "${PROJECT_SOURCE_DIR}/lib/SDL2_mixer-2.0.4/x86_64-w64-mingw32/bin/libopus-0.dll"
#            "${PROJECT_SOURCE_DIR}/lib/SDL2_mixer-2.0.4/x86_64-w64-mingw32/bin/libopusfile-0.dll"
#            "${PROJECT_SOURCE_DIR}/lib/SDL2_mixer-2.0.4/x86_64-w64-mingw32/bin/libvorbis-0.dll"
#            "${PROJECT_SOURCE_DIR}/lib/SDL2_mixer-2.0.4/x86_64-w64-mingw32/bin/libvorbisfile-3.dll"
#            $<TARGET_FILE_DIR:${TARGET_NAME}>
#            )
endif ()


# Copy assets folder after a build
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets/
        $<TARGET_FILE_DIR:${TARGET_NAME}>/assets
        )