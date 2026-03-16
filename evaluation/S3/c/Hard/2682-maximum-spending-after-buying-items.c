// Source: https://leetcode.com/problems/maximum-spending-after-buying-items/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed m * n integer matrix values, representing the values of m * n different items in m different shops. Each shop has n items where the jth item in the ith shop has a value of values[i][j]. Additionally, the items in the ith shop are sorted in non-increasing order of value. That is, values[i][j] >= values[i][j + 1] for all 0 <= j < n - 1.
//
// On each day, you would like to buy a single item from one of the shops. Specifically, On the dth day you can:
//
//
// 	Pick any shop i.
// 	Buy the rightmost available item j for the price of values[i][j] * d. That is, find the greatest index j such that item j was never bought before, and buy it for the price of values[i][j] * d.
//
//
// Note that all items are pairwise different. For example, if you have bought item 0 from shop 1, you can still buy item 0 from any other shop.
//
// Return the maximum amount of money that can be spent on buying all  m * n products.
//
// Example:
// Input: values = [[8,5,2],[6,4,1],[9,7,3]]
// Output: 285
// Explanation: On the first day, we buy product 2 from shop 1 for a price of values[1][2] * 1 = 1.
// On the second day, we buy product 2 from shop 0 for a price of values[0][2] * 2 = 4.
// On the third day, we buy product 2 from shop 2 for a price of values[2][2] * 3 = 9.
// On the fourth day, we buy product 1 from shop 1 for a price of values[1][1] * 4 = 16.
// On the fifth day, we buy product 1 from shop 0 for a price of values[0][1] * 5 = 25.
// On the sixth day, we buy product 0 from shop 1 for a price of values[1][0] * 6 = 36.
// On the seventh day, we buy product 1 from shop 2 for a price of values[2][1] * 7 = 49.
// On the eighth day, we buy product 0 from shop 0 for a price of values[0][0] * 8 = 64.
// On the ninth day, we buy product 0 from shop 2 for a price of values[2][0] * 9 = 81.
// Hence, our total spending is equal to 285.
// It can be shown that 285 is the maximum amount of money that can be spent buying all m * n products.
//
// Constraints:
// 1 <= m == values.length <= 10
// 	1 <= n == values[i].length <= 104
// 	1 <= values[i][j] <= 106
// 	values[i] are sorted in non-increasing order.
//
// Helpful references (internal KB):
// - Minimum spanning tree - Prim's algorithm (graph, heap, array, mst-prim, greedy, heap-select)
//   • When to use: Use Prim's algorithm to find a minimum spanning tree in a connected, weighted graph. It is efficient for both dense graphs (O(V^2)) and sparse graphs (O(E log V)) depending on the implementation.
//   • Idea: Prim's algorithm is a greedy algorithm that builds an MST by iteratively adding the cheapest edge connecting a vertex in the growing tree to a vertex outside the tree. It has a time complexity of O(V^2) for dense graphs using an adjacency matrix or O(E log V) for sparse graphs using a priority queue.
//   • Invariants: All selected vertices and edges form a connected component of the final MST.; For any unselected vertex `v`, `min_e[v]` stores the minimum weight of an edge connecting `v` to the currently selected component.
//   • Tips: For dense graphs, an O(V^2) implementation using an an adjacency matrix and simple array scans is efficient.; For sparse graphs, use a priority queue (min-heap) with an adjacency list to achieve O(E log V) complexity.
//   • Pitfalls: Incorrectly updating the `min_e` array or priority queue entries can lead to an incorrect MST or performance issues.; Forgetting to mark vertices as 'selected' can lead to cycles or infinite loops.
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long maxSpending(int** values, int valuesSize, int* valuesColSize) {
    int m = valuesSize;
    int n = valuesColSize[0];
    
    // Create an array to store the current index of the rightmost available item for each shop
    int* indices = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        indices[i] = n - 1; // Start from the rightmost item
    }
    
    long long totalSpending = 0;
    
    // We will buy items for m*n days
    for (int day = 1; day <= m * n; day++) {
        long long maxCost = 0;
        int shopIndex = -1;
        
        // Find the shop with the most expensive available item for this day
        for (int i = 0; i < m; i++) {
            if (indices[i] >= 0) { // If there are still items available in this shop
                long long cost = (long long)values[i][indices[i]] * day;
                if (cost > maxCost) {
                    maxCost = cost;
                    shopIndex = i;
                }
            }
        }
        
        // Buy the item from the selected shop
        totalSpending += maxCost;
        indices[shopIndex]--; // Move to the next available item in that shop
    }
    
    free(indices);
    return totalSpending;       
}
