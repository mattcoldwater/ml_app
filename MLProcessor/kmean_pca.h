#ifndef KMEAN_PCA_H
#define KMEAN_PCA_H

#include<pca.h>
#include<cluster.h>

class KMEANS_PCA: public PCA,public KMEANS<double>{
public:
    KMEANS_PCA(int k)
        : PCA(), KMEANS<double>(k) {

    }

};

#endif // KMEAN_PCA_H
