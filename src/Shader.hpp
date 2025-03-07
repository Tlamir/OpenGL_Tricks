#pragma once 
#include <string>
#include <unordered_map>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	// Caching for uniforms
	std::unordered_map<std::string, int> m_UniformLocationnCache;

public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void UnBind() const;


	// Set uniforms
	void SetUniform4f(const std::string& name,float v0,float v1,float f2,float f3);
private:
	ShaderProgramSource ParseShader(const std::string& fillepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	unsigned int GetUniformLoaction(const std::string& name);
};

