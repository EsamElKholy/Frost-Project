#version 330

in vec2 frag_texcoord;

out vec4 out_color;

uniform sampler2D sampler;
uniform vec4 lightColor;
uniform int mode;
void main()
{
	vec4 finalColor = texture(sampler, frag_texcoord);	 	

	if(mode == 0)
	{
		out_color = finalColor;
	}else

	if(mode == 1)
	{
		finalColor *= vec4(-1.0f, -1.0f, -1.0f, 0);
		finalColor = vec4(1, 1, 1, 1) + finalColor;
		out_color = finalColor;
	}else

	if(mode == 2)
	{
		float average = finalColor.x * 0.2126f + finalColor.y * 0.7152f + finalColor.z * 0.0722f;
		vec4 color = vec4(average, average, average, 1);
		out_color = color;
	}	   	
}