#version 150
in vec3 vTexCoord;
out vec4 fragColor;
uniform samplerCube cubeMapTex;
void main(void) {
	fragColor = texture(cubeMapTex, vTexCoord);
	//fragColor.rgb = vec3(1,1,1);
}