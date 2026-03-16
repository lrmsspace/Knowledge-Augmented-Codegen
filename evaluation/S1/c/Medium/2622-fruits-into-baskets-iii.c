// Source: https://leetcode.com/problems/fruits-into-baskets-iii/   |   Difficulty: Medium
//
// Problem Description:
// You are given two arrays of integers, fruits and baskets, each of length n, where fruits[i] represents the quantity of the ith type of fruit, and baskets[j] represents the capacity of the jth basket.
//
// From left to right, place the fruits according to these rules:
//
//
// 	Each fruit type must be placed in the leftmost available basket with a capacity greater than or equal to the quantity of that fruit type.
// 	Each basket can hold only one type of fruit.
// 	If a fruit type cannot be placed in any basket, it remains unplaced.
//
//
// Return the number of fruit types that remain unplaced after all possible allocations are made.
//
// Example:
// Input: fruits = [4,2,5], baskets = [3,5,4]
//
// Output: 1
//
// Explanation:
//
//
// 	fruits[0] = 4 is placed in baskets[1] = 5.
// 	fruits[1] = 2 is placed in baskets[0] = 3.
// 	fruits[2] = 5 cannot be placed in baskets[2] = 4.
//
//
// Since one fruit type remains unplaced, we return 1.
//
// Constraints:
// n == fruits.length == baskets.length
// 	1 <= n <= 105
// 	1 <= fruits[i], baskets[i] <= 109
//
// Helpful references (internal KB):
// - Segment Tree (tree, array, segment-tree, divide-and-conquer)
//   • When to use: When you need to perform range queries (like sum, min, max) and point or range updates on an array efficiently, typically in O(log N) time.
//   • Idea: A tree-based data structure that stores information about array segments, allowing for efficient O(log N) range queries and point/range updates. It recursively divides the array into halves, with each node representing an interval.
//   • Invariants: Each node in the segment tree corresponds to a contiguous subsegment of the original array.; The value stored in a node is the aggregate result (e.g., sum, min) of its corresponding array subsegment.
//   • Tips: Use 1-based indexing for array and tree nodes to simplify parent/child calculations.; Implement lazy propagation for efficient range updates to avoid O(N) updates.
//   • Pitfalls: Off-by-one errors in segment boundaries or query ranges are common.; Forgetting to push down lazy updates before accessing children or returning a node's value.
// - Knapsack Problem (array, knapsack, dp-1d, enumeration)
//   • When to use: Use when selecting items from a set to maximize or minimize a value under a capacity constraint. It's also applicable for partitioning problems with a fixed budget.
//   • Idea: This algorithm finds the maximum value that can be obtained by selecting a subset of items, each with a weight and a value, such that their total weight does not exceed a given capacity. It typically uses dynamic programming with a time complexity of O(N*W), where N is the number of items and W is the capacity.
//   • Invariants: After processing item `i`, `dp[w]` stores the maximum value for capacity `w` using items up to `i`.; For each item, `dp[w]` is updated considering either including or excluding the current item.
//   • Tips: Use a 2D DP table `dp[i][w]` for item `i` and weight `w` for clarity, then optimize to 1D.; When optimizing to 1D, iterate weights downwards to avoid using an item multiple times.
//   • Pitfalls: Incorrectly initializing the DP table can lead to wrong results or infinite loops.; Forgetting to iterate weights downwards in 1D DP can lead to items being picked multiple times (unbounded knapsack).
// - Scheduling jobs on two machines (array, greedy)
//   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
//   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
//   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
//   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
//   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int numOfUnplacedFruits(int* fruits, int fruitsSize, int* baskets, int basketsSize) {
    // Segment Tree implementation for range maximum query and point update
    #define MAXN 100000
    int segtree[4 * MAXN];
    
    void build(int node, int start, int end, int* arr) {
        if (start == end) {
            segtree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(2 * node + 1, start, mid, arr);
            build(2 * node + 2, mid + 1, end, arr);
            segtree[node] = segtree[2 * node + 1] > segtree[2 * node + 2] ? segtree[2 * node + 1] : segtree[2 * node + 2];
        }
    }
    
    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return -1; // Out of range
        }
        if (l <= start && end <= r) {
            return segtree[node];
        }
        int mid = (start + end) / 2;
        int p1 = query(2 * node + 1, start, mid, l, r);
        int p2 = query(2 * node + 2, mid + 1, end, l, r);
        return p1 > p2 ? p1 : p2;
    }
    
    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            segtree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (start <= idx && idx <= mid) {
                update(2 * node + 1, start, mid, idx, val);
            } else {
                update(2 * node + 2, mid + 1, end, idx, val);
            }
            segtree[node] = segtree[2 * node + 1] > segtree[2 * node + 2] ? segtree[2 * node + 1] : segtree[2 * node + 2];
        }
    }
    
    build(0, 0, basketsSize - 1, baskets);
    
    int unplacedCount = 0;
    for (int i = 0; i < fruitsSize; i++) {
        int fruit = fruits[i];
        // Binary search to find the leftmost basket that can hold the fruit
        int left = 0, right = basketsSize - 1, pos = -1;
        while (left <= right) {
            int mid = (left + right) / 2;
            int maxInRange = query(0, 0, basketsSize - 1, mid, basketsSize - 1);
            if (maxInRange >= fruit) {
                pos = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        if (pos == -1) {
            unplacedCount++;
        } else {
            // Find the exact basket to place the fruit
            for (int j = pos; j < basketsSize; j++) {
                int basketCapacity = query(0, 0, basketsSize - 1, j, j);
                if (basketCapacity >= fruit) {
                    update(0, 0, basketsSize - 1, j, -1); // Mark basket as used
                    break;
                }
            }
        }
    }
    return unplacedCount;
}
