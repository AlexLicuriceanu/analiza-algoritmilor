#include <bits/stdc++.h>
#include "./utils.h"

using namespace std;

/**
 * The Floyd-Warshall algorithm to compute the shortest path between any
 * two nodes in a graph.
 *
 * @remark O(N^3) complexity, where N is the number of nodes/vertices
 * of the graph.
 * @see https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm
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

    /*
     * Add all vertices one by one to
     * the set of intermediate vertices.
     */
    for (int k = 0; k < size; ++k) {
        /* Pick all vertices as the source, one by one */
        for (int i = 0; i < size; ++i) {
            /* Pick all vertices as the destination for the vertex picked above */
            for (int j = 0; j < size; ++j) {
                /*
                 * If vertex k is on the shortest path from
                 * i to j, then update the value of
                 * the minimum distance from i to j.
                 */
                if (final_matrix[i][j] > final_matrix[i][k] + final_matrix[k][j]) {
                    final_matrix[i][j] = final_matrix[i][k] + final_matrix[k][j];
                }
            }
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (final_matrix[i][j] == INF) {
                final_matrix[i][j] = -1 * INF;
            }
        }
    }

    for (int i = 0; i < size; ++i) {
        if (final_matrix[i][i] < 0) {
            return vector<vector<long long>>(size, vector<long long>(size, -1 * INF));
        }
    }

    return final_matrix;
}