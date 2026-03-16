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
// - Range Minimum Query (array, ds, union-find)
//   • When to use: Use when range minimum queries are needed on an array where elements can be dynamically removed or merged, and Union-Find is employed to manage the active state or connectivity of indices.
//   • Idea: Union-Find can be adapted to assist in range minimum queries, particularly when elements are dynamically removed or merged. It helps maintain connectivity of active elements or segments, allowing efficient traversal to find the minimum among available items, often with near-constant amortized time per Union-Find operation.
//   • Invariants: The `find` operation correctly returns the canonical representative for any element `i`.; Each set in the Union-Find structure maintains a property (e.g., minimum value, next available index) relevant to its merged elements.
//   • Tips: Utilize path compression and union by rank/size for optimal Union-Find performance.; Store relevant properties (e.g., minimum value, next available index) within the representative of each set.
//   • Pitfalls: Union-Find alone does not directly provide range minimums; it typically manages connectivity or availability.; Naive iteration through active elements found by Union-Find can be too slow for large ranges.
// - Disjoint Set Union (ds, linked-list, union-find, dfs)
//   • When to use: Use when you need to maintain a collection of disjoint sets and perform union operations to merge sets or find the representative of an element's set efficiently. It's suitable for problems involving dynamic connectivity or grouping elements.
//   • Idea: Disjoint Set Union (DSU) is a data structure that stores a collection of disjoint sets and supports two primary operations: finding the representative of an element's set and merging two sets. It achieves nearly constant time complexity for these operations with path compression and union by rank/size optimizations.
//   • Invariants: Every element `i` belongs to exactly one set, represented by `find(i)`.; If `parent[i] == i`, then `i` is the representative (root) of its set.
//   • Tips: Implement path compression in `find` for optimal performance.; Use union by size or rank to maintain balanced trees.
//   • Pitfalls: Omitting path compression or union by rank/size can degrade performance to O(N).; Failing to correctly update auxiliary data stored at representatives during a union operation.
// - Disjoint Set Union (ds, tree, array, union-find)
//   • When to use: Use when you need to maintain a collection of disjoint sets and efficiently perform union operations to merge sets or find the representative of an element's set.
//   • Idea: Disjoint Set Union (DSU) is a data structure that stores a collection of disjoint sets and supports two primary operations: finding the representative of an element's set and merging two sets. With path compression and union by rank/size, these operations achieve nearly constant amortized time complexity, O(alpha(N)).
//   • Invariants: Each element `v` is either a root (parent[v] == v) or has a parent pointer to another element in its set.; The `find_set` operation, after path compression, ensures that all nodes on the path from `v` to its root directly point to the root.
//   • Tips: Implement path compression in `find_set` for optimal performance.; Use union by rank or union by size to keep trees flat and balanced.
//   • Pitfalls: Forgetting path compression or union by rank/size leads to O(N) worst-case operations.; Incorrectly merging sets by only updating one root without considering the other's rank/size.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int findLatestStep(int* arr, int arrSize, int m) {
    int n = arrSize;
    int *parent = (int *)malloc((n + 1) * sizeof(int));
    int *size = (int *)malloc((n + 1) * sizeof(int));
    int *count = (int *)calloc(n + 1, sizeof(int)); // Count of groups of size i
    int latestStep = -1;

    for (int i = 0; i <= n; i++) {
        parent[i] = i;
        size[i] = 1;
    }

    for (int step = 0; step < n; step++) {
        int pos = arr[step];
        parent[pos] = pos; // Mark this position as active
        count[1]++; // New group of size 1

        // Check left and right neighbors
        if (pos > 1 && parent[pos - 1] != pos - 1) {
            // Merge with left neighbor
            int leftRoot = find_set(parent, pos - 1);
            count[size[leftRoot]]--; // Decrease count of old group size
            union_sets(parent, size, pos, leftRoot);
            count[size[find_set(parent, pos)]]++; // Increase count of new group size
        }
        if (pos < n && parent[pos + 1] != pos + 1) {
            // Merge with right neighbor
            int rightRoot = find_set(parent, pos + 1);
            count[size[rightRoot]]--; // Decrease count of old group size
            union_sets(parent, size, pos, rightRoot);
            count[size[find_set(parent, pos)]]++; // Increase count of new group size
        }

        if (count[m] > 0) {
            latestStep = step + 1; // Update latest step (1-indexed)
        }
    }

    free(parent);
    free(size);
    free(count);

    return latestStep;      
}
