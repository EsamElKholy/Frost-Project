#include <OpenGLRenderer.h>
#include <string>

GLShape OpenGLRenderer::CreateShape(Vertex *vertices, unsigned verticesCount
	, unsigned int *indices, unsigned int indicesCount, bool withNormals)
{
	GLShape shape;

	shape.VerticesCount = verticesCount;
	shape.IndicesCount = indicesCount;

	if (withNormals)
	{
		CalculateNormals(vertices, verticesCount, indices, indicesCount);
	}
	
	glGenVertexArrays(1, &shape.VAO);
	glGenBuffers(1, &shape.VBO);
	glGenBuffers(1, &shape.IBO);

	glBindVertexArray(shape.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, shape.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * verticesCount, vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void *)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vertex), (void *)sizeof(vec3f));
	glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(Vertex), (void *)(sizeof(vec3f) + sizeof(vec2f)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shape.IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indicesCount, indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return shape;
}

void OpenGLRenderer::CalculateNormals(Vertex *vertices, unsigned verticesCount
	, unsigned int *indices, unsigned int indicesCount)
{
	for (unsigned int i = 0; i < indicesCount; i += 3)
	{
		unsigned int i0 = indices[i + 0];
		unsigned int i1 = indices[i + 1];
		unsigned int i2 = indices[i + 2];

		vec3f v1 = vertices[i1].Pos - vertices[i0].Pos;
		vec3f v2 = vertices[i2].Pos - vertices[i0].Pos;

		vec3f normal = Vec3::Normalize(Vec3::Cross(v1, v2));

		vertices[i0].Normal += normal;
		vertices[i1].Normal += normal;
		vertices[i2].Normal += normal;
	}

	for (unsigned int i = 0; i < verticesCount; i++)
	{
		vertices[i].Normal = Vec3::Normalize(vertices[i].Normal);
	}
}

Renderable& OpenGLRenderer::AddShape(char *name, Vertex *vertices, unsigned verticesCount
								, unsigned int *indices, unsigned int indicesCount, vec4f color, float shininess, char *material, bool withNormals)
{
	Renderable renderable = GetRenderable(name);

	if (!renderable.Shape.IsAvailable())
	{
		renderable.Shape = CreateShape(vertices, verticesCount, indices, indicesCount, withNormals);

		renderable.Skin = GetMaterial(material);

		renderable.Color = color;

		renderable.Skin.Shininess = shininess;

		renderable.Name = name;

		Renderables[name] = renderable;
	}	

	return renderable;
}

GLShape OpenGLRenderer::CreateQuad(vec3f pos, vec2f size, vec2f texScale, bool withNormals)
{
	Vertex vertices[4] =
	{
		Vertex(vec3f(pos.X - (size.X / 2.0f), pos.Y - (size.Y / 2.0f), pos.Z), vec2f(0 * texScale.X, 0 * texScale.Y)), // Bottom left
		Vertex(vec3f(pos.X + (size.X / 2.0f), pos.Y - (size.Y / 2.0f), pos.Z), vec2f(1 * texScale.X, 0 * texScale.Y)), // Bottom right
		Vertex(vec3f(pos.X + (size.X / 2.0f), pos.Y + (size.Y / 2.0f), pos.Z), vec2f(1 * texScale.X, 1 * texScale.Y)), // Top Right
		Vertex(vec3f(pos.X - (size.X / 2.0f), pos.Y + (size.Y / 2.0f), pos.Z), vec2f(0 * texScale.X, 1 * texScale.Y))  // Top left
	};

	unsigned int indices[6] =
	{
		0, 1, 2,
		2, 0, 3
	};

	GLShape shape = CreateShape(vertices, 4, indices, 6, withNormals);

	return shape;
}

