#pragma once

class Drawer {
public:
    void draw_quad(
            double x1, double y1,
            double x2, double y2,
            double x3, double y3,
            double x4, double y4);
    void draw_tri(
            double x1, double y1,
            double x2, double y2,
            double x3, double y3);
};

class Drawable {
    virtual void draw(Drawer* drawer) const = 0;
};
