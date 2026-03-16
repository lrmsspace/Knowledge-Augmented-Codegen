// Source: https://leetcode.com/problems/add-edges-to-make-degrees-of-all-nodes-even/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected graph consisting of n nodes numbered from 1 to n. You are given the integer n and a 2D array edges where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi. The graph can be disconnected.
//
// You can add at most two additional edges (possibly none) to this graph so that there are no repeated edges and no self-loops.
//
// Return true if it is possible to make the degree of each node in the graph even, otherwise return false.
//
// The degree of a node is the number of edges connected to it.
//
// Example:
// Input: n = 5, edges = [[1,2],[2,3],[3,4],[4,2],[1,4],[2,5]]
// Output: true
// Explanation: The above diagram shows a valid way of adding an edge.
// Every node in the resulting graph is connected to an even number of edges.
//
// Constraints:
// 3 <= n <= 105
// 	2 <= edges.length <= 105
// 	edges[i].length == 2
// 	1 <= ai, bi <= n
// 	ai != bi
// 	There are no repeated edges.
//

bool isPossible(int n, int** edges, int edgesSize, int* edgesColSize) {
    int *degree = (int*)calloc(n + 1, sizeof(int));
    if (!degree) return false;

    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0];
        int v = edges[i][1];
        degree[u]++;
        degree[v]++;
    }

    int oddCount = 0;
    int oddNodes[4]; /* store up to 4 odd degree nodes */
    for (int i = 1; i <= n; ++i) {
        if (degree[i] % 2 != 0) {
            if (oddCount < 4) {
                oddNodes[oddCount] = i;
            }
            oddCount++;
        }
    }
    free(degree);

    if (oddCount == 0) {
        return true; /* all even */
    } else if (oddCount == 2) {
        /* check if we can connect the two odd nodes directly or via an intermediate node */
        int a = oddNodes[0];
        int b = oddNodes[1];
        bool canConnectDirectly = true;
        for (int i = 0; i < edgesSize; ++i) {
            if ((edges[i][0] == a && edges[i][1] == b) || (edges[i][0] == b && edges[i][1] == a)) {
                canConnectDirectly = false;
                break;
            }
        }
        if (canConnectDirectly) {
            return true;
        }
        /* check for an intermediate node */
        for (int i = 1; i <= n; ++i) {
            if (i != a && i != b) {
                bool canConnectA = true, canConnectB = true;
                for (int j = 0; j < edgesSize; ++j) {
                    if ((edges[j][0] == a && edges[j][1] == i) || (edges[j][0] == i && edges[j][1] == a)) {
                        canConnectA = false;
                    }
                    if ((edges[j][0] == b && edges[j][1] == i) || (edges[j][0] == i && edges[j][1] == b)) {
                        canConnectB = false;
                    }
                }
                if (canConnectA && canConnectB) {       
                    return true;
                }
            }
        }
        return false;
    } else if (oddCount == 4) {
        /* check if we can pair the odd nodes */
        int a = oddNodes[0], b = oddNodes[1], c = oddNodes[2], d = oddNodes[3];
        bool ab = true, cd = true, ac = true, bd = true, ad = true, bc = true;

        for (int i = 0; i < edgesSize; ++i) {
            int u = edges[i][0], v = edges[i][1];
            if ((u == a && v == b) || (u == b && v == a)) ab = false;
            if ((u == c && v == d) || (u == d && v == c)) cd = false;
            if ((u == a && v == c) || (u == c && v == a)) ac = false;
            if ((u == b && v == d) || (u == d && v == b)) bd = false;
            if ((u == a && v == d) || (u == d && v == a)) ad = false;
            if ((u == b && v == c) || (u == c && v == b)) bc = false;
        }

        if ((ab && cd) || (ac && bd) || (ad && bc)) {
            return true;
        }
        return false;
    } else {
        return false; /* cannot fix odd degree count other than 0, 2, or 4 */
    }
}