Renderable& OpenGLRenderer::AddQuad(char *name, vec3f pos, vec2f size, vec2f texScale, vec4f color, float shininess, char *material, bool withNormals)
{
	Renderable renderable = GetRenderable(name);

	if (!renderable.Shape.IsAvailable())
	{
		renderable.Shape = CreateQuad(pos, size, texScale, withNormals);

		renderable.Skin = GetMaterial(material);

		renderable.Color = color;

		renderable.Skin.Shininess = shininess;

		renderable.Name = name;

		Renderables[name] = renderable;
	}

	return renderable;
}

GLShape OpenGLRenderer::CreateCuboid(vec3f pos, vec3f size, vec2f texScale, bool withNormals)
{
	Vertex vertices[24] =
	{		
		// Up
		Vertex(vec3f(pos.X - (size.X / 2.0f), pos.Y + (size.Y / 2.0f), pos.Z + (size.Z / 2.0f)), vec2f(0 * texScale.X, 0 * texScale.Y)), // Bottom left
		Vertex(vec3f(pos.X + (size.X / 2.0f), pos.Y + (size.Y / 2.0f), pos.Z + (size.Z / 2.0f)), vec2f(1 * texScale.X, 0 * texScale.Y)), // Bottom right
		Vertex(vec3f(pos.X + (size.X / 2.0f), pos.Y + (size.Y / 2.0f), pos.Z - (size.Z / 2.0f)), vec2f(1 * texScale.X, 1 * texScale.Y)), // Top Right
		Vertex(vec3f(pos.X - (size.X / 2.0f), pos.Y + (size.Y / 2.0f), pos.Z - (size.Z / 2.0f)), vec2f(0 * texScale.X, 1 * texScale.Y)), // Top left

		// Down
		Vertex(vec3f(pos.X - (size.X / 2.0f), pos.Y - (size.Y / 2.0f), pos.Z + (size.Z / 2.0f)), vec2f(0 * texScale.X, 0 * texScale.Y)), // Bottom left
		Vertex(vec3f(pos.X + (size.X / 2.0f), pos.Y - (size.Y / 2.0f), pos.Z + (size.Z / 2.0f)), vec2f(1 * texScale.X, 0 * texScale.Y)), // Bottom right
		Vertex(vec3f(pos.X + (size.X / 2.0f), pos.Y - (size.Y / 2.0f), pos.Z - (size.Z / 2.0f)), vec2f(1 * texScale.X, 1 * texScale.Y)), // Top Right
		Vertex(vec3f(pos.X - (size.X / 2.0f), pos.Y - (size.Y / 2.0f), pos.Z - (size.Z / 2.0f)), vec2f(0 * texScale.X, 1 * texScale.Y)), // Top left
		
		// Back
		Vertex(vec3f(pos.X - (size.X / 2.0f), pos.Y - (size.Y / 2.0f), pos.Z - (size.Z / 2.0f)), vec2f(0 * texScale.X, 0 * texScale.Y)), // Bottom left
		Vertex(vec3f(pos.X + (size.X / 2.0f), pos.Y - (size.Y / 2.0f), pos.Z - (size.Z / 2.0f)), vec2f(1 * texScale.X, 0 * texScale.Y)), // Bottom right
		Vertex(vec3f(pos.X + (size.X / 2.0f), pos.Y + (size.Y / 2.0f), pos.Z - (size.Z / 2.0f)), vec2f(1 * texScale.X, 1 * texScale.Y)), // Top Right
		Vertex(vec3f(pos.X - (size.X / 2.0f), pos.Y + (size.Y / 2.0f), pos.Z - (size.Z / 2.0f)), vec2f(0 * texScale.X, 1 * texScale.Y)), // Top left
		
		// Front
		Vertex(vec3f(pos.X - (size.X / 2.0f), pos.Y - (size.Y / 2.0f), pos.Z + (size.Z / 2.0f)), vec2f(0 * texScale.X, 0 * texScale.Y)), // Bottom left
		Vertex(vec3f(pos.X + (size.X / 2.0f), pos.Y - (size.Y / 2.0f), pos.Z + (size.Z / 2.0f)), vec2f(1 * texScale.X, 0 * texScale.Y)), // Bottom right
		Vertex(vec3f(pos.X + (size.X / 2.0f), pos.Y + (size.Y / 2.0f), pos.Z + (size.Z / 2.0f)), vec2f(1 * texScale.X, 1 * texScale.Y)), // Top Right
		Vertex(vec3f(pos.X - (size.X / 2.0f), pos.Y + (size.Y / 2.0f), pos.Z + (size.Z / 2.0f)), vec2f(0 * texScale.X, 1 * texScale.Y)), // Top left

		// Left side
		Vertex(vec3f(pos.X - (size.X / 2.0f), pos.Y - (size.Y / 2.0f), pos.Z - (size.Z / 2.0f)), vec2f(0 * texScale.X, 0 * texScale.Y)), // Bottom left
		Vertex(vec3f(pos.X - (size.X / 2.0f), pos.Y - (size.Y / 2.0f), pos.Z + (size.Z / 2.0f)), vec2f(1 * texScale.X, 0 * texScale.Y)), // Bottom right
		Vertex(vec3f(pos.X - (size.X / 2.0f), pos.Y + (size.Y / 2.0f), pos.Z + (size.Z / 2.0f)), vec2f(1 * texScale.X, 1 * texScale.Y)), // Top Right
		Vertex(vec3f(pos.X - (size.X / 2.0f), pos.Y + (size.Y / 2.0f), pos.Z - (size.Z / 2.0f)), vec2f(0 * texScale.X, 1 * texScale.Y)), // Top left

		// Right side
		Vertex(vec3f(pos.X + (size.X / 2.0f), pos.Y - (size.Y / 2.0f), pos.Z - (size.Z / 2.0f)), vec2f(0 * texScale.X, 0 * texScale.Y)), // Bottom left
		Vertex(vec3f(pos.X + (size.X / 2.0f), pos.Y - (size.Y / 2.0f), pos.Z + (size.Z / 2.0f)), vec2f(1 * texScale.X, 0 * texScale.Y)), // Bottom right
		Vertex(vec3f(pos.X + (size.X / 2.0f), pos.Y + (size.Y / 2.0f), pos.Z + (size.Z / 2.0f)), vec2f(1 * texScale.X, 1 * texScale.Y)), // Top Right
		Vertex(vec3f(pos.X + (size.X / 2.0f), pos.Y + (size.Y / 2.0f), pos.Z - (size.Z / 2.0f)), vec2f(0 * texScale.X, 1 * texScale.Y)), // Top left			
	};

	unsigned int indices[36] =
	{			
		// Up, Front, Left ==> (0, 1, 2), (0, 2, 3)
		// Down, Back, Right ==> (2, 1, 0), (3, 2, 0)

		// Down, Back, Right = Reverse(Up, Front, Left)
		
		// Up
		0, 1, 2,
		0, 2, 3,

		// Down
		2 + 4, 1 + 4, 0 + 4,
		3 + 4, 2 + 4, 0 + 4,

		// Back
		2 + 8, 1 + 8, 0 + 8,
		3 + 8, 2 + 8, 0 + 8,

		// Front
		0 + 12, 1 + 12, 2 + 12,
		0 + 12, 2 + 12, 3 + 12,

		// Left side
		0 + 16, 1 + 16, 2 + 16,
		0 + 16, 2 + 16, 3 + 16,

		// Right side
		2 + 20, 1 + 20, 0 + 20,
		3 + 20, 2 + 20, 0 + 20,
		
	};

	GLShape shape = CreateShape(vertices, 24, indices, 36, withNormals);

	return shape;
}

