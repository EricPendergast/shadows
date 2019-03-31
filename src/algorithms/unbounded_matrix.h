#include <assert.h>
#include <vector>

template <typename T>
class UnboundedMatrix {
protected:
    std::vector<T> internal;
    T def;
public:
    const int width;
    const int height;
    UnboundedMatrix(int w, int h) : internal(w * h), width(w), height(h) {}
    
    T const& get(int x, int y) const {
        if (x < 0 || x >= width ||
            y < 0 || y >= height) {
            return def;
        } else {
            return internal[x + y*width];
        }
    }

    T& set(int x, int y) {
        if (x < 0 || x >= width ||
            y < 0 || y >= height) {
            assert(false && "Index out of range");
        } else {
            return internal[x + y*width];
        }
    }
};
