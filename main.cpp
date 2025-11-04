// put this before any Apple OpenGL includes to silence warnings
#define GL_SILENCE_DEPRECATION

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

int main()
{
    glfwInit();

    // ---- macOS: request a Core profile context (required) ----
#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    // ----------------------------------------------------------

    GLFWwindow *window = glfwCreateWindow(800, 600, "My ImGui App", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // Init ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);

    // Match GLSL to the context we requested above:
    ImGui_ImplOpenGL3_Init("#version 150"); // (GLSL 1.50 == OpenGL 3.2 Core)
    // Alternatively: ImGui_ImplOpenGL3_Init("#version 150 core");

    ImGui::StyleColorsDark();



    // App variables
    bool show_demo = false;
    float value = 0.5f;
    int counter = 0;

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Your UI
        ImGui::Begin("Control Panel");
        ImGui::Text("Hello from Dear ImGui!");
        ImGui::SliderFloat("Value", &value, 0.0f, 1.0f);
        if (ImGui::Button("Click Me"))
            counter++;
        ImGui::SameLine();
        ImGui::Text("Counter: %d", counter);
        ImGui::Checkbox("Show Demo", &show_demo);
        ImGui::End();

        if (show_demo)
            ImGui::ShowDemoWindow();

        // Render
        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}