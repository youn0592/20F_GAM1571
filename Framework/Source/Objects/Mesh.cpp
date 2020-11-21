#include "FrameworkPCH.h"
#include "Framework.h"
#include "Utility/ShaderProgram.h"
#include "Utility/Helpers.h"
#include "Objects/Texture.h"

#include "Mesh.h"

namespace fw {


Mesh::Mesh()
{

}

Mesh::Mesh(int primitiveType, int numVertices, const VertexFormat* pVertices)
{
    CreateShape(primitiveType, numVertices, pVertices);
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &m_VBO);
}

void Mesh::SetUniform1F(ShaderProgram* pShader, char* name, float value)
{
    //Setup our Uniforms
    {
        int loc = glGetUniformLocation(pShader->GetProgram(), name);
        glUniform1f(loc, value);
    }
}

void Mesh::SetUniform2F(ShaderProgram* pShader, char* name, float value1, float value2)
{
    int loc = glGetUniformLocation(pShader->GetProgram(), name);
    glUniform2f(loc, value1, value2);
}

void Mesh::SetUniform2F(ShaderProgram* pShader, char* name, vec2 values)
{
    int loc = glGetUniformLocation(pShader->GetProgram(), name);
    glUniform2f(loc, values.x, values.y);
}

void Mesh::SetUniform4F(ShaderProgram* pShader, char* name, vec4 values)
{
    int loc = glGetUniformLocation(pShader->GetProgram(), name);
    glUniform4f(loc, values.x, values.y, values.z, values.w);
}

void Mesh::SetUniform1i(ShaderProgram* pShader, char* name, int value)
{
    //Setup our Uniforms
    {
        int loc = glGetUniformLocation(pShader->GetProgram(), name);
        glUniform1i(loc, value);
    }
}
void Mesh::Draw(vec2 pos, ShaderProgram* pShader, Texture* pTexture, vec4 color, vec2 UVScale, vec2 UVOffset)
{
    glUseProgram(pShader->GetProgram());

    // Set this VBO to be the currently active one.
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    // Get the attribute variable’s location from the shader.
    GLint loc = glGetAttribLocation(pShader->GetProgram(), "a_Position");
    if (loc != -1)
    {
        glEnableVertexAttribArray(loc);
        glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 16, (void*)0);
    }

    loc = glGetAttribLocation(pShader->GetProgram(), "a_UVCoord");
    if (loc != -1)
    {
        glEnableVertexAttribArray(loc);
        glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 16, (void*)8);
    }

    // Setup our uniforms.
    {
        SetUniform1F(pShader, "u_Time", (float)GetSystemTimeSinceGameStart());
        SetUniform2F(pShader, "u_ObjectPos", pos);
        SetUniform4F(pShader, "u_Color", color);

        SetUniform2F(pShader, "u_UVScale", UVScale);
        SetUniform2F(pShader, "u_UVOffset", UVOffset);

        if (pTexture != nullptr)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, pTexture->GetHandle());
            SetUniform1i(pShader, "u_Texture", 0);
        }
    }

    // Draw the primitive.
    glDrawArrays(m_PrimitiveType, 0, m_NumVertices);
}

void Mesh::CreateShape(int numVertices, int primitiveType, const VertexFormat* pVertices)
{
    // Delete the old buffer if we had one.
    glDeleteBuffers(1, &m_VBO);

    // Generate a buffer for our vertex attributes.
    glGenBuffers(1, &m_VBO); // m_VBO is a GLuint.

    // Set this VBO to be the currently active one.
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    m_NumVertices = numVertices;
    m_PrimitiveType = primitiveType;

    // Copy our attribute data into the VBO.
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * m_NumVertices, pVertices, GL_STATIC_DRAW);

}

void Mesh::CreateCircle(float radius, int numVertices, bool isFilled)
{
    assert(numVertices > 2); //Circle needs to have at least 3 points to be made

    if (m_VBO != 0){
        glDeleteBuffers(1, &m_VBO);
    }

    glGenBuffers(1, &m_VBO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    const float PI = 3.1415926f;

    std::vector<VertexFormat> attribs;
    m_Angle = (2 * PI) / numVertices;



    for (int i = 0; i < numVertices; i++) {
            
            float temp1 = radius * sinf(m_Angle * i);
            float temp2 = radius * cosf(m_Angle * i);



            attribs.push_back(VertexFormat(temp1, temp2, 0, 0));

        }

    if (isFilled) {
        m_PrimitiveType = GL_TRIANGLE_FAN;
    }
    else {
        m_PrimitiveType = GL_LINE_LOOP;
    }

    m_Radius = radius;
    m_NumVertices = numVertices;

    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * numVertices, &attribs[0], GL_STATIC_DRAW);
}

float Mesh::GetRadius()
{
    return m_Radius;
}


} // namespace fw
