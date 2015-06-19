//vertex shader
#version 400 core //lower this version if your card does not support GLSL 4
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec2 in_uv;

uniform mat4 MVP;

out vec4 color;
out vec2 uvVert;

void main()
{
  color = in_color;
  vec4 v = vec4(in_position, 1);
  gl_Position = MVP * v;
  uvVert = in_uv;
}
