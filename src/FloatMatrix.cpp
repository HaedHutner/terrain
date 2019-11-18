#include <FloatMatrix.h>

FloatMatrix::FloatMatrix(const int &sizeX, const int &sizeY, float initialValue)
    : sizeX(sizeX), sizeY(sizeY), data(new float*[sizeY])
{
    for (int i = 0; i < sizeX; i++) {
        data[i] = new float[sizeY];
    }
}

void FloatMatrix::set(const int &x, const int &y, const float &value) {
    data[x][y] = value;
}

float FloatMatrix::at(const int &x, const int &y) const {
    return data[x][y];
}

float FloatMatrix::operator()(const int &x, const int &y) const {
    return data[x][y];
}

FloatMatrix::~FloatMatrix() {
    for (int i = 0; i < sizeX; i++) {
        delete[] data[i];
    }

    delete[] data;
}