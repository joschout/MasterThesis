#include <TriMesh.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <vector>
#include <iostream>


#include <AntTweakBar.h>
#include "Camera.h"
#include "Frustrum.h"
#include "RenderContext.h"
#include "RendererManager.h"
#include "Grid.h"
#include "BasicGridRenderer.h"
#include "util.h"
#include <omp.h>
//#include "controls.hpp"

using namespace std;

// viewpoint
Camera camera;
Frustrum frustrum;
RenderContext render_context;

// renderer
BasicGridRenderer gridRenderer;
int current_r = 0;
int lightselector = 0;


Grid* grid = nullptr;
unsigned char* renderdata;

// OpenGL
GLuint texid;

GLFWwindow* window;

// Draw fullsize quad, regardless of camera standpoint
void drawFullsizeQuad()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);		glVertex3f(-1.0, -1.0, 0.0);
	glTexCoord2f(1.0, 0.0);		glVertex3f(1.0, -1.0, 0.0);
	glTexCoord2f(1.0, 1.0);		glVertex3f(1.0, 1.0, 0.0);
	glTexCoord2f(0.0, 1.0);		glVertex3f(-1.0, 1.0, 0.0);
	glEnd();
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void generateTexture() {
	glBindTexture(GL_TEXTURE_2D, texid);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, render_context.n_x, render_context.n_y, 0, GL_RGBA, GL_UNSIGNED_BYTE, renderdata);
	glEnable(GL_TEXTURE_2D);
}

void setupTexture() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glGenTextures(1, &texid);
	glBindTexture(GL_TEXTURE_2D, texid);
	glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	generateTexture();
}

void display(void)
{
	float ratio;
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);
//	computeMatricesFromInputs(camera);

	Timer t = Timer();

	camera.computeUVW();

	memset(renderdata, 0, render_context.n_x*render_context.n_y * 4);
	gridRenderer.Render(render_context, grid, renderdata);
	generateTexture();
	drawFullsizeQuad();

	//TwDraw();
	//glPopMatrix();

	glfwSwapBuffers(window);

	std::stringstream out;
	out << "Voxelicious v0.2 | Rendertime: " << t.getTimeMilliseconds() << " ms | FPS: " << 1000 / t.getTimeMilliseconds();
	string s = out.str();
	glfwSetWindowTitle(window, s.c_str());
}


//// Initial horizontal angle : toward -Z
//float horizontalAngle = 3.14f;
//
//// Initial vertical angle : none
//float verticalAngle = 0.0f;
float speed = 2.0f; // 3 units / second
//float mouseSpeed = 0.005f;


