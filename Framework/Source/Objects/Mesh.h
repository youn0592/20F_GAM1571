#pragma once

#include "../Math/Vector.h"

namespace fw {
class Texture;

struct VertexFormat {
    float x;
    float y;
    float u;
    float v;
    VertexFormat(float nx, float ny, float nu, float nv)
    {
        x = nx;
        y = ny; 
        u = nu;
        v = nv;
    }
};

class Mesh
{
public:

    Mesh();
    Mesh(int primitiveType, int numVertices, const VertexFormat* pVertices);

    virtual ~Mesh();

    void SetUniform1F(ShaderProgram* pShader, char* name, float value);
    void SetUniform2F(ShaderProgram* pShader, char* name, float value1, float value2);
    void SetUniform2F(ShaderProgram* pShader, char* name, vec2 values);
    void SetUniform4F(ShaderProgram* pShader, char* name, vec4 values);
    void SetUniform1i(ShaderProgram* pShader, char* name, int value);


    void Draw(vec2 pos, ShaderProgram* pShader, Texture* pTexture, vec4 color, vec2 UVScale, vec2 UVOffset);

    void CreateShape(int numVertices, int primitiveType, const VertexFormat* pVertices);
    void CreateCircle(float radius, int numVertices, bool isFilled);

    float GetRadius();

protected:
    GLuint m_VBO = 0;

    int m_NumVertices = 0;
    int m_PrimitiveType = GL_POINTS;

    float m_Radius = 0;
    float m_Angle = 0;
};

} // namespace fw
