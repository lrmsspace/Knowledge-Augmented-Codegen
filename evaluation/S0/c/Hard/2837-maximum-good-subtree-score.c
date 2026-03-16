// Source: https://leetcode.com/problems/maximum-good-subtree-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected tree rooted at node 0 with n nodes numbered from 0 to n - 1. Each node i has an integer value vals[i], and its parent is given by par[i].
//
// A subset of nodes within the subtree of a node is called good if every digit from 0 to 9 appears at most once in the decimal representation of the values of the selected nodes.
//
// The score of a good subset is the sum of the values of its nodes.
//
// Define an array maxScore of length n, where maxScore[u] represents the maximum possible sum of values of a good subset of nodes that belong to the subtree rooted at node u, including u itself and all its descendants.
//
// Return the sum of all values in maxScore.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: vals = [2,3], par = [-1,0]
//
// Output: 8
//
// Explanation:
//
//
//
//
// 	The subtree rooted at node 0 includes nodes {0, 1}. The subset {2, 3} is good as the digits 2 and 3 appear only once. The score of this subset is 2 + 3 = 5.
// 	The subtree rooted at node 1 includes only node {1}. The subset {3} is good. The score of this subset is 3.
// 	The maxScore array is [5, 3], and the sum of all values in maxScore is 5 + 3 = 8. Thus, the answer is 8.
//
// Constraints:
// 1 <= n == vals.length <= 500
// 	1 <= vals[i] <= 109
// 	par.length == n
// 	par[0] == -1
// 	0 <= par[i] < n for i in [1, n - 1]
// 	The input is generated such that the parent array par represents a valid tree.
//

int goodSubtreeSum(int* vals, int valsSize, int* par, int parSize) {
    const int MOD = 1000000007;
    int n = valsSize;
    int *childrenCount = (int*)calloc(n, sizeof(int));
    int **children = (int**)calloc(n, sizeof(int*));
    for (int i = 0; i < n; ++i) {
        children[i] = (int*)calloc(n, sizeof(int));
    }
    for (int i = 1; i < n; ++i) {
        int p = par[i];
        children[p][childrenCount[p]++] = i;
    }

    int *maxScore = (int*)calloc(n, sizeof(int));

    for (int u = n - 1; u >= 0; --u) {
        int valMask = 0;
        int valSum = 0;
        int stack[500];
        int stackSize = 0;
        stack[stackSize++] = u;

        while (stackSize > 0) {
            int node = stack[--stackSize];
            int nodeVal = vals[node];
            int nodeMask = 0;
            while (nodeVal > 0) {
                int digit = nodeVal % 10;
                nodeMask |= (1 << digit);
                nodeVal /= 10;
            }

            if ((valMask & nodeMask) == 0) {
                valMask |= nodeMask;
                valSum += vals[node];
                for (int i = 0; i < childrenCount[node]; ++i) {
                    stack[stackSize++] = children[node][i];
                }
            }
        }
        maxScore[u] = valSum % MOD;
    }

    long long totalSum = 0;
    for (int i = 0; i < n; ++i) {
        totalSum = (totalSum + maxScore[i]) % MOD;
    }

    for (int i = 0; i < n; ++i) {
        free(children[i]);
    }
    free(children);
    free(childrenCount);
    free(maxScore);

    return (int)totalSum;       
}
