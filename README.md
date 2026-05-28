# OpenGL Playground
Project for teaching Hardware Accelerated Graphics with Vulkan

## VSCode IDE

In `.vscode/settings.json`
```
{
    "cmake.configureSettings": {
        "CMAKE_PROJECT_TOP_LEVEL_INCLUDES": "./conan_provider.cmake"
    },
    "cmake.environment": {
        "VULKAN_SDK": "<path-to-vulkan-sdk>"
    }
}
```