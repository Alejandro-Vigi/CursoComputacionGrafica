#version 330 core

in vec3 ourColor;
out vec4 color;

// Se creó esta variable para poder cambiar el color del fragmento desde el programa principal
uniform vec3 uColor;

void main()
{
    // Se multiplica el color del fragmento por el color que se le 
    // asigna desde el programa principal en la asignación de los vértices
    color = vec4(ourColor * uColor, 1.0f);
}