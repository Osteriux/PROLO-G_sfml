#pragma once
#include "multi_texture.h"

class MatrixAnimation : public MultiTexture
{
protected:
    float switchTime, currentTime;
public:
    MatrixAnimation(std::string texture_path, int nbLines, int nbColumns, int* columnsSize, float switchTime);
    bool update(float dt) override;
    ~MatrixAnimation() = default;
};
