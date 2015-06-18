#ifndef VERTEXFORMAT_H
#define VERTEXFORMAT_H

#include "glm/glm.hpp"

struct VertexStructure
{
  glm::vec3 position;//our first vertex attribute
  glm::vec4 color;
  glm::vec2 textureUV;

  VertexStructure(const glm::vec3 &pos, const glm::vec4 &col,  const glm::vec2 &tex)
  {
     position = pos;
     color = col;
     textureUV = tex;
  }
};


#endif // VERTEXFORMAT_H
