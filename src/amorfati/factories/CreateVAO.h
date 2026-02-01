#ifndef MESH_FACTORY_H
#define MESH_FACTORY_H

#include <glad/gl.h>
#include <vector>

namespace amorfati {
    unsigned int CreateVAO(float* vertices, size_t vertSize, unsigned int* edges, size_t edgeSize); //«== "edges" yes I know very funny ==»//
}

#endif
