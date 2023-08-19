#include "shader.hpp"

shader::shader(std::string vert_shader_name, std::string frag_shader_name) {
    compile_vert_shader(
        read_shader_file(vert_shader_name + ".vert").c_str()
    );
    compile_frag_shader(
        read_shader_file(frag_shader_name + ".frag").c_str()
    );

    create_program();
}

shader::~shader() {
    glDeleteShader(id);
}

unsigned int shader::get_id() const {
    return id;
}

void shader::use() const {
    glUseProgram(id);
}

void shader::set_bool(const std::string & name, bool value) const {
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void shader::set_int(const std::string & name, int value) const {
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void shader::set_float(const std::string & name, float value) const {
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void shader::set_vec2(const std::string & name, const glm::vec2 & value) const {
	glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
}

void shader::set_vec2(const std::string & name, float x, float y) const {
	glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);
}

void shader::set_vec3(const std::string & name, const glm::vec3 & value) const {
	glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
}

void shader::set_vec3(const std::string & name, float x, float y, float z) const {
	glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}

void shader::set_vec4(const std::string & name, const glm::vec4 & value) const {
	glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
}

void shader::set_vec4(const std::string & name, float x, float y, float z, float w) const {
	glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
}

void shader::set_mat2(const std::string & name, const glm::mat2 & value) const {
	glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void shader::set_mat3(const std::string & name, const glm::mat3 & value) const {
	glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void shader::set_mat4(const std::string & name, const glm::mat4 & value) const {
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

std::string shader::read_shader_file(std::string filename) {
    std::ifstream file("resources/shaders/" + filename);
    std::stringstream stream;

    stream << file.rdbuf();
    file.close();

    return stream.str();
}

void shader::compile_vert_shader(const char * shader_code) {
    vert_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert_shader, 1, &shader_code, nullptr);
    glCompileShader(vert_shader);

    int success;
    char info_log[512];
    glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vert_shader, 512, nullptr, info_log);
        throw std::runtime_error("failed to compile vertex shader");
    }
}

void shader::compile_frag_shader(const char * shader_code) {
    frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_shader, 1, &shader_code, nullptr);
    glCompileShader(frag_shader);

    int success;
    char info_log[512];
    glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(frag_shader, 512, nullptr, info_log);
        throw std::runtime_error("failed to compile fragment shader");
    }
}

void shader::create_program() {
    id = glCreateProgram();
    glAttachShader(id, vert_shader);
    glAttachShader(id, frag_shader);
    glLinkProgram(id);

    int success;
    char info_log[512];
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 512, nullptr, info_log);
    }

    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);
}