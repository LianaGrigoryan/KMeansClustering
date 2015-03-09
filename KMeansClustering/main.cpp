/*
 
    main.cpp
    k-Means Clustering
    Tufts Comp 135 Homework 5
    7 March 2015
    Mike Yeung
 
    Compile with
    "g++ -o cluster -std=gnu++11 -O3 kmeansclusteringdata.cpp main.cpp".
     
    Run with "./cluster". There are no command line arguments.
 
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
 
    Test results on hw5.2.arff after running iterateUntilNoReassignment 10,000
    times for each k:
 
    k   Quality
    -----------
    2   836,433
    3   560,685
    4   341,668
    5   123,543
    6   119,712
 
    Estimate of correct number of clusters: 5.
 
 */

#include "kmeansclusteringdata.h"

int main(int argc, const char *argv[]) {
    
    cout << "Enter full path for .arff file. Don't use the ~ shortcut." << endl;
    
filepathPrompt:
    string path;
    cin >> path;
    ifstream file;
    file.open(path);
    if (!file.is_open()) {
        cout << "File could not open. Reenter path." << endl;
        goto filepathPrompt;
    }
    KMeansClusteringData data;
    data.readARFF(&file);
    bool qualityMessageShown = false;
    
kPrompt:
    cout << "Enter number of clusters (k)." << endl;
    int k;
    cin >> k;
    if (!qualityMessageShown) {
        cout << "Note: Quality is the sum of squared distances of data points ";
        cout << "from their closest cluster center." << endl;
        qualityMessageShown = true;
    }
    cout << "k: " << k << ". Quality: " << data.iterateNew(k) << "." << endl;
    
anotherIterationPrompt:
    cout << "Do you want another iteration? Type 'yes' or 'no'." << endl;
    string anotherIteration;
    cin >> anotherIteration;
    if (anotherIteration == "yes") {
        cout << "k: " << k << ". Quality: " << data.iterateOld() << "." << endl;
        goto anotherIterationPrompt;
    } else if (anotherIteration == "no") {
        
    newKPrompt:
        cout << "Do you want a new value of k? Type 'yes' or 'no'." << endl;
        string newK;
        cin >> newK;
        if (newK == "yes") {
            goto kPrompt;
        } else if (newK != "no") {
            cout << "Input not recognized." << endl;
            goto newKPrompt;
        }
    } else {
        cout << "Input not recognized." << endl;
        goto anotherIterationPrompt;
    }
    
    return 0;
}
