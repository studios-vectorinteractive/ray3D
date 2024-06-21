#pragma once
#include "core/core.h"
#include "resource/mesh.h"

namespace ray3D
{
    class primitives
    {
    public:

        static auto getCube() -> std::unique_ptr<mesh>;
        static auto getGrid(i32 gridSize, f32 innerAlphaRadius = -1.0f, f32 outerAlphaRadius = -1.0f) -> std::unique_ptr<mesh>;

    private:
        primitives() = default;
        ~primitives() = default;
    };
}