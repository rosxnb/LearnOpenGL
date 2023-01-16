#version 330 core

in vec3 vert_color;
in vec2 texel_cord;

out vec4 fragColor;

uniform sampler2D tex_unit0;
uniform sampler2D tex_unit1;

void main()
{
    fragColor = mix(texture(tex_unit0, texel_cord), texture(tex_unit1, texel_cord), 0.7);
}
