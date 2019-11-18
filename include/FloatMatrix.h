class FloatMatrix {

protected:

    int sizeX, sizeY;

    float** data;

public:

    FloatMatrix(const int &sizeX, const int &sizeY, float initialValue = 0.0f);

    void set(const int &x, const int &y, const float &value);

    float at(const int &x, const int &y) const;

    float operator()(const int &x, const int &y) const;

    ~FloatMatrix();
};