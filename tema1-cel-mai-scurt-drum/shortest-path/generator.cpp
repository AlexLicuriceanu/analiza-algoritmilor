#include <iostream>
#include <fstream>
#include <random>
#include <bits/stdc++.h>
#include "./utils.h"

using namespace std;

#define MAX_NODES 10000
#define MAX_EDGES 1000000
#define MAX_COST 1000000
#define MIN_COST (-1000000)

/**
 * Function that generates a pseudo-random graph input file. The two numbers
 * on the first line of the generated file will represent the number of nodes, and
 * the number of edges, respectively. The parameters prefixed with "min_" or "max_"
 * control the interval of the values generated for the nodes, edges or cost values.
 * The maximum number of edges is the value calculated by the function min(N*N, 10^6)
 * where N is the number of nodes.
 *
 * @param path Output path of the generated file.
 * @param negativeCosts Controls if the algorithm generates edges with negative costs.
 * @param directed Controls if the generated graph is directed or not.
 * @param min_nodes Minimum number of nodes to generate.
 * @param max_nodes Maximum number of nodes to generate.
 * @param min_edges Minimum number of edges to generate.
 * @param min_cost Minimum cost for each edge.
 * @param max_cost Maximum cost for each edge.
 */
void generate_graph(string path, bool negativeCosts, bool directed,
                    int min_nodes, int max_nodes,
                    int min_edges,
                    int min_cost, int max_cost) {
    ofstream out(path);

    /* Generator setup */
    random_device rand_device;
    mt19937 generator(rand_device());

    /* Generate random nodes number in interval [min_nodes, max_nodes] */
    uniform_int_distribution<> nodes_nr_distribution(min_nodes, max_nodes);
    int N = nodes_nr_distribution(generator);

    /* Generate random edges number in interval [min_edges, min(N^2, 10^6)] */
    uniform_int_distribution<> edges_distribution(min_edges, min(N*N, MAX_EDGES));
    int E = edges_distribution(generator);

    /* Output to file */
    if (directed) {
        out << N << " " << E << "\n";
    } else {
        out << N << " " << 2 * E << "\n";
    }


    /*
     * Generate random node pairs in interval [1, E] and cost
     * values in interval [min_cost, max_cost] if the negativeCosts
     * boolean is true or in interval [0, max_cost] if false.
     */
    uniform_int_distribution<> cost_distribution;

    if (negativeCosts) {
        uniform_int_distribution<> negative_cost_distribution(min_cost, max_cost);
        cost_distribution = negative_cost_distribution;
    } else {
        uniform_int_distribution<> positive_cost_distribution(0, max_cost);
        cost_distribution = positive_cost_distribution;
    }

    for (int i = 1; i <= E; i++) {
        uniform_int_distribution<> node_distribution(1, N);
        int startNode = node_distribution(generator);
        int endNode = node_distribution(generator);
        int cost = cost_distribution(generator);

        /* Output to file */
        out << startNode << " " << endNode << " " << cost << "\n";

        if (!directed) {
            out << endNode << " " << startNode << " " << cost << "\n";
        }
    }
    out.close();
}

/**
 * Driver function to generate graph test files with different properties.
 * The program may freeze during the computation of the reference files.
 *
 * @return 0 for successful executions.
 */
