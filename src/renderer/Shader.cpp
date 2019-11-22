#include <renderer/Shader.h>

Shader::Shader() {
}

GLuint Shader::CreateShader(const std::string source, GLenum type) {

	GLint _shader = glCreateShader(type);

	const GLchar* c_source = source.c_str();
	glShaderSource(_shader, 1, &c_source, NULL);
	glCompileShader(_shader);

	GLint success = 0;
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		GLint len = 0;
		glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &len);

		char errorLog[2048];
		glGetShaderInfoLog(_shader, len, 0, errorLog);

		printf("SHADER::%s::COMPILATION_ERROR(%d; %d):\n%s", ((type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT"), len, success, errorLog);

		glDeleteShader(_shader);
		return -1;
	}

	return _shader;
}

Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc) {
	vertex_shader = CreateShader(vertexSrc, GL_VERTEX_SHADER);
	if (vertex_shader == -1) {
		printf("SHADER::VERTEX::LOAD_FAILED");
		return;
	}
	fragment_shader = CreateShader(fragmentSrc, GL_FRAGMENT_SHADER);
	if (fragment_shader == -1) {
		printf("SHADER::FRAGMENT::LOAD_FAILED");
		return;
	}

	program_id = glCreateProgram();
	glAttachShader(program_id, vertex_shader);
	glAttachShader(program_id, fragment_shader);
}

Shader Shader::FromSources(const std::string& vertexSrc, const std::string& fragmentSrc) {
	return Shader(vertexSrc, fragmentSrc);
}

Shader Shader::FromFiles(const std::string& vertexPath, const std::string& fragmentPath) {
	std::ifstream vertexFile{ vertexPath };
	std::string vertexSrc{ std::istreambuf_iterator<char>(vertexFile), std::istreambuf_iterator<char>() };

	std::ifstream fragmentFile{ fragmentPath };
	std::string fragmentSrc{ std::istreambuf_iterator<char>(fragmentFile), std::istreambuf_iterator<char>() };

	Shader program = Shader(vertexSrc.c_str(), fragmentSrc.c_str());

	return program;
}

void Shader::Clear() {
	glDeleteProgram(program_id);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

//void Shader::SetUniformTexture(const std::string& name, const Texture& texture, const GLint& texture_unit) const {
//	texture.bind(GL_TEXTURE0 + texture_unit);
//	set_uniform_int(name, texture_unit);
//}

void Shader::SetUniformBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(program_id, name.c_str()), (int)value);
}

void Shader::SetUniformInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(program_id, name.c_str()), value);
}

void Shader::SetUniformFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(program_id, name.c_str()), value);
}

void Shader::SetUniformFloatArray(const std::string& name, const int size, const float* value) const
{
	glUniform1fv(glGetUniformLocation(program_id, name.c_str()), size, value);
}

void Shader::SetUniformDouble(const std::string& name, double value) const {
	glUniform1d(glGetUniformLocation(program_id, name.c_str()), value);
}

void Shader::SetUniformMat4(const std::string& name, const glm::mat4& matrix) const {
	glUniformMatrix4fv(glGetUniformLocation(program_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetUniformIVec2(const std::string& name, const glm::ivec2& vector) const {
	glUniform2i(glGetUniformLocation(program_id, name.c_str()), vector.x, vector.y);
}

void Shader::SetUniformVec2(const std::string& name, const glm::vec2& vector) const {
	glUniform2f(glGetUniformLocation(program_id, name.c_str()), vector.x, vector.y);
}

void Shader::SetUniformVec3(const std::string& name, const glm::vec3& vector) const {
	glUniform3f(glGetUniformLocation(program_id, name.c_str()), vector.x, vector.y, vector.z);
}

void Shader::SetUniformVec4(const std::string& name, const glm::vec4& vector) const {
	glUniform4f(glGetUniformLocation(program_id, name.c_str()), vector.x, vector.y, vector.z, vector.w);
}

void Shader::Link() {
	glLinkProgram(program_id);

	GLint isLinked = 0;
	glGetProgramiv(program_id, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program_id, maxLength, &maxLength, &infoLog[0]);

		glDeleteProgram(program_id);

		printf("GLSL Program Link Error: %s", &infoLog[0]);

		return;
	}
}

const void Shader::Use() const { glUseProgram(program_id); }

const GLuint Shader::Id() const { return program_id; }