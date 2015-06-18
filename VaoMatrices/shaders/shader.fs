
//fragment shader
#version 400 core

layout(location = 0) out vec4 out_color;

in vec4 color;

uniform vec4 mycolor;

uniform sampler2D tex;
in vec2 uvVert;

void main()
{
  if(mycolor!=0)//this is for the uniform grid color
     out_color = mycolor;
  else if (uvVert!=0)
     out_color = texture(tex, uvVert);
  else
     out_color = color;

}