// Keyboard
void keyboardfunc(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

//	// Get mouse position
//	double xpos, ypos;
//	glfwGetCursorPos(window, &xpos, &ypos);

//	// Reset mouse position for next frame
//	glfwSetCursorPos(window, render_context.n_x / 2, render_context.n_y / 2);

//	// Compute new orientation
//	horizontalAngle += mouseSpeed * float(render_context.n_x / 2 - xpos);
//	verticalAngle += mouseSpeed * float(render_context.n_y / 2 - ypos);

//	// Direction : Spherical coordinates to Cartesian coordinates conversion
//	trimesh::vec3 gaze = trimesh::vec3(
//		cos(verticalAngle) * sin(horizontalAngle),
//		sin(verticalAngle),
//		cos(verticalAngle) * cos(horizontalAngle)
//		);
//
//	// Right vector
//	trimesh::vec3 right = trimesh::vec3(
//		sin(horizontalAngle - 3.14f / 2.0f),
//		0,
//		cos(horizontalAngle - 3.14f / 2.0f)
//		);


	// Up vector
	trimesh::vec3 right = camera.top CROSS camera.gaze;

	


	//TwEventKeyboardGLUT(key,x,y);
	switch (key) {
	case GLFW_KEY_ESCAPE:
		if(action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	case GLFW_KEY_KP_0:
		render_context.lights[lightselector].position = render_context.lights[lightselector].position + vec3(0, -0.1, 0);
		break;
	case GLFW_KEY_KP_2:
		render_context.lights[lightselector].position = render_context.lights[lightselector].position + vec3(0, 0.1, 0);
		break;
	case GLFW_KEY_KP_1:
		render_context.lights[lightselector].position = render_context.lights[lightselector].position + vec3(-0.1, 0, 0);
		break;
	case GLFW_KEY_KP_3:
		render_context.lights[lightselector].position = render_context.lights[lightselector].position + vec3(0.1, 0, 0);
		break;
	case GLFW_KEY_KP_9:
	case GLFW_KEY_KP_SUBTRACT:
		camera.eye = camera.eye + vec3(0, 0, -0.2);
		break;
	case GLFW_KEY_KP_7:
	case GLFW_KEY_KP_ADD:
		camera.eye = camera.eye + vec3(0, 0, 0.2);
		break;
	case GLFW_KEY_KP_6:
		camera.eye = camera.eye + vec3(0.2, 0, 0);
		break;
	case GLFW_KEY_RIGHT:
		camera.eye -= right * deltaTime * speed;
		lastTime = currentTime;
		break;
	case GLFW_KEY_LEFT:
		camera.eye += right * deltaTime * speed;
		lastTime = currentTime;
		break;
	case GLFW_KEY_KP_4:
		camera.eye = camera.eye + vec3(-0.2, 0, 0);
		break;
	
	case GLFW_KEY_UP:
		camera.eye = camera.eye - camera.gaze * deltaTime * speed;
		lastTime = currentTime;
		break;
	case GLFW_KEY_KP_8:
		camera.eye = camera.eye + vec3(0, 0.2, 0);
		break;
	case GLFW_KEY_DOWN:
		camera.eye = camera.eye + camera.gaze * deltaTime*speed;
		lastTime = currentTime;
		break;
	case GLFW_KEY_KP_5:

		camera.eye = camera.eye + vec3(0, -0.2, 0);
		break;
	case GLFW_KEY_W:
		camera.gaze = camera.gaze + vec3(0.2, 0, 0);
		break;
	case GLFW_KEY_S:
		camera.gaze = camera.gaze + vec3(-0.2, 0, 0);
		break;
	case GLFW_KEY_A:
		camera.gaze = camera.gaze + vec3(0, 0.2, 0);
		break;
	case GLFW_KEY_D:
		camera.gaze = camera.gaze + vec3(0, -0.2, 0);
		break;
	case GLFW_KEY_R:
		camera.gaze = camera.gaze + vec3(0, 0, -0.2);
		break;
	case GLFW_KEY_F:
		camera.gaze = camera.gaze + vec3(0, 0, -0.2);
		break;
	case GLFW_KEY_N:
		lightselector = (lightselector + 1) % (render_context.lights.size());
		cout << "light selector:" << lightselector << endl;
		break;
	case GLFW_KEY_I:
	{string filename = "image" + getTimeString() + "";
	writePPM(render_context.n_x, render_context.n_y, renderdata, filename);
	std::cout << "Image file written: " << filename << ".ppm" << std::endl;}
	break;
	}
}

void printInfo() {
	std::cout << "Voxel Renderer Proof Of Concept" << std::endl;
	std::cout << "Jeroen Baert - 2012" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "jeroen.baert@cs.kuleuven.be" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "I'll be using " << omp_get_num_procs() << " CPU cores for rendering" << std::endl << std::endl;
}

void printControls() {
	std::cout << "Controls (on numeric keypad):" << std::endl;
	std::cout << "-----------------------------" << std::endl;
	std::cout << "4-6: Camera left-right" << std::endl;
	std::cout << "8-5: Camera up-down" << std::endl;
	std::cout << "7-9: Camera nearer-further" << std::endl;
	std::cout << "i: save screenshot in .PPM format" << std::endl;
	std::cout << "p: toggle work rendering" << std::endl;
	std::cout << "-----------------------------" << std::endl;
}

void printInvalid() {
	std::cout << "Not enough or invalid arguments, please try again.\n" << endl;
	std::cout << "At the bare minimum, I need a path to a data file (binvox/avox)" << endl;
	std::cout << "For Example: voxelraycaster.exe -f /home/jeroen/bunny256.avox" << endl;
}

void parseParameters(int argc, char **argv, string& file, FileFormat &inputformat, unsigned int& rendersize) {
	if (argc < 2) { printInvalid(); exit(0); }
	for (int i = 1; i < argc; i++) {
		if (string(argv[i]) == "-f") {
			file = argv[i + 1];
			size_t check_octree = file.find(".octree");
			if (check_octree != string::npos) {
				inputformat = OCTREE;
			}
			else {
				cout << "Data filename does not end in .octree - I only support that file format" << endl;
				printInvalid();
				exit(0);
			}
			i++;
		}
		else if (string(argv[i]) == "-s") {
			rendersize = atoi(argv[i + 1]);
			i++;
		}
		else { printInvalid(); exit(0); }
	}
}

void generateLightTWBars(TwBar* bar) {
	TwStructMember lightMembers[] = // array used to describe tweakable variables of the Light structure
	{
		{ "Active",    TW_TYPE_BOOL32, offsetof(Light, active),"" },
		{ "Position",    TW_TYPE_DIR3F, offsetof(Light, position),"" },
		{ "Diffuse",     TW_TYPE_COLOR3F, offsetof(Light, diffuse),"" },
		{ "Specular",    TW_TYPE_COLOR3F,   offsetof(Light, specular),"" },
		{ "Constant Attenuation", TW_TYPE_FLOAT, offsetof(Light, CONSTANT_ATTENUATION), "" },
		{ "Linear Attenuation", TW_TYPE_FLOAT, offsetof(Light, LINEAR_ATTENUATION), "" },
		{ "Quadratic Attenuation", TW_TYPE_FLOAT, offsetof(Light, QUADRATIC_ATTENUATION), "" },
		{ "Shininess", TW_TYPE_FLOAT, offsetof(Light, SHININESS), "" }
	};
	TwType lightType = TwDefineStruct("Light", lightMembers, 7, sizeof(Light), NULL, NULL);

	for (int i = 0; i<render_context.lights.size(); i++) {
		std::stringstream name;
		name << "Light " << i + 1;
		TwAddVarRW(bar, name.str().c_str(), lightType, &render_context.lights[i], "group='Lights'"); // Add a lightType variable and group it into the 'Edit lights' group
		TwSetParam(bar, name.str().c_str(), "label", TW_PARAM_CSTRING, 1, name.str().c_str()); // Set label
	}
}

void initRenderSystem(unsigned int render_x, unsigned int render_y) {
	camera = Camera(vec3(0, 0, -2), vec3(0, 0, -1), vec3(0, 1, 0));
	float aspect_ratio = render_x / render_y;
	frustrum = Frustrum(45, aspect_ratio, 1, 100); // THIS near and far SHOULD BE NEGATIVE
	render_context = RenderContext(&camera, &frustrum, render_x, render_y);
	Light mylight = Light(vec3(0, 0, 0), vec3(1.0, 1.0, 1.0));
	mylight.SHININESS = 25.0f;
	Light mylight2 = Light(vec3(4, 0, -3.0f), vec3(0.0, 0.0, 0.8));
	Light mylight3 = Light(vec3(0, 0, -3.0f), vec3(0.0, 0.8, 0.0));
	render_context.lights.push_back(mylight);
	render_context.lights.push_back(mylight2);
	render_context.lights.push_back(mylight3);
}

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}
//static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, GL_TRUE);
//}

