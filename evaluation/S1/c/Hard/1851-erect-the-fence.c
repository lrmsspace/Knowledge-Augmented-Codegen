// Source: https://leetcode.com/problems/erect-the-fence/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array trees where trees[i] = [xi, yi] represents the location of a tree in the garden.
//
// Fence the entire garden using the minimum length of rope, as it is expensive. The garden is well-fenced only if all the trees are enclosed.
//
// Return the coordinates of trees that are exactly located on the fence perimeter. You may return the answer in any order.
//
// Example:
// Input: trees = [[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]
// Output: [[1,1],[2,0],[4,2],[3,3],[2,4]]
// Explanation: All the trees will be on the perimeter of the fence except the tree at [2, 2], which will be inside the fence.
//
// Constraints:
// 1 <= trees.length <= 3000
// 	trees[i].length == 2
// 	0 <= xi, yi <= 100
// 	All the given positions are unique.
//
// Helpful references (internal KB):
// - Convex Hull construction (geometry, array, enumeration)
//   • When to use: Use when you need to find the smallest convex polygon that encloses a given set of points in a plane. It is fundamental for various geometric algorithms and optimization problems.
//   • Idea: Convex hull construction identifies the subset of points that form the vertices of the smallest convex polygon containing all given points. Common algorithms achieve this in O(N log N) time complexity.
//   • Invariants: The sequence of points currently forming the hull maintains a convex property.; All points considered up to the current iteration are either part of the hull or lie within the polygon defined by the hull.
//   • Tips: Sort points by X-coordinate (and Y for ties) as a common preprocessing step.; Consider algorithms like Graham Scan or Monotone Chain for efficiency.
//   • Pitfalls: Floating point precision issues can lead to incorrect orientation calculations.; Incorrectly handling collinear points can result in non-minimal hulls or errors.
// - Solve RMQ (Range Minimum Query) by finding LCA (Lowest Common Ancestor) (array, tree, stack, simulation, monotonic-stack)
//   • When to use: This technique is used to answer Range Minimum Queries efficiently on a static array by transforming them into Lowest Common Ancestor queries on a Cartesian Tree.
//   • Idea: This approach solves Range Minimum Query problems by constructing a Cartesian Tree from the input array, where the root of any subtree is its minimum element. RMQ for a given range then reduces to finding the Lowest Common Ancestor of the range's endpoints in this tree, allowing O(N) construction and O(1) query time after O(N) preprocessing.
//   • Invariants: For any node `u` in the Cartesian Tree, `value(u)` is the minimum among all values in the subtree rooted at `u`.; For any node `u`, all nodes in its left subtree have indices smaller than `index(u)`, and all nodes in its right subtree have indices larger than `index(u)`.
//   • Tips: A Cartesian Tree is a binary tree where each node's value is less than its children's values, and an in-order traversal yields the original array.; Utilize a monotonic stack to construct the Cartesian Tree in linear O(N) time.
//   • Pitfalls: Correctly implementing the monotonic stack for Cartesian Tree construction can be challenging.; Edge cases, such as an empty stack or handling the last elements during tree building, must be managed carefully.
// - Convex hull trick and Li Chao tree (array, number, dp-1d)
//   • When to use: Use when the optimal solution for a subproblem depends only on solutions to smaller, contiguous subproblems. It's effective for optimizing sequential decision-making or finding optimal values in arrays.
//   • Idea: Dynamic Programming 1D solves problems by breaking them into overlapping subproblems and storing results to avoid recomputation. It typically achieves O(N) or O(N log N) time and O(N) or O(1) space complexity.
//   • Invariants: dp[i] correctly stores the optimal solution for the subproblem ending at index i.; All dp[j] for j < i have been computed and are correct.
//   • Tips: Clearly define the state: what does dp[i] represent for the subproblem?; Establish correct base cases for the smallest subproblems.
//   • Pitfalls: Incorrectly defining the state or recurrence relation.; Missing or incorrect base cases, leading to incorrect results.
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
int** outerTrees(int** trees, int treesSize, int* treesColSize, int* returnSize, int** returnColumnSizes) {
    // Implementation of the Convex Hull algorithm (Monotone Chain)
    if (treesSize <= 3) {
        // All points are on the hull
        int** result = (int**)malloc(treesSize * sizeof(int*));
        *returnColumnSizes = (int*)malloc(treesSize * sizeof(int));
        for (int i = 0; i < treesSize; i++) {
            result[i] = (int*)malloc(2 * sizeof(int));
            result[i][0] = trees[i][0];
            result[i][1] = trees[i][1];
            (*returnColumnSizes)[i] = 2;
        }
        *returnSize = treesSize;
        return result;
    }

    // Sort points lexicographically
    qsort(trees, treesSize, sizeof(int*), [](const void* a, const void* b) {
        int* p1 = *(int**)a;
        int* p2 = *(int**)b;
        if (p1[0] != p2[0]) return p1[0] - p2[0];
        return p1[1] - p2[1];
    });

    // Build lower hull
    int** hull = (int**)malloc(treesSize * 2 * sizeof(int*));
    int hullSize = 0;

    for (int i = 0; i < treesSize; i++) {
        while (hullSize >= 2) {
            int* p1 = hull[hullSize - 2];
            int* p2 = hull[hullSize - 1];
            int* p3 = trees[i];
            int cross = (p2[0] - p1[0]) * (p3[1] - p1[1]) - (p2[1] - p1[1]) * (p3[0] - p1[0]);
            if (cross < 0) {
                hullSize--;
            } else {
                break;
            }
        }
        hull[hullSize++] = trees[i];
    }

    // Build upper hull
    int lowerHullSize = hullSize;
    for (int i = treesSize - 1; i >= 0; i--) {
        while (hullSize > lowerHullSize) {
            int* p1 = hull[hullSize - 2];
            int* p2 = hull[hullSize - 1];
            int* p3 = trees[i];
            int cross = (p2[0] - p1[0]) * (p3[1] - p1[1]) - (p2[1] - p1[1]) * (p3[0] - p1[0]);
            if (cross < 0) {
                hullSize--;
            } else {
                break;
            }
        }
        hull[hullSize++] = trees[i];
    }
    // Remove duplicates
    int uniqueCount = 0;
    int** uniqueHull = (int**)malloc(hullSize * sizeof(int*));
    for (int i = 0; i < hullSize; i++) {
        int isDuplicate = 0;
        for (int j = 0; j < uniqueCount; j++) {
            if (hull[i][0] == uniqueHull[j][0] && hull[i][1] == uniqueHull[j][1]) {
                isDuplicate = 1;
                break;
            }
        }
        if (!isDuplicate) {
            uniqueHull[uniqueCount++] = hull[i];
        }
    }
    free(hull);
    *returnSize = uniqueCount;
    *returnColumnSizes = (int*)malloc(uniqueCount * sizeof(int));
    for (int i = 0; i < uniqueCount; i++) {
        (*returnColumnSizes)[i] = 2;
    }
    return uniqueHull;
}
