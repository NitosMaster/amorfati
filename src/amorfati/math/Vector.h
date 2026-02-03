#ifdef VECTOR_H
#define VECTOR_H

#include "Vector.cpp"

namespace amorfati {
    class Vector {
    private:
            int mDimensions;
            double mData[mDimensions];
    public:
            newVector(dim);
            ~Vector();

            void Print();
    };
}

#endif
