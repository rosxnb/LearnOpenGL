#version 330 core

layout (location = 0) in vec3 aVertex;
layout (location = 1) in vec2 aTexel;

out vec2 texel_cord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aVertex, 1.f);
    texel_cord = aTexel;
}
