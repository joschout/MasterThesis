#include "CameraControl.h"
#include <GLFW/glfw3.h>
#include "Renderers/LevelRenderer.h"


CameraController::CameraController(): 
	camera(nullptr), inputformat(nullptr),
	rmanager(nullptr), rmanager4D(nullptr),
	octree(nullptr), render_context(nullptr), renderdata(nullptr),
    camera_eye_plus_X(false), camera_eye_minus_X(false), camera_eye_plus_Y(false),
	camera_eye_minus_Y(false), camera_eye_plus_Z(false), camera_eye_minus_Z(false),
	camera_gaze_plus_X(false), camera_gaze_minus_X(false), camera_gaze_plus_Y(false),
	camera_gaze_minus_Y(false), camera_gaze_plus_Z(false), camera_gaze_minus_Z(false),
	time_plus_constant(false), time_minus_constant(false),
	time_plus_timestep(false), time_minus_timestep(false)
{
}

CameraController::CameraController(
	Camera* camera, FileFormat *inputformat,
	RendererManager *render_manager, RendererManager4D *render_manager4D,
	Octree * octree, RenderContext *rc,
	unsigned char* renderdata): 
	camera_eye_plus_X(false), camera_eye_minus_X(false), camera_eye_plus_Y(false),
	camera_eye_minus_Y(false), camera_eye_plus_Z(false), camera_eye_minus_Z(false),
	camera_gaze_plus_X(false), camera_gaze_minus_X(false), camera_gaze_plus_Y(false),
	camera_gaze_minus_Y(false), camera_gaze_plus_Z(false), camera_gaze_minus_Z(false),
	time_plus_constant(false), time_minus_constant(false),
	time_plus_timestep(false), time_minus_timestep(false)
{
	this->camera = camera;
	this->inputformat = inputformat;
	this->rmanager = render_manager;
	this->rmanager4D = render_manager4D;
	this->octree = octree;
	this->render_context = rc;
	this->renderdata = renderdata;

}

// Keyboard
void CameraController::keyboardfunc(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	if(changeOnlyOnKeyPress)
	{
		handleSingleKeyPress(window, key, scancode, action, mods);
	}else
	{
		handleContinuousKeyPress(window, key, scancode, action, mods);
	}	

	handleKeyPressOnly(window, key, scancode, action, mods);
}

void CameraController::moveCamera() {


	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);



	// camera eye
	if (camera_eye_plus_X)
	{
		camera->eye = camera->eye + deltaTime * camera_eye_movement_speed * vec(1.0, 0, 0);
	}
	if (camera_eye_minus_X)
	{
		camera->eye = camera->eye - deltaTime * camera_eye_movement_speed * vec(1.0, 0, 0);
	}
	if (camera_eye_plus_Y)
	{
		camera->eye = camera->eye + deltaTime * camera_eye_movement_speed * vec(0, 1.0, 0);
	}
	if (camera_eye_minus_Y)
	{
		camera->eye = camera->eye - deltaTime * camera_eye_movement_speed * vec(0, 1.0, 0);
	}
	if (camera_eye_plus_Z)
	{
		camera->eye = camera->eye + deltaTime * camera_eye_movement_speed * vec(0, 0, 1.0);
	}
	if (camera_eye_minus_Z)
	{
		camera->eye = camera->eye - deltaTime * camera_eye_movement_speed * vec(0, 0, 1.0);
	}

	// camera gaze
	if (camera_gaze_plus_X)

	{
		camera->gaze = camera->gaze + deltaTime * camera_gaze_movement_speed * vec3(1.0, 0, 0);
	}
	if (camera_gaze_minus_X)
	{
		camera->gaze = camera->gaze - deltaTime * camera_gaze_movement_speed * vec3(1.0, 0, 0);
	}
	if (camera_gaze_plus_Y)
	{
		camera->gaze = camera->gaze + deltaTime * camera_gaze_movement_speed * vec3(0, 1.0, 0);
	}
	if (camera_gaze_minus_Y)
	{
		camera->gaze = camera->gaze - deltaTime * camera_gaze_movement_speed * vec3(0, 1.0, 0);
	}
	if (camera_gaze_plus_Z)
	{
		camera->gaze = camera->gaze + deltaTime * camera_gaze_movement_speed * vec3(0, 0, 1.0);
	}
	if (camera_gaze_minus_Z)
	{
		camera->gaze = camera->gaze - deltaTime * camera_gaze_movement_speed * vec3(0, 0, 1.0);
	}


	// time point
	if (time_plus_constant)
	{
		time_point = time_point + deltaTime * time_movement_speed;
	}
	if (time_minus_constant)
	{
		time_point = time_point - deltaTime * time_movement_speed;
	}
	if (time_plus_timestep)
	{
		time_point = time_point + time_step;
	}
	if (time_minus_timestep)
	{
		time_point = time_point - time_step;
	}

}

