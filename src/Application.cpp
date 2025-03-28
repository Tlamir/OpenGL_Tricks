#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include"Renderer.hpp"

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


// Every cpp code runs in CPU
// 
// OpenGL operates like state machine
// 
// Vertex Buffer
// Blob of memory to push bytes , in GPU VRAM
// Vertex Buffer -> Drawcall(CPU)(Read from GPU VRAM Draw to screen) -> Tell GPU To draw (SHADER)
// 
// Vertex Attributes is an input variable to a shader that is supplied with per-vertex data. 
// In OpenGL core profile, they are specified as in variables in a vertex shader and are backed by a GL_ARRAY_BUFFER. 
// These variable can contain, for example, positions, normals or texture coordinates.
// A vertex is the combination of all the vertex attributes that belong together
// 
// Vertex shader called by each vertecies. (3 in Triangle)
// Fragment shader called by each pixels and colors. (too many times)
//
// All buffers should be unsingned integers
// 
// Debug break at OpenGL with asserts
// 
// Uniform move data from c++ to gpu
// Uniforms are set per draw
// Attributes are set per vertex
//
// Vertex Arrays
// 
// Size -> Bytes
// Count -> Element Count

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	// Set openGL profile to Core profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // In Core profile have to create VAO 

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(2);

	// Call glew after we have valid openGL context
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error initalize GLEW" << std::endl;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;
	{
		float position[] = {
			-0.5,-0.5f,0.0f,0.0f,
			0.5f,-0.5f,1.0f,0.0f,
			0.5f,0.5f,1.0f,1.0f,
			-0.5f,0.5f,0.0f,1.0f
		};

		// Index buffer

		unsigned int indecies[]{
			0,1,2,
			2,3,0
		};

		// Enable blending
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		// Vertex Array
		unsigned int vao;
		GLCall(glGenVertexArrays(1, &vao));
		GLCall(glBindVertexArray(vao));

		VertexArray va;

		// Define Vertex Buffer
		VertexBuffer vb(position, 4 * 4 * sizeof(float));
		unsigned int buffer;

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		va.Addbuffer(vb, layout);

		// Create projection matrix
		glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);

		// Define Index Buffer
		IndexBuffer ib(indecies, 6);
		unsigned int ibo;

		// Shader
		Shader shader("res/shaders/Shader.shader");
		shader.Bind();
		shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.2f, 1.0f);
		shader.SetUniformMat4f("u_MVP", proj);

		// Texture should match the texture slot
		Texture texture("res/textures/logo.png");
		texture.Bind();
		shader.SetUniform1i("u_Texture", 0);

		// UNBIND Everything
		va.Unbind();
		vb.Unbind();
		ib.Unbind();
		shader.UnBind();

		Renderer renderer;

		float r = 0.0f;
		float increment = 0.05f;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			renderer.Clear();

			// Bind Shader
			shader.Bind();
			shader.SetUniform4f("u_Color", r, 0.3f, 0.2f, 1.0f);

			// Draw Call
			renderer.Draw(va, ib, shader);

			// Color RED value change (r,g,b)
			if (r > 1.0f)
				increment = -0.05f;
			else if (r < 0.0f)
				increment = 0.05f;

			r += increment;

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}