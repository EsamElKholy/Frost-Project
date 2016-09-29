#pragma once

#include <InputManager.h>
#include <math.h>

class Camera
{
public:
	Camera(int projType = 1
		, vec3f eye = vec3f(0.0f, 0.0f, 3.0f)
		, vec3f target = vec3f(0.0f, 0.0f, -1.0f)
		, vec3f up = vec3f(0.0f, -1.0f, 0.0f))
		:
		  Eye(eye)
		, Up(up)
		, WorldUp(up)
		, Target(target)
		, RightDir(vec3f(1.0f, 0.0f, 0.0f))

#if 0
		, OldEye(glm::vec3(0.0f, 0.0f, -1.0f))
		, OldTarget(glm::vec3(0.0f, 0.0f, 0.0f))
		, OldUp(glm::vec3(0.0f, 1.0f, 0.0f))
#endif
		, ProjectionType(projType)
	{
		Yaw = -90;
		Pitch = 0;
		MouseSensitivity = 0.05f;
		Speed = 5.0f;
	}
public:
	void SetPerspective(float fov = 45.0f
		, float width = 1280.0f 
		, float height = 720.0f
		, float near = 0.01f
		, float far = 1000.0f);

	void SetOrthographic(float left, float right, float top, float bottom, float near, float far);

	mat4f& GetViewMatrix();
	mat4f& GetProjectionMatrix();

	bool HasChanged();

	void Update();
public:
	vec3f Eye;
	vec3f Target;
	vec3f WorldUp;
	vec3f Up;
	vec3f RightDir;

private:
	float Yaw;
	float Pitch;
	float MouseSensitivity;
	float Speed;

	int ProjectionType;

	float FOV, Width, Height, Near, Far;
	float Left, Right, Top, Bottom;

	mat4f View;
	mat4f Perspective;
	mat4f Orthographic;
};

