#pragma once

#include <cinder\CinderMath.h>

using namespace Cinder::Math;

class Transform
{
public:
	Transform(vec3f pos = vec3f(0.0f, 0.0f, 0.0f)
		, vec3f rot = vec3f(0.0f, 0.0f, 0.0f)
		, vec3f scale = vec3f(1.0f, 1.0f, 1.0f))
		:
		Position(pos)
		, Rotation(rot)
		, Scale(scale)
		, OldPosition(vec3f(0.0f, 0.0f, 0.0f))
		, OldRotation(vec3f(0.0f, 0.0f, 0.0f))
		, OldScale(vec3f(1.0f, 1.0f, 1.0f))
	{}
public:
	mat4f& GetModelMatrix();

	bool HasChanged();

	void Update();
public:
	vec3f Position;
	vec3f Rotation;
	vec3f Scale;

private:
	vec3f OldPosition;
	vec3f OldRotation;
	vec3f OldScale;

	mat4f Model;
};