#pragma once

#include<GL/glew.h>
#include<iostream>

#include"VertexArray.hpp"
#include"IndexBuffer.hpp"
#include"Shader.hpp"

// __debugbreak() MSVC only
#define ASSERT(x) if(!(x)) __debugbreak(); 
// Clear glerror then logcall
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x,__FILE__,__LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
	// Things we need for Draw Call
	// Vertex Array , Index Buffer , Shader
	// Vertex Buffer bound to Vertex Array

	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

private:

};