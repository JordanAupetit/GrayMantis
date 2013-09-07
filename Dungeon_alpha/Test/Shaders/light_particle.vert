
#version 150 core


// Entrées

in vec3 in_Vertex;
in vec4 in_color;
in vec2 in_TexCoord0;
in vec4 in_aux0;

// Uniform

uniform mat4 u_projection;
uniform mat4 u_modelview;
//uniform vec3 CameraPoint;
//uniform vec3 u_pos;

// Sortie

out vec2 coordTexture;
out vec4 color;


void main(void)
{ 

    vec4 wpos = vec4(in_aux0.xyz, 1.0); //vec4 wpos = vec4(u_pos, 1.0);
    vec4 epos = u_modelview * wpos;
    epos.xy += in_Vertex.xy * in_aux0.w; 
    gl_Position = u_projection * epos;

    coordTexture = /*in_Vertex.xy*0.5 + vec2(0.5);*/ in_TexCoord0;

    color = in_color;

}
