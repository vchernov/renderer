#include "DiffuseVertexShader.h"

VertexOutput DiffuseVertexShader::vertex(const Vertex& v)
{
    VertexOutput o;
    glm::vec4 worldPos = model * glm::vec4(v.position, 1.0f);
    o.position = projection * view * worldPos;
    o.uv = v.uv;
    o.normal = v.normal;

    o.worldPos = worldPos / worldPos.w;
    o.ndc = o.position / o.position.w;
    o.sc = viewport * o.position;
    o.nsc = o.sc / o.sc.w;
    o.sp = glm::ivec2(o.nsc);
    return o;
}
