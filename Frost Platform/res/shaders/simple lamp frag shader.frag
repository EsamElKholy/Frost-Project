#version 330

in vec2 frag_texcoord;

out vec4 out_color;

uniform sampler2D sampler;
uniform vec4 lightColor;

void main()
{
	vec4 finalColor = texture(sampler, frag_texcoord);
	
	out_color = finalColor * lightColor;
}