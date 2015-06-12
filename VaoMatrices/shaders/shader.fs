//fragment shader
#version 400 core

layout(location = 0) out vec4 out_color;

in vec4 color;

uniform vec4 mycolor;

void main()
{
  if(mycolor!=0)//this is for the uniform grid color
     out_color = mycolor;
  else
     out_color = color;
}
