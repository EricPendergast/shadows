#include <vector>
#include <functional>

#include "unbounded_matrix.h"
#include "matrix.h"

template <typename T>
class SumSquares {
private:
    UnboundedMatrix<T> rowSums;
    UnboundedMatrix<T> colSums;
    Matrix<T> boxSums;
public:
    SumSquares(int width, int height) : 
        rowSums(width, height),
        colSums(width, height),
        boxSums(width, height) {}
    
    void populate(const std::function<T(int, int)>& get, int width, int height) {
        for (int x = 0; x < boxSums.width; x++) {
            for (int y = 0; y < boxSums.height; y++) {
                rowSums.set(x, y) = 0;
                boxSums.set(x, y) = 0;
            }
        }
        
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < boxSums.height; y++) {
                rowSums.set(0, y) += get(x, y);
            }
        }
        
        for (int x = 1; x < boxSums.width; x++) {
            for (int y = 1; y < boxSums.height; y++) {
                // Invariant: colSums[x][y-1] is correct
                // Invariant: rowSums[x-1][y] is correct
                rowSums.set(x, y) = rowSums.get(x-1, y) - get(x-1, y) + get(x-1+width, y);
            }
        }
        
        for (int x = 0; x < boxSums.width; x++) {
            for (int y = 0; y < height; y++) {
                boxSums.set(x, 0) += rowSums.get(x, y);
            }
        }
        
        for (int x = 0; x < boxSums.width; x++) {
            for (int y = 1; y < boxSums.height; y++) {
                // Invariant: boxSums[x, y-1] is correct
                boxSums.set(x, y) = boxSums.get(x, y-1) - rowSums.get(x, y-1) + rowSums.get(x, y-1+height);
            }
        }
    }
    
    T get_sum(int x, int y) {
        return boxSums.get(x, y);
    }
    
    int get_width() {
        return boxSums.width;
    }

    int get_height() {
        return boxSums.height;
    }
};