int main(int argc, char **argv) {
	printInfo();
	printControls();

	// Input argument validation
	string datafile = "";
	unsigned int rendersize = 640;
	FileFormat inputformat;
	//parseParameters(argc,argv,datafile,inputformat,rendersize);

	// Initialize render system
	unsigned int render_x = rendersize;
	unsigned int render_y = rendersize;
	initRenderSystem(render_x, render_y);


	grid = new Grid();
	grid->min = vec3(0, 0, 0);
	grid->max = vec3(1, 1, 1);
	grid->gridlength = 16;
	grid->initSparseColorsRand();


	//cout << "Starting rendering ..." << endl;

	const int rgba_amount = render_x*render_y * 4;
	renderdata = new unsigned char[rgba_amount]; // put this on heap, it's too big, captain

												 // Init GLFW system
	if (!glfwInit()) exit(EXIT_FAILURE);
	// Init window
	window = glfwCreateWindow(render_x, render_y, "Voxel Ray Caster", NULL, NULL);
	if (!window) { glfwTerminate();exit(EXIT_FAILURE); }
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetKeyCallback(window, keyboardfunc);

	setupTexture();

	while (!glfwWindowShouldClose(window))
	{
		int current_width, current_height;
		glfwGetFramebufferSize(window, &current_width, &current_height);
		glViewport(0, 0, current_width, current_height);

		display();
		glfwWaitEvents();
	}
	delete renderdata;
	delete grid;
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);

}