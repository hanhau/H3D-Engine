#version 330 core

in vec2 TexCoords;
in vec3 posout;
in vec3 Normal;
out vec4 FragColor;
uniform vec3 lightPos;

void main()
{    
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * vec3(1.0,0.95,0.95);

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos*10 - posout);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0,0.95,0.95);
            
    vec3 result = (ambient + diffuse) * vec3(0.5,0.7,0.3);

	FragColor = vec4(Normal, 1.0) + vec4(result, 1.0);
}