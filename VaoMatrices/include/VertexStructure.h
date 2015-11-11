#ifndef VERTEXFORMAT_H
#define VERTEXFORMAT_H

#include "glm/glm.hpp"

struct VertexStructure
{
  glm::vec3 position;//our first vertex attribute
  glm::vec4 color;  
  glm::vec2 textureUV;
  glm::vec3 normal;
  glm::vec3 bitangent;
  glm::vec3 binormal;

  VertexStructure(){}

  VertexStructure(const glm::vec3 &pos, const glm::vec4 &col,  const glm::vec2 &tex, const glm::vec3 &norm, const glm::vec3 & bitan, const glm::vec3 & binorm)
  {
     position = pos;
     color = col;
     textureUV = tex;
     normal=norm;
     bitangent=bitan;
     binormal=binorm;

  }
};


#endif // VERTEXFORMAT_H
