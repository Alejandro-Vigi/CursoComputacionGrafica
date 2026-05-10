// Previo 12: Animación por KeyFrames
// Marco Alejandro Vigi Garduño
// No. Cuenta: 319159709
// Fecha de entrega: 03 de mayo de 2026

#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"


// Function prototypes
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();
void Animation();
void cargarKeyFramesGuardados();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
bool active;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.0f,2.0f, 0.0f),
	glm::vec3(0.0f,0.0f, 0.0f),
	glm::vec3(0.0f,0.0f,  0.0f),
	glm::vec3(0.0f,0.0f, 0.0f)
};

float vertices[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};


glm::vec3 Light1 = glm::vec3(0);
//Anim
float rotBall = 0.0f;
float rotDog = 0.0f;
float rotDogSide = 0.0f;
float rotDogFront = 0.0f;
int dogAnim = 0;
// Para este previo se solicitó mover de forma independiente cada pata por lo que no es necesario que estas variables utilicen memoria
// float FLegs = 0.0f;
// float RLegs = 0.0f;
float head = 0.0f;
float tail = 0.0f;
float F_LeftLegDog = 0.0f;
float F_LeftLegDogInc = 0.0f;
float F_RightLegDog = 0.0f;
float F_RightLegDogInc = 0.0f;
float B_LeftLegDog = 0.0f;
float B_LeftLegDogInc = 0.0f;
float B_RightLegDog = 0.0f;
float B_RightLegDogInc = 0.0f;



//KeyFrames
float dogPosX , dogPosY , dogPosZ  ;

#define MAX_FRAMES 30
int i_max_steps = 190;
int i_curr_steps = 0;
typedef struct _frame {
	
	float rotDog;
	float rotDogInc;
	float rotDogSide;
	float rotDogSideInc;
	float dogPosX;
	float dogPosY;
	float dogPosZ;
	float incX;
	float incY;
	float incZ;
	float head;
	float headInc;
	float F_LeftLegDog;
	float F_LeftLegDogInc;
	float F_RightLegDog;
	float F_RightLegDogInc;
	float B_LeftLegDog;
	float B_LeftLegDogInc;
	float B_RightLegDog;
	float B_RightLegDogInc;
	float tail;
	float tailInc;
	float rotDogFront;
	float rotDogFrontInc;


}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;

void saveFrame(void)
{

	printf("frameindex %d\n", FrameIndex);

	KeyFrame[FrameIndex].dogPosX = dogPosX;
	KeyFrame[FrameIndex].dogPosY = dogPosY;
	KeyFrame[FrameIndex].dogPosZ = dogPosZ;
	KeyFrame[FrameIndex].head = head;
	KeyFrame[FrameIndex].F_LeftLegDog = F_LeftLegDog;
	KeyFrame[FrameIndex].F_RightLegDog = F_RightLegDog;
	KeyFrame[FrameIndex].B_LeftLegDog = B_LeftLegDog;
	KeyFrame[FrameIndex].B_RightLegDog = B_RightLegDog;
	KeyFrame[FrameIndex].tail = tail;
	KeyFrame[FrameIndex].rotDogSide = rotDogSide;
	KeyFrame[FrameIndex].rotDogFront = rotDogFront;

	KeyFrame[FrameIndex].rotDog = rotDog;


	FrameIndex++;

	printf("\n--- FRAME %d ---\n", FrameIndex);
	printf("Pos:   X=%.3f Y=%.3f Z=%.3f\n", dogPosX, dogPosY, dogPosZ);
	printf("Rot:   Body=%.3f Side=%.3f Front=%.3f\n", rotDog, rotDogSide, rotDogFront);
	printf("Head:  %.3f | Tail: %.3f\n", head, tail);
	printf("FLeg:  L=%.3f R=%.3f\n", F_LeftLegDog, F_RightLegDog);
	printf("BLeg:  L=%.3f R=%.3f\n", B_LeftLegDog, B_RightLegDog);
	printf("----------------\n\n");
}

