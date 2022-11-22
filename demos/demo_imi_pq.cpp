/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <random>

#include <sys/time.h>

#include <faiss/IndexFlat.h>
#include <faiss/IndexIVFPQ.h>
#include <faiss/IndexPQ.h>
#include <faiss/index_io.h>

double elapsed() {
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

int main() {
    
    int nq = 1;
    float xq[128] = { 52.,  33.,   2.,   0.,   0.,   0.,   0.,   1.,  56.,  81., 115.,
        56.,   0.,   0.,   0.,   2.,  43.,  97.,  66.,  56.,   0.,   0.,
         0.,   4.,  39.,  52.,   4.,   2.,   4.,   7.,   5.,  12., 136.,
         8.,   0.,   0.,   0.,   0.,   0.,  20., 137.,  38.,  37.,  58.,
         0.,   1.,   5.,  55.,  21.,  13.,  89., 137.,  19.,   9.,  18.,
        10.,  19.,   2.,   6.,  22.,  22.,  20.,  36.,  37.,  93.,   9.,
         0.,   0.,   0.,   0.,   0.,  12., 137.,   1.,   1.,   1.,   0.,
        18., 121., 137.,   3.,   0.,   4.,  22.,  21.,  76., 137.,  11.,
         0.,   0.,   0.,   9.,  30., 118.,  79.,  20.,  17.,   7.,   0.,
         0.,   0.,   0.,   0.,   6.,  17.,   0.,   0.,   0.,   0.,  12.,
        64.,  38.,   3.,   0.,   0.,   0.,   0.,  24., 101.,   4.,   1.,
         3.,   6.,   1.,   2.,  23.,  22.,   3.};
    faiss::Index *idx = faiss::read_index("/home/lfy/vecdb/index/IMI2x7_PQ16x8_new");
    auto index = reinterpret_cast<faiss::IndexIVFPQ *> (idx);
    index->nprobe = 1000;
    index->max_codes = 200;
    int k = 10;
    int64_t *I = new int64_t[k];
    float *D = new float[k];

    index->search(nq, xq, k, D, I);

    for(int i = 0;i < k;i++) {
        printf("%d\n", I[i]);
    }

    delete [] I;
    delete [] D;

    return 0;
}
