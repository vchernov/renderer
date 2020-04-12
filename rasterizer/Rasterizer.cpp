#include "Rasterizer.h"

#include <glm/gtc/packing.hpp>

#include <IRenderOutput.h>
#include <barycentric.h>

#include "DiffuseVertexShader.h"

Rasterizer::Rasterizer(FrameBuffer& fb)
    : fb(fb)
    , canvas(fb)
    , zbuffer(fb.width, fb.height)
{
    fb.fill({0.0f, 0.0f, 0.0f});
    zbuffer.fill(1.0f);
}

Rasterizer::~Rasterizer()
{
}

void Rasterizer::rasterize(const Mesh& mesh, DiffuseVertexShader* vertexShader, IFragmentShader* fragmentShader)
{
    glm::vec4 forward = vertexShader->view * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
    glm::vec3 lineOfSight = glm::normalize(glm::vec3(forward / forward.w));

    for (const auto& face : mesh.faces)
    {
        VertexOutput vo[3];
        for (int i = 0; i < 3; i++)
        {
            Vertex v;
            v.position = mesh.vertices[face.vertexIndices[i]];
            v.uv = mesh.texCoords[face.texCoordIndices[i]];
            v.normal = mesh.normals[face.normalIndices[i]];
            vo[i] = vertexShader->vertex(v);
        }

        glm::ivec2 boundsMin, boundsMax;
        getBounds(vo, boundsMin, boundsMax);

        glm::vec3 normal = glm::cross(vo[1].worldPos - vo[0].worldPos, vo[2].worldPos - vo[0].worldPos);
        normal = glm::normalize(normal);
        float winding = glm::dot(normal, lineOfSight);
        if (winding > 0.0f)
            continue;

        for (int y = boundsMin.y; y <= boundsMax.y; y++)
        {
            for (int x = boundsMin.x; x <= boundsMax.x; x++)
            {
                glm::vec3 p = glm::vec3(x, y, 0.0f);
                glm::vec3 bc = barycentric(vo[0].nsc, vo[1].nsc, vo[2].nsc, p);
                if (isInsideTriangle(bc.x, bc.y, bc.z))
                {
                    //canvas.wireframe(vo[0].sp, vo[1].sp, vo[2].sp, {1.0f, 1.0f, 1.0f});

                    float z = vo[0].sc.z * bc.x + vo[1].sc.z * bc.y + vo[2].sc.z * bc.z;
                    float w = vo[0].sc.w * bc.x + vo[1].sc.w * bc.y + vo[2].sc.w * bc.z;
                    float depth = z / w;
                    if (zbuffer(x, y) > depth)
                    {
                        FragmentInput fi;
                        fi.color = vo[0].color * bc.x + vo[1].color * bc.y + vo[2].color * bc.z;
                        fi.normal = vo[0].normal * bc.x + vo[1].normal * bc.y + vo[2].normal * bc.z;
                        fi.worldPos = vo[0].worldPos * bc.x + vo[1].worldPos * bc.y + vo[2].worldPos * bc.z;

                        // Flat shading
                        /*
                        float intensity = -winding;
                        fi.color = fi.color * intensity;
                        */

                        glm::vec3 color = fragmentShader->fragment(fi);
                        canvas.pixel(x, y, color);
                        zbuffer(x, y) = depth;
                    }
                }
            }
        }
    }
}

void Rasterizer::getBounds(VertexOutput vo[3], glm::ivec2& boundsMin, glm::ivec2& boundsMax)
{
    boundsMin = glm::vec2(fb.width - 1, fb.height - 1);
    boundsMax = glm::vec2(0);
    for (int i = 0; i < 3; i++)
    {
        boundsMin.x = glm::min(boundsMin.x, vo[i].sp.x);
        boundsMin.y = glm::min(boundsMin.y, vo[i].sp.y);
        boundsMax.x = glm::max(boundsMax.x, vo[i].sp.x);
        boundsMax.y = glm::max(boundsMax.y, vo[i].sp.y);
    }
    boundsMin.x = glm::max(boundsMin.x, 0);
    boundsMin.y = glm::max(boundsMin.y, 0);
    boundsMax.x = glm::min(boundsMax.x, fb.width - 1);
    boundsMax.y = glm::min(boundsMax.y, fb.height - 1);
}

void Rasterizer::render(IRenderOutput* output)
{
    uint8_t* buffer = new uint8_t[(size_t)fb.width * fb.height * 3];
    //fb.get(buffer, [](float c) { return static_cast<uint8_t>(c * 255.0f); });
    fb.get(buffer, glm::packUnorm1x8);
    output->render(buffer, fb.width, fb.height);
    delete[] buffer;
}
