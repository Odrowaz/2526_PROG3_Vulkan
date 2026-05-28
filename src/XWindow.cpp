#include "XWindow.h"
#include "Common.h"

XWindow::XWindow(int InWidth, int InHeight, const std::string& InTitle)
    : Width(InWidth), Height(InHeight), Title(InTitle), DeltaTime(0.f)
{
    CHECK_DIE(glfwInit(), "GLFW Initialization");

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // No OpenGL context

	GLFWmonitor* Monitor = NULL; //windowed mode
	RawWindow = glfwCreateWindow(Width, Height, Title.c_str(), Monitor, NULL);
    CHECK_DIE(RawWindow, "GLFW Create Window");

    glfwSetWindowUserPointer(RawWindow, this);
    glfwSetFramebufferSizeCallback(RawWindow, [](GLFWwindow* w, int, int) {
        static_cast<XWindow*>(glfwGetWindowUserPointer(w))->Context.NotifyFramebufferResized();
    });

    Context.Init(RawWindow);
}

XWindow::~XWindow()
{
    Context.WaitIdle();
    Context.Cleanup();
    glfwDestroyWindow(RawWindow);
    glfwTerminate();
}

void XWindow::Update() 
{
    static float LastTime = glfwGetTime();
    float CurrentTime = glfwGetTime();
    DeltaTime = CurrentTime - LastTime;
    LastTime = CurrentTime;

	glfwPollEvents();
    Context.DrawFrame();
}

bool XWindow::IsOpened() const 
{
    return !glfwWindowShouldClose(RawWindow);
}

void XWindow::SetTitle(const std::string& InTitle)
{
    Title = InTitle;
    glfwSetWindowTitle(RawWindow, Title.c_str());
}

float XWindow::GetDeltaTime() const
{
    return DeltaTime;
}

void XWindow::SetVSync(bool InEnabled)
{
    // Note: This approach is no-more valid
    /*
    Control VSync: 0 = disable, 1 = enabled (default).
    int Value = InEnabled ? 1 : 0;
    glfwSwapInterval(Value);
    */
}

int XWindow::GetWidth() const
{
    return Width;
}

int XWindow::GetHeight() const
{
    return Height;
}