Renderable& OpenGLRenderer::AddCuboid(char *name, vec3f pos, vec3f size, vec2f texScale, vec4f color, float shininess, char *material, bool withNormals)
{
	Renderable renderable = GetRenderable(name);

	if (!renderable.Shape.IsAvailable())
	{
		renderable.Shape = CreateCuboid(pos, size, texScale, withNormals);

		renderable.Skin = GetMaterial(material);

		renderable.Color = color;

		renderable.Skin.Shininess = shininess;

		renderable.Name = name;

		Renderables[name] = renderable;
	}

	return renderable;
}

Renderable& OpenGLRenderer::AddLamp(char *name, vec3f pos, vec3f size, vec4f color, float ambientStrength, float attenuation, char *material)
{
	SimpleLamp lamp = GetLamp(name); 

	if (!lamp.Shape.IsAvailable())
	{
		lamp.Shape = CreateCuboid(pos, size, vec2f(1, 1), false);

		lamp.Skin = GetMaterial(material);

		lamp.Color = color;

		lamp.AmbientStrength = ambientStrength;

		lamp.Attenuation = attenuation;

		lamp.Name = name;

		Lamps[name] = lamp;
	}

	return lamp;
}

void OpenGLRenderer::AddTexture(char *path, char *name, bool invertY)
{
	if (TextureCache.find(name) == TextureCache.end())
	{
		Texture texture = Texture(path, invertY);

		TextureCache[name] = texture;
	}
}

