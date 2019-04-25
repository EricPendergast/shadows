#include <vector>
#include <assert.h>

template <typename T>
class Matrix {
protected:
    std::vector<T> internal;
public:
    const int width;
    const int height;
    Matrix(int w, int h) : internal(w * h), width(w), height(h) {}
    
    T& set(int x, int y) {
        assert_in_range(x, y);

        return internal[x + y*width];
    }

    const T& get(int x, int y) {
        return set(x, y);
    }

    void assert_in_range(int x, int y) {
        assert(x >= 0 && x < width);
        assert(y >= 0 && y < height);
    }
};
