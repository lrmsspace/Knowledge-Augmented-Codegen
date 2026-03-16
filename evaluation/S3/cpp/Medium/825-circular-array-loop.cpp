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
// - Josephus Problem (number, simulation, recursion)
//   • When to use: Use when determining the survivor's position in a circular game where every k-th person is eliminated, especially for large N where direct simulation is too slow.
//   • Idea: This algorithm finds the position of the last remaining person in the Josephus problem by iteratively reducing the problem size using a recursive formula and modulo arithmetic. It achieves an optimized time complexity of O(k log n).
//   • Invariants: The number of remaining elements decreases in each recursive step.; The relative order of the remaining elements is preserved throughout the process.
//   • Tips: Handle the base case where n < k separately to avoid infinite loops or incorrect calculations.; Use 0-indexing for simpler modulo arithmetic in the recursive formulas.
//   • Pitfalls: Incorrectly handling index shifts after elements are removed can lead to wrong results.; Forgetting the base case n < k can lead to infinite recursion or incorrect behavior.
// - Josephus Problem (number, recursion, counting)
//   • When to use: Use when simulating a circular elimination process with a fixed step size, especially when seeking the survivor's position. It's particularly efficient for specific step sizes like two.
//   • Idea: The Josephus Problem determines the last remaining position in a circular arrangement after elements are eliminated at fixed intervals. The recursive solution for a step size of two has a logarithmic time complexity, O(log N), due to its divide-and-conquer nature.
//   • Invariants: The number of participants N is always positive in each recursive subproblem.; The returned position is always within the valid range [0, current N-1] (or [1, current N]).
//   • Tips: Base cases are crucial for recursive solutions, typically for N=1.; Observe patterns for specific step sizes, especially k=2, which has a simpler formula.
//   • Pitfalls: Off-by-one errors when converting between 0-indexed and 1-indexed results.; Incorrectly applying the position 'shift' after elements are eliminated in subproblems.
// - Josephus Problem (number, dp-1d, recursion)
//   • When to use: Used to determine the position of the last remaining person in a circle where every k-th person is eliminated until only one remains. It models sequential removal processes in a circular arrangement.
//   • Idea: The Josephus Problem determines the position of the survivor in a circle of N people, where every K-th person is eliminated. The standard solution uses a recursive relation or dynamic programming, typically achieving O(N) time complexity.
//   • Invariants: The result J(n, k) represents the survivor's original 0-indexed position among n people.; Each recursive step J(n, k) correctly transforms the result from J(n-1, k) based on the k-th elimination.
//   • Tips: Use 0-indexing for a simpler and more elegant recursive formula.; Establish the base case for N=1 (the survivor is always 0 or 1).
//   • Pitfalls: Off-by-one errors when switching between 0-indexing and 1-indexing.; Incorrectly applying the modulo operator, especially with negative results in some languages.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool circularArrayLoop(vector<int>& nums) {
        int n = nums.size();    
        for (int i = 0; i < n; ++i) {
            if (nums[i] == 0) continue; // Already visited or no movement
            int slow = i, fast = i;
            bool isForward = nums[i] > 0; // Direction of movement
            
            while (true) {
                // Move slow pointer one step
                slow = nextIndex(nums, slow, isForward);
                if (slow == -1) break; // Invalid move
                
                // Move fast pointer two steps
                fast = nextIndex(nums, fast, isForward);
                if (fast == -1) break; // Invalid move
                fast = nextIndex(nums, fast, isForward);
                if (fast == -1) break; // Invalid move
                
                if (slow == fast) return true; // Cycle detected
            }
            
            // Mark all nodes in the current path as visited
            int j = i;
            while (nums[j] != 0) {
                int next = nextIndex(nums, j, nums[j] > 0);
                nums[j] = 0; // Mark as visited
                j = next;
            }
        }
        return false;
    }
};