void CameraController::handleSingleKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		case GLFW_KEY_KP_9:
		case GLFW_KEY_KP_SUBTRACT:
			camera->eye = camera->eye + vec3(0, 0, -space_step_Z);
			break;
		case GLFW_KEY_KP_7:
		case GLFW_KEY_KP_ADD:
			camera->eye = camera->eye + vec3(0, 0, space_step_Z);
			break;
		case GLFW_KEY_KP_6:
		case GLFW_KEY_RIGHT:
			camera->eye = camera->eye + vec3(space_step_X, 0, 0);
			break;
		case GLFW_KEY_KP_4:
		case GLFW_KEY_LEFT:
			camera->eye = camera->eye + vec3(-space_step_X, 0, 0);
			break;
		case GLFW_KEY_KP_8:
		case GLFW_KEY_UP:
			camera->eye = camera->eye + vec3(0, space_step_Y, 0);
			break;
		case GLFW_KEY_KP_5:
		case GLFW_KEY_DOWN:
			camera->eye = camera->eye + vec3(0, -space_step_Y, 0);
			break;
		case GLFW_KEY_W:
			camera->gaze = camera->gaze + vec3(0.2, 0, 0);
			break;
		case GLFW_KEY_S:
			camera->gaze = camera->gaze + vec3(-0.2, 0, 0);
			break;
		case GLFW_KEY_A:
			camera->gaze = camera->gaze + vec3(0, 0.2, 0);
			break;
		case GLFW_KEY_D:
			camera->gaze = camera->gaze + vec3(0, -0.2, 0);
			break;
		case GLFW_KEY_R:
			camera->gaze = camera->gaze + vec3(0, 0, 0.2);
			break;
		case GLFW_KEY_F:
			camera->gaze = camera->gaze + vec3(0, 0, -0.2);
			break;
			
		// Moving along the time dimension
		case GLFW_KEY_T:
			time_point = time_point + 0.1;
			break;
		case GLFW_KEY_Y:
			time_point = time_point - 0.1;
			break;
		case GLFW_KEY_G:
			time_point = time_point + time_step;
			break;
		case GLFW_KEY_H:
			time_point = time_point - time_step;
			break;
	
		}
	}
}

