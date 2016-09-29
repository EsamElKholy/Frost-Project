#version 330

in vec2 frag_texcoord;
in vec3 frag_normal;
in vec3 frag_pos;
in vec3 frag_eyePos;

out vec4 out_color;

struct Material
{
	sampler2D Diffuse;
	sampler2D Specular;

	float Shininess;
};

struct DirectionalLight
{
	vec3 Direction;

	vec4 Ambient;
	vec4 Diffuse;
	vec4 Specular;

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
	vec3 Position;

	vec4 Ambient;
	vec4 Diffuse;
	vec4 Specular;

	Attenuation Atten;

	float AmbientStrength;
};

struct SpotLight
{
	vec3 Position;
	vec3 Direction;

	vec4 Ambient;
	vec4 Diffuse;
	vec4 Specular;

	Attenuation Atten;

	float AmbientStrength;

	float InnerCut;
	float OuterCut;
};

uniform Material objMaterial;
uniform vec4 objectColor;

uniform DirectionalLight directional;

#define NUM_POINT_LIGHT 10
uniform PointLight point;
uniform PointLight points[NUM_POINT_LIGHT];

uniform SpotLight spot;

vec4 calcDirectional(DirectionalLight dir, vec3 normal, vec3 viewDir)
{
	vec4 ambCol = dir.Ambient * dir.AmbientStrength * texture(objMaterial.Diffuse, frag_texcoord);

	vec3 norm = (normal);
	vec3 lightDir = normalize(-dir.Direction);

	float diffuseAngle = max(dot(norm, lightDir), 0.0f);
	vec4 diffCol = diffuseAngle * dir.Diffuse * texture(objMaterial.Diffuse, frag_texcoord);

	vec3 reflectionDir = normalize(reflect(-lightDir, norm));
	float spec = pow(max(dot(viewDir, reflectionDir), 0.0f), 32.0f);
	vec4 specCol = spec * dir.Specular * objMaterial.Shininess * texture(objMaterial.Specular, frag_texcoord);

	vec4 finalLight = ambCol + ((diffCol + specCol));

	return finalLight;
}

vec4 calcPoint(PointLight pointLight, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec4 ambCol = pointLight.Ambient * pointLight.AmbientStrength * texture(objMaterial.Diffuse, frag_texcoord);

	vec3 norm = (normal);
	vec3 lightDir = normalize(pointLight.Position - fragPos);

	float diffuseAngle = max(dot(norm, lightDir), 0.0f);
	vec4 diffCol = diffuseAngle * pointLight.Diffuse * texture(objMaterial.Diffuse, frag_texcoord);

	vec3 reflectionDir = normalize(reflect(-lightDir, norm));
	float spec = pow(max(dot(viewDir, reflectionDir), 0.0f), 32.0f);
	vec4 specCol = spec * pointLight.Specular * objMaterial.Shininess * texture(objMaterial.Specular, frag_texcoord);
	
	float atten = 1.0f / (pointLight.Atten.Constant
						 + (pointLight.Atten.Linear * length(pointLight.Position - fragPos))
						 + (pointLight.Atten.Quadratic * pow(length(pointLight.Position - fragPos), 2.0f)));

	vec4 finalLight = (atten * ambCol) + (atten * diffCol) + (atten * specCol);

	return finalLight;
}

vec4 calcSpot(SpotLight spotLight, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec4 ambCol = spotLight.Ambient * spotLight.AmbientStrength * texture(objMaterial.Diffuse, frag_texcoord);

	vec3 norm = (normal);
	vec3 lightDir = normalize(spotLight.Position - frag_pos);

	float diffuseAngle = max(dot(norm, lightDir), 0.0f);
	vec4 diffCol = diffuseAngle * spotLight.Diffuse * texture(objMaterial.Diffuse, frag_texcoord);

	vec3 reflectionDir = normalize(reflect(-lightDir, norm));
	float spec = pow(max(dot(viewDir, reflectionDir), 0.0f), 32.0f);
	vec4 specCol = spec * spotLight.Specular * objMaterial.Shininess * texture(objMaterial.Specular, frag_texcoord);
	
	float atten = 1.0f / (spotLight.Atten.Constant
						 + (spotLight.Atten.Linear * length(spotLight.Position - fragPos))
						 + (spotLight.Atten.Quadratic * pow(length(spotLight.Position - fragPos), 2.0f)));

	float theta = dot(lightDir, normalize(-spotLight.Direction));
	float epsilon = spotLight.InnerCut - spotLight.OuterCut;
	float intensity = clamp((theta - spotLight.OuterCut) / epsilon, 0, 1);

	vec4 finalLight = atten * ambCol;
	
	finalLight += (atten * intensity * diffCol) + (atten * intensity * specCol);
	
	return finalLight;
}

void main()
{
	vec3 viewDir = normalize(frag_eyePos - frag_pos);
	vec3 normal = normalize(frag_normal);
	
	vec4 dirResult = calcDirectional(directional, normal, viewDir);
	vec4 pointResult = vec4(0, 0, 0, 1);//calcPoint(point, normal, frag_pos, viewDir);
	vec4 spotResult = calcSpot(spot, normal, frag_pos, viewDir);
	
	for(int i = 0; i < NUM_POINT_LIGHT; i++)
	{
		pointResult += calcPoint(points[i], normal, frag_pos, viewDir);
	}

	vec4 finalLight = dirResult + pointResult + spotResult;
	
	out_color = vec4((finalLight).xyz * (objectColor).xyz, 1);
}