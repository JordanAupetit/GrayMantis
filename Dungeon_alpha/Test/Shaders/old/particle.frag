
#version 150 core


// Entrée

in vec2 coordTexture;


// Uniform

uniform sampler2D textures;


// Sortie 

out vec4 out_Color;


void main(void)
{
	vec2 TexCoord = coordTexture;
	vec4 TexColor = texture2D(textures, TexCoord);
	//out_Color = TexColor*VertexColor;
	out_Color = texture2D(textures, TexCoord);
}


