#version 150 core                                                                        
                                                                                    

in vec3 in_Vertex;
    
                                                                                    
// Uniform

uniform mat4 u_projection;
uniform mat4 u_modelview;                                                              
        
// Sortie
                                                                            
out vec4 Color;                                                                     
                                                                                    
void main()                                                                         
{                                                                                   
    gl_Position = u_projection * u_modelview * vec4(in_Vertex, 1.0);                         
    Color = vec4(clamp(in_Vertex, 0.0, 1.0), 1.0);                                   
}