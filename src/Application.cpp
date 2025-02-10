#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
// Every cpp code done in CPU
// OpenGL operates like state machine
// Vertex Buffer
// Blob of memory to push bytes , in GPU VRAM
// Vertex Buffer -> Drawcall(CPU)(Read from GPU VRAM Draw to screen) -> Tell GPU To draw (SHADER)
int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// Call glew after we have valid openGL context
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error initalize GLEW" << std::endl;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	float position[6] = {
		-0.5f, -0.5f,
		0.0f, 0.5f,
		0.5f, -0.5f
	};

	// Define Vertex Buffer
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float),position,GL_STATIC_DRAW);

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{

			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);
			
			// Draw without index buffer
			glDrawArrays(GL_TRIANGLES, 0, 3);
			// Draw with index buffer
			

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}

	glfwTerminate();
	return 0;
}