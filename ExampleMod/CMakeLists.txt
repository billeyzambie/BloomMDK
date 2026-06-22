# CMakeList.txt : CMake project for ExampleMod, include source and define
# project specific logic here.


set(BLOOM_API_DIR "${CMAKE_SOURCE_DIR}/bloomapi")

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCHITECTURE "x64")
else()
    set(ARCHITECTURE "x86")
endif()

set(BLOOM_LIB "${BLOOM_API_DIR}/bin/${CMAKE_BUILD_TYPE}${ARCHITECTURE}/LawnProject.lib")

set(BLOOM_INCLUDE "${BLOOM_API_DIR}/include/")

include_directories("${BLOOM_INCLUDE}/Bloom/")
include_directories("${BLOOM_INCLUDE}/Lawn/")
include_directories("${BLOOM_INCLUDE}/SexyAppFramework/")

set(SEXY_USE_IMGUI ON)
set(SEXY_USE_CONTROLLER ON)
set(SEXY_CRASH_HANDLER ON)
find_package(SDL3 CONFIG REQUIRED)
find_package(ZLIB REQUIRED)
find_package(OpenAL CONFIG REQUIRED)
find_package(Ogg CONFIG REQUIRED)
find_package(Vorbis CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Freetype REQUIRED)
if (SEXY_CRASH_HANDLER)
find_package(cpptrace CONFIG REQUIRED)
endif()
find_package(CURL CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_SOURCE_DIR}/thirdparty/src/*.c"
    "${CMAKE_SOURCE_DIR}/thirdparty/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/thirdparty/src/*.h"
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC 
    ${BLOOM_LIB}
    SDL3::SDL3
    ZLIB::ZLIB
    OpenAL::OpenAL
    glm::glm
    Ogg::ogg
    Freetype::Freetype
    Vorbis::vorbisfile
    Vorbis::vorbis
    $<$<BOOL:${SEXY_CRASH_HANDLER}>:cpptrace::cpptrace>
    CURL::libcurl
    #ImageLib
    #PakLib
)
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(THIRDPARTY_DIR "${CMAKE_SOURCE_DIR}/thirdparty/x64")
else()
    set(THIRDPARTY_DIR "${CMAKE_SOURCE_DIR}/thirdparty/x86")
endif()

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC
        bass.lib
        avcodec.lib
        avdevice.lib
        avformat.lib
        avutil.lib
        swresample.lib
        swscale.lib
    )

elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(AVCODEC REQUIRED libavcodec)
    pkg_check_modules(AVDEVICE REQUIRED libavdevice)
    pkg_check_modules(AVFORMAT REQUIRED libavformat)
    pkg_check_modules(AVUTIL REQUIRED libavutil)
    pkg_check_modules(SWRESAMPLE REQUIRED libswresample)
    pkg_check_modules(SWSCALE REQUIRED libswscale)

    target_include_directories(${PROJECT_NAME} PUBLIC
        ${AVCODEC_INCLUDE_DIRS}
        ${AVDEVICE_INCLUDE_DIRS}
        ${AVFORMAT_INCLUDE_DIRS}
        ${AVUTIL_INCLUDE_DIRS}
        ${SWRESAMPLE_INCLUDE_DIRS}
        ${SWSCALE_INCLUDE_DIRS}
    )

    target_link_libraries(${PROJECT_NAME} PUBLIC
        ${AVCODEC_LIBRARIES}
        ${AVDEVICE_LIBRARIES}
        ${AVFORMAT_LIBRARIES}
        ${AVUTIL_LIBRARIES}
        ${SWRESAMPLE_LIBRARIES}
        ${SWSCALE_LIBRARIES}
    )

    find_library(BASS_LIBRARY NAMES bass)
    if(BASS_LIBRARY)
        target_link_libraries(${PROJECT_NAME} PUBLIC ${BASS_LIBRARY})
    else()
        message(WARNING "BASS library not found by CMake! Falling back to linking dynamically to 'bass'.")
        target_link_libraries(${PROJECT_NAME} PUBLIC bass)
    endif()
endif()

target_link_directories(${PROJECT_NAME} PUBLIC
    ${THIRDPARTY_DIR}
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:NDEBUG>

    # SAF specific
    USE_OGG_LIB
    SEXY_USE_OPENGL
    SEXY_USE_SDL3_RENDERER
)

if(SEXY_USE_CONTROLLER)
    target_compile_definitions(${PROJECT_NAME} PUBLIC SEXY_USE_CONTROLLER)
endif()

if(SEXY_USE_IMGUI)
    target_compile_definitions(${PROJECT_NAME} PUBLIC SEXY_USE_IMGUI)
endif()

if(SEXY_CRASH_HANDLER AND SEXY_USE_IMGUI)
    target_compile_definitions(${PROJECT_NAME} PUBLIC SEXY_CRASH_HANDLER)
endif()


if (CMAKE_SIZEOF_VOID_P EQUAL 8)
target_compile_definitions(${PROJECT_NAME} PUBLIC
    SEXY_IS_X64
)
else ()
target_compile_definitions(${PROJECT_NAME} PUBLIC
    SEXY_IS_X86
)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/thirdparty/src"
)