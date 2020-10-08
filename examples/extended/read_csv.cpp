#include <Matrix.hpp>

// Example program

// Read a csv file and get a Matrix object
// The Matrix object is then printed to the console.
int main() {
    Matrix mat = read_csv("./datasets/blobs/blobs.csv");
    mat.print();

    return 0;
}