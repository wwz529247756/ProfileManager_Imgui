#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <windows.h>
#include "profilewindow.h"

int main( int argc, char** argv )
{
    // HWND hWnd = GetConsoleWindow();
    // ShowWindow(hWnd, SW_HIDE);

    if ( !glfwInit() )
        return 1;

    const char * glsl_version = "#version 130";

    GLFWwindow * window = glfwCreateWindow(1280, 720, "OneFLOW GLFW+OpenGL3 test", NULL, NULL);
    if ( window == NULL )
        return 1;
    glfwMakeContextCurrent( window );
    glfwSwapInterval(1); // Enable vsync

    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    ImFont *font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\msyh.ttc",
        20.0f, nullptr, io.Fonts->GetGlyphRangesChineseFull());
    
    ImGui_ImplGlfw_InitForOpenGL( window, true );
    ImGui_ImplOpenGL3_Init(glsl_version);

    ProfileWindow proWin;

    while ( !glfwWindowShouldClose( window ) )
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();
        proWin.Draw();
        ImGui::ShowDemoWindow();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow( window );
    glfwTerminate();

    return 0;
}