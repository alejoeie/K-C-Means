#include "kmeans.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

obs* importData(char* filepath, int* count_obs){
    FILE * fp;
    char buffer[100];
    int counter = 0;
    fp = fopen(filepath, "r");
    if (fp == NULL){
        exit(-1);
    }

    while(fgets(buffer, 100, fp) != NULL){
        counter++;
    }

    *count_obs = counter;
    rewind(fp);
    p2D getPoints[counter];
    obs* getObs = malloc(sizeof(obs)*counter);
    rewind(fp);
    float convertObs = 0;
    float convertYObs = 0;
    int tag = 0;
    for(int i = 0; i < counter; ++i){
        if (fgets(buffer, 100, fp) != NULL){
            fscanf(fp, "%f %f", &convertObs, &convertYObs);
            getObs[i].point_of_observation.x = convertObs;
            getObs[i].point_of_observation.y = convertYObs;
            getObs[i].cluster_tag = tag;
        }
    }
    fclose(fp);
    return getObs;

}

centroide* getInitialCentroids(int clusters, obs* seenObs){

    centroide* getCentroid = malloc(sizeof(centroide)*clusters);
    if (getCentroid == NULL) {
        perror("malloc failed!");
        exit(EXIT_FAILURE);
    }
    obs arrObs[OBSERVATIONS];
    for(int i = 0; i < clusters; ++i){
        int n = rand()%300;
        getCentroid[i].point_of_cluster.x = seenObs[n].point_of_observation.x; 
        getCentroid[i].point_of_cluster.y = seenObs[n].point_of_observation.y;
        getCentroid[i].centroid_cluster_tag = 0;
        
    }

    return getCentroid;
}

float euclideanDistance(p2D A, p2D B){
    float x_res = pow((A.x - B.x),2);
    float y_res = pow((A.y - B.y),2);
    return sqrt(x_res + y_res);

}

void kMeans(centroide* initialCentroids, obs* seenObs, int cantObs, int clusters){
    for(int lx = 0; lx < ITER; ++lx){
        for(int i = 0; i<clusters; ++i){
            initialCentroids[i].centroid_cluster_tag = i;
        }

        float euclidean_distance = 0.0;
        float minimal = 10000.0;
        float minimal_values[10];
    
        for(int i = 0; i < cantObs-1; ++i){
            for (int j = 0; j < 10; ++j){
                euclidean_distance = euclideanDistance(seenObs[i].point_of_observation, initialCentroids[j].point_of_cluster);
                minimal_values[j] = euclidean_distance;
            
            }
            float min_value = minimal_values[0];
            int pos = 0;
            for(int k = 0; k < 10; ++k){
                if (minimal_values[k] < min_value){
                    min_value = minimal_values[k];
                    pos = k;
                } 
            }
            seenObs[i].cluster_tag = initialCentroids[pos].centroid_cluster_tag;
        }
    
        for(int itr = 0; itr < 10; ++itr){
            float acumX = 0.0;
            float acumY = 0.0;
            float promedioX = 0.0;
            float promedioY = 0.0;
            int counter  = 0;
            for(int j = 0; j < cantObs-1; ++j){
                if(seenObs[j].cluster_tag == itr){
                    printf("\nObsX: %.1f ObsY: %.1f Centroid_Tag: %d\n",seenObs[j].point_of_observation.x, seenObs[j].point_of_observation.y, seenObs[j].cluster_tag);
                    acumX += seenObs[j].point_of_observation.x;
                    acumY += seenObs[j].point_of_observation.y;
                    counter++;
                }
            }
            promedioX = (acumX / counter);
            promedioY = (acumY / counter);
            initialCentroids[itr].point_of_cluster.x = promedioX;
            initialCentroids[itr].point_of_cluster.y = promedioY;
            initialCentroids[itr].centroid_cluster_tag = itr;
            printf("itr: %d, promX: %.1f, counter: %d\n", itr, promedioX, counter);
        }
    }

}

void exportClusters(centroide* centroids, obs* observations, int cantOfObs, int clustersCant, char* filepath){
    FILE* fp;

    fp = fopen(filepath, "w");
    for (int i = 0; i < clustersCant; ++i){
        fprintf(fp, "%.1f %.1f %d \n", centroids[i].point_of_cluster.x, centroids[i].point_of_cluster.y, centroids[i].centroid_cluster_tag);
    }

    fprintf(fp, "\n");

    for (int ob = 0; ob < cantOfObs-1; ++ob){
        fprintf(fp, "%.1f %.1f %d \n", observations[ob].point_of_observation.x, observations[ob].point_of_observation.y, observations[ob].cluster_tag);

    }
    fclose(fp);
}