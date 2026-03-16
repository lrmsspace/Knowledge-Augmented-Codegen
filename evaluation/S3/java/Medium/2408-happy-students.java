// Source: https://leetcode.com/problems/happy-students/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums of length n where n is the total number of students in the class. The class teacher tries to select a group of students so that all the students remain happy.
//
// The ith student will become happy if one of these two conditions is met:
//
//
// 	The student is selected and the total number of selected students is strictly greater than nums[i].
// 	The student is not selected and the total number of selected students is strictly less than nums[i].
//
//
// Return the number of ways to select a group of students so that everyone remains happy.
//
// Example:
// Input: nums = [1,1]
// Output: 2
// Explanation: 
// The two possible ways are:
// The class teacher selects no student.
// The class teacher selects both students to form the group. 
// If the class teacher selects just one student to form a group then the both students will not be happy. Therefore, there are only two possible ways.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] < nums.length
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
// - bucket-sort (array, bucket-sort)
//   • When to use: Use when sorting elements with a known, uniform distribution over a specific range. It is efficient for numbers that are uniformly distributed across a range, often achieving linear time complexity.
//   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket individually, and then concatenates them. It can achieve O(N+K) average time complexity for uniformly distributed data.
//   • Invariants: After distributing elements, each element `x` is in bucket `floor(N * x)`.; After sorting buckets, every bucket `buckets[i]` contains its elements in sorted order.
//   • Tips: Choose the number of buckets appropriately based on data distribution and range.; Normalize input data to a [0, 1) range for simpler bucket indexing.
//   • Pitfalls: Poor performance with non-uniform data distribution, potentially degrading to O(N^2).; Requires extra space for the buckets, proportional to N+K.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int countWays(List<Integer> nums) {
        Collections.sort(nums);
        int n = nums.size();
        int count = 0;
        for (int i = 0; i <= n; i++) {
            if ((i > 0 && nums.get(i - 1) >= i) || (i < n && nums.get(i) <= i)) {
                continue;
            }
            count++;
        }
        return count;           
    }
}
