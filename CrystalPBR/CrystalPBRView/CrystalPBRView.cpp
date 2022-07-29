﻿#include "Crystal/ThirdParty/glew-2.1.0/include/GL/glew.h"

#include "CrystalUI/CrystalUI/imgui.h"
#include "CrystalUI/CrystalUI/imgui_impl_glfw.h"
#include "CrystalUI/CrystalUI/imgui_impl_opengl3.h"
#include <stdio.h>
#include "CrystalUI/ThirdParty/glfw-3.3/include/GLFW/glfw3.h"

//#include "Crystal/ThirdParty/glew-2.1.0/include/GL/glew.h"

#include <iostream>

namespace {
    void glfw_error_callback(int error, const char* description)
    {
        fprintf(stderr, "Glfw Error %d: %s\n", error, description);
    }
}


int main() {
    if (!glfwInit()) {
        return false;
    }

    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    auto window = glfwCreateWindow(1280, 720, "Hello", NULL, NULL);
    glfwMakeContextCurrent(window);
    //	gl3wInit();

    const auto e = glewInit();
    if (e != GLEW_OK) {
        return false;
    }


    // Setup ImGui binding
    //ImGui_ImplGlfwGL3_Init(window, true);

    const char* glsl_version = "#version 130";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);


   // glfwSetScrollCallback(window, onWheel);
   // glfwSetMouseButtonCallback(window, onMouse);
   // glfwSetCursorPosCallback(window, onMouseMove);

   // glfwSetWindowCloseCallback(window, onClose);


    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

	while (!glfwWindowShouldClose(window)) {
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (ImGui::BeginMainMenuBar()) {
			ImGui::EndMainMenuBar();
		}

		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		int width, height;
		glfwGetWindowSize(window, &width, &height);
		//world->getRenderer()->render(*world->getCamera()->getCamera(), width, height);
		//const auto animations = world->getAnimations();
		//for (auto& a : animations) {
		//	a->step();
		//}

		glFlush();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
		glfwPollEvents();
    }

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();

	ImGui::DestroyContext();
	glfwTerminate();
}