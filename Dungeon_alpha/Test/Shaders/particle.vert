
#version 150 core


// Entrées

in vec3 in_Vertex;
in vec3 in_color;
in vec2 in_TexCoord0;


// Uniform

uniform mat4 projection_modelview;
uniform vec3 CameraPoint;

// Sortie

out vec2 coordTexture;
out vec3 color;


void main(void)
{ 

	float ParticleSize = in_TexCoord0[1];
	vec3 camPoint = vec3(3.0, 3.0, 3.0);
	camPoint = CameraPoint;

	vec3 nnTmp = normalize(camPoint - in_Vertex);

	float VertexNum = in_TexCoord0[0];
	vec3 Vertex;

	vec3 nnTmp2 = normalize(vec3(1.0, 1.0, -(nnTmp.x + nnTmp.y)/nnTmp.z));

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

	color = in_color;
	gl_Position = projection_modelview * vec4(Vertex, 1.0);
}
