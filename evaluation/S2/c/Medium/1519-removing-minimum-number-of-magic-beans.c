// Source: https://leetcode.com/problems/removing-minimum-number-of-magic-beans/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of positive integers beans, where each integer represents the number of magic beans found in a particular magic bag.
//
// Remove any number of beans (possibly none) from each bag such that the number of beans in each remaining non-empty bag (still containing at least one bean) is equal. Once a bean has been removed from a bag, you are not allowed to return it to any of the bags.
//
// Return the minimum number of magic beans that you have to remove.
//
// Example:
// Input: beans = [4,1,6,5]
// Output: 4
// Explanation: 
// - We remove 1 bean from the bag with only 1 bean.
//   This results in the remaining bags: [4,0,6,5]
// - Then we remove 2 beans from the bag with 6 beans.
//   This results in the remaining bags: [4,0,4,5]
// - Then we remove 1 bean from the bag with 5 beans.
//   This results in the remaining bags: [4,0,4,4]
// We removed a total of 1 + 2 + 1 = 4 beans to make the remaining non-empty bags have an equal number of beans.
// There are no other solutions that remove 4 beans or fewer.
//
// Constraints:
// 1 <= beans.length <= 105
// 	1 <= beans[i] <= 105
//
// Helpful references (internal KB):
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// - Second Best Minimum Spanning Tree (graph, array, mst-kruskal, enumeration)
//   • When to use: Use when you need to find a spanning tree with the second smallest total edge weight, often for redundancy or alternative network path planning. It's applicable in scenarios requiring fault tolerance beyond a single optimal solution.
//   • Idea: This algorithm finds a spanning tree with the second minimum total edge weight in a connected, undirected graph. It involves finding the primary MST, then modifying it by replacing one MST edge with a non-MST edge.
//   • Invariants: The primary MST is always a valid spanning tree with minimum total weight.; Adding any non-MST edge (u,v) to the MST creates exactly one cycle.
//   • Tips: First, compute the primary Minimum Spanning Tree (MST) using an algorithm like Kruskal's or Prim's.; For each edge not in the MST, adding it to the MST creates a unique cycle. Find the maximum weight edge on this cycle.
//   • Pitfalls: Naively recomputing an entire MST for each removed edge is inefficient (O(V * E log E)).; Incorrectly identifying the maximum weight edge on the cycle formed by adding a non-MST edge.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when scheduling a set of jobs on a single machine to minimize the total weighted completion time, where each job has a processing time and a linear penalty coefficient.
//   • Idea: This algorithm finds an optimal schedule for jobs on a single machine with linear penalty functions by sorting jobs based on a specific ratio. It achieves an optimal solution in O(N log N) time complexity.
//   • Invariants: The partial schedule constructed so far is optimal for the jobs included.; For any two adjacent jobs 'j' and 'k' in the final schedule, if 'j' precedes 'k', then 'c_j/t_j >= c_k/t_k'.
//   • Tips: Derive the sorting criterion using an exchange argument for adjacent jobs.; The optimal order is determined by the ratio of cost coefficient to processing time.
//   • Pitfalls: Incorrectly applying the sorting criterion, especially the ratio order.; Overlooking edge cases like zero processing times or zero penalty coefficients.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long minimumRemoval(int* beans, int beansSize) {
    // Sort the array of beans to facilitate the calculation of the minimum removals.
    qsort(beans, beansSize, sizeof(int), (int (*)(const void *, const void *))compare);
    
    long long totalBeans = 0;
    for (int i = 0; i < beansSize; i++) {
        totalBeans += beans[i];
    }
    
    long long minRemoval = totalBeans; // Start with the worst case: remove all beans.
    
    for (int i = 0; i < beansSize; i++) {
        // Calculate the number of beans to remove if we keep all bags with at least beans[i] beans.
        long long currentRemoval = totalBeans - (long long)beans[i] * (beansSize - i);
        if (currentRemoval < minRemoval) {
            minRemoval = currentRemoval;
        }
    }
    
    return minRemoval;      
}
