#pragma once
#include <GL/glew.h>

#include <GLFW/glfw3.h>  

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class IndexBuffer
{
private:
	unsigned int m_rendererID;
	unsigned int m_Count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void unbind() const;

	void setData(const unsigned int* data, unsigned int count);
	inline unsigned int GetCount() const { return m_Count; }
};