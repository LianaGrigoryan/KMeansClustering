/*
 
    kmeansclusteringdata.cpp
    k-Means Clustering
    Tufts Comp 135 Homework 5
    7 March 2015
    Mike Yeung
 
    These are structures for k-means clustering.
 
 */

#include "kmeansclusteringdata.h"

// Simple Euclidean distance
float distance(vector<float> a, vector<float> b) {
    int size = (int)a.size();
    assert(size == b.size());
    float squaredDistances = 0;
    for (int i = 0; i < size; i++) {
        squaredDistances += pow(b[i] - a[i], 2);
    }
    return sqrt(squaredDistances);
}

// Generates a random number from 0 to values - 1
int KMeansClusteringData::random(int values) {
    uniform_int_distribution<int> distribution(0, values - 1);
    return distribution(generator);
}

// Assigns data point to nearest cluster and returns distance to it
float DataPoint::assignCluster(vector<Cluster *> clusters) {
    float minDistance = FLT_MAX;
    float tempDistance;
    cluster = NULL;
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

// Recalculates center of cluster to average of its data points' values
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

// Assigns all data points to clusters. If cluster has no points, it chooses a
// new random data point as its center.
float KMeansClusteringData::assignClusters() {
    
start:
    float distances = 0;
    int numberOfPoints = (int)dataPoints.size();
    for (int i = 0; i < numberOfPoints; i++) {
        distances += pow(dataPoints[i]->assignCluster(clusters), 2);
    }
    
    int numberOfClusters = (int)clusters.size();
    for (int i = 0; i < numberOfClusters; i++) {
        if (clusters[i]->dataPoints.size() == 0) {
            DataPoint *randomPoint;
            do {
                randomPoint = dataPoints[random((int)dataPoints.size())];
            } while (randomPoint->cluster->dataPoints.size() < 2);
            clusters[i]->center = randomPoint->values;
            for (int j = 0; j < numberOfClusters; j++) {
                clusters[j]->dataPoints.clear();
            }
            goto start;
        }
    }
    
    return distances;
}

int KMeansClusteringData::getDataPointsSize() {
    return (int)dataPoints.size();
}

void KMeansClusteringData::readARFF(ifstream *file) {
    
    assert(file->is_open());
    
    string text;
    while (!file->eof()) {
        *file >> text;
        if (text == "@attribute") {
            *file >> text;
            attributes.push_back(text);
            *file >> text;
            assert(text == "numeric");
        } else if (text == "@data") {
            getline(*file, text);
            break;
        }
    }
    
    stringstream ss;
    string value;
    
    while (getline(*file, text)) {
        ss << text;
        DataPoint *dataPoint = new DataPoint;
        while (getline(ss, value, ',')) {
            dataPoint->values.push_back(stof(value));
        }
        dataPoints.push_back(dataPoint);
        ss.clear();
    }
}

// Initializes clusters with random different data points, iterates once on
// cluster assignment.
float KMeansClusteringData::iterateNew(int k) {
    
    assert(k <= dataPoints.size());
    clusters.clear();
    
    for (int i = 0; i < k; i++) {
        Cluster *cluster = new Cluster;
    assign:
        cluster->center = dataPoints[random((int)dataPoints.size())]->values;
        for (int j = 0; j < i; j++) {
            if (clusters[j]->center == cluster->center) {
                goto assign;
            }
        }
        clusters.push_back(cluster);
    }
    
    return assignClusters();
}

// Recalculates all cluster centers and iterates once on cluster assignment
float KMeansClusteringData::iterateOld() {
    int numberOfClusters = (int)clusters.size();
    for (int i = 0; i < numberOfClusters; i++) {
        clusters[i]->recalculateCenter();
    }
    return assignClusters();
}

float KMeansClusteringData::iterateUntilNoReassignment(int k, int times) {
    assert(k <= dataPoints.size());
    float minDistances = FLT_MAX;
    float distances;
    float temp;
    for (int i = 0; i < times; i++) {
        distances = iterateNew(k);
        while (true) {
            temp = iterateOld();
            if (distances == temp) {
                break;
            }
            distances = temp;
        }
        if (distances < minDistances) {
            minDistances = distances;
        }
    }
    return minDistances;
}