Texture OpenGLRenderer::GetTexture(char *name) 
{
	if (TextureCache.find(name) != TextureCache.end())
	{
		return TextureCache[name];
	}

	Texture texture;

	return texture;
}

void OpenGLRenderer::RemoveTexture(char *name)
{
	Texture texture = GetTexture(name);

	if (texture.TextureID)
	{
		texture.UnloadTexture();

		TextureCache.erase(name);
	}
}

void OpenGLRenderer::AddMaterial(char *name, Material material) 
{
	if (MaterialCache.find(name) == MaterialCache.end())
	{
		MaterialCache[name] = material;
	}
}

Material OpenGLRenderer::GetMaterial(char *name) 
{
	if (MaterialCache.find(name) != MaterialCache.end())
	{
		return MaterialCache[name];
	}

	return Material{};
}

void OpenGLRenderer::RemoveMaterial(char *name) 
{
	Material material = GetMaterial(name);

	if (MaterialCache.find(name) != MaterialCache.end())
	{
		material.DiffuseSkin.UnloadTexture();
		material.SpecularSkin.UnloadTexture();

		MaterialCache.erase(name);
	}
}

void OpenGLRenderer::RenderShapes(OpenGLShader *shader)
{
	/*
	shader->Activate();

	unsigned int modelLoc = glGetUniformLocation(shader->Program, "model");
	unsigned int viewLoc = glGetUniformLocation(shader->Program, "view");
	unsigned int projectionLoc = glGetUniformLocation(shader->Program, "projection");

	glUniformMatrix4fv(viewLoc, 1, 0, MainCamera.GetViewMatrix().Elements_1D);
	glUniformMatrix4fv(projectionLoc, 1, 0, MainCamera.GetProjectionMatrix().Elements_1D);	

	std::map<char *, Renderable>::iterator renderable;
	for (renderable = Renderables.begin(); renderable != Renderables.end(); renderable++)
	{
		//renderable->second.Orientation.Update();

		glUniformMatrix4fv(modelLoc, 1, 0, renderable->second.Orientation.GetModelMatrix().Elements_1D);

		bool withTexture = renderable->second.Skin.IsAvailable();
		
		if (withTexture)
		{
			renderable->second.Skin.BindTexture();
		}

		renderable->second.Shape.BindBuffers();

		glDrawElements(GL_TRIANGLES, renderable->second.Shape.IndicesCount, GL_UNSIGNED_INT, 0);

		renderable->second.Shape.UnbindBuffers();

		if (withTexture)
		{
			renderable->second.Skin.UnbindTexture();
		}
	}
	*/
}

