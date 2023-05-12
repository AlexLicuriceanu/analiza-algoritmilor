#include <iostream>
#include <fstream>
#include <chrono>
#include "./utils.h"
#define TIME_PROGRAM true;


/*
 * Modify this when adding/removing test files
 * to specify how many tests to run. Test files
 * should be named "testX.in" and the numbering
 * should start from 1.
 */
#define TESTS_NUMBER 44;

using namespace std;

/**
 * Driver function for the tester program of the 3 algorithms. The program accepts
 * arguments when executing it. The argument represents the test file's name. If no
 * argument was provided, the program will test all sets in the ./in folder and
 * output the results in the ./out folder. If the program is ran with an argument,
 * the input test file should be in the same directory as the algorithm's executable
 * and the program will create a file named "test.out" in the directory in which is ran.
 *
 * @warning The test files in the ./in directory have to be named "testX.in", where X is
 * the test's number starting from 1.
 * @param argc The number of arguments provided.
 * @param argv The arguments.
 * @return 0 on exit.
 */
int main(int argc, char **argv) {
    int tests_number = TESTS_NUMBER;

    if (argc == 2) {
        /* Only one file to test, open it */
        string inFile = argv[1];
        ifstream fin(inFile);

        if (fin.is_open()) {
            string outFile = "test.out";
            /* Create the output file */
            ofstream fout(outFile);

            int N, E;
            fin >> N >> E;
            vector<vector<edge>> adjacency_list(N);

            for (int j = 1; j <= E; j++) {
                int startNode, endNode, cost;
                fin >> startNode >> endNode >> cost;
                adjacency_list[startNode-1].push_back(make_pair(endNode-1, cost));
            }

            /* Execute whichever algorithm and time it if the timer is enabled */
            auto start_time = std::chrono::high_resolution_clock::now();
            vector<vector<long long>> result_matrix = shortest_path(adjacency_list);
            auto stop_time = std::chrono::high_resolution_clock::now();

            bool timer = TIME_PROGRAM;
            if (timer) {
                auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_time-start_time);
                cout << "Test duration: " << duration.count() << " ns" << endl;
            }

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
            fin.close();
        } else {
            cout << "Could not find file named " << inFile << ", exiting." << endl;
        }

        return 0;
    } else if (argc > 2) {
        cout << "Usage: ./<program> [test_file] or ./<program>" << endl;
        return 0;
    }

    for (int i = 1; i <= tests_number; i++) {

        /* Open the file */
        string inFile = "in/test" + to_string(i) + ".in";
        ifstream fin(inFile);

        /* Read from file */
        if (fin.is_open()) {
            string outFile = "tester-out/test" + to_string(i) + ".out";
            /* Create the output file */
            ofstream fout(outFile);

            int N, E;
            fin >> N >> E;
            vector<vector<edge>> adjacency_list(N);

            for (int j = 1; j <= E; j++) {
                int startNode, endNode, cost;
                fin >> startNode >> endNode >> cost;
                adjacency_list[startNode-1].push_back(make_pair(endNode-1, cost));
            }

            /* Execute whichever algorithm and time it if the timer is enabled */
            auto start_time = std::chrono::high_resolution_clock::now();
            vector<vector<long long>> result_matrix = shortest_path(adjacency_list);
            auto stop_time = std::chrono::high_resolution_clock::now();

            bool timer = TIME_PROGRAM;
            if (timer) {
                auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_time-start_time);
                cout << "Test " << i << " duration: " << duration.count() << " ns" << endl;
            }


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

    return 0;
}