void CameraController::handleContinuousKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	bool keyIsBeingPressed = (action != GLFW_RELEASE);

	//KEYS THAT ALSO FUNCTION WHEN THEY ARE BEING PRESSED
	switch (key) {
	case GLFW_KEY_KP_9:
	case GLFW_KEY_KP_SUBTRACT:
		camera_eye_minus_Z = keyIsBeingPressed;
		break;
	case GLFW_KEY_KP_7:
	case GLFW_KEY_KP_ADD:
		camera_eye_plus_Z = keyIsBeingPressed;
		break;
	case GLFW_KEY_KP_6:
	case GLFW_KEY_RIGHT:
		camera_eye_plus_X = keyIsBeingPressed;
		break;
	case GLFW_KEY_KP_4:
	case GLFW_KEY_LEFT:
		camera_eye_minus_X = keyIsBeingPressed;
		break;
	case GLFW_KEY_KP_8:
	case GLFW_KEY_UP:
		camera_eye_plus_Y = keyIsBeingPressed;
		break;
	case GLFW_KEY_KP_5:
	case GLFW_KEY_DOWN:
		camera_eye_minus_Y = keyIsBeingPressed;
		break;
	case GLFW_KEY_W:
		camera_gaze_plus_X = keyIsBeingPressed;
		break;
	case GLFW_KEY_S:
		camera_gaze_minus_X = keyIsBeingPressed;
		break;
	case GLFW_KEY_A:
		camera_gaze_plus_Y = keyIsBeingPressed;
		break;
	case GLFW_KEY_D:
		camera_gaze_minus_Y = keyIsBeingPressed;
		break;
	case GLFW_KEY_R:
		camera_gaze_plus_Z = keyIsBeingPressed;
		break;
	case GLFW_KEY_F:
		camera_gaze_minus_Z = keyIsBeingPressed;
		break;

		// Moving along the time dimension
	case GLFW_KEY_T:
		time_plus_constant = keyIsBeingPressed;
		break;
	case GLFW_KEY_Y:
		time_minus_constant = keyIsBeingPressed;
		break;
	case GLFW_KEY_G:
		time_plus_timestep = keyIsBeingPressed;
		break;
	case GLFW_KEY_H:
		time_minus_timestep = keyIsBeingPressed;
		break;


	default:
		break;
	}


}

void CameraController::handleKeyPressOnly(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//KEYS THAT ONLY WORK ON PRESS
	if (action == GLFW_PRESS) {
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;

		case GLFW_KEY_L:
			changeOnlyOnKeyPress = !changeOnlyOnKeyPress;
			break;

			//Rotation around axes
		case GLFW_KEY_Z:
			camera->gaze = rotateX(camera->gaze, 25);
			camera->top = rotateX(camera->top, 25);
			break;
		case GLFW_KEY_X:
			camera->gaze = rotateX(camera->gaze, -25);
			camera->top = rotateX(camera->top, -25);
			break;
		case GLFW_KEY_C:
			camera->gaze = rotateY(camera->gaze, 25);
			camera->top = rotateY(camera->top, 25);
			break;
		case GLFW_KEY_V:
			camera->gaze = rotateY(camera->gaze, -25);
			camera->top = rotateY(camera->top, -25);
			break;
		case GLFW_KEY_B:
			camera->gaze = rotateZ(camera->gaze, 25);
			camera->top = rotateZ(camera->top, 25);
			break;
		case GLFW_KEY_N:
			camera->gaze = rotateZ(camera->gaze, -25);
			camera->top = rotateZ(camera->top, -25);
			break;

		case GLFW_KEY_P:
			switch (*inputformat)
			{
			case GRID: break;
			case OCTREE:
				rmanager->switchRenderer();
				break;
			case TREE4D:
				rmanager4D->switchRenderer();
				break;
			}
			break;

		case GLFW_KEY_J:
			{
				LevelRenderer* lr = dynamic_cast<LevelRenderer*>(rmanager->getRenderer("level"));
				lr->maxlevel = (lr->maxlevel - 1) % (int)(log2(octree->gridlength) + 2);
				std::cout << "Max level for Level renderer: " << lr->maxlevel << std::endl;
			}
			break;
		case GLFW_KEY_K:
			{
				LevelRenderer* lr = dynamic_cast<LevelRenderer*>(rmanager->getRenderer("level"));
				lr->maxlevel = (lr->maxlevel + 1) % (int)(log2(octree->gridlength) + 2);
				std::cout << "Max level for Level renderer: " << lr->maxlevel << std::endl;
			}
			break;

		case GLFW_KEY_I:
			{	
				std::string filename = "image" + getTimeString() + "";
				writePPM(render_context->n_x, render_context->n_y, renderdata, filename);
				std::cout << "Image file written: " << filename << ".ppm" << std::endl;
			}
			break;

		default:
			break;
		}
	}
}