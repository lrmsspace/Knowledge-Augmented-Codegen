// Source: https://leetcode.com/problems/minimum-seconds-to-equalize-a-circular-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums containing n integers.
//
// At each second, you perform the following operation on the array:
//
//
// 	For every index i in the range [0, n - 1], replace nums[i] with either nums[i], nums[(i - 1 + n) % n], or nums[(i + 1) % n].
//
//
// Note that all the elements get replaced simultaneously.
//
// Return the minimum number of seconds needed to make all elements in the array nums equal.
//
// Example:
// Input: nums = [1,2,1,2]
// Output: 1
// Explanation: We can equalize the array in 1 second in the following way:
// - At 1st second, replace values at each index with [nums[3],nums[1],nums[3],nums[3]]. After replacement, nums = [2,2,2,2].
// It can be proven that 1 second is the minimum amount of seconds needed for equalizing the array.
//
// Constraints:
// 1 <= n == nums.length <= 105
// 	1 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
// - Hash Tables (array, number, string, hashing)
//   • When to use: Use when you need to store and retrieve key-value pairs efficiently by transforming keys into array indices, managing potential collisions.
//   • Idea: Hash tables map keys to array indices using a hash function, enabling average O(1) time complexity for insertions, deletions, and lookups by efficiently managing potential collisions.
//   • Invariants: The hash function always produces an index within the valid array bounds [0, M-1].; For any two equal keys, their hash values remain identical.
//   • Tips: Design hash functions for uniform key distribution across the array.; Ensure hash functions are deterministic and efficient to compute.
//   • Pitfalls: Using a hash function that does not uniformly distribute keys, leading to many collisions.; Failing to implement a proper collision resolution strategy.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minimumSeconds(List<Integer> nums) {
        int n = nums.size();
        Map<Integer, List<Integer>> positionsMap = new HashMap<>();
        for (int i = 0; i < n; i++) {
            positionsMap.computeIfAbsent(nums.get(i), k -> new ArrayList<>()).add(i);
        }

        int minSeconds = Integer.MAX_VALUE;
        for (List<Integer> positions : positionsMap.values()) {
            int maxGap = 0;
            int m = positions.size();
            for (int i = 0; i < m; i++) {
                int current = positions.get(i);
                int next = positions.get((i + 1) % m);
                if (next <= current) {
                    next += n;
                }
                int gap = next - current - 1;
                maxGap = Math.max(maxGap, gap);
            }
            int secondsNeeded = (maxGap + 1) / 2;
            minSeconds = Math.min(minSeconds, secondsNeeded);
        }

        return minSeconds;          
    }
}
