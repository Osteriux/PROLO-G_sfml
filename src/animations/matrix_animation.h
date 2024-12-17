#pragma once
#include "multi_texture.h"

class MatrixAnimation : public MultiTexture
{
protected:
    float switchTime, currentTime;
public:
    MatrixAnimation(std::string texture_path, int nbLines, int nbColumns, std::vector<int> columnsSize, float switchTime);
    void setLine(int line) override;
    void setColumn(int column) override{};
    bool update(float dt) override;
    ~MatrixAnimation() = default;
};
