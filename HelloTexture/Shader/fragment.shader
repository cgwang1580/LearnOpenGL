#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

out vec4 FragColor;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float thresh;

void main()
{
	//FragColor = texture(texture1, TexCoord);
	//FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
	vec4 textColor = texture (texture1, TexCoord);
	/*if (textColor.a < 0.5) {
		discard;
	}*/
	//float gray = textColor.x * 0.299 + textColor.y * 0.587 + textColor.z * 0.114;
	//if (gray < 0.8) {
	//	//discard;
	//}
	//thresh = 0.6;
	//FragColor = mix(texture(texture1, TexCoord), textColor, thresh);
	//FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), thresh);
	FragColor = textColor;
}