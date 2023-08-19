#pragma once

#include "../common.hpp"

class shader {
public:
    shader(std::string vert_shader_file, std::string frag_shader_file);
    ~shader();

    unsigned int get_id() const;

    void use() const;
	void set_bool(const std::string & name, bool value) const;
	void set_int(const std::string & name, int value) const;
	void set_float(const std::string & name, float value) const;
	void set_vec2(const std::string & name, const glm::vec2 & value) const;
	void set_vec2(const std::string & name, float x, float y) const;
	void set_vec3(const std::string & name, const glm::vec3 & value) const;
	void set_vec3(const std::string & name, float x, float y, float z) const;
	void set_vec4(const std::string & name, const glm::vec4 & value) const;
	void set_vec4(const std::string & name, float x, float y, float z, float w) const;
	void set_mat2(const std::string & name, const glm::mat2 & value) const;
	void set_mat3(const std::string & name, const glm::mat3 & value) const;
	void set_mat4(const std::string & name, const glm::mat4 & value) const;
private:
    unsigned int id;
    unsigned int vert_shader, frag_shader;

    static std::string read_shader_file(std::string filename);

    void compile_vert_shader(const char * shader_code);
    void compile_frag_shader(const char * shader_code);

    void create_program();
};