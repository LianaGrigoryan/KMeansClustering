/*
 
    kmeansclusteringdata.cpp
    k-Means Clustering
    Tufts Comp 135 Homework 5
    7 March 2015
    Mike Yeung
 
    These are structures for k-means clustering.
 
 */

#include "kmeansclusteringdata.h"

float distance(vector<float> a, vector<float> b) {
    int size = (int)a.size();
    assert(size == b.size());
    float squaredDistances = 0;
    for (int i = 0; i < size; i++) {
        squaredDistances += pow(b[i] - a[i], 2);
    }
    return sqrt(squaredDistances);
}

float DataPoint::assignCluster(vector<Cluster> clusters) {
    float minDistance = FLT_MAX;
    float tempDistance;
    Cluster *cluster = NULL;
    int size = (int)clusters.size();
    for (int i = 0; i < size; i++) {
        tempDistance = distance(values, clusters[i].center);
        if (tempDistance < minDistance) {
            minDistance = tempDistance;
            cluster = &clusters[i];
        }
    }
    cluster->dataPoints.push_back(this);
    return minDistance;
}

void Cluster::recalculateCenter() {
    
}

void KMeansClusteringData::readARFF(ifstream file) {
    
    assert(file.is_open());
    
    string text;
    while (!file.eof()) {
        file >> text;
        if (text == "@attribute") {
            file >> text;
            attributes.push_back(text);
            file >> text;
            assert(text == "numeric");
        } else if (text == "@data") {
            getline(file, text);
            break;
        }
    }
    
    stringstream ss;
    string value;
    
    while (getline(file, text)) {
        ss << text;
        DataPoint *dataPoint = new DataPoint;
        while (getline(ss, value, ',')) {
            dataPoint->values.push_back(stof(value));
        }
        dataPoints.push_back(dataPoint);
        ss.clear();
    }
}