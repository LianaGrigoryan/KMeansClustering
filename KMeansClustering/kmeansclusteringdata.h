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
#include <fstream>
#include <string>
#include <sstream>
#include <cfloat>
#include <vector>
#include <random>
#include <cassert>
using namespace std;

struct DataPoint;
struct Cluster;

struct DataPoint {
    vector<float> values;
    Cluster *cluster;
    float assignCluster(vector<Cluster *> clusters);    // Returns distance
};

struct Cluster {
    vector<DataPoint *> dataPoints;
    vector<float> center;
    void recalculateCenter();   // Clears data points
};

class KMeansClusteringData {

private:
    
    vector<string> attributes;
    vector<DataPoint *> dataPoints;
    vector<Cluster *> clusters;
    default_random_engine generator;
    int random(int values);
    float assignClusters(); // Returns sum of squared distances
    
public:
    
    // Parses file into private variables
    void readARFF(ifstream *file);
    
    // Returns sum of squared distances from each point to its cluster center
    float iterateNew(int k);
    float iterateOld();
    
    // Iterates until no point reassigned to different cluster
    float iterateUntilNoReassignment(int k);
};

#endif
