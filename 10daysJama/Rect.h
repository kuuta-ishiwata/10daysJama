#pragma once
#include <iostream>

class Rect
{

public:
    float x, y;       // ����̍��W
    float width, height;

    Rect(float x_, float y_, float w_, float h_)
        : x(x_), y(y_), width(w_), height(h_) {
    }


};

// �����蔻��iAABB�����j
bool isColliding(const Rect& a, const Rect& b) {
    return (a.x < b.x + b.width &&
        a.x + a.width > b.x &&
        a.y < b.y + b.height &&
        a.y + a.height > b.y);
}

