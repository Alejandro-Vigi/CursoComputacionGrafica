// Práctica #3 
// Marco Alejandro Vigi Garduño
// No. Cuenta: 319150709
// Fecha de entrega: 27 de febrero de 2026
// Laboratorio de computación gráfica
// Profesor: Arturo Pérez de la Cruz

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecciones y transformaciones basicas", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificaci�n de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers
	// use with Orthographic Projection

	//GLfloat vertices[] = {
 //      -0.5f*500, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,//Front
	//	0.5f * 500, -0.5f * 500, 0.5f * 500,  1.0f, 0.0f,0.0f,
	//	0.5f * 500,  0.5f * 500, 0.5f * 500,  1.0f, 0.0f,0.0f,
	//	0.5f * 500,  0.5f * 500, 0.5f * 500,  1.0f, 0.0f,0.0f,
	//	-0.5f * 500,  0.5f * 500, 0.5f * 500, 1.0f, 0.0f,0.0f,
	//	-0.5f * 500, -0.5f * 500, 0.5f * 500, 1.0f, 0.0f,0.0f,
	//	
	//    -0.5f * 500, -0.5f * 500,-0.5f * 500, 0.0f, 1.0f,0.0f,//Back
	//	 0.5f * 500, -0.5f * 500,-0.5f * 500, 0.0f, 1.0f,0.0f,
	//	 0.5f * 500,  0.5f * 500,-0.5f * 500, 0.0f, 1.0f,0.0f,
	//	 0.5f * 500,  0.5f * 500,-0.5f * 500, 0.0f, 1.0f,0.0f,
	//    -0.5f * 500,  0.5f * 500,-0.5f * 500, 0.0f, 1.0f,0.0f,
	//    -0.5f * 500, -0.5f * 500,-0.5f * 500, 0.0f, 1.0f,0.0f,
	//	
	//	 0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 0.0f,1.0f,
	//	 0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 0.0f,1.0f,
	//	 0.5f * 500,  0.5f * 500, -0.5f * 500,  0.0f, 0.0f,1.0f,
	//	 0.5f * 500,  0.5f * 500, -0.5f * 500,  0.0f, 0.0f,1.0f,
	//	 0.5f * 500,  0.5f * 500,  0.5f * 500,  0.0f, 0.0f,1.0f,
	//	 0.5f * 500,  -0.5f * 500, 0.5f * 500, 0.0f, 0.0f,1.0f,
 //     
	//	-0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 1.0f,0.0f,
	//	-0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 1.0f,0.0f,
	//	-0.5f * 500, -0.5f * 500, -0.5f * 500,  1.0f, 1.0f,0.0f,
	//	-0.5f * 500, -0.5f * 500, -0.5f * 500,  1.0f, 1.0f,0.0f,
	//	-0.5f * 500, -0.5f * 500,  0.5f * 500,  1.0f, 1.0f,0.0f,
	//	-0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 1.0f,0.0f,
	//	
	//	-0.5f * 500, -0.5f * 500, -0.5f * 500, 0.0f, 1.0f,1.0f,
	//	0.5f * 500, -0.5f * 500, -0.5f * 500,  0.0f, 1.0f,1.0f,
	//	0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 1.0f,1.0f,
	//	0.5f * 500, -0.5f * 500,  0.5f * 500,  0.0f, 1.0f,1.0f,
	//	-0.5f * 500, -0.5f * 500,  0.5f * 500, 0.0f, 1.0f,1.0f,
	//	-0.5f * 500, -0.5f * 500, -0.5f * 500, 0.0f, 1.0f,1.0f,
	//	
	//	-0.5f * 500,  0.5f * 500, -0.5f * 500, 1.0f, 0.2f,0.5f,
	//	0.5f * 500,  0.5f * 500, -0.5f * 500,  1.0f, 0.2f,0.5f,
	//	0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.2f,0.5f,
	//	0.5f * 500,  0.5f * 500,  0.5f * 500,  1.0f, 0.2f,0.5f,
	//	-0.5f * 500,  0.5f * 500,  0.5f * 500, 1.0f, 0.2f,0.5f,
	//	-0.5f * 500,  0.5f * 500, -0.5f * 500, 1.0f, 0.2f,0.5f,
	//};


	// use with Perspective Projection

	// Investigando un poco, añadí los colores da todos los cubos y deje colores distintos para las caras
	// para que simularan tener sombra o bien que se pueda ver de una mejor forma el cubo con su profundidad según sea 
	// la perspectiva.
	float vertices[] = {
		-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, // Cara de frente
		0.5f, -0.5f, 0.5f,  1.0f, 1.0f, 1.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 1.0f, 1.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f,

		-0.5f, -0.5f,-0.5f, 1.0f, 1.0f, 1.0f, // Cara de atras
		 0.5f, -0.5f,-0.5f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,-0.5f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,-0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,-0.5f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f,-0.5f, 1.0f, 1.0f, 1.0f,

		 0.5f, -0.5f,  0.5f,  0.75f, 0.75f, 0.75f, // Cara derecha
		 0.5f, -0.5f, -0.5f,  0.75f, 0.75f, 0.75f,
		 0.5f,  0.5f, -0.5f,  0.75f, 0.75f, 0.75f,
		 0.5f,  0.5f, -0.5f,  0.75f, 0.75f, 0.75f,
		 0.5f,  0.5f,  0.5f,  0.75f, 0.75f, 0.75f,
		 0.5f,  -0.5f, 0.5f, 0.75f, 0.75f, 0.75f,

		-0.5f,  0.5f,  0.5f,  0.75f, 0.75f, 0.75f, // Cara izquierda
		-0.5f,  0.5f, -0.5f,  0.75f, 0.75f, 0.75f,
		-0.5f, -0.5f, -0.5f,  0.75f, 0.75f, 0.75f,
		-0.5f, -0.5f, -0.5f,  0.75f, 0.75f, 0.75f,
		-0.5f, -0.5f,  0.5f,  0.75f, 0.75f, 0.75f,
		-0.5f,  0.5f,  0.5f,  0.75f, 0.75f, 0.75f,

		-0.5f, -0.5f, -0.5f, 0.6f, 0.6f, 0.6f, // Cara inferior
		0.5f, -0.5f, -0.5f,  0.6f, 0.6f, 0.6f,
		0.5f, -0.5f,  0.5f,  0.6f, 0.6f, 0.6f,
		0.5f, -0.5f,  0.5f,  0.6f, 0.6f, 0.6f,
		-0.5f, -0.5f,  0.5f, 0.6f, 0.6f, 0.6f,
		-0.5f, -0.5f, -0.5f, 0.6f, 0.6f, 0.6f,

		-0.5f,  0.5f, -0.5f, 0.6f, 0.6f, 0.6f, // Cara superior
		0.5f,  0.5f, -0.5f,  0.6f, 0.6f, 0.6f,
		0.5f,  0.5f,  0.5f,  0.6f, 0.6f, 0.6f,
		0.5f,  0.5f,  0.5f,  0.6f, 0.6f, 0.6f,
		-0.5f,  0.5f,  0.5f, 0.6f, 0.6f, 0.6f,
		-0.5f,  0.5f, -0.5f, 0.6f, 0.6f, 0.6f,
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	glm::mat4 projection = glm::mat4(1);

	projection = glm::perspective(45.0f, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model = glm::mat4(1);
		glm::mat4 view = glm::mat4(1);

		// Se obtiene la ubicación de la variable uniforme "uColor" en el shader para colorear cada cubo con un color distinto, 
		// se puede usar el color del vértice pero no cambiara el color de cada cubo.
		GLint colorLoc = glGetUniformLocation(ourShader.Program, "uColor");

		// "Cámara" o punto de vista, decidi dejarla casi en el lugar de origen con menor distancia en el eje z para 
		// que se vean mejor las transformaciones, similar al previo.
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));

		// Se inclina hacia arriba la cámara en radianes para una mejor perspectiva pareciendose a lo mencionado en la clase
		view = glm::rotate(view, glm::radians(-30.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		// Primer cubo: Le aplicamos traslación, rotación y escala para que se vea más pequeño, con una inclinación hacia un lado y 
		// de color café.
		model = glm::translate(model, glm::vec3(-1.5f, -4.0f, 0.0f));
		model = glm::rotate(model, 0.5f, glm::vec3(0.0f, -1.0f, 0.0f)); // use to compare orthographic and perspective projection
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3f(colorLoc, 0.678f, 0.467f, 0.180f);

		// Vista ortogonal
		//view = glm::translate( view, glm::vec3( screenWidth / 2, screenHeight / 1,-800.0f ) ); // use with orthographic projection

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");

		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Primer nombre: Marco: Por lo tanto son 5 cubos en total:

		// 2do cubo: Le aplicamos traslación, rotación y escala para que se un poco mas grande que el primero, con una inclinación 
		// hacia un lado y de color morado.
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-1.35f, -3.25f, 0.0f));
		model = glm::rotate(model, 0.5f, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniform3f(colorLoc, 0.663f, 0.463f, 0.878f); // color 
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 3er cubo: Le aplicamos traslación, rotación y escala para que se un poco mas grande que el segundo, con una inclinación 
		// hacia un lado y de color azul.
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-1.05f, -2.0f, 0.0f));
		model = glm::rotate(model, 0.5f, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.75f, 1.75f, 1.75f));
		glUniform3f(colorLoc, 0.545f, 0.545f, 0.831f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 4to cubo: Le aplicamos traslación, rotación y escala para que se un poco mas grande que el tercero, con una inclinación 
		// hacia un lado y de color verde.
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-0.85f, 0.0f, 0.0f));
		model = glm::rotate(model, 0.5f, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.25f, 2.25f, 2.25f));
		glUniform3f(colorLoc, 0.427f, 0.659f, 0.427f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 5to cubo: Le aplicamos traslación, rotación y escala para que se un poco mas grande que el primero, con una inclinación 
		// hacia un lado y de color rojo.
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-1.0f, 4.5f, 0.0f));
		model = glm::rotate(model, 0.5f, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::rotate(model, 0.5f, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 0.1f, glm::vec3(-1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniform3f(colorLoc, 0.749f, 0.22f, 0.129f);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);

	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;



}

