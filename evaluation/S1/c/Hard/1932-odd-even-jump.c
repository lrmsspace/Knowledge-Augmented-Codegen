// Source: https://leetcode.com/problems/odd-even-jump/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array arr. From some starting index, you can make a series of jumps. The (1st, 3rd, 5th, ...) jumps in the series are called odd-numbered jumps, and the (2nd, 4th, 6th, ...) jumps in the series are called even-numbered jumps. Note that the jumps are numbered, not the indices.
//
// You may jump forward from index i to index j (with i < j) in the following way:
//
//
// 	During odd-numbered jumps (i.e., jumps 1, 3, 5, ...), you jump to the index j such that arr[i] <= arr[j] and arr[j] is the smallest possible value. If there are multiple such indices j, you can only jump to the smallest such index j.
// 	During even-numbered jumps (i.e., jumps 2, 4, 6, ...), you jump to the index j such that arr[i] >= arr[j] and arr[j] is the largest possible value. If there are multiple such indices j, you can only jump to the smallest such index j.
// 	It may be the case that for some index i, there are no legal jumps.
//
//
// A starting index is good if, starting from that index, you can reach the end of the array (index arr.length - 1) by jumping some number of times (possibly 0 or more than once).
//
// Return the number of good starting indices.
//
// Example:
// Input: arr = [10,13,12,14,15]
// Output: 2
// Explanation: 
// From starting index i = 0, we can make our 1st jump to i = 2 (since arr[2] is the smallest among arr[1], arr[2], arr[3], arr[4] that is greater or equal to arr[0]), then we cannot jump any more.
// From starting index i = 1 and i = 2, we can make our 1st jump to i = 3, then we cannot jump any more.
// From starting index i = 3, we can make our 1st jump to i = 4, so we have reached the end.
// From starting index i = 4, we have reached the end already.
// In total, there are 2 different starting indices i = 3 and i = 4, where we can reach the end with some number of
// jumps.
//
// Constraints:
// 1 <= arr.length <= 2 * 104
// 	0 <= arr[i] < 105
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int oddEvenJumps(int* arr, int arrSize) {
    int nextHigher[arrSize];
    int nextLower[arrSize];
    int stack[arrSize];
    int stackSize;

    // Helper function to compute next indices
    void computeNext(int* indices, int* result) {
        stackSize = 0;
        for (int i = 0; i < arrSize; i++) {
            while (stackSize > 0 && indices[stack[stackSize - 1]] < indices[i]) {
                result[stack[--stackSize]] = i;
            }
            stack[stackSize++] = i;
        }
        while (stackSize > 0) {
            result[stack[--stackSize]] = -1;
        }
    }

    // Create sorted indices for next higher and next lower jumps
    int sortedIndices[arrSize];
    for (int i = 0; i < arrSize; i++) {
        sortedIndices[i] = i;
    }

    // Sort for next higher jumps
    qsort(sortedIndices, arrSize, sizeof(int), (int (*)(const void*, const void*)) (int (*)(int, int)) [](const int* a, const int* b) {
        if (arr[*a] == arr[*b]) return *a - *b;
        return arr[*a] - arr[*b];
    });
    computeNext(sortedIndices, nextHigher);

    // Sort for next lower jumps
    qsort(sortedIndices, arrSize, sizeof(int), (int (*)(const void*, const void*)) (int (*)(int, int)) [](const int* a, const int* b) {
        if (arr[*a] == arr[*b]) return *a - *b;
        return arr[*b] - arr[*a];
    });
    computeNext(sortedIndices, nextLower);

    // DP arrays to track reachability
    int oddReachable[arrSize];
    int evenReachable[arrSize];
    oddReachable[arrSize - 1] = 1;
    evenReachable[arrSize - 1] = 1;

    for (int i = arrSize - 2; i >= 0; i--) {
        oddReachable[i] = nextHigher[i] != -1 ? evenReachable[nextHigher[i]] : 0;
        evenReachable[i] = nextLower[i] != -1 ? oddReachable[nextLower[i]] : 0;
    }
    int count = 0;
    for (int i = 0; i < arrSize; i++) {
        if (oddReachable[i]) {
            count++;
        }
    }
    return count;
}
