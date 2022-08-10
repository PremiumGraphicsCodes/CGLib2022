#version 150
in vec2 vTexCoord;
out vec4 fragColor;
uniform sampler2D texture;

void main(void) {
	fragColor = texture2D(texture, vTexCoord);
}