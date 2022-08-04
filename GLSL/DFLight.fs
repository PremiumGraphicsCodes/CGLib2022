#version 150
uniform sampler2D positionTexture;
uniform sampler2D normalTexture;
uniform sampler2D colorTexture;
uniform mat4 invProjectionMatrix;
uniform mat4 invModelViewMatrix;
uniform mat3 invNormalMatrix;
struct Light {
	vec3 position;
	vec3 color;
};
uniform Light light;
in vec2 texCoord;
out vec4 fragColor;

vec3 getWorldPosition(vec3 pos)
{
	vec4 pos4 = invModelViewMatrix * invProjectionMatrix * vec4(pos, 1.0);
	return pos4.rgb;
}

vec3 getWorldNormal(vec3 normal)
{
	return invNormalMatrix * normal;
}

vec3 getDiffuseColor(vec3 position, vec3 normal, vec3 color)
{
	vec3 lightDir = normalize(light.position - position);
	float d = dot(normal, lightDir);
	if( d <= 0.0 ) {
		return vec3(1,1,1);
	}
	vec3 diffuse = max(d, 0.0 ) * color * light.color;
	return diffuse;
}

void main(void) {
	vec3 pos = texture(positionTexture, texCoord).rgb;
	vec3 normal = texture(normalTexture, texCoord).rgb;
	vec3 worldPos = getWorldPosition(pos);
	vec3 worldNormal = getWorldNormal(normal);
	vec3 color = texture(colorTexture, texCoord).rgb;
	vec3 lighting = getDiffuseColor(worldPos, worldNormal, color); 
	fragColor = vec4(lighting, 1.0);
}