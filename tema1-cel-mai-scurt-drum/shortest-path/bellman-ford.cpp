#include <bits/stdc++.h>
#include "./utils.h"

using namespace std;

/**
 * The Bellman-Ford algorithm modified to compute the shortest path between any
 * two nodes in a graph.
 *
 * @warning Very slow on big test sets compared to Dijkstra of Floyd-Warshall.
 * @remark O(N^2*E) complexity, where N is the number of nodes/vertices
 * of the graph and E is the number of edges of the graph.
 * @see https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm
 * @param graph The graph in matrix representation.
 * @return The matrix with the shortest path for every node pair.
 */
std::vector<std::vector<long long>> shortest_path(const std::vector<std::vector<edge>>& graph) {
    int V = graph.size(); // Number of vertices in graph

    vector<vector<long long>> final_matrix(V, vector<long long>(V, INF));

    for (int k = 0; k < V; ++k) {
        // Initialize distance of all vertices as 0.
        long long dist[V];
        for (int i = 0; i < V; ++i) {
            dist[i] = INF;
        }

        // initialize distance of source as 0
        dist[k] = 0;

        // Relax all edges |V| - 1 times. A simple
        // shortest path from src to any other
        // vertex can have at-most |V| - 1 edges
        for (int i = 0; i < V - 1; ++i) {
            for (int j = 0; j < V; ++j) {
                for (auto& it : graph[j]) {
                    if (dist[j] + it.second < dist[it.first]) {
                        dist[it.first] = dist[j] + it.second;
                    }
                }
            }
        }

        // check for negative-weight cycles.
        // The above step guarantees shortest
        // distances if graph doesn't contain
        // negative weight cycle.  If we get a
        // shorter path, then there is a cycle.
        for (int i = 0; i < V; ++i) {
            for (auto& it : graph[i]) {
                int x = i;
                int y = it.first;
                int weight = it.second;

                if (dist[x] != INF && dist[x] + weight < dist[y]) {
                    return vector<vector<long long>>(V, vector<long long>(V, -1));
                }
            }
        }

        for (int i = 0; i < V; ++i) {
            final_matrix[k][i] = dist[i];
        }

    }

    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (final_matrix[i][j] == INF) {
                final_matrix[i][j] = -1 * INF;
            }
        }
    }

    return final_matrix;
}