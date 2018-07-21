#include <vector>

template <typename T>
class Matrix {
protected:
    std::vector<T> internal;
public:
    const int width;
    const int height;
    Matrix(int w, int h) : internal(w * h), width(w), height(h) {}
    
    T& get(int x, int y) {
        assert(x >= 0 && x < width);
        assert(y >= 0 && y < height);
        return internal[x + y*width];
    }
};
