//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//using namespace std;
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//
//int main() {
//	//Init GLFW Window
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	//Set A Window Parameter
//	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
//
//
//	//Detect Window
//	if (window == NULL) {
//		cout << "Failed to create GLFW window" << endl;
//		glfwTerminate();
//		return -1;
//	}
//
//	//Set WindwoContext As Now Procedure Context
//	glfwMakeContextCurrent(window);
//
//
//	//Init Glad
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	//Set View Size
//	glViewport(0, 0, 800, 600);
//
//	//Follow the Window Size Change
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//
//	//Renderer 
//	while (!glfwWindowShouldClose(window)) {
//		//Swap ARGB Buffer
//		glfwSwapBuffers(window);
//		//Detect Event(Such as KeyBoard¡¢Mouse)
//		glfwPollEvents();
//	}
//
//	//Release GLFW
//	glfwTerminate();
//	return 0;
//}
//
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//	glViewport(0, 0, width, height);
//}