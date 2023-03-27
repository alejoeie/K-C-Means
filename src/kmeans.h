#ifndef KMEANS_H
#define KMEANS_H

#define ITER 100
#define OBSERVATIONS 300
typedef struct point_two_dimensions{
   float x;
   float y; 
} p2D;

typedef struct observations{
    p2D point_of_observation;
    int cluster_tag;
}obs;

typedef struct def_centroide{
    p2D point_of_cluster;
    int centroid_cluster_tag; 

}centroide;

obs* importData(char* , int*);
centroide* getInitialCentroids(int, obs*);
float euclideanDistance(p2D, p2D);
void kMeans(centroide*, obs*, int, int);
void exportClusters(centroide*, obs*, int, int, char*);
#endif