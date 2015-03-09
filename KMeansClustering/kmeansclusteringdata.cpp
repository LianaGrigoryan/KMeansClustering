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

float DataPoint::assignCluster(vector<Cluster *> clusters) {
    float minDistance = FLT_MAX;
    float tempDistance;
    Cluster *cluster = NULL;
    int size = (int)clusters.size();
    for (int i = 0; i < size; i++) {
        tempDistance = distance(values, clusters[i]->center);
        if (tempDistance < minDistance) {
            minDistance = tempDistance;
            cluster = clusters[i];
        }
    }
    cluster->dataPoints.push_back(this);
    return minDistance;
}

void Cluster::recalculateCenter() {
    int numberOfAttributes = (int)center.size();
    int numberOfPoints = (int)dataPoints.size();
    center.clear();
    center.resize(numberOfAttributes, 0);
    for (int i = 0; i < numberOfPoints; i++) {
        for (int j = 0; j < numberOfAttributes; j++) {
            center[j] += dataPoints[i]->values[j];
        }
    }
    for (int i = 0; i < numberOfAttributes; i++) {
        center[i] /= numberOfPoints;
    }
    dataPoints.clear();
}

float KMeansClusteringData::assignClusters() {
    float distances = 0;
    int numberOfPoints = (int)dataPoints.size();
    for (int i = 0; i < numberOfPoints; i++) {
        distances += pow(dataPoints[i]->assignCluster(clusters), 2);
    }
    return distances;
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

float KMeansClusteringData::iterateNew(int k) {
    
    clusters.clear();
    
    default_random_engine generator;
    uniform_int_distribution<int> distribution(0, (int)dataPoints.size() - 1);
    auto random = bind(distribution, generator);
    
    for (int i = 0; i < k; i++) {
        Cluster *cluster = new Cluster;
    assign:
        cluster->center = dataPoints[random()]->values;
        for (int j = 0; j < i; j++) {
            if (clusters[j]->center == cluster->center) {
                goto assign;
            }
        }
        clusters.push_back(cluster);
    }
    
    return assignClusters();
}

float KMeansClusteringData::iterateOld() {
    int numberOfClusters = (int)clusters.size();
    for (int i = 0; i < numberOfClusters; i++) {
        clusters[i]->recalculateCenter();
    }
    return assignClusters();
}

float KMeansClusteringData::iterateUntilNoReassignment(int k) {
    float distances = iterateNew(k);
    float temp;
    while (true) {
        temp = iterateOld();
        if (distances == temp) {
            break;
        }
        distances = temp;
    }
    return distances;
}