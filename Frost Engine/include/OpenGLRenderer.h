#pragma once

#include <vector>
#include <map>
#include <Vertex.h>
#include <GLShape.h>
#include <Texture.h>
#include <GLShader.h>
#include <Transform.h>
#include <Camera.h>

struct Material
{
	Texture DiffuseSkin;
	Texture SpecularSkin;

	float Shininess;
};

struct Renderable
{
	GLShape Shape;
	Material Skin;	
	vec4f Color;
	Transform Orientation;
	char *Name;
};

struct PhongLight
{
	vec4f AmbientColor;
	vec4f DiffuseColor;
	vec4f SpecularColor;
};

struct DirectionalLight 
{
	vec3f Direction;

	vec4f AmbientColor;
	vec4f DiffuseColor;
	vec4f SpecularColor;

	float AmbientStrength;
};

struct Attenuation 
{
	float Constant;
	float Linear;
	float Quadratic;
};

struct PointLight 
{
	vec3f Position;

	vec4f AmbientColor;
	vec4f DiffuseColor;
	vec4f SpecularColor;

	Attenuation Atten;

	float AmbientStrength;
};

struct SpotLight
{
	vec3f *Position;
	vec3f *Direction;

	vec4f AmbientColor;
	vec4f DiffuseColor;
	vec4f SpecularColor;

	Attenuation Atten;

	float AmbientStrength;
	float InnerCut;
	float OuterCut;
};

struct SimpleLamp
	: public Renderable
{
	float Attenuation;
	float AmbientStrength;
};

class OpenGLRenderer
{
public:
	OpenGLRenderer() {}
public:
	GLShape CreateShape(Vertex *vertices, unsigned verticesCount
		, unsigned int *indices, unsigned int indicesCount, bool withNormals = true);
	GLShape CreateQuad(vec3f pos, vec2f size, vec2f texScale, bool withNormals = true);
	GLShape CreateCuboid(vec3f pos, vec3f size, vec2f texScale, bool withNormals = true);
	void DestroyShape(GLShape *shape);

	Renderable& AddShape(char *name, Vertex *vertices, unsigned verticesCount
		, unsigned int *indices, unsigned int indicesCount, vec4f color, float shininess, char *material = NULL, bool withNormals = true);
	Renderable& AddQuad(char *name, vec3f pos, vec2f size, vec2f texScale, vec4f color, float shininess, char *material = NULL, bool withNormals = true);
	Renderable& AddCuboid(char *name, vec3f pos, vec3f size, vec2f texScale, vec4f color, float shininess, char *material = NULL, bool withNormals = true);
	Renderable& AddLamp(char *name, vec3f pos, vec3f size, vec4f color, float ambientStrength, float attenuation, char *material = NULL);

	Renderable& GetRenderable(char *name);
	void RemoveRenderable(char *name);

	SimpleLamp& GetLamp(char *name);
	void RemoveLamp(char *name);

	void AddTexture(char *path, char *name, bool invertY = true);
	Texture GetTexture(char *name);
	void RemoveTexture(char *name);

	void AddMaterial(char *name, Material material);
	Material GetMaterial(char *name);
	void RemoveMaterial(char *name);

	void AddShader(OpenGLShader shader, char *name);
	OpenGLShader GetShader(char *name);
	void RemoveShader(char *name);

	void RenderShapes(OpenGLShader *shader);
	void RenderShape(Renderable *renderable, OpenGLShader *shader, SimpleLamp *lamp = NULL);

	void Update();

private:
	void CalculateNormals(Vertex *vertices, unsigned verticesCount
		, unsigned int *indices, unsigned int indicesCount);

public:
	Camera MainCamera;

	DirectionalLight Directional;
	PointLight Point;

#define NUM_POINT_LIGHT 10
	PointLight Points[NUM_POINT_LIGHT];

	SpotLight Spot;
private:
	std::map<char *, Renderable> Renderables;
	std::map<char *, SimpleLamp> Lamps;
	std::map<char *, Texture> TextureCache;
	std::map<char *, Material> MaterialCache;
	std::map<char *, OpenGLShader> ShaderCache;
};
