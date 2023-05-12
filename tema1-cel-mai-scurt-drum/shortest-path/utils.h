#ifndef UTILS_H
#define UTILS_H

#include <vector>
#define INF 0x7f7f7f7f7f7f

/*
 * edge.first  -> adjacent node
 * edge.second -> cost
 */
typedef std::pair<int, int> edge;

std::vector<std::vector<long long>> shortest_path(const std::vector<std::vector<edge>>& graph);

#endif //UTILS_H
