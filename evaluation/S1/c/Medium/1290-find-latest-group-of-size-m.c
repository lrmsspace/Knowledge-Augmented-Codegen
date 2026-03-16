// Source: https://leetcode.com/problems/find-latest-group-of-size-m/   |   Difficulty: Medium
//
// Problem Description:
// Given an array arr that represents a permutation of numbers from 1 to n.
//
// You have a binary string of size n that initially has all its bits set to zero. At each step i (assuming both the binary string and arr are 1-indexed) from 1 to n, the bit at position arr[i] is set to 1.
//
// You are also given an integer m. Find the latest step at which there exists a group of ones of length m. A group of ones is a contiguous substring of 1's such that it cannot be extended in either direction.
//
// Return the latest step at which there exists a group of ones of length exactly m. If no such group exists, return -1.
//
// Example:
// Input: arr = [3,5,1,2,4], m = 1
// Output: 4
// Explanation: 
// Step 1: "00100", groups: ["1"]
// Step 2: "00101", groups: ["1", "1"]
// Step 3: "10101", groups: ["1", "1", "1"]
// Step 4: "11101", groups: ["111", "1"]
// Step 5: "11111", groups: ["11111"]
// The latest step at which there exists a group of size 1 is step 4.
//
// Constraints:
// n == arr.length
// 	1 <= m <= n <= 105
// 	1 <= arr[i] <= n
// 	All integers in arr are distinct.
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d, counting, segment-tree)
//   • When to use: Use when seeking the longest possible sequence of elements from a given array such that each element is greater than the preceding one, preserving their original relative order.
//   • Idea: The Longest Increasing Subsequence (LIS) problem identifies the longest possible subsequence where elements are in strictly increasing order, preserving their original relative positions. It can be solved efficiently in O(N log N) time using dynamic programming with binary search or a segment tree.
//   • Invariants: The `tails` array elements are always strictly increasing.; For any index `k`, `tails[k]` holds the smallest possible ending element of an increasing subsequence of length `k+1`.
//   • Tips: Use a `tails` array to store the smallest ending element for LIS of each length.; Employ binary search on the `tails` array to update or extend subsequences.
//   • Pitfalls: Confusing subsequence (relative order) with contiguous subarray.; Incorrectly implementing strict vs. non-strict increasing conditions.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, matrix, matrix-exp, counting)
//   • When to use: Use when needing to count the number of paths of a specific length between all pairs of vertices in a graph, or to find reachability in a fixed number of steps.
//   • Idea: This algorithm leverages matrix exponentiation to find the number of paths of a fixed length `k` between all pairs of vertices in a graph. Each matrix multiplication step extends path lengths by one, resulting in an O(N^3 log K) time complexity for an N-vertex graph.
//   • Invariants: After `m` matrix multiplications, `C_m[i][j]` stores the number of paths of length `m` from `i` to `j`.; The initial adjacency matrix `G` remains constant throughout the exponentiation process.
//   • Tips: Represent the graph as an adjacency matrix where `G[i][j]` is the number of direct edges.; Matrix multiplication `C_k * G` yields `C_{k+1}` for path counts.
//   • Pitfalls: Standard matrix multiplication is O(N^3), leading to O(N^3 log K) overall time complexity.; Memory usage is O(N^2) for storing matrices, which can be prohibitive for very large graphs.
// - Range Minimum Query (array, ds, union-find)
//   • When to use: Use when range minimum queries are needed on an array where elements can be dynamically removed or merged, and Union-Find is employed to manage the active state or connectivity of indices.
//   • Idea: Union-Find can be adapted to assist in range minimum queries, particularly when elements are dynamically removed or merged. It helps maintain connectivity of active elements or segments, allowing efficient traversal to find the minimum among available items, often with near-constant amortized time per Union-Find operation.
//   • Invariants: The `find` operation correctly returns the canonical representative for any element `i`.; Each set in the Union-Find structure maintains a property (e.g., minimum value, next available index) relevant to its merged elements.
//   • Tips: Utilize path compression and union by rank/size for optimal Union-Find performance.; Store relevant properties (e.g., minimum value, next available index) within the representative of each set.
//   • Pitfalls: Union-Find alone does not directly provide range minimums; it typically manages connectivity or availability.; Naive iteration through active elements found by Union-Find can be too slow for large ranges.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int findLatestStep(int* arr, int arrSize, int m) {
    int n = arrSize;
    if (m == n) return n;

    int *lengths = (int *)calloc(n + 2, sizeof(int));
    int *count = (int *)calloc(n + 1, sizeof(int));
    int result = -1;

    for (int step = 0; step < n; step++) {
        int pos = arr[step];
        int left = lengths[pos - 1];
        int right = lengths[pos + 1];
        int newLength = left + right + 1;

        lengths[pos - left] = newLength;
        lengths[pos + right] = newLength;

        count[left]--;
        count[right]--;
        count[newLength]++;

        if (count[m] > 0) {
            result = step + 1;
        }
    }

    free(lengths);
    free(count);
    return result;      
}