void resetElements(void)
{
	dogPosX = KeyFrame[0].dogPosX;
	dogPosY = KeyFrame[0].dogPosY;
	dogPosZ = KeyFrame[0].dogPosZ;
	head = KeyFrame[0].head;
	F_LeftLegDog = KeyFrame[0].F_LeftLegDog;
	F_RightLegDog = KeyFrame[0].F_RightLegDog;
	B_LeftLegDog = KeyFrame[0].B_LeftLegDog;
	B_RightLegDog = KeyFrame[0].B_RightLegDog;
	tail = KeyFrame[0].tail;
	rotDogSide = KeyFrame[0].rotDogSide;
	rotDogFront = KeyFrame[0].rotDogFront;

	rotDog = KeyFrame[0].rotDog;

}
void interpolation(void)
{

	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].dogPosX - KeyFrame[playIndex].dogPosX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].dogPosY - KeyFrame[playIndex].dogPosY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].dogPosZ - KeyFrame[playIndex].dogPosZ) / i_max_steps;
	KeyFrame[playIndex].headInc = (KeyFrame[playIndex + 1].head - KeyFrame[playIndex].head) / i_max_steps;
	KeyFrame[playIndex].F_LeftLegDogInc = (KeyFrame[playIndex + 1].F_LeftLegDog - KeyFrame[playIndex].F_LeftLegDog) / i_max_steps;
	KeyFrame[playIndex].F_RightLegDogInc = (KeyFrame[playIndex + 1].F_RightLegDog - KeyFrame[playIndex].F_RightLegDog) / i_max_steps;
	KeyFrame[playIndex].B_LeftLegDogInc = (KeyFrame[playIndex + 1].B_LeftLegDog - KeyFrame[playIndex].B_LeftLegDog) / i_max_steps;
	KeyFrame[playIndex].B_RightLegDogInc = (KeyFrame[playIndex + 1].B_RightLegDog - KeyFrame[playIndex].B_RightLegDog) / i_max_steps;
	KeyFrame[playIndex].tailInc = (KeyFrame[playIndex + 1].tail - KeyFrame[playIndex].tail) / i_max_steps;
	KeyFrame[playIndex].rotDogFrontInc = (KeyFrame[playIndex + 1].rotDogFront - KeyFrame[playIndex].rotDogFront) / i_max_steps;
	KeyFrame[playIndex].rotDogSideInc = (KeyFrame[playIndex + 1].rotDogSide - KeyFrame[playIndex].rotDogSide) / i_max_steps;

	KeyFrame[playIndex].rotDogInc = (KeyFrame[playIndex + 1].rotDog - KeyFrame[playIndex].rotDog) / i_max_steps;

}



// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Previo 12: Animacion maquina de estados - Vigi Garduño Marco Alejandro", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);



	Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");
	Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");
	Shader skyboxshader("Shader/skybox.vs", "Shader/skybox.frag");
	
	
	//models
	Model DogBody((char*)"Models/PartsDog/DogBody.obj");
	Model HeadDog((char*)"Models/PartsDog/HeadDog.obj");
	Model DogTail((char*)"Models/PartsDog/TailDog.obj");
	Model F_RightLeg((char*)"Models/PartsDog/F_RightLegDog.obj");
	Model F_LeftLeg((char*)"Models/PartsDog/F_LeftLegDog.obj");
	Model B_RightLeg((char*)"Models/PartsDog/B_RightLegDog.obj");
	Model B_LeftLeg((char*)"Models/PartsDog/B_LeftLegDog.obj");
	Model Piso((char*)"Models/Floor/piso.obj");
	Model Ball((char*)"Models/Ball/ball.obj");

	GLfloat skyboxVertices[] = {
		// Positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};


	//KeyFrames
	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].dogPosX = 0;
		KeyFrame[i].dogPosY = 0;
		KeyFrame[i].dogPosZ = 0;
		KeyFrame[i].incX = 0;
		KeyFrame[i].incY = 0;
		KeyFrame[i].incZ = 0;
		KeyFrame[i].rotDog = 0;
		KeyFrame[i].rotDogInc = 0;
		KeyFrame[i].head = 0;
		KeyFrame[i].headInc = 0;
		KeyFrame[i].F_LeftLegDog = 0;
		KeyFrame[i].F_LeftLegDogInc = 0;
		KeyFrame[i].F_RightLegDog = 0;
		KeyFrame[i].F_RightLegDogInc = 0;
		KeyFrame[i].B_LeftLegDog = 0;
		KeyFrame[i].B_LeftLegDogInc = 0;
		KeyFrame[i].B_RightLegDog = 0;
		KeyFrame[i].B_RightLegDogInc = 0;
		KeyFrame[i].tail = 0;
		KeyFrame[i].tailInc = 0;
		KeyFrame[i].rotDogSide = 0;
		KeyFrame[i].rotDogSideInc = 0;
		KeyFrame[i].rotDogFront = 0;
		KeyFrame[i].rotDogFrontInc = 0;
	}


	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Skybox
	GLuint skyboxVBO, skyboxVAO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	//Load textures
	// Skybox de paisaje extra
	std::vector<const GLchar*> faces;
	faces.push_back("SkyBox/right.png");
	faces.push_back("SkyBox/left.png");
	faces.push_back("SkyBox/top.png");
	faces.push_back("SkyBox/bottom.png");
	faces.push_back("SkyBox/back.png");
	faces.push_back("SkyBox/front.png");
	GLuint skybox = TextureLoading::LoadCubemap(faces);

	//Load textures
	// Skybox de video
	std::vector<const GLchar*> faces2;
	faces2.push_back("SkyBox/video/right.jpg");
	faces2.push_back("SkyBox/video/left.jpg");
	faces2.push_back("SkyBox/video/top.jpg");
	faces2.push_back("SkyBox/video/bottom.jpg");
	faces2.push_back("SkyBox/video/back.jpg");
	faces2.push_back("SkyBox/video/front.jpg");
	GLuint skybox2 = TextureLoading::LoadCubemap(faces2);

	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.difuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.specular"), 1);

	
	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();
		Animation();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	   
		// OpenGL options
		glEnable(GL_DEPTH_TEST);

		
		glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
		
	

		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();

        glUniform1i(glGetUniformLocation(lightingShader.Program, "diffuse"), 0);
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "specular"),1);

		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"),0.6f,0.6f,0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.6f, 0.6f, 0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"),0.3f, 0.3f, 0.3f);


		// Point light 1
	    glm::vec3 lightColor;
		lightColor.x= abs(sin(glfwGetTime() *Light1.x));
		lightColor.y= abs(sin(glfwGetTime() *Light1.y));
		lightColor.z= sin(glfwGetTime() *Light1.z);

		
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x,lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x,lightColor.y,lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 0.2f, 0.2f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"),0.075f);


		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.2f, 0.2f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.2f, 0.2f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.3f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.7f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(18.0f)));
		

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 5.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


		glm::mat4 model(1);

	
		
		//Carga de modelo 
        view = camera.GetViewMatrix();	
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Piso.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		//Body
		modelTemp= model = glm::translate(model, glm::vec3(dogPosX,dogPosY,dogPosZ));
		modelTemp= model = glm::rotate(model, glm::radians(rotDog), glm::vec3(0.0f, 1.0f, 0.0f));
		modelTemp = model = glm::rotate(model, glm::radians(rotDogFront), glm::vec3(1.0f, 0.0f, 0.0f));
		modelTemp = model = glm::rotate(model, glm::radians(rotDogSide), glm::vec3(0.0f, 0.0f, 1.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		DogBody.Draw(lightingShader);
		//Head
		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.0f, 0.093f, 0.208f));
		model = glm::rotate(model, glm::radians(head), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		HeadDog.Draw(lightingShader);
		//Tail 
		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.0f, 0.026f, -0.288f));
		model = glm::rotate(model, glm::radians(tail), glm::vec3(0.0f, 0.0f, -1.0f)); 
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); 
		DogTail.Draw(lightingShader);
		//Front Left Leg
		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.112f, -0.044f, 0.074f));
		model = glm::rotate(model, glm::radians(F_LeftLegDog), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		F_LeftLeg.Draw(lightingShader);
		//Front Right Leg
		model = modelTemp; 
		model = glm::translate(model, glm::vec3(-0.111f, -0.055f, 0.074f));
		model = glm::rotate(model, glm::radians(F_RightLegDog), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		F_RightLeg.Draw(lightingShader);
		//Back Left Leg
		model = modelTemp; 
		model = glm::translate(model, glm::vec3(0.082f, -0.046, -0.218)); 
		model = glm::rotate(model, glm::radians(B_LeftLegDog), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); 
		B_LeftLeg.Draw(lightingShader);
		//Back Right Leg
		model = modelTemp; 
		model = glm::translate(model, glm::vec3(-0.083f, -0.057f, -0.231f));
		model = glm::rotate(model, glm::radians(B_RightLegDog), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		B_RightLeg.Draw(lightingShader); 


		model = glm::mat4(1);
		glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1);
		model = glm::rotate(model, glm::radians(rotBall), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	    Ball.Draw(lightingShader); 
		glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glBindVertexArray(0);
	

		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		
		model = glm::mat4(1);
		model = glm::translate(model, pointLightPositions[0]);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		glBindVertexArray(0);

		//Draw SkyBox
		glDepthFunc(GL_LEQUAL);
		skyboxshader.Use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(skyboxshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skyboxshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		GLuint currentSkybox = skybox;
		glBindTexture(GL_TEXTURE_CUBE_MAP, currentSkybox);
		glUniform1i(glGetUniformLocation(skyboxshader.Program, "skybox"), 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}


	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVBO);
	
	

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();



	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{
	//Dog Controls
	
	// Tail
	if (keys[GLFW_KEY_O])
	{

		tail += 1.0f;

	}

	if (keys[GLFW_KEY_P])
	{

		tail -= 1.0f;

	}

	// Right Front Leg
	if (keys[GLFW_KEY_4])
	{

		F_RightLegDog += 1.0f;

	}

	if (keys[GLFW_KEY_5])
	{

		F_RightLegDog -= 1.0f;

	}

	// Left Front Leg
	if (keys[GLFW_KEY_6])
	{

		F_LeftLegDog += 1.0f;

	}

	if (keys[GLFW_KEY_7])
	{

		F_LeftLegDog -= 1.0f;

	}
	// Right Back Leg
	if (keys[GLFW_KEY_8])
	{

		B_RightLegDog += 1.0f;

	}

	if (keys[GLFW_KEY_9])
	{

		B_RightLegDog -= 1.0f;

	}

	// Left Back Leg
	if (keys[GLFW_KEY_R])
	{

		B_LeftLegDog += 1.0f;

	}

	if (keys[GLFW_KEY_F])
	{

		B_LeftLegDog -= 1.0f;

	}
	// Head
	if (keys[GLFW_KEY_2])
	{

		head += 1.0f;

	}

	if (keys[GLFW_KEY_3])
	{

		head -= 1.0f;

	}
	
	// Rotation
	if (keys[GLFW_KEY_0])
	{
		
			rotDog += 1.0f;

	}

	if (keys[GLFW_KEY_1])
	{
		
			rotDog -= 1.0f;

	}

	// Rotation
	if (keys[GLFW_KEY_Z])
	{
		rotDogSide += 1.0f;
	}

	if (keys[GLFW_KEY_X])
	{
		rotDogSide -= 1.0f;
	}

	// Rotation
	if (keys[GLFW_KEY_C])
	{
		rotDogFront += 1.0f;
	}

	if (keys[GLFW_KEY_V])
	{
		rotDogFront -= 1.0f;
	}
	
	// Position Z
	if (keys[GLFW_KEY_H])
	{
		dogPosZ += 0.01;
	}

	if (keys[GLFW_KEY_Y])
	{
		dogPosZ -= 0.01;
	}

	// Position X
	if (keys[GLFW_KEY_G])
	{
		dogPosX -= 0.01;
	}

	if (keys[GLFW_KEY_J])
	{
		dogPosX += 0.01;
	}

	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}

	// Light controls

	if (keys[GLFW_KEY_B])
	{
		pointLightPositions[0].x += 0.01f;
	}

	if (keys[GLFW_KEY_N])
	{
		pointLightPositions[0].x -= 0.01f;
	}

	if (keys[GLFW_KEY_M])
	{
		pointLightPositions[0].y += 0.01f;
	}

	if (keys[GLFW_KEY_COMMA])
	{
		pointLightPositions[0].y -= 0.01f;
	}

	if (keys[GLFW_KEY_PERIOD])
	{
		pointLightPositions[0].z += 0.01f;
	}

	if (keys[GLFW_KEY_SLASH])
	{
		pointLightPositions[0].z -= 0.01f;
	}
	
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{

	if (keys[GLFW_KEY_L])
	{
		if (play == false && (FrameIndex > 1))
		{

			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}

	}

	if (key == GLFW_KEY_I && action == GLFW_PRESS)
	{
		cargarKeyFramesGuardados();
		if (play == false)
		{
			resetElements();
			interpolation();
			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
	}

	if (keys[GLFW_KEY_K])
	{
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}

	}



	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (keys[GLFW_KEY_SPACE])
	{
		active = !active;
		if (active)
		{
			Light1 = glm::vec3(0.2f, 0.8f, 1.0f);
			
		}
		else
		{
			Light1 = glm::vec3(0);//Cuado es solo un valor en los 3 vectores pueden dejar solo una componente
		}
	}


}
void Animation() {

	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			dogPosX += KeyFrame[playIndex].incX;
			dogPosY += KeyFrame[playIndex].incY;
			dogPosZ += KeyFrame[playIndex].incZ;
			head += KeyFrame[playIndex].headInc;
			F_LeftLegDog += KeyFrame[playIndex].F_LeftLegDogInc;
			F_RightLegDog += KeyFrame[playIndex].F_RightLegDogInc;
			B_LeftLegDog += KeyFrame[playIndex].B_LeftLegDogInc;
			B_RightLegDog += KeyFrame[playIndex].B_RightLegDogInc;
			tail += KeyFrame[playIndex].tailInc;
			rotDogSide += KeyFrame[playIndex].rotDogSideInc;
			rotDogFront += KeyFrame[playIndex].rotDogFrontInc;
			rotDog += KeyFrame[playIndex].rotDogInc;

			i_curr_steps++;
		}

	}
	
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}

void cargarKeyFramesGuardados() {
	// Gracias a la impresion de cada frame pudimos guardar los valores de cada frame y posteriormente cargarlos para crear la animación, 
	// esto se hizo con un script de python que extrajo los valores de cada frame y 
	// los organizo en el formato necesario para ser cargados en esta función.

	FrameIndex = 25;

	// FRAME 0 (Estado inicial)
	KeyFrame[0].dogPosX = 0.000f; KeyFrame[0].dogPosY = 0.000f; KeyFrame[0].dogPosZ = 0.000f;
	KeyFrame[0].rotDog = 0.000f; KeyFrame[0].rotDogSide = 0.000f; KeyFrame[0].rotDogFront = 0.000f;
	KeyFrame[0].head = 0.000f; KeyFrame[0].tail = 0.000f;
	KeyFrame[0].F_LeftLegDog = 0.000f; KeyFrame[0].F_RightLegDog = 0.000f;
	KeyFrame[0].B_LeftLegDog = 0.000f; KeyFrame[0].B_RightLegDog = 0.000f;

	// FRAME 1 al 4 (Rotación Frontal progresiva)
	KeyFrame[1].rotDogFront = -36.000f;
	KeyFrame[2].rotDogFront = -41.000f;
	KeyFrame[3].rotDogFront = -45.000f;
	KeyFrame[4].rotDogFront = -59.000f;

	// FRAME 5 al 8 (Movimiento de patas delanteras)
	for (int i = 5; i <= 8; i++) KeyFrame[i].rotDogFront = -59.001f;
	KeyFrame[5].F_RightLegDog = -48.000f;
	KeyFrame[6].F_LeftLegDog = 27.000f; KeyFrame[6].F_RightLegDog = -48.000f;
	KeyFrame[7].F_LeftLegDog = 27.000f; KeyFrame[7].F_RightLegDog = -5.000f;
	KeyFrame[8].F_LeftLegDog = -3.000f; KeyFrame[8].F_RightLegDog = -5.000f;

	// FRAME 9 al 14 (Ajuste de cuerpo y patas)
	KeyFrame[9].rotDogFront = -31.002f; KeyFrame[9].F_LeftLegDog = -3.000f; KeyFrame[9].F_RightLegDog = -5.000f;
	KeyFrame[10].rotDogFront = -6.002f;  KeyFrame[10].F_LeftLegDog = -3.000f; KeyFrame[10].F_RightLegDog = -5.000f;
	KeyFrame[11].rotDogFront = -6.003f; KeyFrame[11].F_RightLegDog = -34.000f; KeyFrame[11].F_LeftLegDog = -3.000f;
	KeyFrame[12].rotDogFront = -6.003f; KeyFrame[12].F_RightLegDog = -89.000f;
	KeyFrame[13].rotDogFront = -6.003f; KeyFrame[13].F_RightLegDog = -58.000f;
	KeyFrame[14].rotDogFront = -6.003f; KeyFrame[14].F_RightLegDog = 11.000f;

	// FRAME 15 al 17 (Patas traseras)
	KeyFrame[15].rotDogFront = -39.003f; KeyFrame[15].B_LeftLegDog = -42.000f; KeyFrame[15].B_RightLegDog = 18.000f;
	KeyFrame[16].rotDogFront = -39.003f; KeyFrame[16].B_LeftLegDog = -42.000f; KeyFrame[16].B_RightLegDog = 38.000f;
	KeyFrame[17].rotDogFront = -39.003f; KeyFrame[17].B_LeftLegDog = -42.000f; KeyFrame[17].B_RightLegDog = 38.000f;

	// FRAME 18 al 22 (Inclinación lateral y Posición X)
	KeyFrame[18].rotDogFront = -39.004f; KeyFrame[18].rotDogSide = 13.000f;
	KeyFrame[19].rotDogFront = -39.004f; KeyFrame[19].rotDogSide = 19.000f;
	KeyFrame[20].rotDogFront = -39.005f; KeyFrame[20].rotDogSide = 29.000f;
	KeyFrame[21].rotDogFront = -39.005f; KeyFrame[21].rotDogSide = 29.000f; KeyFrame[21].dogPosX = -0.140f;
	KeyFrame[22].rotDogFront = -39.005f; KeyFrame[22].rotDogSide = 50.000f; KeyFrame[22].dogPosX = -0.210f;

	// FRAME 23 al 24 (Finalización de pose)
	KeyFrame[22].dogPosX = -0.210f;
	KeyFrame[22].dogPosY = -0.050f;

	KeyFrame[23].rotDogFront = 5.994f; KeyFrame[23].rotDogSide = 70.000f;
	KeyFrame[23].dogPosX = -0.210f;
	KeyFrame[23].dogPosY = -0.080f;
	KeyFrame[23].B_LeftLegDog = 3.000f; KeyFrame[23].B_RightLegDog = 20.000f;

	KeyFrame[24].rotDogFront = 5.994f; KeyFrame[24].rotDogSide = 86.000f;
	KeyFrame[24].dogPosX = -0.210f;
	KeyFrame[24].dogPosY = -0.100f;
	KeyFrame[24].B_LeftLegDog = 3.000f; KeyFrame[24].B_RightLegDog = 20.000f;

	printf("Animación cargada correctamente.\n");
}