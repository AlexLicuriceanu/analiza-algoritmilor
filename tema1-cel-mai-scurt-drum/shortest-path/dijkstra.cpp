#include <bits/stdc++.h>
#include "./utils.h"

using namespace std;

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in the shortest path tree
/**
 * Utility function to find the node with the minimum distance value
 * from the set of nodes not yet included in the shortest path tree
 *
 * @param dist Array containing minimum distances.
 * @param sptSet Shortest path tree.
 * @param size Total number of nodes.
 */
int minDistance(long long dist[], bool sptSet[], int size) {
    /* Initialize min value */
    long long min = INF;
    int min_index = 0;

    for (int v = 0; v < size; ++v) {
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

/**
 * Dijkstra's algorithm modified to compute the shortest path between any two
 * nodes in a graph. Implemented using a adjacency matrix.
 *
 * @remark O(N^3) complexity, where N is the number of nodes/vertices
 * of the graph. Can also be implemented in O(N*E*log(N)) time with the
 * use of a min heap, where E is the number of edges and N is the number
 * of nodes of the graph.
 * @see https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
 * @param graph The graph in matrix representation.
 * @return The matrix with the shortest path for every node pair.
 */
std::vector<std::vector<long long>> shortest_path(const std::vector<std::vector<edge>>& graph) {
    int size = graph.size();

    vector<vector<long long>> final_matrix(size, vector<long long>(size, INF));

    for (int i = 0; i < size; ++i) {
        for (auto& it : graph[i]) {
            final_matrix[i][it.first] = it.second;
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i == j) {
                final_matrix[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (final_matrix[i][j] < 0) {
                return vector<vector<long long>>(size, vector<long long>(size, -1 * INF));
            }
        }
    }

    for (int i = 0; i < size; ++i) {
        /*
         * The output array, dist[i] will hold the shortest
         * distance from src to i
         */
        long long dist[size];

        /*
         * sptSet[i] will be true if vertex [i] is included in the shortest
         * path tree or shortest distance from src to i is finalized
         */
        bool sptSet[size];

        /* Initialize all distances as INFINITE and stpSet[] as false */
        for (int j = 0; j < size; ++j) {
            dist[j] = INF;
            sptSet[j] = false;
        }

        /* Distance of source vertex from itself is always 0 */
        dist[i] = 0;

        /* Find the shortest path for all vertices */
        for (int count = 0; count < size - 1; ++ count) {
            /*
             * Pick the minimum distance vertex from the set of vertices not
             * yet processed. u is always equal to src in the first iteration.
             */
            int u = minDistance(dist, sptSet, size);

            /* Mark the picked vertex as processed */
            sptSet[u] = true;

            /* Update dist value of the adjacent vertices of the picked vertex */
            for (int v = 0; v < size; ++v) {
                /*
                 * Update dist[v] only if is not in sptSet, there is an edge from
                 * u to v, and total weight of path from src to  v through u is
                 * smaller than current value of dist[v]
                 */
                if (!sptSet[v] && final_matrix[u][v] && dist[u] != INF
                    && dist[u] + final_matrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + final_matrix[u][v];
                }
            }
        }
        for (int h = 0; h < size; ++h) {
            final_matrix[i][h] = dist[h];
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (final_matrix[i][j] == INF) {
                final_matrix[i][j] = -1 * INF;
            }
        }
    }
    return final_matrix;
}