void OpenGLRenderer::RenderShape(Renderable *renderable, OpenGLShader *shader, SimpleLamp *lamp)
{
	shader->Activate();

	unsigned int modelLoc = glGetUniformLocation(shader->Program, "model");
	unsigned int viewLoc = glGetUniformLocation(shader->Program, "view");
	unsigned int projectionLoc = glGetUniformLocation(shader->Program, "projection");
	unsigned int eyeLoc = glGetUniformLocation(shader->Program, "eyePos");

	glUniformMatrix4fv(viewLoc, 1, 0, MainCamera.GetViewMatrix().Elements_1D);
	glUniformMatrix4fv(projectionLoc, 1, 0, MainCamera.GetProjectionMatrix().Elements_1D); 
	glUniformMatrix4fv(modelLoc, 1, 0, renderable->Orientation.GetModelMatrix().Elements_1D);
	glUniform3f(eyeLoc, MainCamera.Eye.X, MainCamera.Eye.Y, MainCamera.Eye.Z);

	if (lamp)
	{
		{
			unsigned int objColLoc = glGetUniformLocation(shader->Program, "objectColor");
			unsigned int shiLoc = glGetUniformLocation(shader->Program, "objMaterial.Shininess");

			glUniform4f(objColLoc, renderable->Color.R, renderable->Color.G, renderable->Color.B, renderable->Color.A);
			glUniform1f(shiLoc, renderable->Skin.Shininess);
		}

		{			
			unsigned int dir_ambColLoc = glGetUniformLocation(shader->Program, "directional.Ambient");
			unsigned int dir_diffColLoc = glGetUniformLocation(shader->Program, "directional.Diffuse");
			unsigned int dir_specColLoc = glGetUniformLocation(shader->Program, "directional.Specular");
			unsigned int dir_dirLoc = glGetUniformLocation(shader->Program, "directional.Direction");
			unsigned int dir_ambStrLoc = glGetUniformLocation(shader->Program, "directional.AmbientStrength");

			glUniform4f(dir_ambColLoc, Directional.AmbientColor.R, Directional.AmbientColor.G, Directional.AmbientColor.B, Directional.AmbientColor.A);
			glUniform4f(dir_diffColLoc, Directional.DiffuseColor.R, Directional.DiffuseColor.G, Directional.DiffuseColor.B, Directional.DiffuseColor.A);
			glUniform4f(dir_specColLoc, Directional.SpecularColor.R, Directional.SpecularColor.G, Directional.SpecularColor.B, Directional.SpecularColor.A);
			glUniform3f(dir_dirLoc, Directional.Direction.X, Directional.Direction.Y, Directional.Direction.Z);
			glUniform1f(dir_ambStrLoc, Directional.AmbientStrength);
		}
		
		{
			unsigned int point_ambColLoc = glGetUniformLocation(shader->Program, "point.Ambient");
			unsigned int point_diffColLoc = glGetUniformLocation(shader->Program, "point.Diffuse");
			unsigned int point_specColLoc = glGetUniformLocation(shader->Program, "point.Specular");
			unsigned int point_posLoc = glGetUniformLocation(shader->Program, "point.Position");
			unsigned int point_ambStrLoc = glGetUniformLocation(shader->Program, "point.AmbientStrength");
			unsigned int point_atten_conLoc = glGetUniformLocation(shader->Program, "point.Atten.Constant");
			unsigned int point_atten_linLoc = glGetUniformLocation(shader->Program, "point.Atten.Linear");
			unsigned int point_atten_quadLoc = glGetUniformLocation(shader->Program, "point.Attenu.Quadratic");

			glUniform4f(point_ambColLoc, Point.AmbientColor.R, Point.AmbientColor.G, Point.AmbientColor.B, Point.AmbientColor.A);
			glUniform4f(point_diffColLoc, Point.DiffuseColor.R, Point.DiffuseColor.G, Point.DiffuseColor.B, Point.DiffuseColor.A);
			glUniform4f(point_specColLoc, Point.SpecularColor.R, Point.SpecularColor.G, Point.SpecularColor.B, Point.SpecularColor.A);
			glUniform3f(point_posLoc, Point.Position.X, Point.Position.Y, Point.Position.Z);
			glUniform1f(point_ambStrLoc, Point.AmbientStrength);
			glUniform1f(point_atten_conLoc, Point.Atten.Constant);
			glUniform1f(point_atten_linLoc, Point.Atten.Linear);
			glUniform1f(point_atten_quadLoc, Point.Atten.Quadratic);
		}
		{			
			for (unsigned int i = 0; i < NUM_POINT_LIGHT; i++)
			{
				std::string index = std::to_string(i);
				std::string s = "points[" + index + "].";

				unsigned int point_ambColLoc = glGetUniformLocation(shader->Program, (s + "Ambient").c_str());
				unsigned int point_diffColLoc = glGetUniformLocation(shader->Program, (s + "Diffuse").c_str());
				unsigned int point_specColLoc = glGetUniformLocation(shader->Program, (s + "Specular").c_str());
				unsigned int point_posLoc = glGetUniformLocation(shader->Program, (s + "Position").c_str());
				unsigned int point_ambStrLoc = glGetUniformLocation(shader->Program, (s + "AmbientStrength").c_str());
				unsigned int point_atten_conLoc = glGetUniformLocation(shader->Program, (s + "Atten.Constant").c_str());
				unsigned int point_atten_linLoc = glGetUniformLocation(shader->Program, (s + "Atten.Linear").c_str());
				unsigned int point_atten_quadLoc = glGetUniformLocation(shader->Program, (s + "Attenu.Quadratic").c_str());

				glUniform4f(point_ambColLoc, Points[i].AmbientColor.R, Points[i].AmbientColor.G, Points[i].AmbientColor.B, Points[i].AmbientColor.A);
				glUniform4f(point_diffColLoc, Points[i].DiffuseColor.R, Points[i].DiffuseColor.G, Points[i].DiffuseColor.B, Points[i].DiffuseColor.A);
				glUniform4f(point_specColLoc, Points[i].SpecularColor.R, Points[i].SpecularColor.G, Points[i].SpecularColor.B, Points[i].SpecularColor.A);
				glUniform3f(point_posLoc, Points[i].Position.X, Points[i].Position.Y, Points[i].Position.Z);
				glUniform1f(point_ambStrLoc, Points[i].AmbientStrength);
				glUniform1f(point_atten_conLoc, Points[i].Atten.Constant);
				glUniform1f(point_atten_linLoc, Points[i].Atten.Linear);
				glUniform1f(point_atten_quadLoc, Points[i].Atten.Quadratic);
			}
		}
		
		{
			unsigned int spot_ambColLoc = glGetUniformLocation(shader->Program, "spot.Ambient");
			unsigned int spot_diffColLoc = glGetUniformLocation(shader->Program, "spot.Diffuse");
			unsigned int spot_specColLoc = glGetUniformLocation(shader->Program, "spot.Specular");
			unsigned int spot_posLoc = glGetUniformLocation(shader->Program, "spot.Position");
			unsigned int spot_dirLoc = glGetUniformLocation(shader->Program, "spot.Direction");
			unsigned int spot_ambStrLoc = glGetUniformLocation(shader->Program, "spot.AmbientStrength");
			unsigned int spot_atten_conLoc = glGetUniformLocation(shader->Program, "spot.Atten.Constant");
			unsigned int spot_atten_linLoc = glGetUniformLocation(shader->Program, "spot.Atten.Linear");
			unsigned int spot_atten_quadLoc = glGetUniformLocation(shader->Program, "spot.Attenu.Quadratic");
			unsigned int spot_in_cutLoc = glGetUniformLocation(shader->Program, "spot.InnerCut");
			unsigned int spot_out_cutLoc = glGetUniformLocation(shader->Program, "spot.OuterCut");

			glUniform4f(spot_ambColLoc, Spot.AmbientColor.R, Spot.AmbientColor.G, Spot.AmbientColor.B, Spot.AmbientColor.A);
			glUniform4f(spot_diffColLoc, Spot.DiffuseColor.R, Spot.DiffuseColor.G, Spot.DiffuseColor.B, Spot.DiffuseColor.A);
			glUniform4f(spot_specColLoc, Spot.SpecularColor.R, Spot.SpecularColor.G, Spot.SpecularColor.B, Spot.SpecularColor.A);
			glUniform3f(spot_posLoc, Spot.Position->X, Spot.Position->Y, Spot.Position->Z);
			glUniform3f(spot_dirLoc, Spot.Direction->X, Spot.Direction->Y, Spot.Direction->Z);
			glUniform1f(spot_ambStrLoc, Spot.AmbientStrength);
			glUniform1f(spot_atten_conLoc, Spot.Atten.Constant);
			glUniform1f(spot_atten_linLoc, Spot.Atten.Linear);
			glUniform1f(spot_atten_quadLoc, Spot.Atten.Quadratic);
			glUniform1f(spot_in_cutLoc, Spot.InnerCut);
			glUniform1f(spot_out_cutLoc, Spot.OuterCut);
		}		
	}
	else
	{
		//if (renderable->Name == "lamp")
		{
			unsigned int liColLoc = glGetUniformLocation(shader->Program, "lightColor");
			glUniform4f(liColLoc, renderable->Color.R, renderable->Color.G, renderable->Color.B, renderable->Color.A);
		}
	}

	bool withDiffueTexture = renderable->Skin.DiffuseSkin.IsAvailable();
	bool withSpecularTexture = renderable->Skin.DiffuseSkin.IsAvailable();

	if (withDiffueTexture)
	{
		unsigned int diffLoc = glGetUniformLocation(shader->Program, "objMaterial.Diffuse");
		glUniform1i(diffLoc, 0);

		renderable->Skin.DiffuseSkin.BindTexture(0);
	}

	if (withSpecularTexture)
	{
		unsigned int specLoc = glGetUniformLocation(shader->Program, "objMaterial.Specular");
		glUniform1i(specLoc, 1);

		renderable->Skin.SpecularSkin.BindTexture(1);
	}

	renderable->Shape.BindBuffers();

	glDrawElements(GL_TRIANGLES, renderable->Shape.IndicesCount, GL_UNSIGNED_INT, 0);

	renderable->Shape.UnbindBuffers();

	if (withDiffueTexture)
	{
		renderable->Skin.DiffuseSkin.UnbindTexture();
	}

	if (withSpecularTexture)
	{
		renderable->Skin.SpecularSkin.UnbindTexture();
	}
}

