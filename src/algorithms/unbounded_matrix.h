
template <typename T>
class UnboundedMatrix {
protected:
    std::vector<T> internal;
    T internal_def;
    T def;
public:
    const int width;
    const int height;
    UnboundedMatrix(int w, int h) : internal(w * h), width(w), height(h) {}
    
    T& get(int x, int y) {
        if (x < 0 || x >= width ||
            y < 0 || y >= height) {
            //assert(def == internal_def);
            return def;
        } else {
            return internal[x + y*width];
        }
    }
};
