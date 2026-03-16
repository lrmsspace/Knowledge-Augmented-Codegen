// Source: https://leetcode.com/problems/valid-arrangement-of-pairs/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed 2D integer array pairs where pairs[i] = [starti, endi]. An arrangement of pairs is valid if for every index i where 1 <= i < pairs.length, we have endi-1 == starti.
//
// Return any valid arrangement of pairs.
//
// Note: The inputs will be generated such that there exists a valid arrangement of pairs.
//
// Example:
// Input: pairs = [[5,1],[4,5],[11,9],[9,4]]
// Output: [[11,9],[9,4],[4,5],[5,1]]
// Explanation:
// This is a valid arrangement since endi-1 always equals starti.
// end0 = 9 == 9 = start1 
// end1 = 4 == 4 = start2
// end2 = 5 == 5 = start3
//
// Constraints:
// 1 <= pairs.length <= 105
// 	pairs[i].length == 2
// 	0 <= starti, endi <= 109
// 	starti != endi
// 	No two pairs are exactly the same.
// 	There exists a valid arrangement of pairs.
//
// Helpful references (internal KB):
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when tasks with associated processing times and costs need to be sequenced on a single machine to minimize a total objective function, typically involving weighted completion times or penalties. The optimal sequence is found by a greedy sort.
//   • Idea: This method finds an optimal schedule for jobs on a single machine by sorting them according to a greedy criterion derived from an exchange argument. It achieves an optimal solution with O(N log N) time complexity, dominated by the sorting step.
//   • Invariants: The relative order of any two jobs i and j in the sorted sequence is consistent with the greedy comparison rule.; Any prefix of the sorted schedule represents an optimal ordering for the jobs within that prefix.
//   • Tips: Clearly define the objective function to be minimized.; Formulate the greedy sorting rule using an exchange argument for any two adjacent jobs.
//   • Pitfalls: Incorrectly deriving the greedy comparison criterion.; Applying this method to problems with multiple machines or complex precedence constraints without adaptation.
// - Strongly connected components and the condensation graph (graph, array, dfs, enumeration)
//   • When to use: Use this when systematically exploring all possible configurations, paths, or subsets within a graph or array. It's ideal for finding every solution or verifying properties across all potential states.
//   • Idea: Depth-First Search (DFS) is a graph traversal algorithm that explores as far as possible along each branch before backtracking. When combined with enumeration, it systematically generates all possible combinations or paths, typically with exponential time complexity O(V+E) for traversal or O(N!) / O(2^N) for enumeration.
//   • Invariants: The current path/subset being built is valid up to the current depth.; All previously explored branches from the current node have been fully processed.
//   • Tips: Define clear base cases for recursion termination.; Manage state changes carefully when entering and exiting recursive calls.
//   • Pitfalls: Infinite recursion due to missing or incorrect base cases.; Redundant computations if states are not properly managed or memoized.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** validArrangement(int** pairs, int pairsSize, int* pairsColSize, int* returnSize, int** returnColumnSizes) {
    (void)pairsColSize;

    int n = pairsSize;
    int i;

    {
        int m = n * 2;
        int* head = (int*)malloc((size_t)m * sizeof(int));
        int* to = (int*)malloc((size_t)m * sizeof(int));
        int* next = (int*)malloc((size_t)m * sizeof(int));
        int* degree = (int*)malloc((size_t)m * sizeof(int));
        int* stack = (int*)malloc((size_t)m * sizeof(int));

        if (head == NULL || to == NULL || next == NULL || degree == NULL || stack == NULL) {
            free(head);
            free(to);
            free(next);
            free(degree);
            free(stack);
            return NULL;
        }

        for (i = 0; i < m; ++i) {
            head[i] = -1;
            degree[i] = 0;
        }

        for (i = 0; i < n; ++i) {
            int a = pairs[i][0];
            int b = pairs[i][1];

            to[2 * i] = b;
            next[2 * i] = head[a];
            head[a] = 2 * i;
            ++degree[a];

            to[2 * i + 1] = a;
            next[2 * i + 1] = head[b];
            head[b] = 2 * i + 1;
            ++degree[b];
        }

        {
            int sp = 0;
            for (i = 0; i < m; ++i) {
                if ((degree[i] & 1) != 0) {
                    stack[sp++] = i;
                }
            }

            while (sp > 0) {
                int u = stack[--sp];
                int e;

                while (head[u] != -1) {
                    e = head[u];
                    head[u] = next[e];
                    --degree[u];

                    if ((degree[to[e]] & 1) != 0) {
                        stack[sp++] = to[e];
                    }
                    --degree[to[e]];
                }
            }
        }

        {
            int** ans = (int**)malloc((size_t)n * sizeof(int*));
            int* colSizes = (int*)malloc((size_t)n * sizeof(int));

            if (ans == NULL || colSizes == NULL) {
                free(head);
                free(to);
                free(next);
                free(degree);
                free(stack);
                free(ans);
                free(colSizes);
                return NULL;
            }
            for (i = 0; i < n; ++i) {
                ans[i] = (int*)malloc(2 * sizeof(int));
                if (ans[i] == NULL) {
                    free(head);
                    free(to);
                    free(next);
                    free(degree);
                    free(stack);
                    for (int j = 0; j < i; ++j) {
                        free(ans[j]);
                    }
                    free(ans);
                    free(colSizes);
                    return NULL;
                }
                colSizes[i] = 2;
            }
            *returnSize = n;
            *returnColumnSizes = colSizes;
            return ans;
        }
    }
}