#pragma once 

#include <vector>
#include <gl/glew.h>
#include "Renderer.hpp"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GeSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector< VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout()
		: m_Stride(0) {
	}

	template<typename T>
	void Push(unsigned int count)
	{
		//static_assert(false);
		static_assert(sizeof(T) == 0, "Unsupported type in VertexBufferLayout::Push.");
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back(VertexBufferElement{ GL_FLOAT,count,GL_FALSE });
		m_Stride += count * VertexBufferElement::GeSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int >(unsigned int count)
	{
		m_Elements.push_back(VertexBufferElement{ GL_UNSIGNED_INT,count,GL_FALSE });
		m_Stride += count * VertexBufferElement::GeSizeOfType(GL_UNSIGNED_INT);

	}

	template<>
	void Push<unsigned char >(unsigned int count)
	{
		m_Elements.push_back(VertexBufferElement{ GL_UNSIGNED_BYTE,count,GL_TRUE });
		m_Stride += count * VertexBufferElement::GeSizeOfType(GL_UNSIGNED_BYTE);

	}

	inline const std::vector<VertexBufferElement> GetElements() const& { return  m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};