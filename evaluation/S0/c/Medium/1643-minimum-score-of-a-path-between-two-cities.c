// Source: https://leetcode.com/problems/minimum-score-of-a-path-between-two-cities/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer n representing n cities numbered from 1 to n. You are also given a 2D array roads where roads[i] = [ai, bi, distancei] indicates that there is a bidirectional road between cities ai and bi with a distance equal to distancei. The cities graph is not necessarily connected.
//
// The score of a path between two cities is defined as the minimum distance of a road in this path.
//
// Return the minimum possible score of a path between cities 1 and n.
//
// Note:
//
//
// 	A path is a sequence of roads between two cities.
// 	It is allowed for a path to contain the same road multiple times, and you can visit cities 1 and n multiple times along the path.
// 	The test cases are generated such that there is at least one path between 1 and n.
//
// Example:
// Input: n = 4, roads = [[1,2,9],[2,3,6],[2,4,5],[1,4,7]]
// Output: 5
// Explanation: The path from city 1 to 4 with the minimum score is: 1 -> 2 -> 4. The score of this path is min(9,5) = 5.
// It can be shown that no other path has less score.
//
// Constraints:
// 2 <= n <= 105
// 	1 <= roads.length <= 105
// 	roads[i].length == 3
// 	1 <= ai, bi <= n
// 	ai != bi
// 	1 <= distancei <= 104
// 	There are no repeated edges.
// 	There is at least one path between 1 and n.
//

int minScore(int n, int** roads, int roadsSize, int* roadsColSize) {
    // Adjacency list representation of the graph
    typedef struct Edge {
        int to;
        int distance;
        struct Edge* next;
    } Edge;

    Edge** graph = (Edge**)calloc(n + 1, sizeof(Edge*));
    for (int i = 0; i < roadsSize; i++) {
        int a = roads[i][0];
        int b = roads[i][1];
        int distance = roads[i][2];

        Edge* edgeA = (Edge*)malloc(sizeof(Edge));
        edgeA->to = b;
        edgeA->distance = distance;
        edgeA->next = graph[a];
        graph[a] = edgeA;

        Edge* edgeB = (Edge*)malloc(sizeof(Edge));
        edgeB->to = a;
        edgeB->distance = distance;
        edgeB->next = graph[b];
        graph[b] = edgeB;
    }

    // BFS to find the minimum score path from city 1 to city n
    int* visited = (int*)calloc(n + 1, sizeof(int));
    int queue[n + 1];
    int front = 0, back = 0;
    queue[back++] = 1;
    visited[1] = 1;
    int minScore = INT_MAX;

    while (front < back) {
        int city = queue[front++];
        for (Edge* edge = graph[city]; edge != NULL; edge = edge->next) {
            if (edge->distance < minScore) {
                minScore = edge->distance;
            }
            if (!visited[edge->to]) {
                visited[edge->to] = 1;
                queue[back++] = edge->to;
            }
        }
    }

    // Free allocated memory
    for (int i = 1; i <= n; i++) {
        Edge* edge = graph[i];
        while (edge) {
            Edge* temp = edge;
            edge = edge->next;
            free(temp);
        }
    }
    free(graph);
    free(visited);

    return minScore;        
}
