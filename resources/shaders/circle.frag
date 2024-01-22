#version 330 core

in vec2 texCoordV;

layout (location = 0) out vec4 frag_color;

uniform vec2 center;
uniform float radius;
uniform vec3 color;

float circle(in vec2 _center, in float _radius, in vec2 xy)
{
    vec2 d = xy - _center;
    float sq = _radius * _radius;
    return 1.0 - smoothstep(0.99 * sq, 1.01 * sq, dot(d, d));
}

void main()
{
    frag_color = vec4(color, circle(center, radius, texCoordV));
}