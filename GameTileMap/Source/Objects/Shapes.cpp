#include "GamePCH.h"
#include "Shapes.h"

const fw::VertexFormat meshAttribs_Sprite[] =
{
    fw::VertexFormat(-0.50f, -0.50f,   0, 0), // bl
    fw::VertexFormat(0.50f,  0.50f,   1, 1), // tr
    fw::VertexFormat(0.50f, -0.50f,   1, 0), // br

    fw::VertexFormat(-0.50f, -0.50f,   0, 0), // bl
    fw::VertexFormat(-0.50f,  0.50f,   0, 1), // tl
    fw::VertexFormat(0.50f,  0.50f,   1, 1), // tr
};
const int meshPrimType_Sprite = GL_TRIANGLE_FAN;
const int meshNumVerts_Sprite = sizeof(meshAttribs_Sprite) / sizeof(fw::VertexFormat);