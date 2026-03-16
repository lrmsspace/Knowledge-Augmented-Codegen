// Source: https://leetcode.com/problems/alternating-groups-iii/   |   Difficulty: Hard
//
// Problem Description:
// There are some red and blue tiles arranged circularly. You are given an array of integers colors and a 2D integers array queries.
//
// The color of tile i is represented by colors[i]:
//
//
//  colors[i] == 0 means that tile i is red.
//  colors[i] == 1 means that tile i is blue.
//
//
// An alternating group is a contiguous subset of tiles in the circle with alternating colors (each tile in the group except the first and last one has a different color from its adjacent tiles in the group).
//
// You have to process queries of two types:
//
//
//  queries[i] = [1, sizei], determine the count of alternating groups with size sizei.
//  queries[i] = [2, indexi, colori], change colors[indexi] to colori.
//
//
// Return an array answer containing the results of the queries of the first type in order.
//
// Note that since colors represents a circle, the first and the last tiles are considered to be next to each other.
//
// Example:
// Input: colors = [0,1,1,0,1], queries = [[2,1,0],[1,4]]
//
// Output: [2]
//
// Explanation:
//
//
//
// First query:
//
// Change colors[1] to 0.
//
//
//
// Second query:
//
// Count of the alternating groups with size 4:
//
// Constraints:
// 4 <= colors.length <= 5 * 104
//  0 <= colors[i] <= 1
//  1 <= queries.length <= 5 * 104
//  queries[i][0] == 1 or queries[i][0] == 2
//  For all i that:
//  
//   queries[i][0] == 1: queries[i].length == 2, 3 <= queries[i][1] <= colors.length - 1
//   queries[i][0] == 2: queries[i].length == 3, 0 <= queries[i][1] <= colors.length - 1, 0 <= queries[i][2] <= 1
//
// Helpful references (internal KB):
// - Sqrt Tree (array, tree, divide-and-conquer, recursion, prefix-sum)
//   • When to use: When performing associative range queries on an array, especially when O(1) query time is critical and O(N log log N) preprocessing is acceptable.
//   • Idea: The Sqrt Tree is a data structure that answers associative range queries on an array in O(1) time after O(N log log N) preprocessing. It achieves this by recursively applying sqrt decomposition, precomputing block-wise prefix/suffix operations and inter-block results.
//   • Invariants: The `prefixOp` array for any block `k` stores the associative sum from the block's start to each element within it.; The `suffixOp` array for any block `k` stores the associative sum from each element within it to the block's end.
//   • Tips: Ensure the operation is strictly associative for correctness.; Carefully handle block boundaries and partial blocks during query processing.
//   • Pitfalls: Using non-associative operations will yield incorrect results.; High memory usage for the 'between' array if not optimized or if N is very large.
// - Fenwick Tree (array, bit-fenwick, difference-array)
//   • When to use: Use when an array requires frequent point updates and efficient retrieval of prefix sums or range sums. It offers logarithmic time complexity for both operations.
//   • Idea: A Fenwick Tree, or Binary Indexed Tree (BIT), is a data structure that efficiently supports point updates and prefix sum queries on an array in O(log N) time.
//   • Invariants: Each `bit[i]` stores the sum of a contiguous range of elements from the original array.; The range length represented by `bit[i]` is determined by `i & -i` (the least significant bit).
//   • Tips: Use 1-based indexing for simpler bitwise operations (`i & -i`).; Initialize with an existing array in O(N) time using a linear construction method.
//   • Pitfalls: Directly finding range minimum/maximum is not efficient or generally supported.; Operations must be associative and preferably invertible for general range queries.
// - Treap (Cartesian tree) (tree, array, divide-and-conquer, recursion)
//   • When to use: Use when a dynamic data structure is needed to support efficient array-like operations (insert, delete, range queries/updates) on an ordered sequence, especially with frequent modifications at arbitrary positions.
//   • Idea: A Treap is a randomized binary search tree that maintains both BST properties on keys and heap properties on randomly assigned priorities. It supports various dynamic array operations and range queries/updates in expected O(log N) time.
//   • Invariants: For any node, its key is greater than all keys in its left subtree and less than all keys in its right subtree.; For any node, its priority is greater than or equal to the priorities of its children.
//   • Tips: Use random priorities to ensure probabilistic balance, avoiding worst-case O(N) operations.; Implement `split` and `merge` as fundamental building blocks for all other operations.
//   • Pitfalls: Forgetting to push lazy tags before accessing children or performing splits/merges.; Incorrectly updating `cnt` or aggregate fields after tree modifications.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public List<Integer> numberOfAlternatingGroups(int[] colors, int[][] queries) {
        int n = colors.length;
        TreeMap<Integer, Integer> groupCount = new TreeMap<>();
        List<Integer> result = new ArrayList<>();

        // Helper function to add group size count
        Runnable addGroup = (size) -> {
            groupCount.put(size, groupCount.getOrDefault(size, 0) + 1);
        };

        // Helper function to remove group size count
        Runnable removeGroup = (size) -> {
            groupCount.put(size, groupCount.get(size) - 1);
            if (groupCount.get(size) == 0) {
                groupCount.remove(size);
            }
        };

        // Initial grouping
        for (int i = 0; i < n; ) {
            int j = i;
            while (j < n && colors[j] == colors[i]) {
                j++;
            }
            int groupSize = j - i;
            addGroup.run(groupSize);
            i = j;
        }

        // Handle circular case
        if (colors[0] == colors[n - 1]) {
            int firstGroupSize = 0;
            int lastGroupSize = 0;

            for (int i = 0; i < n && colors[i] == colors[0]; i++) {
                firstGroupSize++;
            }
            for (int i = n - 1; i >= 0 && colors[i] == colors[0]; i--) {
                lastGroupSize++;
            }

            removeGroup.run(firstGroupSize);
            removeGroup.run(lastGroupSize);
            addGroup.run(firstGroupSize + lastGroupSize);
        }

        // Process queries
        for (int[] query : queries) {
            if (query[0] == 1) {
                int size = query[1];
                result.add(groupCount.getOrDefault(size, 0));
            } else {
                int index = query[1];
                int newColor = query[2];
                if (colors[index] != newColor) {
                    // Update groups
                    int leftIndex = (index - 1 + n) % n;
                    int rightIndex = (index + 1) % n;

                    int leftColor = colors[leftIndex];
                    int rightColor = colors[rightIndex];
                    int currentColor = colors[index];

                    // Remove current groups
                    int leftGroupSize = 1;
                    int rightGroupSize = 1;
                    int i = leftIndex;
                    while (i != index && colors[i] == currentColor) {
                        leftGroupSize++;
                        i = (i - 1 + n) % n;
                    }
                    i = rightIndex;
                    while (i != index && colors[i] == currentColor) {
                        rightGroupSize++;
                        i = (i + 1) % n;
                    }
                    removeGroup.run(leftGroupSize);
                    removeGroup.run(rightGroupSize);
                    addGroup.run(leftGroupSize + rightGroupSize - 1);
                    // Add new groups
                    if (newColor == leftColor && newColor == rightColor) {
                        removeGroup.run(leftGroupSize + rightGroupSize - 1);
                        addGroup.run(leftGroupSize + rightGroupSize + 1);
                    } else if (newColor == leftColor) {
                        removeGroup.run(leftGroupSize);
                        addGroup.run(leftGroupSize + 1);
                    } else if (newColor == rightColor) {
                        removeGroup.run(rightGroupSize);
                        addGroup.run(rightGroupSize + 1);
                    } else {
                        addGroup.run(1);
                    }
                    colors[index] = newColor;
                }
            }
        }
        return result;
    }
}
