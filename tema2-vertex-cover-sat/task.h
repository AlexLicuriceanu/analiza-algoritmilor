#ifndef TASK_H_
#define TASK_H_

#include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <array>
#include <utility>
#include <string>


class Task {
 public:
   
    /*
     * Stores the files paths as class attributes.
     *
     * @param in_filename:         the file containing the problem input
     * @param oracle_in_filename:  the file containing the oracle input
     * @param oracle_out_filename: the file containing the oracle output
     * @param out_filename:        the file containing the problem output
     */

    /*
     * Asks the oracle for an answer to the formulated question.
     */
    void ask_oracle() {
        std::string solver_path = "sat_oracle.py";
        std::string command = "python3 " + solver_path + " sat.cnf sat.sol";
        std::array<char, 512> buffer{};
        std::string output;

        auto pipe = popen(command.c_str(), "r");

        while (!feof(pipe)) {
            if (fgets(buffer.data(), 512, pipe) != nullptr) {
                output += buffer.data();
            }
        }

        auto rc = pclose(pipe);

        if (rc != EXIT_SUCCESS) {
            std::cerr << "Error encountered while running oracle" << std::endl;
            std::cerr << output << std::endl;
            exit(-1);
        }
    }
};

#endif  // TASK_H_