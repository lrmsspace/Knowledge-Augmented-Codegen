// Source: https://leetcode.com/problems/minimum-cost-for-cutting-cake-i/   |   Difficulty: Medium
//
// Problem Description:
// There is an m x n cake that needs to be cut into 1 x 1 pieces.
//
// You are given integers m, n, and two arrays:
//
//
// 	horizontalCut of size m - 1, where horizontalCut[i] represents the cost to cut along the horizontal line i.
// 	verticalCut of size n - 1, where verticalCut[j] represents the cost to cut along the vertical line j.
//
//
// In one operation, you can choose any piece of cake that is not yet a 1 x 1 square and perform one of the following cuts:
//
//
// 	Cut along a horizontal line i at a cost of horizontalCut[i].
// 	Cut along a vertical line j at a cost of verticalCut[j].
//
//
// After the cut, the piece of cake is divided into two distinct pieces.
//
// The cost of a cut depends only on the initial cost of the line and does not change.
//
// Return the minimum total cost to cut the entire cake into 1 x 1 pieces.
//
// Example:
// Input: m = 3, n = 2, horizontalCut = [1,3], verticalCut = [5]
//
// Output: 13
//
// Explanation:
//
//
//
//
// 	Perform a cut on the vertical line 0 with cost 5, current total cost is 5.
// 	Perform a cut on the horizontal line 0 on 3 x 1 subgrid with cost 1.
// 	Perform a cut on the horizontal line 0 on 3 x 1 subgrid with cost 1.
// 	Perform a cut on the horizontal line 1 on 2 x 1 subgrid with cost 3.
// 	Perform a cut on the horizontal line 1 on 2 x 1 subgrid with cost 3.
//
//
// The total cost is 5 + 1 + 1 + 3 + 3 = 13.
//
// Constraints:
// 1 <= m, n <= 20
// 	horizontalCut.length == m - 1
// 	verticalCut.length == n - 1
// 	1 <= horizontalCut[i], verticalCut[i] <= 103
//
// Helpful references (internal KB):
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when tasks with associated processing times and costs need to be sequenced on a single machine to minimize a total objective function, typically involving weighted completion times or penalties. The optimal sequence is found by a greedy sort.
//   • Idea: This method finds an optimal schedule for jobs on a single machine by sorting them according to a greedy criterion derived from an exchange argument. It achieves an optimal solution with O(N log N) time complexity, dominated by the sorting step.
//   • Invariants: The relative order of any two jobs i and j in the sorted sequence is consistent with the greedy comparison rule.; Any prefix of the sorted schedule represents an optimal ordering for the jobs within that prefix.
//   • Tips: Clearly define the objective function to be minimized.; Formulate the greedy sorting rule using an exchange argument for any two adjacent jobs.
//   • Pitfalls: Incorrectly deriving the greedy comparison criterion.; Applying this method to problems with multiple machines or complex precedence constraints without adaptation.
// - Minimum Spanning Trees (graph, greedy)
//   • When to use: When you need to find a subset of edges in a connected, edge-weighted graph that connects all vertices with the minimum possible total edge weight. Useful for network design problems where minimizing connection costs is crucial.
//   • Idea: A Minimum Spanning Tree (MST) algorithm finds a subset of edges in an edge-weighted graph that connects all vertices with the minimum possible total weight, forming a tree. This is typically solved using greedy approaches with a time complexity often involving sorting edges or using a priority queue.
//   • Invariants: The set of edges selected so far always forms a forest.; Each connected component formed by the chosen edges is a valid subtree of some Minimum Spanning Tree.
//   • Tips: Greedy approaches often work by iteratively adding the cheapest valid edge or expanding from a starting vertex.; The cut property and cycle property are fundamental for proving correctness of MST algorithms.
//   • Pitfalls: Assuming the graph is always connected; disconnected graphs require finding a minimum spanning forest.; Incorrectly applying the greedy choice without ensuring it maintains the MST property (e.g., creating a cycle).
// - Scheduling jobs on two machines (array, greedy)
//   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
//   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
//   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
//   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
//   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minimumCost(int m, int n, vector<int>& horizontalCut, vector<int>& verticalCut) {
        sort(horizontalCut.rbegin(), horizontalCut.rend());
        sort(verticalCut.rbegin(), verticalCut.rend());

        int hCuts = 1, vCuts = 1;
        int hIdx = 0, vIdx = 0;
        int totalCost = 0;

        while (hIdx < horizontalCut.size() || vIdx < verticalCut.size()) {
            if (vIdx >= verticalCut.size() || (hIdx < horizontalCut.size() && horizontalCut[hIdx] >= verticalCut[vIdx])) {
                totalCost += horizontalCut[hIdx] * vCuts;
                hCuts++;
                hIdx++;
            } else {
                totalCost += verticalCut[vIdx] * hCuts;
                vCuts++;
                vIdx++;
            }
        }

        return totalCost;           
    }
};
