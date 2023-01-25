#version 330 core

layout (location = 0) in vec3 aVertex;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexel;

out vec3 vert_color;
out vec2 texel_cord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aVertex, 1.f);
    vert_color = aColor;
    texel_cord = aTexel;
}
