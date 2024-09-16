#version 330 core

in vec2 texCoordV;

layout (location = 0) out vec4 frag_color;

uniform vec2 center;
uniform float radius;
uniform vec4 color;

uniform bool has_input_color;
uniform vec4 input_color;

float circle(in vec2 _center, in float _radius, in vec2 xy)
{
    vec2 d = xy - _center;
    float sq = _radius * _radius;
    return 1.0 - smoothstep(0.99 * sq, 1.01 * sq, dot(d, d));
}

void main()
{
    frag_color = color * vec4(1.0, 1.0, 1.0, circle(center, radius, texCoordV));
}