#version 150
in vec3 position;
in vec3 normal;
out vec4 vPosition;
out vec3 vNormal;
uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;
uniform mat3 normalMatrix;
void main(void)
{
	gl_Position = projectionMatrix * modelviewMatrix * vec4(position, 1.0);
	vPosition = gl_Position;
	vNormal = normalMatrix * normal;
}
