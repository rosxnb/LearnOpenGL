#version 330 core

in vec3 vert_color;
in vec2 texel_cord;

out vec4 fragColor;

uniform sampler2D ourTexture;

void main()
{
    fragColor = texture(ourTexture, texel_cord) * vec4(vert_color, 1.f);
}
