/*
 * File: Cluster.h
 * --------------------
 * This file is to identify the outliers based on K-means clustering.
 */

#ifndef CLUSTER_H
#define CLUSTER_H

#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <math.h>
using namespace std;



//PART 1

/*
 * Class: KEAMS
 * --------------------------------------------------------------------------
 * It is the first part that divide the n observations into k clusters
 */
template <typename T>
class KMEANS{
public:
    KMEANS<T>(int k);

    /*
     * Function: k_means
     * -------------------------
     * The function includes 2 parts: Cluster and Identifying outliers.
     * The Cluster part includes 4 steps to get k clusters.
     * The second part include 2 steps.
     */
    void k_means(vector< vector<T> > data, int k, int max_intera);

    vector< vector<T> > data;
    int k;
    int sample_size;
    int components_num;

    /*
    * Struct: Cluster
    * ------------------------------
    * This struction is in order to define a cluster, including a centroid point and the samples.
    * The centroid point is represented by its features; the samples are represented by their No.
    */
    struct Cluster{
        vector<double> centroid;
        vector<int> samples;
    };

    /*
    * Function: EcluDist
    * ---------------------
    * This function aims to compute the distance using EcludDist.
    * We use distance to represent the dissimilarity between observations and then, divide them into k clusters.
    */
    double EcludDist(vector<T> & v1, vector<T> & v2);
};

/*
 * The following is the implementation.
 */

//PART 1
template <typename T>
KMEANS<T>::KMEANS(int k){
    this -> k = k;
}

/*
 * Implementation: EcludDist
 * ------------------------
 * Calculate the distance using Ecludian method
 * d = sqrt[∑(x-mean)^2]
 */
template <typename T>
double KMEANS<T>::EcludDist(vector<T> & v1, vector<T> & v2){
    if (v1.size() != v2.size()){
        fprintf(stderr,"the two vectors should have the same length");
    }
    int len = v1.size();
    T dist_square = 0;
    for (int i = 0 ; i < len ; i++){
        dist_square += (v1[i] - v2[i]) * (v1[i] - v2[i]);
    }
    return sqrt(dist_square);
}


/*
 * Implementation: k_means
 * -----------------------------------
 * This function aims to find out outliers and delete them based on k-means clustering.
 */

template <typename T>
void KMEANS<T>::k_means(vector< vector<T> > data, int k, int max_itera){

    //PART 1
    //Using the k_means to do the cluster.
    //(1)Choose k centroid points randomly;
    //(2)Decide which cluster the sample points belong to according to Ecludian distance: belong to the nearest centroid point;
    //(3)Renew the centroid points by the points that are in the same cluster: their mean;
    //(4)Iterate the (2) and (3) until the centroid points do not change(do it for max_itera times);

    sample_size = data.size();
    components_num = data[0].size();

    /* Initialize the centroids */
    vector<Cluster> clusters(k);
    int seed = time(NULL);
    for (int i = 0; i < k; i++){
        srand(seed);
        int p = rand() % sample_size;
        clusters[i].centroid = data[p];
        seed = rand();
    }

    /* Iterate the process for max_itera times */
    for (int t = 0; t < max_itera; t++){
        /* Clear the points in every cluster before doing the following process */
        for (int m = 0; m < k; m++){
            clusters[m].samples.clear();
        }
        /* Identify which cluster the points belong to */
        for (int j = 0; j < sample_size; j++){
            int c = 0;            /* Initially, all points belong to clusters[0] */
            double init_dist = EcludDist(clusters[c].centroid, data[j]);
            /* Compare the different distance between point j and different centroids */
            for (int i = 1; i < k; i++){
                double dist = EcludDist(clusters[i].centroid, data[j]);
                if (dist < init_dist)
                    init_dist = dist;
                    c = i;
            }
            clusters[c].samples.push_back(j);
        }

        /* Change the centroids according to the new clusters */
          /* Initialize a new_cent matrix, the first vector includes k centroids, the seconds includes components */
        vector< vector<T> > new_cent(k);
        for (int m = 0; m < k; m++){
            new_cent[m].resize(components_num,0);
        }
          /* Find the new centroids */
        for (int m = 0; m < k; m++){                                   /* For each cluster or centroid */
            for (int j = 0; j < components_num; j++){
                for (int i = 0; i < clusters[m].samples.size(); i++){
                    int point_id = clusters[m].samples[i];
                    new_cent[m][j] += data[point_id][j];
                }
                //new_cent[m][j] = new_cent[m][j] / clusters[m].samples.size();
                clusters[m].centroid[j] = new_cent[m][j] / clusters[m].samples.size();
            }
            //clusters[m].centroid = new_cent[m];
        }
    } //iteration for
    //return clusters;

    //PART 2
    //Indentify outliers and delete them
    //(1)Calculate the threshold = the mean distance of each cluster + 1.5*standard deviation;
    //(2)In each cluster, decide outliers if the distance >= threshold, and delete them;

    for (int i = 0; i < k; i++){
        //Calculate mean
        double dist_sum = 0;
        for (int j = 0; j < clusters[i].samples.size(); j++){
            int pointID = clusters[i].samples[j];
            dist_sum += EcludDist(clusters[i].centroid, data[pointID]);
        }// interate for : every observation in cluster k
        double mean_dist = dist_sum / clusters[i].samples.size();

        //Calculate standard deviation
        double value = 0;
        for (int j = 0; j < clusters[i].samples.size(); j++){
            int pointID = clusters[i].samples[j];
            double diff = EcludDist(clusters[i].centroid, data[pointID]) - mean_dist;
            value += diff * diff;
        }
        double sd_dev = sqrt(value / clusters[i].samples.size());

        //Calulate threshold
        double threshold = mean_dist + 1.5*sd_dev;

        //Identify outliers and delete them from data
        //(a)If the distance between centroid and observation is larger than threshold, it is an outlier
        //(b)Delete outliers from data set
        for (int j = 0; j < clusters[i].samples.size(); j++){
            int pointID = clusters[i].samples[j];
             double dist = EcludDist(clusters[i].centroid, data[pointID]);
             if (dist > threshold) data.erase(data.begin()+pointID);
        }
    }// iterate for : k clusters

}

#endif // CLUSTER_H
