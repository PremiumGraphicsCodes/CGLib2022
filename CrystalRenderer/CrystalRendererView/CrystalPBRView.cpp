#include "Crystal/ThirdParty/glew-2.1.0/include/GL/glew.h"

#include "CrystalUI/CrystalUI/imgui.h"
#include "CrystalUI/CrystalUI/imgui_impl_glfw.h"
#include "CrystalUI/CrystalUI/imgui_impl_opengl3.h"
#include <stdio.h>
#include "CrystalUI/ThirdParty/glfw-3.3/include/GLFW/glfw3.h"

#include "SkyBoxShader.h"
#include "PolygonShader.h"
#include "PBLightShader.h"

#include "CrystalRenderer/CrystalRenderer/IrradianceRenderer.h"

//#include "Crystal/ThirdParty/glew-2.1.0/include/GL/glew.h"

#include <iostream>

using namespace Crystal;
using namespace Crystal::Math;

namespace {
    void glfw_error_callback(int error, const char* description)
    {
        fprintf(stderr, "Glfw Error %d: %s\n", error, description);
    }

    UI::PolygonShader renderer;
	Shader::IrradianceRenderer irradianceRenderer;
	UI::SkyBoxShader cubeMapRenderer;
	UI::PBLightShader pbLightRenderer;
    Shader::GLObjectFactory factory;
    Graphics::Camera camera(Vector3df(0,0,1), Vector3df(0,0,0), Vector3df(0,1,0), 0.1, 10.0);

    void onInit()
    {
		renderer.build(factory);
		irradianceRenderer.build(factory);
		pbLightRenderer.build();
		cubeMapRenderer.build();
        //renderer.build(factory);
    }

    void onRender(const int width, const int height)
    {
		pbLightRenderer.render(camera, width, height);
		//cubeMapRenderer.render(camera, width, height);
        //renderer.render(camera, width, height);
    }

	bool isLeftDown;
	bool isRightDown;

	Vector2df toScreenCoord(GLFWwindow* window, const double x, const double y) {
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		const auto xx = x / (float)width;
		const auto yy = 1.0 - y / (float)height;
		return Vector2df(xx, yy);
	}

	Vector2df prevCoord(0, 0);

	void onMouse(GLFWwindow* window, int button, int action, int mods) {
		if (ImGui::IsMouseHoveringAnyWindow()) {
			return;
		}

		double x, y;
		glfwGetCursorPos(window, &x, &y);
		const auto& coord = toScreenCoord(window, x, y);
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			if (action == GLFW_PRESS) {
				prevCoord = coord;
				//canvas->onLeftButtonDown(coord);
				isLeftDown = true;
			}
			else if (action == GLFW_RELEASE) {
				//canvas->onLeftButtonUp(coord);
				isLeftDown = false;
			}
		}
		else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			if (action == GLFW_PRESS) {
				prevCoord = coord;
				//canvas->onRightButtonDown(coord);
				isRightDown = true;
			}
			else if (action == GLFW_RELEASE) {
				//canvas->onRightButtonUp(coord);
				isRightDown = false;
			}
		}
	}


	void onMouseMove(GLFWwindow* window, double xpos, double ypos)
	{
		const auto& coord = toScreenCoord(window, xpos, ypos);
		if (isLeftDown) {
			const auto diff = (coord - prevCoord) * 1.0f;
			camera.setEye(camera.getEye() + Vector3df(diff, 0.0));
			camera.setTarget(camera.getTarget() + Vector3df(diff, 0.0));
			prevCoord = coord;
			//canvas->onLeftDragging(coord);
		}
		else if (isRightDown) {
			const auto diff = prevCoord - coord;
			//const auto bb = world->getBoundingBox();
			const auto scale = 1.0;//glm::distance(bb.getMin(), bb.getMax()) * 0.1;

			const auto& matrix = camera.getRotationMatrix();
			const auto v = glm::transpose(Matrix3dd(matrix)) * Vector3dd(diff, 0.0);

			{
				const Vector3df t = v;
				const auto& eye = camera.getEye();
				const auto& target = camera.getTarget();
				const auto& up = camera.getUp();
				camera.lookAt(eye + t, target, up);
			}

			prevCoord = coord;
		}
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
	glfwSetMouseButtonCallback(window, onMouse);
	glfwSetCursorPosCallback(window, onMouseMove);

   // glfwSetWindowCloseCallback(window, onClose);


    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    onInit();

	while (!glfwWindowShouldClose(window)) {
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("Save")) {

				}
				if (ImGui::MenuItem("Load")) {

				}

				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		int width, height;
		glfwGetWindowSize(window, &width, &height);

        onRender(width, height);
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