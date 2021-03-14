#pragma once
class GameObject {

public:

    // Updates the bounding box values
    virtual void update() = 0;
    double min_x, min_y, max_x, max_y;

private:

};