#include <Camera.h>

void Camera::SetPerspective(float fov
	, float width
	, float height
	, float near
	, float far)
{

	Perspective = Mat4::Perspective(fov, width, height, near, far);

	FOV = fov;
	Width = width;
	Height = height;
	Near = near;
	Far = far;
}

void Camera::SetOrthographic(float left, float right, float top, float bottom, float near, float far)
{
	Orthographic = Mat4::Orthographic(left, right, bottom, top, near, far);
	
	Left = left;
	Right = right;
	Top = top;
	Bottom = bottom;
	Near = near;
	Far = far;
}

mat4f& Camera::GetViewMatrix()
{
	View = Mat4::LookAt(Eye, Eye + Target, Up);
	return View;
}

mat4f& Camera::GetProjectionMatrix()
{
	if (ProjectionType == 0)
	{
		Orthographic = Mat4::Orthographic(Left, Right, Bottom, Top, Near, Far);
		return Orthographic;
	}
	else
	{
		Perspective = Mat4::Perspective(FOV, Width, Height, Near, Far);
		return Perspective;
	}
}

bool mouseMove = false;
bool Camera::HasChanged()
{
	return false;
}

void Camera::Update()
{
	float cameraSpeed = Speed * (1.0f / 60.0f);

	if (InputManager::IsKeyDown(GLFW_KEY_W))
	{
		Eye += cameraSpeed * Target;
	}

	if (InputManager::IsKeyDown(GLFW_KEY_S))
	{
		Eye -= cameraSpeed * Target;
	}

	if (InputManager::IsKeyDown(GLFW_KEY_A))
	{
		Eye -= cameraSpeed * Vec3::Normalize(Vec3::Cross(Up, Target));
	}

	if (InputManager::IsKeyDown(GLFW_KEY_D))
	{
		Eye += cameraSpeed * Vec3::Normalize(Vec3::Cross(Up, Target));
	}	

	if (InputManager::IsKeyUp(GLFW_KEY_M))
	{
		mouseMove = !mouseMove;

		if (mouseMove)
		{
			glfwSetInputMode(InputManager::Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else
		{
			glfwSetInputMode(InputManager::Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}	

	if (mouseMove)
	{
		Yaw = std::fmod(Yaw + (InputManager::MousePosOffset.X * MouseSensitivity), 360.0f);
		Pitch += InputManager::MousePosOffset.Y * MouseSensitivity;

		if (Pitch < -89.0f)
		{
			Pitch = -89.0f;
		}

		if (Pitch > 89.0f)
		{
			Pitch = 89.0f;
		}

		vec3f newTarget;

		newTarget.X = cos(ToRadians(Pitch)) * cos(ToRadians(Yaw));
		newTarget.Y = sin(ToRadians(Pitch));
		newTarget.Z = cos(ToRadians(Pitch)) * sin(ToRadians(Yaw));

		Target = Vec3::Normalize(newTarget);
	}
}