// Source: https://leetcode.com/problems/minimum-operations-to-convert-number/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums containing distinct numbers, an integer start, and an integer goal. There is an integer x that is initially set to start, and you want to perform operations on x such that it is converted to goal. You can perform the following operation repeatedly on the number x:
//
// If 0 <= x <= 1000, then for any index i in the array (0 <= i < nums.length), you can set x to any of the following:
//
//
// 	x + nums[i]
// 	x - nums[i]
// 	x ^ nums[i] (bitwise-XOR)
//
//
// Note that you can use each nums[i] any number of times in any order. Operations that set x to be out of the range 0 <= x <= 1000 are valid, but no more operations can be done afterward.
//
// Return the minimum number of operations needed to convert x = start into goal, and -1 if it is not possible.
//
// Example:
// Input: nums = [2,4,12], start = 2, goal = 12
// Output: 2
// Explanation: We can go from 2 → 14 → 12 with the following 2 operations.
// - 2 + 12 = 14
// - 14 - 2 = 12
//
// Constraints:
// 1 <= nums.length <= 1000
// 	-109 <= nums[i], goal <= 109
// 	0 <= start <= 1000
// 	start != goal
// 	All the integers in nums are distinct.
//
// Helpful references (internal KB):
// - Breadth-first search (graph, array, bfs, counting)
//   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level to explore all reachable nodes. It is also suitable for finding connected components or checking reachability.
//   • Idea: Breadth-first search explores a graph layer by layer, finding the shortest path in terms of edges from a source node to all other reachable nodes. It typically runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
//   • Invariants: All nodes currently in the queue are at the same or next level of traversal from the source.; All nodes already dequeued have been fully processed, and their unvisited neighbors have been enqueued.
//   • Tips: Use a queue to manage nodes to visit in a FIFO manner.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing and cycles.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs or incorrect path lengths.; Not handling disconnected components if the goal is to traverse the entire graph.
// - Minimum stack / Minimum queue (queue, stack, simulation)
//   • When to use: Use when needing to efficiently query the minimum element of a stack or queue in O(1) average time. Also applicable for finding minimums in all fixed-length subarrays using a sliding window.
//   • Idea: This technique augments a stack or queue to support O(1) average time retrieval of its minimum element, typically by storing minimums alongside data or using auxiliary structures. It achieves amortized constant time for all operations.
//   • Invariants: For a minimum stack, the auxiliary minimum stack's top element is always the minimum of all elements currently in the main stack.; For a minimum queue implemented with two stacks, the output stack is only refilled from the input stack when the output stack becomes empty.
//   • Tips: For a minimum stack, use an auxiliary stack to store minimums encountered so far.; Only push to the auxiliary minimum stack if the new element is less than or equal to its current top.
//   • Pitfalls: Forgetting to pop from the auxiliary minimum stack when the main stack's top is removed.; Incorrectly handling the transfer logic between the two stacks for a minimum queue.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minimumOperations(vector<int>& nums, int start, int goal) {
        const int MAX_X = 1000;
        const int OFFSET = 1000; // To handle negative indices

        bool visited[2001] = {false}; // Track visited states from -1000 to 1000
        std::queue<std::pair<int, int>> q; // Pair of (current value, steps)
        q.push({start, 0});
        visited[start + OFFSET] = true;

        while (!q.empty()) {
            auto [curr, steps] = q.front();
            q.pop();

            if (curr == goal) {
                return steps;
            }

            for (int num : nums) {
                int next_vals[3] = {curr + num, curr - num, curr ^ num};
                for (int next : next_vals) {
                    if (next == goal) {
                        return steps + 1;
                    }
                    if (next >= 0 && next <= MAX_X && !visited[next + OFFSET]) {
                        visited[next + OFFSET] = true;
                        q.push({next, steps + 1});
                    }
                }
            }
        }

        return -1; // Goal not reachable            
    }
};
