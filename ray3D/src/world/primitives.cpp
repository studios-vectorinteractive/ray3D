#include "primitives.h"
#include "renderer/buffer.h"
#include "renderer/vertAttribs.h"

namespace ray3D
{
    static std::vector<texPosNorColVert> vertexData = {

        //    TexCoord              Position                  Normal                    Color

        {   {0.0f, 0.0f},   { -1.0f, -1.0f,  1.0f },    {0.0f, 0.0f, -1.0f},   {1.0f, 0.0f, 0.0f, 1.0f}   },
        {   {1.0f, 0.0f},   {  1.0f, -1.0f,  1.0f },    {0.0f, 0.0f, -1.0f},   {1.0f, 0.0f, 0.0f, 1.0f}   },
        {   {1.0f, 1.0f},   {  1.0f,  1.0f,  1.0f },    {0.0f, 0.0f, -1.0f},   {1.0f, 0.0f, 0.0f, 1.0f}   },
        {   {0.0f, 1.0f},   { -1.0f,  1.0f,  1.0f },    {0.0f, 0.0f, -1.0f},   {1.0f, 0.0f, 0.0f, 1.0f}   },

        {   {0.0f, 0.0f},   { -1.0f, -1.0f, -1.0f },    {0.0f, 0.0f, 1.0f},    {0.0f, 0.0f, 1.0f, 1.0f}   },
        {   {1.0f, 0.0f},   { -1.0f,  1.0f, -1.0f },    {0.0f, 0.0f, 1.0f},    {0.0f, 0.0f, 1.0f, 1.0f}   },
        {   {1.0f, 1.0f},   {  1.0f,  1.0f, -1.0f },    {0.0f, 0.0f, 1.0f},    {0.0f, 0.0f, 1.0f, 1.0f}   },
        {   {0.0f, 1.0f},   {  1.0f, -1.0f, -1.0f },    {0.0f, 0.0f, 1.0f},    {0.0f, 0.0f, 1.0f, 1.0f}   },

        {   {0.0f, 0.0f},   {  1.0f, -1.0f, -1.0f },    {-1.0f, 0.0f, 0.0f},   {0.0f, 1.0f, 0.0f, 1.0f}   },
        {   {1.0f, 0.0f},   {  1.0f,  1.0f, -1.0f },    {-1.0f, 0.0f, 0.0f},   {0.0f, 1.0f, 0.0f, 1.0f}   },
        {   {1.0f, 1.0f},   {  1.0f,  1.0f,  1.0f },    {-1.0f, 0.0f, 0.0f},   {0.0f, 1.0f, 0.0f, 1.0f}   },
        {   {0.0f, 1.0f},   {  1.0f, -1.0f,  1.0f },    {-1.0f, 0.0f, 0.0f},   {0.0f, 1.0f, 0.0f, 1.0f}   },

        {   {0.0f, 0.0f},   { -1.0f, -1.0f, -1.0f },    {1.0f, 0.0f, 0.0f},    {1.0f, 0.0f, 1.0f, 1.0f}   },
        {   {1.0f, 0.0f},   { -1.0f, -1.0f,  1.0f },    {1.0f, 0.0f, 0.0f},    {1.0f, 0.0f, 1.0f, 1.0f}   },
        {   {1.0f, 1.0f},   { -1.0f,  1.0f,  1.0f },    {1.0f, 0.0f, 0.0f},    {1.0f, 0.0f, 1.0f, 1.0f}   },
        {   {0.0f, 1.0f},   { -1.0f,  1.0f, -1.0f },    {1.0f, 0.0f, 0.0f},    {1.0f, 0.0f, 1.0f, 1.0f}   },

        {   {0.0f, 0.0f},   { -1.0f,  1.0f,  1.0f },    {0.0f, -1.0f, 0.0f},   {0.0f, 1.0f, 1.0f, 1.0f}   },
        {   {1.0f, 0.0f},   {  1.0f,  1.0f,  1.0f },    {0.0f, -1.0f, 0.0f},   {0.0f, 1.0f, 1.0f, 1.0f}   },
        {   {1.0f, 1.0f},   {  1.0f,  1.0f, -1.0f },    {0.0f, -1.0f, 0.0f},   {0.0f, 1.0f, 1.0f, 1.0f}   },
        {   {0.0f, 1.0f},   { -1.0f,  1.0f, -1.0f },    {0.0f, -1.0f, 0.0f},   {0.0f, 1.0f, 1.0f, 1.0f}   },

        {   {0.0f, 0.0f},   { -1.0f, -1.0f,  1.0f },    {0.0f, 1.0f, 0.0f},    {1.0f, 1.0f, 0.0f, 1.0f}   },
        {   {1.0f, 0.0f},   { -1.0f, -1.0f, -1.0f },    {0.0f, 1.0f, 0.0f},    {1.0f, 1.0f, 0.0f, 1.0f}   },
        {   {1.0f, 1.0f},   {  1.0f, -1.0f, -1.0f },    {0.0f, 1.0f, 0.0f},    {1.0f, 1.0f, 0.0f, 1.0f}   },
        {   {0.0f, 1.0f},   {  1.0f, -1.0f,  1.0f },    {0.0f, 1.0f, 0.0f},    {1.0f, 1.0f, 0.0f, 1.0f}   },
    };

