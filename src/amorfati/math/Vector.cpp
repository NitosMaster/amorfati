#include<iostream>

namespace amorfati {
    Vector::Vector (const int dim) {
        mDimensions = dim;

        for (int i = 0; i <= mDimensions; i++) {
            mData[i] = 0;
        }
    };
}
