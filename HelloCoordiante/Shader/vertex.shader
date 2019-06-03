#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * transform * vec4(aPos, 1.0f);
	//gl_Position = vec4(aPos, 1.0f);
	ourColor = aColor;
	TexCoord = vec2(aTexCoord.x, 1.0f - aTexCoord.y);
}