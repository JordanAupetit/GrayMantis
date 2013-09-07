#version 150 core                                                                        
                                                                                    

in vec4 Color;                                                                      
                                                                                    
out vec4 FragColor;                                                                 
                                                                                    
void main()                                                                         
{                                                                                   
    FragColor = vec4(1.0, Color.y, Color.z, 1.0);                                                              
}