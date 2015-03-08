/*
 
    main.cpp
    k-Means Clustering
    Tufts Comp 135 Homework 5
    7 March 2015
    Mike Yeung
 
    Implementation of k-means clustering on .arff files with numeric attributes.
    This reads in a file, then asks the user for a value of k. It starts by
    initializing the cluster centers to k random, different data points. At each
    iteration it assigns each data point to the closest cluster center and
    calculates the sum of the squared distances of each data point from its
    cluster center. After printing this value it asks the user if another
    iteration is desired. If so, new cluster centers are calculated by averaging
    the points in each cluster, the points reassigned to clusters, and the new
    sum of distances calculated. When the user doesn't want any more iterations,
    the program asks if a new value of k is desired, and restarts with that
    value, picking k new random data points.
 
 */

#include "kmeansclusteringdata.h"

int main(int argc, const char *argv[]) {
    // insert code here...
    cout << "Hello, World!\n";
    return 0;
}
