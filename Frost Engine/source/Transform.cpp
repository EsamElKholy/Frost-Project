#include <Transform.h>

bool Transform::HasChanged()
{
	if (Position != OldPosition)
	{
		return true;
	}

	if (Rotation != OldRotation)
	{
		return true;
	}

	if (Scale != OldScale)
	{
		return true;
	}

	return false;
}

void Transform::Update()
{
	if (OldPosition != vec3f(0.0f, 0.0f, 0.0f))
	{
		OldPosition = Position;
		OldRotation = Rotation;
		OldScale = Scale;
	}
	else
	{
		OldPosition = Position + vec3f(1.0f, 0.0f, 0.0f);
		OldRotation = Rotation * 0.5f;
		OldScale = Scale + vec3f(1.0f, 1.0f, 1.0f);
	}
}

mat4f& Transform::GetModelMatrix()
{
#if 0
	if (HasChanged())
	{
#endif
		mat4f trans = Mat4::Translation(Position);
		mat4f rot = Mat4::Rotation(Rotation);
		mat4f scale = Mat4::Scale(Scale);

		Model = trans * rot * scale;

		return Model;
#if 0
	}

	return Model;
#endif
}
