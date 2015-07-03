//vertex shader
#version 400 core //lower this version if your card does not support GLSL 4
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec2 in_uv;
layout(location = 3) in vec3 in_normal;
layout(location = 4) in vec3 in_bitangent;
layout(location = 5) in vec3 in_binormal;


uniform mat4 MVP;

out vec4 color;
//out vec2 uvVert;


//in vec3 vert;
//in vec2 vertTexCoord;
//in vec3 vertNormal;

out vec3 fragVert;
out vec2 fragTexCoord;
out vec3 fragNormal;


uniform struct Light {
   vec3 position;
   vec3 intensities; // the color of the light
   float ambientCoefficient;
} light;


out vec3 lightDir;
uniform mat4 MV;
// a light Vector to be passed to the frag shader
out vec3 lightVec;
// a half (blinn) vector to be passed to the frag shader
out vec3 halfVec;

void main()
{
  vec4 worldPosition = MV * vec4(in_position, 1.0);
  vec3 lightDir = normalize(light.position.xyz - worldPosition.xyz);
  lightVec.x = dot (lightDir, in_bitangent );
  lightVec.y = dot (lightDir, in_binormal);
  lightVec.z = dot (lightDir, in_normal );

  vec3 halfVector = normalize(worldPosition.xyz + lightDir);
  halfVec.x = dot (halfVector, in_bitangent);
  halfVec.y = dot (halfVector, in_binormal);
  halfVec.z = dot (halfVector, in_normal);



  fragVert=in_position;
  fragTexCoord=in_uv;
  fragNormal=in_normal;

  color = in_color;
  vec4 v = vec4(in_position, 1);
  gl_Position = MVP * v;
  //uvVert = in_uv;
}
