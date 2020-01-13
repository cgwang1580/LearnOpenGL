#version 330 core
out vec4 FragColor;

in vec3 ourColor;
uniform bool is_sprite;
uniform sampler2D sprite_texture;

void main()
{
	if (is_sprite) {
		if (length(gl_PointCoord-vec2(0.5)) > 0.35){
			discard;
		}
	}
	FragColor = texture(sprite_texture, gl_PointCoord);
}