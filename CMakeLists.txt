project(OpenGLFramework)

#Dependencies
set(DEPENDENCIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)
set(GLFW_DIR ${DEPENDENCIES_DIR}/GLFW)
set(GLAD_DIR ${DEPENDENCIES_DIR}/GLAD)
set(GLM_DIR ${DEPENDENCIES_DIR}/GLM)
set(STBIMG_DIR ${DEPENDENCIES_DIR}/stbimg)
set(MyGL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/MyGL)
set(ASSIMP_DIR ${DEPENDENCIES_DIR}/assimp)

set(MyGL_INCLUDES
    ${DEPENDENCIES_DIR}
    ${GLFW_DIR}/include
    ${GLAD_DIR}/include
    ${GLM_DIR}/glm
    ${STBIMG_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${MyGL_DIR}
    ${ASSIMP_DIR}/include
)

# Assimp
add_subdirectory(${ASSIMP_DIR})
set(ASSIMP_BUILD_DIR ${PROJECT_BINARY_DIR}/dependencies/assimp)
set(ASSIMP_CONFIG_LOCATION ${PROJECT_BINARY_DIR}/dependencies/assimp/include/assimp)
# Move config.h to include directory
file(COPY ${ASSIMP_CONFIG_LOCATION}/config.h DESTINATION ${ASSIMP_DIR}/include/assimp)

# GLFW
add_subdirectory(${GLFW_DIR})

# Export includes
set(MyGL_EXTERNAL_INCLUDES
    ${MyGL_INCLUDES}
    PARENT_SCOPE
)

#GLAD

set(GLAD_SOURCE_PATH ${GLAD_DIR}/src/glad.c)
set(GLAD_INCLUDE_PATH ${GLAD_DIR}/include)

add_library(glad STATIC ${GLAD_SOURCE_PATH})
target_include_directories(glad PRIVATE ${GLAD_INCLUDE_PATH})

#MyGL
file(GLOB MyGL_SOURCES ${MyGL_DIR}/*.cpp)

option(BUILD_STATIC "Build MyGL as a static library" ON)

if(BUILD_STATIC)
    message("------ Building MyGL Static ----")
    add_compile_definitions(BUILD_SHARED=0)
    add_library(MyGL STATIC
        ${MyGL_SOURCES}
        ${STBIMG_DIR}/stb_image.h
        )
else()
    message("---- Building MyGL Dynamic ----")
    message(FATAL_ERROR "Dynamic library not supported yet")
    add_compile_definitions(BUILD_SHARED=1)
    add_compile_definitions(DLLEXPORT)

    add_library(MyGL SHARED
        ${MyGL_SOURCES}
    )
    #set_target_properties(MyGL PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

endif()

target_include_directories(MyGL PUBLIC
    ${MyGL_INCLUDES}
)

#GCC
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    message("Using GCC")
    target_link_libraries(MyGL
        glfw
        glad
        Assimp::assimp
    )
    add_dependencies(MyGL Assimp::assimp glad glfw)
    #file(COPY ${GLFW_DIR}/lib-mingw-w64/glfw3.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)

#MSVC
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    message("Using MSVC")
    #Linking

    #Assimp
    #Check if debug or release
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Debug)
    endif()
    message("Build type: ${CMAKE_BUILD_TYPE}")
    # Find the library manually
    if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set(ASSIMP_LIB_DIR ${ASSIMP_BUILD_DIR}/${ASSIMP_LIB_INSTALL_DIR}/Debug)
    else()
        set(ASSIMP_LIB_DIR ${ASSIMP_BUILD_DIR}/${ASSIMP_LIB_INSTALL_DIR}/Release)
    endif()

    set(GLFW_LIB_PATH ${PROJECT_BINARY_DIR}/dependencies/GLFW/src/Debug/glfw3ddll.lib PARENT_SCOPE)

    target_link_libraries(MyGL
        glfw
        glad #GLAD
        ${ASSIMP_LIB_DIR}/*.lib #Link manually because cmake can't find it (assimp puts it inside ASSIMP_LIB_INSTALL_DIR)
    )
    add_dependencies(MyGL
        Assimp::assimp
        glad
        glfw
    )

    #Assimp congfig.h
    target_include_directories(MyGL PRIVATE
        ${ASSIMP_CONFIG_LOCATION}
    )
    #Export Libraries
    set(MyGL_Libraries
        MyGL
        glad
        glfw
        PARENT_SCOPE
    )

else()
    message(FATAL_ERROR "Compiler not compatible")
endif()