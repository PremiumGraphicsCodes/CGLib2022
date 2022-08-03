#include "PBLightRenderer.h"

#include <sstream>

using namespace Crystal::Shader;

namespace {
	constexpr auto projectionMatrixLabel = "projection";
	constexpr auto modelMatrixLabel = "model";
    constexpr auto viewMatrixLabel = "view";

    constexpr auto positionLabel = "aPos";
    constexpr auto normalLabel = "aNormal";

    constexpr auto albedoLabel = "albedo";
    constexpr auto metaricLabel = "metallic";
    constexpr auto roughbessLabel = "roughness";
    constexpr auto aoLabel = "ao";

    // lights
    //uniform vec3 lightPositions[4];
    //uniform vec3 lightColors[4];

    constexpr auto camerPosLabel = "camPos";
}

PBLightRenderer::PBLightRenderer() :
	shader(nullptr)
{
}

ShaderBuildStatus PBLightRenderer::build(GLObjectFactory& factory)
{
	const auto& vsSource = getBuildInVertexShaderSource();
	const auto& fsSource = getBuiltInFragmentShaderSource();

	shader = factory.createShaderObject();
	const auto isOk = shader->build(vsSource, fsSource);
	if (!isOk) {
		ShaderBuildStatus status;
		status.isOk = false;
		status.log = shader->getLog();
		return status;
	}

	shader->findUniformLocation(::projectionMatrixLabel);
	shader->findUniformLocation(::modelMatrixLabel);
    shader->findUniformLocation(::viewMatrixLabel);

    shader->findUniformLocation(::albedoLabel);
    shader->findUniformLocation(::metaricLabel);
    shader->findUniformLocation(::roughbessLabel);
    shader->findUniformLocation(::aoLabel);

    shader->findUniformLocation(::camerPosLabel);

    for (int i = 0; i < 1; ++i) {
        shader->findUniformLocation("lightPositions[" + std::to_string(i) + "]");
        shader->findUniformLocation("lightColors[" + std::to_string(i) + "]");
    }

	shader->findAttribLocation(::positionLabel);
	shader->findAttribLocation(::normalLabel);

	ShaderBuildStatus status;
	status.isOk = true;
	return status;
}

void PBLightRenderer::release(GLObjectFactory& factory)
{
	factory.remove(shader);
}

void PBLightRenderer::render(const Buffer& buffer)
{
	shader->bind();
	shader->bindOutput("FragColor");

	shader->enableDepthTest();

	shader->sendUniform(::projectionMatrixLabel, buffer.projectionMatrix);
	shader->sendUniform(::modelMatrixLabel, buffer.modelMatrix);
    shader->sendUniform(::viewMatrixLabel, buffer.viewMatrix);
    shader->sendUniform(::camerPosLabel, buffer.eyePosition);

    shader->sendUniform(::albedoLabel, buffer.albedo);
    shader->sendUniform(::metaricLabel, buffer.metalic);
    shader->sendUniform(::roughbessLabel, buffer.roughness);
    shader->sendUniform(::aoLabel, buffer.ao);

    shader->sendUniform("lightPositions[0]", buffer.lightPosition);
    shader->sendUniform("lightColors[0]", buffer.lightColor);

	shader->sendVertexAttribute3df(::positionLabel, buffer.position);
	shader->sendVertexAttribute3df(::normalLabel, buffer.normal);

    buffer.position.bind();
    buffer.normal.bind();
	shader->enableVertexAttribute(::positionLabel);
	shader->enableVertexAttribute(::normalLabel);

	shader->drawTriangles(buffer.indices);

	shader->disableVertexAttribute(::positionLabel);
	shader->disableVertexAttribute(::normalLabel);

	shader->disableDepthTest();

	shader->unbind();
}

std::string PBLightRenderer::getBuildInVertexShaderSource() const
{
	const std::string str = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 WorldPos;
out vec3 Normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    WorldPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(model) * aNormal;   

    gl_Position =  projection * view * vec4(WorldPos, 1.0);
}
)";
	return str;
}

std::string PBLightRenderer::getBuiltInFragmentShaderSource() const
{
	const std::string str = R"(
#version 330 core
out vec4 FragColor;
in vec3 WorldPos;
in vec3 Normal;

// material parameters
uniform vec3 albedo;
uniform float metallic;
uniform float roughness;
uniform float ao;

// lights
uniform vec3 lightPositions[1];
uniform vec3 lightColors[1];

uniform vec3 camPos;

const float PI = 3.14159265359;
// ----------------------------------------------------------------------------
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}
// ----------------------------------------------------------------------------
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}
// ----------------------------------------------------------------------------
void main()
{		
    vec3 N = normalize(Normal);
    vec3 V = normalize(camPos - WorldPos);

    // calculate reflectance at normal incidence; if dia-electric (like plastic) use F0 
    // of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)    
    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);

    // reflectance equation
    vec3 Lo = vec3(0.0);
    for(int i = 0; i < 1; ++i) 
    {
        // calculate per-light radiance
        vec3 L = normalize(lightPositions[i] - WorldPos);
        vec3 H = normalize(V + L);
        float distance = length(lightPositions[i] - WorldPos);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance = lightColors[i] * attenuation;

        // Cook-Torrance BRDF
        float NDF = DistributionGGX(N, H, roughness);   
        float G   = GeometrySmith(N, V, L, roughness);      
        vec3 F    = fresnelSchlick(clamp(dot(H, V), 0.0, 1.0), F0);
           
        vec3 numerator    = NDF * G * F; 
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001; // + 0.0001 to prevent divide by zero
        vec3 specular = numerator / denominator;
        
        // kS is equal to Fresnel
        vec3 kS = F;
        // for energy conservation, the diffuse and specular light can't
        // be above 1.0 (unless the surface emits light); to preserve this
        // relationship the diffuse component (kD) should equal 1.0 - kS.
        vec3 kD = vec3(1.0) - kS;
        // multiply kD by the inverse metalness such that only non-metals 
        // have diffuse lighting, or a linear blend if partly metal (pure metals
        // have no diffuse light).
        kD *= 1.0 - metallic;	  

        // scale light by NdotL
        float NdotL = max(dot(N, L), 0.0);        

        // add to outgoing radiance Lo
        Lo += (kD * albedo / PI + specular) * radiance * NdotL;  // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
    }   
    
    // ambient lighting (note that the next IBL tutorial will replace 
    // this ambient lighting with environment lighting).
    vec3 ambient = vec3(0.03) * albedo * ao;

    vec3 color = ambient + Lo;

    // HDR tonemapping
    color = color / (color + vec3(1.0));
    // gamma correct
    color = pow(color, vec3(1.0/2.2)); 

    FragColor = vec4(color, 1.0);
}

)";
    return str;
}
