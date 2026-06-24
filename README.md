# Vulkan Renderer - Coursework Project

A C++/Vulkan renderer started as coursework at AIV, originally provided by the instructor.

## My contribution

Building on the base provided, I implemented:

- **Texture mapping**: loaded images via `stb_image`, created Vulkan images with staging buffer, layout transitions, and image views; sampled in fragment shader via descriptor sets
- **Material system**: `Material` class manages descriptor sets binding multiple textures to a pipeline
- **Model Pipeline**: dedicated Vulkan pipeline for OBJ models with UVs, normals, depth testing, and correct CCW winding
- **Lighting (Phong)**: ambient + diffuse (Lambert) + specular computed in the fragment shader, with camera position passed via push constants
- **Push Constants**: extended the existing push constant block to also pass camera position to the fragment shader (used for specular calculation)
- **Camera**: perspective `Camera` class with WASD + arrow key movement and rotation, aspect ratio updated on window resize
- **Multiple objects in scene**: two independent `GameObject` instances (`stormtrooper`, `suzanne`) with separate positions
- **VSync toggle**: runtime toggle with the V key via `SetVSync`
- **Delta time / FPS counter**: improved frame timing display in the window title
- **Code restructuring**: split the original monolithic file into focused classes (`VulkanContext`, `VulkanPipeline`, `XWindow`, `Mesh`, `Texture`, `Material`, `Camera`, `GameObject`, `ObjLoader`), with CMake automating `.spv` shader compilation

> Work in progress — some parts are still being moved into their proper abstractions and may be partially hardcoded.

## Tech

- **Language:** C++
- **Graphics API:** Vulkan
- **Build:** CMake + Conan
- **Libraries:** GLM, GLFW, stb_image

## Note

This is a fork of the instructor's base repository (`aiv01/2526_PROG3_Vulkan`). The original provided only a minimal single-file setup rendering a obj file with normals as colors, with no texturing. Everything listed above was added on top of that foundation.

## Setup (VS Code)

In `.vscode/settings.json`:
```json
{
    "cmake.configureSettings": {
        "CMAKE_PROJECT_TOP_LEVEL_INCLUDES": "./conan_provider.cmake"
    },
    "cmake.environment": {
        "VULKAN_SDK": "<path-to-vulkan-sdk>"
    }
}
```
