#pragma once

#include <cinder\CinderMath.h>

using namespace Cinder::Math;

struct Vertex
{
	Vertex(vec3f pos = vec3f(), vec2f tex = vec2f(), vec3f normal = vec3f())
		: Pos(pos), TexCoord(tex), Normal(normal)
	{}

	vec3f Pos;
	vec2f TexCoord;
	vec3f Normal;
};