    static std::vector<ui32> indices =
    {

        // Front face
        0, 1, 2,
        2, 3, 0,

        // Back face
        4, 5, 6,
        6, 7, 4,

        // Right face
        8, 9, 10,
        10, 11, 8,

        // Left face
        12, 13, 14,
        14, 15, 12,

        // Top face
        16, 17, 18,
        18, 19, 16,

        // Bottom face
        20, 21, 22,
        22, 23, 20

    };

    auto primitives::getCube() -> std::unique_ptr<mesh>
    {
        std::shared_ptr<vertexBuffer> cubeVertBuffer = vertexBuffer::create(vertexData, vertAttribLayoutType::tex_pos_nor_col);
        std::shared_ptr<indexBuffer> cubeIndexBuffer = indexBuffer::create(indices);

        return mesh::create(cubeVertBuffer, cubeIndexBuffer);
    }

    auto primitives::getGrid(i32 gridSize, f32 innerAlphaRadius, f32 outerAlphaRadius) -> std::unique_ptr<mesh>
    {

        gridSize = (gridSize % 2) == 0 ? gridSize : gridSize + 1;

        i32 totalVerts = (gridSize + 1) * (gridSize + 1);
        i32 gridSizeBy2 = gridSize / 2;
        std::vector<posColVert> gridVertData(totalVerts);
        i32 bufferIdx = 0;

        for (i32 x = 0; x <= gridSize; x++)
        {
            for (i32 z = 0; z <= gridSize; z++)
            {
                posColVert& vert = gridVertData[bufferIdx++];
                f32 xPos = x - gridSizeBy2;
                f32 zPos = z - gridSizeBy2;

                vert.position.x = xPos;
                vert.position.z = zPos;

                if (xPos == 0 || zPos == 0)
                {
                    vert.color = zPos == 0 ? glm::vec4(0.35f, 0.0f, 0.0f, 1.0f) : glm::vec4(0.0f, 0.35f, 0.0f, 1.0f);
                }
                else
                {
                    vert.color = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
                }

                if (innerAlphaRadius > 0.0f && outerAlphaRadius > 0.0f)
                {
                    f32 distFromInnerAlphaRadius = glm::distance(glm::vec3(0.0f), vert.position);
                    if (distFromInnerAlphaRadius > innerAlphaRadius)
                    {
                        f32 delta = distFromInnerAlphaRadius - innerAlphaRadius;
                        f32 alpha = 1.0f - (delta / outerAlphaRadius);
                        alpha = glm::clamp(alpha, 0.0f, 1.0f);
                        vert.color.a = alpha;
                    }
                }
            }
        }

        std::vector<ui32> gridIndices(gridSize * gridSize * 8);
        bufferIdx = 0;

        for (i32 i = 0; i < gridSize; i++)
        {
            for (i32 j = 0; j < gridSize; j++)
            {
                ui32 pt_1 = i * (gridSize + 1) + j;
                ui32 pt_2 = pt_1 + 1;
                ui32 pt_3 = (i + 1) * (gridSize + 1) + j + 1;
                ui32 pt_4 = pt_3 - 1;

                gridIndices[bufferIdx++] = pt_1;
                gridIndices[bufferIdx++] = pt_2;

                gridIndices[bufferIdx++] = pt_2;
                gridIndices[bufferIdx++] = pt_3;

                gridIndices[bufferIdx++] = pt_3;
                gridIndices[bufferIdx++] = pt_4;

                gridIndices[bufferIdx++] = pt_4;
                gridIndices[bufferIdx++] = pt_1;
            }
        }

        std::shared_ptr<vertexBuffer> gridVertBuffer = vertexBuffer::create(gridVertData, vertAttribLayoutType::pos_col);
        std::shared_ptr<indexBuffer> gridIndexBuffer = indexBuffer::create(gridIndices);

        return mesh::create(gridVertBuffer, gridIndexBuffer);
    }
}