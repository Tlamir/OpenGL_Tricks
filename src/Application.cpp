#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
// Every cpp code done in CPU
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

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	// Error handling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char)); // Alloca allocate memory on stack dinamicly
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex " : "fragment ") << " shader! " << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	// Link both shader
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

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

	float position[12] = {
		-0.2f, -0.2f,
		0.0f, 0.2f,
		0.2f, -0.2f,
		0.2f,-0.2f,
		0.4f,0.2,
		0.6,-0.2f
	};

	// Define Vertex Buffer
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), position, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	std::string vertexShader =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec4 position;"
		"\n"
		"void main()\n"
		"{\n"
		"	gl_Position = position;\n"
		"}\n";

	std::string fragmentShader =
		"#version 330 core \n"
		"\n"
		"layout(location = 0) out vec4 color;"
		"\n"
		"\n"
		"void main()\n"
		"{\n"
		" color = vec4(0.0,1.0,0.0,1.0);\n"  // r g b a
		"}\n";

	unsigned int shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw without index buffer
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Draw with index buffer


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteProgram(shader);

	glfwTerminate();
	return 0;
}