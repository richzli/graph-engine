#version 330 core

layout (location = 0) in vec2 position;

out vec2 texCoordV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    texCoordV = position;
    gl_Position = projection * view * model * vec4(position, 0.0, 1.0);
}