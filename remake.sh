#!/bin/zsh
. ~/.zshrc
conda activate vecdb
cd ~/vecdb/faiss
cmake -B build -DFAISS_ENABLE_GPU=OFF -DFAISS_ENABLE_PYTHON=ON -DBUILD_TESTING=OFF -DBUILD_SHARED_LIBS=ON
make -C build -j20 faiss faiss_avx
make -C build -j20 swigfaiss swigfaiss_avx2
cd build/faiss/python && python setup.py install
