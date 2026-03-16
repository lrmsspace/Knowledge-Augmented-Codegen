// Source: https://leetcode.com/problems/longest-path-with-different-adjacent-characters/   |   Difficulty: Hard
//
// Problem Description:
// You are given a tree (i.e. a connected, undirected graph that has no cycles) rooted at node 0 consisting of n nodes numbered from 0 to n - 1. The tree is represented by a 0-indexed array parent of size n, where parent[i] is the parent of node i. Since node 0 is the root, parent[0] == -1.
//
// You are also given a string s of length n, where s[i] is the character assigned to node i.
//
// Return the length of the longest path in the tree such that no pair of adjacent nodes on the path have the same character assigned to them.
//
// Example:
// Input: parent = [-1,0,0,1,1,2], s = "abacbe"
// Output: 3
// Explanation: The longest path where each two adjacent nodes have different characters in the tree is the path: 0 -> 1 -> 3. The length of this path is 3, so 3 is returned.
// It can be proven that there is no longer path that satisfies the conditions.
//
// Constraints:
// n == parent.length == s.length
// 	1 <= n <= 105
// 	0 <= parent[i] <= n - 1 for all i >= 1
// 	parent[0] == -1
// 	parent represents a valid tree.
// 	s consists of only lowercase English letters.
//

int longestPath(int* parent, int parentSize, char* s) {
    if (parentSize <= 0 || !s) return 0;

    /* build adjacency list */
    int *head = (int*)calloc(parentSize, sizeof(int));
    int *next = (int*)malloc(parentSize * sizeof(int));
    if (!head || !next) {
        free(head); free(next); return 0;
    }
    memset(head, -1, parentSize * sizeof(int));
    for (int i = 1; i < parentSize; ++i) {
        next[i] = head[parent[i]];
        head[parent[i]] = i;
    }

    int maxPath = 1;

    /* post-order DFS using stack */
    int *stack = (int*)malloc(parentSize * sizeof(int));
    int *visited = (int*)calloc(parentSize, sizeof(int));
    int *longestChain = (int*)calloc(parentSize, sizeof(int));
    if (!stack || !visited || !longestChain) {
        free(head); free(next); free(stack); free(visited); free(longestChain);
        return 0;
    }

    stack[0] = 0;
    int sp = 1;

    while (sp > 0) {
        int node = stack[sp - 1];
        if (!visited[node]) {
            visited[node] = 1;
            for (int child = head[node]; child != -1; child = next[child]) {
                stack[sp++] = child;
            }
        } else {
            sp--;
            int firstMax = 0, secondMax = 0;
            for (int child = head[node]; child != -1; child = next[child]) {
                if (s[child] != s[node]) {
                    int chainLen = longestChain[child];
                    if (chainLen > firstMax) {
                        secondMax = firstMax;
                        firstMax = chainLen;
                    } else if (chainLen > secondMax) {
                        secondMax = chainLen;
                    }
                }
            }
            longestChain[node] = firstMax + 1;
            int pathLen = firstMax + secondMax + 1;
            if (pathLen > maxPath) {
                maxPath = pathLen;
            }
        }
    }

    free(head); free(next); free(stack); free(visited); free(longestChain);
    return maxPath;     
}
