#include "IrradianceRenderer.h"

using namespace Crystal::Shader;

IrradianceRenderer::IrradianceRenderer() :
    shader(nullptr)
{}

ShaderBuildStatus IrradianceRenderer::build(GLObjectFactory& factory)
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
    ShaderBuildStatus status;
    status.isOk = true;
    return status;
}

void IrradianceRenderer::release(Shader::GLObjectFactory& factory)
{

}

void IrradianceRenderer::render(const Buffer& buffer)
{

}

std::string IrradianceRenderer::getBuildInVertexShaderSource() const
{
	std::string str = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 WorldPos;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    WorldPos = aPos;  
    gl_Position =  projection * view * vec4(WorldPos, 1.0);
}
)";
    return str;
}

std::string IrradianceRenderer::getBuiltInFragmentShaderSource() const
{
    const std::string str = R"(
#version 330 core
out vec4 FragColor;
in vec3 WorldPos;

uniform samplerCube environmentMap;

const float PI = 3.14159265359;

void main()
{		
	// The world vector acts as the normal of a tangent surface
    // from the origin, aligned to WorldPos. Given this normal, calculate all
    // incoming radiance of the environment. The result of this radiance
    // is the radiance of light coming from -Normal direction, which is what
    // we use in the PBR shader to sample irradiance.
    vec3 N = normalize(WorldPos);

    vec3 irradiance = vec3(0.0);   
    
    // tangent space calculation from origin point
    vec3 up    = vec3(0.0, 1.0, 0.0);
    vec3 right = normalize(cross(up, N));
    up         = normalize(cross(N, right));
       
    float sampleDelta = 0.025;
    float nrSamples = 0.0;
    for(float phi = 0.0; phi < 2.0 * PI; phi += sampleDelta)
    {
        for(float theta = 0.0; theta < 0.5 * PI; theta += sampleDelta)
        {
            // spherical to cartesian (in tangent space)
            vec3 tangentSample = vec3(sin(theta) * cos(phi),  sin(theta) * sin(phi), cos(theta));
            // tangent space to world
            vec3 sampleVec = tangentSample.x * right + tangentSample.y * up + tangentSample.z * N; 

            irradiance += texture(environmentMap, sampleVec).rgb * cos(theta) * sin(theta);
            nrSamples++;
        }
    }
    irradiance = PI * irradiance * (1.0 / float(nrSamples));
    
    FragColor = vec4(irradiance, 1.0);
}

)";
    return str;
}
