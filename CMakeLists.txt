cmake_minimum_required(VERSION 3.5)
project(on1four_engine VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Vulkan REQUIRED)

# add external libraries
add_subdirectory(thirdparty/glm)
add_subdirectory(thirdparty/glfw)

set(SOURCES
    src/core/engine.cpp
    src/core/layer/layer.cpp
    src/core/window.cpp

    src/graphics/renderer.cpp

    src/drivers/vulkan/vulkan_instance.cpp
    src/drivers/vulkan/vulkan_logging.cpp
    src/drivers/vulkan/vulkan_queue_family.cpp
    src/drivers/vulkan/vulkan_device.cpp
    src/drivers/vulkan/vulkan_swapchain.cpp
    src/drivers/vulkan/vulkan_frame.cpp
    src/graphics/vulkan/vulkan_pipeline.cpp


    src/utils/shader.cpp
)

#file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp,${PROJECT_SOURCE_DIR}/src/*/*.cpp, ${PROJECT_SOURCE_DIR}/src/*/*/*.cpp )

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_compile_definitions(${PROJECT_NAME} PRIVATE ON1F_EXPORT)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        glm
        glfw
        ${Vulkan_INCLUDE_DIRS}
    PRIVATE

)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        glm
        glfw
        ${Vulkan_LIBRARIES}
    PRIVATE

)
#link_directories(${VULKAN_PATH}/Bin;${VULKAN_PATH}/Lib32;)
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/w4251")

target_link_directories(${PROJECT_NAME} 
    PUBLIC
    glfw
    ${Vulkan_LIBRARIES}
)

target_precompile_headers(on1four_engine PUBLIC include/of_pch.h)




# set_target_properties(on1four_engine PROPERTIES
#     IMPORTED_LOCATION "${DEPENDENCIES_DIR}/on1four_engine/bin/Debug/on1four_engine.dll"
#     IMPORTED_IMPLIB "${DEPENDENCIES_DIR}/on1four_engine/lib/Debug/on1four_engine.lib"
#     INTERFACE_INCLUDE_DIRECTORIES "${DEPENDENCIES_DIR}/on1four_engine/include"
# )



#file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp" "src/*/*/*.cpp")



#set(source_dir "${PROJECT_SOURCE_DIR}/src/")
#file(
#    GLOB
#    source_files
#    "${source_dir}/engine.cpp"
#)

# option(ENABLE_PCH "enable pre-compiled headers" ON)
# if(ENABLE_PCH)
#    list(APPEND SOURCES src/of_pch.cpp)
# endif()







#-------------------Editor
# set(BUILD_EDITOR OFF)
# # Add the editor source files
# if(BUILD_EDITOR)
# add_executable(editor
#     src/tools/editor/editor.cpp
#     src/drivers/vulkan/vulkan_instance.cpp
#     src/graphics/vulkan/vulkan_renderer.cpp
# )
# endif()
#-------------------------