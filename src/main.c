#include <stdio.h>
#include "kmeans.c"
#include <unistd.h>

int main(int argc, char** argv){

    char* filepath = "./data/data.txt";
    int obs_detected = 0;
    obs* getObs = importData(filepath, &obs_detected);
    
    int clusters = 5;
    centroide* gotCentroids = getInitialCentroids(clusters,getObs);

    kMeans(gotCentroids, getObs, obs_detected, clusters);

    char* output_file = "./data/kmeans.txt";
    exportClusters(gotCentroids, getObs, obs_detected, clusters, output_file);
    free(gotCentroids);
    free(getObs);
    return 0;
}