int main() {
    int test_number = 1;

    /* Number of tests for every interval of values */
    int number_of_tests = 5;

    cout << "Generating test files. ";

    /*
     * Code to generate some directed graph test sets
     */
    for (int i = 0; i < number_of_tests; i++, test_number++) {
        string inFile = "in/test" + to_string(test_number) + ".in";
        generate_graph(inFile, false, true, 1, 10, 1, 0, 100);
    }

    for (int i = 0; i < number_of_tests; i++, test_number++) {
        string inFile = "in/test" + to_string(test_number) + ".in";
        generate_graph(inFile, false, true, 10, 100, 1, 100, 1000);
    }

    for (int i = 0; i < number_of_tests; i++, test_number++) {
        string inFile = "in/test" + to_string(test_number) + ".in";
        generate_graph(inFile, false, true, 100, 500, 1, 1000, 10000);
    }

    for (int i = 0; i < number_of_tests; i++, test_number++) {
        string inFile = "in/test" + to_string(test_number) + ".in";
        generate_graph(inFile, false, true, 100, 500, 1, 1000, 10000);
    }


    /*
     * Code to generate some undirected graph test sets
     */
    for (int i = 0; i < number_of_tests; i++, test_number++) {
        string inFile = "in/test" + to_string(test_number) + ".in";
        generate_graph(inFile, false, false, 1, 10, 1, 0, 100);
    }

    for (int i = 0; i < number_of_tests; i++, test_number++) {
        string inFile = "in/test" + to_string(test_number) + ".in";
        generate_graph(inFile, false, false, 10, 100, 1, 100, 1000);
    }

    for (int i = 0; i < number_of_tests; i++, test_number++) {
        string inFile = "in/test" + to_string(test_number) + ".in";
        generate_graph(inFile, false, false, 100, 500, 1, 1000, 10000);
    }

    for (int i = 0; i < number_of_tests; i++, test_number++) {
        string inFile = "in/test" + to_string(test_number) + ".in";
        generate_graph(inFile, false, false, 100, 500, 1, 1000, 10000);
    }


    cout << "Done.\n";
    cout << "Generating big test files. ";

    /*
     * Generate two graphs with number of nodes between 1000 and 1500 and
     * minimum 100000 edges with costs between 10000 and 100000 (1 directed, 1 undirected)
     */
    string bigInFile1 = "in/test" + to_string(test_number) + ".in";
    generate_graph(bigInFile1, false, true, 1000, 1500, 100000, 10000, 100000);
    test_number++;

    string bigInFile2 = "in/test" + to_string(test_number) + ".in";
    generate_graph(bigInFile2, false, false, 1000, 1500, 100000, 10000, 100000);
    test_number++;

    /*
    * Generate two graphs with number of nodes between 1000 and 1500 and
    * minimum 100000 edges with costs between 0 and 100 (1 directed, 1 undirected)
    */
    string bigInFile3 = "in/test" + to_string(test_number) + ".in";
    generate_graph(bigInFile3, false, true, 1000, 1500, 100000, 0, 100);
    test_number++;

    string bigInFile4 = "in/test" + to_string(test_number) + ".in";
    generate_graph(bigInFile4, false, false, 1000, 1500, 100000, 0, 100);
    test_number++;

    cout << "Done.\n";
    cout << "Generating ref files. ";

    /* Generate the ref files in the ./out folder for each new test set */
    for (int i = 1; i <= test_number; i++) {
        string inFile = "in/test" + to_string(i) + ".in";
        ifstream fin(inFile);

        if (fin.is_open()) {
            /* Open the input file */
            string outFile = "out/test" + to_string(i) + ".out";
            /* Create the output file */
            ofstream fout(outFile);

            /* Read number of nodes & edges */
            int N, E;
            fin >> N >> E;
            vector<vector<edge>> adjacency_list(N);

            for (int j = 1; j <= E; j++) {
                int startNode, endNode, cost;
                fin >> startNode >> endNode >> cost;
                adjacency_list[startNode-1].push_back(make_pair(endNode-1, cost));
            }

            /* Execute Floyd-Warshall to get the reference result */
            vector<vector<long long>> result_matrix = shortest_path(adjacency_list);
            for (int row = 0; row < N; row++) {
                for (int column = 0; column < N; column++) {
                    if (result_matrix[row][column] == -1 * INF) {
                        fout << "NaN ";
                    } else {
                        fout << result_matrix[row][column] << " ";
                    }
                }
                fout << "\n";
            }

            fout.close();
        }
        fin.close();
    }

    cout << "Done.\n";

    return 0;
}