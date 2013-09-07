
#version 150 core


// Entrées

in vec3 in_Vertex;
in vec2 in_TexCoord0;


// Uniform

uniform mat4 projection;
uniform mat4 modelview;

uniform vec3 CameraPoint;
uniform vec3 uni_size;
uniform float uni_v_id;

// Sortie

out vec2 coordTexture;


void main(void)
{ 

	float ParticleSize = in_TexCoord0.y;

	vec3 nnTmp = normalize(CameraPoint - in_Vertex);

	float VertexNum = in_TexCoord0.x;
	vec3 Vertex;

	vec3 nnTmp2 = normalize(vec3(1.0, 1.0, -(nnTmp[0] + nnTmp[1])/nnTmp[2]));

	if (VertexNum == 1.0 || VertexNum == 3.0)
	{

		vec3 nnTmp3 = cross(nnTmp,nnTmp2);
		nnTmp3 = normalize(nnTmp3);

		if (VertexNum == 1.0)
		{
			Vertex = in_Vertex + nnTmp3*(-ParticleSize*1.5);
			coordTexture.x = 0.0;
			coordTexture.y = 1.0;
		}
		else // 3.0
		{
			Vertex = in_Vertex + nnTmp3*(ParticleSize*1.5);
			coordTexture.x = 1.0;
			coordTexture.y = 0.0;
		}
	}
	else
	{
		if (VertexNum == 2.0)
		{
			Vertex = in_Vertex + nnTmp2*(ParticleSize*1.5);
			coordTexture.x = 0.0;
			coordTexture.y = 0.0;
		}
		else // 4.0
		{
			Vertex = in_Vertex + nnTmp2*(-ParticleSize*1.5);
			coordTexture.x = 1.0;
			coordTexture.y = 1.0;
		}
	}


	gl_Position = projection * modelview * vec4(Vertex, 1.0);
}
