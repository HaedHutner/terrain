#ifndef _SHADER_H
#define _SHADER_H

#include <vector>
#include <fstream>

#include <glad\glad.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <string>

class Shader {
private:
	GLuint program_id;

	GLuint vertex_shader;
	GLuint fragment_shader;

	static GLuint CreateShader(const std::string source, GLenum type);

	Shader(const std::string& vertexSrc, const std::string& fragmentSrc);

public:

	Shader();

	static Shader FromSources(const std::string& vertexSrc, const std::string& fragmentSrc);

	static Shader FromFiles(const std::string& vertexPath, const std::string& fragmentPath);

	// void SetUniformTexture(const std::string& name, const Texture& texture, const GLint& texture_unit) const;

	void SetUniformBool(const std::string& name, bool value) const;

	void SetUniformInt(const std::string& name, int value) const;

	void SetUniformFloat(const std::string& name, float value) const;

	void SetUniformDouble(const std::string& name, double value) const;

	void SetUniformMat4(const std::string& name, const glm::mat4& matrix) const;

	void SetUniformIVec2(const std::string& name, const glm::ivec2& vector) const;

	void SetUniformVec2(const std::string& name, const glm::vec2& vector) const;

	void SetUniformVec3(const std::string& name, const glm::vec3& vector) const;

	void SetUniformVec4(const std::string& name, const glm::vec4& vector) const;

	void Link();

	const void Use() const;

	void Clear();

	const GLuint Id() const;
};

#endif // !_SHADER_H
