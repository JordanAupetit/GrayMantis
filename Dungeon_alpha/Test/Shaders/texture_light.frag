// Version du GLSL

#version 150 core


// Entrée

in vec2 coordTexture;


// Uniform

uniform sampler2D textures;
uniform vec4 light;                                                                    
                                                       
// Sortie 

out vec4 out_Color;


// Fonction main

void main()
{
    // Couleur du pixel

    out_Color = texture(textures, coordTexture) * 
    vec4(light.x, light.y, light.z, 1.0f) * 
    light.w;


}
