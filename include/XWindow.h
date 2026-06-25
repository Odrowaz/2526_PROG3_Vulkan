#pragma once

#include <string>
#include <functional>
#include "VulkanContext.h"

class XWindow
{
public:
    XWindow(int InWidth, int InHeight, const std::string& InTitle);
    ~XWindow();
    void Update(std::function<void(VkCommandBuffer)> DrawCallback);
    bool IsOpened() const;
    void SetTitle(const std::string& InTitle);
    float GetDeltaTime() const;
    void SetVSync(bool InEnabled);
    int GetWidth() const;
    int GetHeight() const;
    float GetAspectRatio() const;
    bool KeyPressed(int Key) const { return glfwGetKey(RawWindow, Key) == GLFW_PRESS; }
private:
    int Width;
    int Height;
    std::string Title;
    GLFWwindow* RawWindow;
    float DeltaTime;
};