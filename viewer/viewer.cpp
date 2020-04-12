#include <iostream>
#include <memory>

#include <glm/gtc/matrix_transform.hpp>

#include <CompositeRenderOutput.h>
#include <DiffuseFragmentShader.h>
#include <DiffuseVertexShader.h>
#include <FileRenderOutput.h>
#include <Mesh.h>
#include <ObjReader.h>
#include <Rasterizer.h>
#include <WindowRenderOutput.h>

int main(int argc, char** argv)
{
    std::cout << "start" << std::endl;

    std::string meshFn;
    if (argc > 1)
        meshFn = argv[1];

    std::string outImgFn;
    if (argc > 2)
        outImgFn = argv[2];

    Mesh mesh = ObjReader::load(meshFn);

    FrameBuffer fb(1024, 768);
    Rasterizer rasterizer(fb);

    DiffuseVertexShader vertexShader;
    vertexShader.projection = glm::perspective(glm::radians(45.0f), (float)fb.width / fb.height, 0.1f, 10.0f);
    vertexShader.view = glm::translate(vertexShader.view, glm::vec3(0.0f, 0.0f, -3.0f));
    vertexShader.viewport = fb.getViewportMatrix();

    DiffuseFragmentShader fragmentShader;
    fragmentShader.lightPos = glm::vec3(0.0f, 0.0f, -3.0f);
    fragmentShader.normalMatrix = glm::transpose(glm::inverse(glm::mat3(vertexShader.model)));

    rasterizer.rasterize(mesh, &vertexShader, &fragmentShader);

    CompositeRenderOutput output;
    output.add(std::make_shared<WindowRenderOutput>());
    if (!outImgFn.empty())
        output.add(std::make_shared<FileRenderOutput>(outImgFn));

    rasterizer.render(&output);

    std::cout << "end" << std::endl;
    return 0;
}
