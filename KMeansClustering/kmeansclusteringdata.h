/*
 
    kmeansclusteringdata.h
    k-Means Clustering
    Tufts Comp 135 Homework 5
    7 March 2015
    Mike Yeung
 
    These are structures for k-means clustering.
 
 */

#ifndef __KMeansClustering__kmeansclusteringdata__
#define __KMeansClustering__kmeansclusteringdata__

#include <iostream>
#include <vector>
#include <random>
using namespace std;

struct DataPoint;
struct Cluster;

struct DataPoint {
    vector<float> values;
    Cluster *cluster;
    void assignCluster(vector<Cluster> clusters);
    float distanceToCluster();
};

struct Cluster {
    vector<DataPoint *> dataPoints;
    vector<float> center;
    void recalculateCenter();
};

class KMeansClusteringData {

private:
    
    vector<string> attributes;
    vector<DataPoint *> dataPoints;
    vector<Cluster *> clusters;
    
public:
    
    // Parses file into private variables
    void readARFF(string file);
    
    // Returns sum of squared distances from each point to its cluster center
    float iterate(int k, bool newPoints);
    
    // Iterates until no point reassigned to different cluster
    float iterateUntilNoReassignment(int k);
};

#endif
