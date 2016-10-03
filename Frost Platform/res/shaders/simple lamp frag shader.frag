#version 330

in vec2 frag_texcoord;
in vec3 frag_pos;
in vec3 frag_eyePos;

out vec4 out_color;

uniform sampler2D sampler;
uniform vec4 lightColor;

void main()
{
	vec4 finalColor = texture(sampler, frag_texcoord);
	
	float dMax = 50;
	float dMin = 25;
	float dist = length(frag_eyePos - frag_pos);
	float fog = (dMax - dist) / (dMax - dMin);
	fog = clamp(fog, 0, 1);
	
	vec3 color = mix(vec3(0.15f, 0.15f, 0.15f), (lightColor).xyz * (finalColor).xyz, fog);

	out_color = vec4(color, 1);
}