void OpenGLRenderer::Update() 
{
	MainCamera.Update();
}


void OpenGLRenderer::AddShader(OpenGLShader shader, char *name) 
{	
	if (ShaderCache.find(name) == ShaderCache.end())
	{
		ShaderCache[name] = shader;
	}
}

OpenGLShader OpenGLRenderer::GetShader(char *name)
{
	if (ShaderCache.find(name) != ShaderCache.end())
	{
		return ShaderCache[name];
	}

	OpenGLShader shader;

	return shader;
}

void OpenGLRenderer::RemoveShader(char *name)
{
	OpenGLShader shader = GetShader(name);

	if (shader.IsAvailable())
	{
		shader.Unload();

		ShaderCache.erase(name);
	}
}

void OpenGLRenderer::DestroyShape(GLShape *shape)
{
	if (shape)
	{
		shape->Destroy();
	}
}

Renderable& OpenGLRenderer::GetRenderable(char *name)
{
	if (Renderables.find(name) != Renderables.end())
	{
		return Renderables[name];
	}

	return Renderable{};
}

void OpenGLRenderer::RemoveRenderable(char *name)
{
	Renderable renderable = GetRenderable(name);

	if (renderable.Shape.IsAvailable())
	{
		renderable.Shape.Destroy();

		Renderables.erase(name);
	}
}

SimpleLamp& OpenGLRenderer::GetLamp(char *name) 
{
	if (Lamps.find(name) != Lamps.end())
	{
		return Lamps[name];
	}

	return SimpleLamp{};
}

void OpenGLRenderer::RemoveLamp(char *name) 
{
	SimpleLamp lamp = GetLamp(name);

	if (lamp.Shape.IsAvailable())
	{
		lamp.Shape.Destroy();

		Lamps.erase(name);
	}
}