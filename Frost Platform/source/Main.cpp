#include <WindowManager.h>
#include <GLShader.h>
#include <OpenGLRenderer.h>
#include <InputManager.h>

//int main() 
//{
//	if (WindowManager::CreateOpenGLWindow(1280, 720, "test") != true)
//	{
//		return -1;
//	}
//
//	//WindowManager::SetClearColor(0, 0.5f, 0.8f, 1);
//	InputManager::Init(WindowManager::Window);
//
//	OpenGLShader firstShader = OpenGLShader("res\\shaders\\simple vertex shader.vert",
//											"res\\shaders\\simple fragment shader.frag");
//
//	OpenGLShader secondShader = OpenGLShader("res\\shaders\\simple vertex shader.vert",
//											"res\\shaders\\simple lamp frag shader.frag");
//
//	firstShader.CreateShaders();
//	secondShader.CreateShaders();
//
//	OpenGLRenderer renderer;
//	
//	renderer.MainCamera.SetPerspective();
//	
//	renderer.AddTexture("res\\textures\\wall.jpg", "wall");
//	renderer.AddTexture("res\\textures\\empty.png", "empty");
//	renderer.AddTexture("res\\textures\\container2.png", "container");
//	renderer.AddTexture("res\\textures\\container2_specular.png", "container_specular");
//
//	renderer.AddMaterial("wall", Material{ renderer.GetTexture("wall") });
//	renderer.AddMaterial("empty", Material{ renderer.GetTexture("empty") });
//	renderer.AddMaterial("container", Material{ renderer.GetTexture("container"), renderer.GetTexture("container_specular") });
//	
//	renderer.AddShader(firstShader, "first");
//
//	renderer.AddShader(secondShader, "second");
//	renderer.AddCuboid("floor", vec3f(0, -40), vec3f(200, 0.1f, 200), vec2f(8, 8), vec4f(1, 0.6, 0.7, 1), 2, "wall");
//	renderer.AddCuboid("floor1", vec3f(0, -40, -102), vec3f(200, 120, 0.1f), vec2f(8, 8), vec4f(1, 1, 1, 1), 2, "wall");
//	renderer.AddCuboid("floor2", vec3f(0, -40, 95), vec3f(200, 120, 0.1f), vec2f(8, 8), vec4f(1, 1, 1, 1), 2, "wall");
//	renderer.AddCuboid("floor3", vec3f(0, 10), vec3f(200, 0.1f, 200), vec2f(25, 25), vec4f(1, 0.6, 0.7, 1), 2, "container");
//
//	renderer.AddCuboid("cube1", vec3f(), vec3f(2, 2, 2), vec2f(1, 1), vec4f(1, 1, 1, 1), 2, "container");
//	renderer.AddCuboid("cube2", vec3f(), vec3f(4, 4, 4), vec2f(1, 1), vec4f(1, 1, 1, 1), 2, "container");
//	renderer.AddCuboid("cube3", vec3f(), vec3f(10, 20.0f, 5), vec2f(2, 3), vec4f(1, 1, 1, 1), 2, "container");
//	renderer.AddCuboid("cube4", vec3f(), vec3f(3.5f, 3.5f, 3.5f), vec2f(1, 1), vec4f(1, 1, 1, 1), 2, "container");
//	renderer.AddCuboid("cube5", vec3f(), vec3f(2.5f, 2.5f, 2.5f), vec2f(1, 1), vec4f(1, 1, 1, 1), 2, "container");
//	renderer.AddCuboid("cube6", vec3f(), vec3f(10, 20.0f, 5), vec2f(2, 3), vec4f(1, 1, 1, 1), 2, "wall");
//	renderer.AddCuboid("cube7", vec3f(), vec3f(3.5f, 3.5f, 3.5f), vec2f(1, 1), vec4f(1, 1, 1, 1), 2, "container");
//	renderer.AddCuboid("cube8", vec3f(), vec3f(10, 20.0f, 5), vec2f(2, 3), vec4f(1, 1, 1, 1), 2, "wall");
//	renderer.AddCuboid("cube9", vec3f(), vec3f(3.5f, 3.5f, 3.5f), vec2f(1, 1), vec4f(1, 1, 1, 1), 2, "container");
//	renderer.AddCuboid("cube10", vec3f(), vec3f(3, 3, 3), vec2f(1, 1), vec4f(1, 1, 1, 1), 2, "container");
//
//	renderer.AddLamp("lamp", vec3f(), vec3f(1.5f, 1.5f, 1.5f), vec4f(0, 1, 0, 1), 0.53f, 0, "empty");
//	renderer.AddLamp("lamp0", vec3f(), vec3f(1.5f, 1.5f, 1.5f), vec4f(0, 0.5f, 1, 1), 0.53f, 0, "empty");
//	renderer.AddLamp("lamp1", vec3f(), vec3f(1.5f, 1.5f, 1.5f), vec4f(0, 1, 0.7f, 1), 0.53f, 0, "empty");
//	renderer.AddLamp("lamp2", vec3f(), vec3f(1.5f, 1.5f, 1.5f), vec4f(0.4f, 0, 1, 1), 0.53f, 0, "empty");
//	renderer.AddLamp("lamp3", vec3f(), vec3f(1.5f, 1.5f, 1.5f), vec4f(1, 0.4f, 0.5f, 1), 0.5f, 0, "empty");
//	renderer.AddLamp("lamp4", vec3f(), vec3f(1.5f, 1.5f, 1.5f), vec4f(0.8, 0.4f, 0.5f, 1), 0.5f, 0, "empty");
//	renderer.AddLamp("lamp5", vec3f(), vec3f(1.5f, 1.5f, 1.5f), vec4f(0.3, 0.4f, 0.5f, 1), 0.5f, 0, "empty");
//	renderer.AddLamp("lamp6", vec3f(), vec3f(1.5f, 1.5f, 1.5f), vec4f(0, 0.8f, 0.3f, 1), 0.5f, 0, "empty");
//	renderer.AddLamp("lamp7", vec3f(), vec3f(1.5f, 1.5f, 1.5f), vec4f(1, 0.3f, 0.8f, 1), 0.5f, 0, "empty");
//	renderer.AddLamp("lamp8", vec3f(), vec3f(1.5f, 1.5f, 1.5f), vec4f(0.4, 0.4f, 0.9f, 1), 0.5f, 0, "empty");
//	renderer.AddLamp("lamp9", vec3f(), vec3f(1.5f, 1.5f, 1.5f), vec4f(1, 0, 0.5f, 1), 0.5f, 0, "empty");	
//
//	renderer.GetRenderable("cube1").Orientation.Position.Z = 0.0f;
//	renderer.GetRenderable("cube1").Orientation.Rotation.Y += -35.0f;
//
//	renderer.GetRenderable("cube2").Orientation.Position.Z = 5.0f;
//	//renderer.GetRenderable("cube2").Orientation.Position.X = 15.0f;
//	renderer.GetRenderable("cube2").Orientation.Position.Y = -35.0f;
//	//renderer.GetRenderable("cube2").Orientation.Rotation += vec3f(100.0f, 100.0f, 100.0f);
//
//	renderer.GetRenderable("cube3").Orientation.Position.Z = 10.0f;
//	//renderer.GetRenderable("cube3").Orientation.Position.X = 8.0f;
//	renderer.GetRenderable("cube3").Orientation.Position.Y = -35.0f;
//	//renderer.GetRenderable("cube3").Orientation.Rotation += vec3f(2.0f, 2.0f, 2.0f);
//
//	renderer.GetRenderable("cube4").Orientation.Position.Z = 15.0f;
//	//renderer.GetRenderable("cube4").Orientation.Position.X = 5.0f;
//	renderer.GetRenderable("cube4").Orientation.Position.Y = -35.0f;
//	//renderer.GetRenderable("cube4").Orientation.Rotation += vec3f(15.0f, 15.0f, 15.0f);
//
//	renderer.GetRenderable("cube5").Orientation.Position.Z = -5.0f;
//	//renderer.GetRenderable("cube5").Orientation.Position.X = -14.0f;
//	renderer.GetRenderable("cube5").Orientation.Position.Y = -35.0f;
//	//renderer.GetRenderable("cube5").Orientation.Rotation += vec3f(51.0f, 51.0f, 51.0f);
//
//	renderer.GetRenderable("cube6").Orientation.Position.Z = -10.0f;
//	//renderer.GetRenderable("cube6").Orientation.Position.X = -7.0f;
//	renderer.GetRenderable("cube6").Orientation.Position.Y = -35.0f;
//	//renderer.GetRenderable("cube6").Orientation.Rotation += vec3f(10.0f, 10.0f, 10.0f);
//
//	renderer.GetRenderable("cube7").Orientation.Position.Z = -15.0f;
//	//renderer.GetRenderable("cube7").Orientation.Position.X = 17.0f;
//	renderer.GetRenderable("cube7").Orientation.Position.Y = -35.0f;
//	//renderer.GetRenderable("cube7").Orientation.Rotation += vec3f(7.0f, 7.0f, 7.0f);
//
//	renderer.GetRenderable("cube8").Orientation.Position.Z = 20.0f;
//	//renderer.GetRenderable("cube8").Orientation.Position.X = 12.0f;
//	renderer.GetRenderable("cube8").Orientation.Position.Y = -35.0f;
//	//renderer.GetRenderable("cube8").Orientation.Rotation += vec3f(3.0f, 3.0f, 3.0f);
//
//	renderer.GetRenderable("cube9").Orientation.Position.Z = -20.0f;
//	//renderer.GetRenderable("cube9").Orientation.Position.Z = -15.0f;
//	renderer.GetRenderable("cube9").Orientation.Position.Z = -35.0f;
//	//renderer.GetRenderable("cube9").Orientation.Rotation += vec3f(5.0f, 5.0f, 5.0f);
//
//	renderer.GetRenderable("cube10").Orientation.Position.Z = -25.0f;
//	//renderer.GetRenderable("cube10").Orientation.Position.X = 17.0f;
//	renderer.GetRenderable("cube10").Orientation.Position.Y = -35.0f;
//	//renderer.GetRenderable("cube10").Orientation.Rotation += vec3f(50.0f, 50.0f, 50.0f);
//	
//	renderer.GetLamp("lamp").Orientation.Position.Z = 2;
//	renderer.GetLamp("lamp").Orientation.Position.X = 8;
//	renderer.GetLamp("lamp").Orientation.Position.Y = 15.0f;
//
//	renderer.GetLamp("lamp0").Orientation.Position.Z = 2;
//	renderer.GetLamp("lamp0").Orientation.Position.X = -8;
//	renderer.GetLamp("lamp0").Orientation.Position.Y = 15.0f;
//
//	renderer.GetLamp("lamp0").Orientation.Position.Z = 8;
//	renderer.GetLamp("lamp0").Orientation.Position.X = 8;
//	renderer.GetLamp("lamp0").Orientation.Position.Y = 15.0f;
//
//	renderer.GetLamp("lamp1").Orientation.Position.Z = 8;
//	renderer.GetLamp("lamp1").Orientation.Position.X = -8;
//	renderer.GetLamp("lamp1").Orientation.Position.Y = 15.0f;
//
//	renderer.GetLamp("lamp2").Orientation.Position.Z = 14;
//	renderer.GetLamp("lamp2").Orientation.Position.X = 8;
//	renderer.GetLamp("lamp2").Orientation.Position.Y = 15.0f;
//
//	renderer.GetLamp("lamp3").Orientation.Position.Z = 14;
//	renderer.GetLamp("lamp3").Orientation.Position.X = -8;
//	renderer.GetLamp("lamp3").Orientation.Position.Y = 15.0f;
//
//	renderer.GetLamp("lamp4").Orientation.Position.Z = 20;
//	renderer.GetLamp("lamp4").Orientation.Position.X = 8;
//	renderer.GetLamp("lamp4").Orientation.Position.Y = 15.0f;
//
//	renderer.GetLamp("lamp5").Orientation.Position.Z = 20;
//	renderer.GetLamp("lamp5").Orientation.Position.X = -8;
//	renderer.GetLamp("lamp5").Orientation.Position.Y = 15.0f;
//
//	renderer.GetLamp("lamp6").Orientation.Position.Z = 26;
//	renderer.GetLamp("lamp6").Orientation.Position.X = 8;
//	renderer.GetLamp("lamp6").Orientation.Position.Y = 15.0f;
//
//	renderer.GetLamp("lamp7").Orientation.Position.Z = 26;
//	renderer.GetLamp("lamp7").Orientation.Position.X = -8;
//	renderer.GetLamp("lamp7").Orientation.Position.Y = 15.0f;
//
//	renderer.GetLamp("lamp8").Orientation.Position.Z = 32;
//	renderer.GetLamp("lamp8").Orientation.Position.X = 8;
//	renderer.GetLamp("lamp8").Orientation.Position.Y = 15.0f;
//
//	renderer.GetLamp("lamp9").Orientation.Position.Z = 32;
//	renderer.GetLamp("lamp9").Orientation.Position.X = -8;
//	renderer.GetLamp("lamp9").Orientation.Position.Y = 15.0f;
//
//	renderer.Directional = 
//		DirectionalLight
//		{
//			vec3f(-0, 0, -0), 
//			vec4f(1, 1, 1, 1), 
//			vec4f(1, 1, 1, 1),
//			vec4f(1, 1, 1, 1),
//			0.002f
//		};
//
//	renderer.Point =
//		PointLight
//		{
//			renderer.GetLamp("lamp").Orientation.Position,
//			vec4f(0, 1, 0, 1),
//			vec4f(0, 1, 0, 1),
//			vec4f(0, 1, 0, 1),
//			Attenuation {1, 0.22f, 0.2f },
//			0.2f
//		};
//	
//	{
//		renderer.Points[0] =
//			PointLight
//		{
//			renderer.GetLamp("lamp0").Orientation.Position,
//			vec4f(0, 0.5f, 1, 1),
//			vec4f(0, 0.5f, 1, 1),
//			vec4f(0, 0.5f, 1, 1),
//			Attenuation{ 1, 0.22f, 0.2f },
//			0.002f
//		};
//
//		renderer.Points[1] =
//			PointLight
//		{
//			renderer.GetLamp("lamp1").Orientation.Position,
//			vec4f(0, 1, 0.7f, 1),
//			vec4f(0, 1, 0.7f, 1),
//			vec4f(0, 1, 0.7f, 1),
//			Attenuation{ 1, 0.22f, 0.2f },
//			0.002f
//		};
//
//		renderer.Points[2] =
//			PointLight
//		{
//			renderer.GetLamp("lamp2").Orientation.Position,
//			vec4f(0.4f, 0, 1, 1),
//			vec4f(0.4f, 0, 1, 1),
//			vec4f(0.4f, 0, 1, 1),
//			Attenuation{ 1, 0.22f, 0.2f },
//			0.002f
//		};
//
//		renderer.Points[3] =
//			PointLight
//		{
//			renderer.GetLamp("lamp3").Orientation.Position,
//			vec4f(1, 0.4f, 0.5f, 1),
//			vec4f(1, 0.4f, 0.5f, 1),
//			vec4f(1, 0.4f, 0.5f, 1),
//			Attenuation{ 1, 0.22f, 0.2f },
//			0.002f
//		};
//
//		renderer.Points[4] =
//			PointLight
//		{
//			renderer.GetLamp("lamp4").Orientation.Position,
//			vec4f(0.8, 0.4f, 0.5f, 1),
//			vec4f(0.8, 0.4f, 0.5f, 1),
//			vec4f(0.8, 0.4f, 0.5f, 1),
//			Attenuation{ 1, 0.22f, 0.2f },
//			0.002f
//		};
//
//		renderer.Points[5] =
//			PointLight
//		{
//			renderer.GetLamp("lamp5").Orientation.Position,
//			vec4f(0.3, 0.4f, 0.5f, 1),
//			vec4f(0.3, 0.4f, 0.5f, 1),
//			vec4f(0.3, 0.4f, 0.5f, 1),
//			Attenuation{ 1, 0.22f, 0.2f },
//			0.002f
//		};
//
//		renderer.Points[6] =
//			PointLight
//		{
//			renderer.GetLamp("lamp6").Orientation.Position,
//			vec4f(0, 0.8f, 0.3f, 1),
//			vec4f(0, 0.8f, 0.3f, 1),
//			vec4f(0, 0.8f, 0.3f, 1),
//			Attenuation{ 1, 0.22f, 0.2f },
//			0.002f
//		};
//
//		renderer.Points[7] =
//			PointLight
//		{
//			renderer.GetLamp("lamp7").Orientation.Position,
//			vec4f(1, 0.3f, 0.8f, 1),
//			vec4f(1, 0.3f, 0.8f, 1),
//			vec4f(1, 0.3f, 0.8f, 1),
//			Attenuation{ 1, 0.22f, 0.2f },
//			0.002f
//		};
//
//		renderer.Points[8] =
//			PointLight
//		{
//			renderer.GetLamp("lamp8").Orientation.Position,
//			vec4f(0.4, 0.4f, 0.9f, 1),
//			vec4f(0.4, 0.4f, 0.9f, 1),
//			vec4f(0.4, 0.4f, 0.9f, 1),
//			Attenuation{ 1, 0.22f, 0.2f },
//			0.002f
//		};
//
//		renderer.Points[9] =
//			PointLight
//		{
//			renderer.GetLamp("lamp9").Orientation.Position,
//			vec4f(1, 0, 0.5f, 1),
//			vec4f(1, 0, 0.5f, 1),
//			vec4f(1, 0, 0.5f, 1),
//			Attenuation{ 1, 0.22f, 0.2f },
//			0.002f
//		};
//	}
//
//	renderer.Spot =
//		SpotLight
//		{
//			&renderer.MainCamera.Eye,
//			&renderer.MainCamera.Target,
//			vec4f(1, 1, 1, 1),
//			vec4f(1, 1, 1, 1),
//			vec4f(1, 1, 1, 1),
//			Attenuation{ 1, 0.22f, 0.2f },
//			0.2f,
//			cosf(ToRadians(15.5f)),
//			cosf(ToRadians(19.5f))
//		};
//	
//	while (!WindowManager::ShouldClose())
//	{
//		WindowManager::Update();
//
//		renderer.Update();
//
//		/*renderer.RenderShape(&renderer.GetLamp("lamp"), &secondShader);
//
//		renderer.RenderShape(&renderer.GetLamp("lamp0"), &secondShader);
//		renderer.RenderShape(&renderer.GetLamp("lamp1"), &secondShader);
//		renderer.RenderShape(&renderer.GetLamp("lamp2"), &secondShader);
//		renderer.RenderShape(&renderer.GetLamp("lamp3"), &secondShader);
//		renderer.RenderShape(&renderer.GetLamp("lamp4"), &secondShader);
//		renderer.RenderShape(&renderer.GetLamp("lamp5"), &secondShader);
//		renderer.RenderShape(&renderer.GetLamp("lamp6"), &secondShader);
//		renderer.RenderShape(&renderer.GetLamp("lamp7"), &secondShader);
//		renderer.RenderShape(&renderer.GetLamp("lamp8"), &secondShader);
//		renderer.RenderShape(&renderer.GetLamp("lamp9"), &secondShader);*/
//
//		/*renderer.RenderShape(&renderer.GetRenderable("floor1"), &secondShader);
//		renderer.RenderShape(&renderer.GetRenderable("floor2"), &secondShader);
//		renderer.RenderShape(&renderer.GetRenderable("floor3"), &secondShader);*/
//
//		//renderer.RenderShape(&renderer.GetLamp("lamp"), &secondShader);
//
//		renderer.RenderShape(&renderer.GetLamp("lamp0"), &secondShader);
//		renderer.RenderShape(&renderer.GetLamp("lamp1"), &secondShader);
//		renderer.RenderShape(&renderer.GetLamp("lamp2"), &secondShader);
//		renderer.RenderShape(&renderer.GetLamp("lamp3"), &secondShader);
//		renderer.RenderShape(&renderer.GetLamp("lamp4"), &secondShader);
//		renderer.RenderShape(&renderer.GetLamp("lamp5"), &secondShader);
//		renderer.RenderShape(&renderer.GetLamp("lamp6"), &secondShader);
//		renderer.RenderShape(&renderer.GetLamp("lamp7"), &secondShader);
//		renderer.RenderShape(&renderer.GetLamp("lamp8"), &secondShader);
//		renderer.RenderShape(&renderer.GetLamp("lamp9"), &secondShader);
//		
//		/*
//		renderer.GetRenderable("cube1").Orientation.Rotation += vec3f(0.1f, 0.1f, 0.1f);
//		renderer.GetRenderable("cube2").Orientation.Rotation += vec3f(0.1f, 0.1f, 0.1f);
//		renderer.GetRenderable("cube3").Orientation.Rotation += vec3f(0.4f, 0.1f, 0.1f);
//		renderer.GetRenderable("cube4").Orientation.Rotation += vec3f(0.1f, 0.6f, 0.1f);
//		renderer.GetRenderable("cube5").Orientation.Rotation += vec3f(0.1f, 0.1f, 0.3f);
//		renderer.GetRenderable("cube6").Orientation.Rotation += vec3f(0.1f, 0.7f, 0.1f);
//		renderer.GetRenderable("cube7").Orientation.Rotation += vec3f(0.8f, 0.1f, 0.8f);
//		renderer.GetRenderable("cube8").Orientation.Rotation += vec3f(0.7f, 0.7f, 0.1f);
//		renderer.GetRenderable("cube9").Orientation.Rotation += vec3f(0.3f, 0.5f, 0.6f);
//		renderer.GetRenderable("cube10").Orientation.Rotation += vec3f(0.1f, 0.1f, 0.1f);
//		*/
//
//		renderer.RenderShape(&renderer.GetRenderable("floor"), &firstShader, &renderer.GetLamp("lamp"));
//		renderer.RenderShape(&renderer.GetRenderable("floor1"), &firstShader, &renderer.GetLamp("lamp"));
//		renderer.RenderShape(&renderer.GetRenderable("floor2"), &firstShader, &renderer.GetLamp("lamp"));
//		renderer.RenderShape(&renderer.GetRenderable("floor3"), &firstShader, &renderer.GetLamp("lamp"));
//		
//		/*renderer.RenderShape(&renderer.GetRenderable("cube1"), &firstShader, &renderer.GetLamp("lamp"));
//		renderer.RenderShape(&renderer.GetRenderable("cube2"), &firstShader, &renderer.GetLamp("lamp"));
//		renderer.RenderShape(&renderer.GetRenderable("cube3"), &firstShader, &renderer.GetLamp("lamp"));
//		renderer.RenderShape(&renderer.GetRenderable("cube4"), &firstShader, &renderer.GetLamp("lamp"));
//		renderer.RenderShape(&renderer.GetRenderable("cube5"), &firstShader, &renderer.GetLamp("lamp"));
//		renderer.RenderShape(&renderer.GetRenderable("cube6"), &firstShader, &renderer.GetLamp("lamp"));
//		renderer.RenderShape(&renderer.GetRenderable("cube7"), &firstShader, &renderer.GetLamp("lamp"));
//		renderer.RenderShape(&renderer.GetRenderable("cube8"), &firstShader, &renderer.GetLamp("lamp"));
//		renderer.RenderShape(&renderer.GetRenderable("cube9"), &firstShader, &renderer.GetLamp("lamp"));
//		renderer.RenderShape(&renderer.GetRenderable("cube10"), &firstShader, &renderer.GetLamp("lamp"));*/
//		
//
//		WindowManager::Render();
//	}
//
//	WindowManager::Destroy();
//	
//	system("PAUSE");
//
//	return 0;
//}

#include <vector>
#include <iostream>

void main()
{
	std::vector<int> a;
	std::vector<int> b;
	int n;

	std::cin >> n;

	for (unsigned int i = 0; i < n; i++)
	{
		int temp;
		std::cin >> temp;

		a.push_back(temp);
		b.push_back(0);
	}

	b[n - 1] = a[n - 1];

	for (int i = n - 2; i >= 0; i--)
	{
		b[i] = a[i] + a[i + 1];
	}

	for (unsigned int i = 0; i < n; i++)
	{
		std::cout << b[i] << " ";
	}

	std::cout << "\n";

	system("PAUSE");
}
/*

+
+-
+-+
+-+-
+-+-+

a5 = b5
a4 = b4 - b5
a3 = b3 - b4 + b5
a2 = b2 - b3 + b4 - b5
a1 = b1 - b2 + b3 - b4 + b5

*/