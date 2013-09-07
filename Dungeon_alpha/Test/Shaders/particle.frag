
#version 150 core


// Entrée

in vec2 coordTexture;
in vec3 color;


// Uniform

uniform sampler2D textures;


// Sortie 

out vec4 out_Color;


void main(void)
{
	vec2 TexCoord = coordTexture;
	vec4 TexColor = texture2D(textures, TexCoord);
	vec4 VertexColor = vec4(color, 1.0);
	out_Color = TexColor*VertexColor;
}


