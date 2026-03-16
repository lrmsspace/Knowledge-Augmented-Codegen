// Source: https://leetcode.com/problems/circular-array-loop/   |   Difficulty: Medium
//
// Problem Description:
// You are playing a game involving a circular array of non-zero integers nums. Each nums[i] denotes the number of indices forward/backward you must move if you are located at index i:
//
//
// 	If nums[i] is positive, move nums[i] steps forward, and
// 	If nums[i] is negative, move nums[i] steps backward.
//
//
// Since the array is circular, you may assume that moving forward from the last element puts you on the first element, and moving backwards from the first element puts you on the last element.
//
// A cycle in the array consists of a sequence of indices seq of length k where:
//
//
// 	Following the movement rules above results in the repeating index sequence seq[0] -> seq[1] -> ... -> seq[k - 1] -> seq[0] -> ...
// 	Every nums[seq[j]] is either all positive or all negative.
// 	k > 1
//
//
// Return true if there is a cycle in nums, or false otherwise.
//
// Example:
// Input: nums = [2,-1,1,2,2]
// Output: true
// Explanation: The graph shows how the indices are connected. White nodes are jumping forward, while red is jumping backward.
// We can see the cycle 0 --> 2 --> 3 --> 0 --> ..., and all of its nodes are white (jumping in the same direction).
//
// Constraints:
// 1 <= nums.length <= 5000
// 	-1000 <= nums[i] <= 1000
// 	nums[i] != 0
//
//
//  
// Follow up: Could you solve it in O(n) time complexity and O(1) extra space complexity?
//
// Helpful references (internal KB):
// - Floyd's Linked List Cycle Finding Algorithm (linked-list, two-pointers, simulation)
//   • When to use: Use this algorithm to efficiently detect if a linked list contains a cycle and, optionally, find the entry point of that cycle, using only constant extra space.
//   • Idea: This algorithm uses two pointers, one moving faster than the other, to detect if a cycle exists in a linked list. If a cycle is found, it can then determine the cycle's starting node in O(N) time complexity and O(1) space complexity.
//   • Invariants: The slow and fast pointers are always valid nodes or null.; In the detection phase, the fast pointer always covers twice the distance of the slow pointer.
//   • Tips: Initialize both slow and fast pointers at the head of the list.; Move the slow pointer by one step and the fast pointer by two steps in each iteration.
//   • Pitfalls: Forgetting to check for null on 'fast' and 'fast.next' before dereferencing them.; Incorrectly assuming the list is non-empty or has at least two nodes.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Josephus Problem (number, simulation, recursion)
//   • When to use: Use when determining the survivor's position in a circular game where every k-th person is eliminated, especially for large N where direct simulation is too slow.
//   • Idea: This algorithm finds the position of the last remaining person in the Josephus problem by iteratively reducing the problem size using a recursive formula and modulo arithmetic. It achieves an optimized time complexity of O(k log n).
//   • Invariants: The number of remaining elements decreases in each recursive step.; The relative order of the remaining elements is preserved throughout the process.
//   • Tips: Handle the base case where n < k separately to avoid infinite loops or incorrect calculations.; Use 0-indexing for simpler modulo arithmetic in the recursive formulas.
//   • Pitfalls: Incorrectly handling index shifts after elements are removed can lead to wrong results.; Forgetting the base case n < k can lead to infinite recursion or incorrect behavior.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private int getNextIndex(int[] nums, boolean isForward, int currentIndex) {
        boolean direction = nums[currentIndex] > 0;
        if (isForward != direction) {
            return -1;
        }

        int n = nums.length;
        int nextIndex = (currentIndex + nums[currentIndex]) % n;
        if (nextIndex < 0) {
            nextIndex += n;
        }

        if (nextIndex == currentIndex) {
            return -1;
        }

        return nextIndex;
    }
    public boolean circularArrayLoop(int[] nums) {
        int n = nums.length;

        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) {
                continue;
            }

            int slow = i, fast = i;
            boolean isForward = nums[i] > 0;

            while (true) {
                slow = getNextIndex(nums, isForward, slow);
                if (slow == -1) {
                    break;
                }

                fast = getNextIndex(nums, isForward, fast);
                if (fast == -1) {
                    break;
                }
                fast = getNextIndex(nums, isForward, fast);
                if (fast == -1) {
                    break;
                }

                if (slow == fast) {
                    return true;
                }
            }

            slow = i;
            int val = nums[i];
            while (true) {
                int next = getNextIndex(nums, val > 0, slow);
                if (next == -1) {
                    break;
                }
                nums[slow] = 0;
                slow = next;
            }
        }

        return false;           
    }
}
