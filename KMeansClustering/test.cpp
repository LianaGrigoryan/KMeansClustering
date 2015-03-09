#include "kmeansclusteringdata.h"

int main(int argc, const char *argv[]) {
    
    ifstream file;
    file.open("/Users/Mike/Desktop/hw5.2.arff");
    KMeansClusteringData data;
    data.readARFF(&file);
    
    for (int i = 1; i <= data.getDataPointsSize(); i++) {
        cout << "k: " << i << ". Quality: " << data.iterateUntilNoReassignment(i, 10000) << "." << endl;
    }
    
    return 0;
}