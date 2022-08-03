#version 150
in vec4 vPosition;
in vec3 vNormal;
out vec4 gPosition;
out vec3 gNormal;

void main(void) {
	gPosition = vPosition;
	gNormal.rgb = normalize(vNormal);
}