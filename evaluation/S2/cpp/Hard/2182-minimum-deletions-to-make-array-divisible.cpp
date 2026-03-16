// Source: https://leetcode.com/problems/minimum-deletions-to-make-array-divisible/   |   Difficulty: Hard
//
// Problem Description:
// You are given two positive integer arrays nums and numsDivide. You can delete any number of elements from nums.
//
// Return the minimum number of deletions such that the smallest element in nums divides all the elements of numsDivide. If this is not possible, return -1.
//
// Note that an integer x divides y if y % x == 0.
//
// Example:
// Input: nums = [2,3,2,4,3], numsDivide = [9,6,9,3,15]
// Output: 2
// Explanation: 
// The smallest element in [2,3,2,4,3] is 2, which does not divide all the elements of numsDivide.
// We use 2 deletions to delete the elements in nums that are equal to 2 which makes nums = [3,4,3].
// The smallest element in [3,4,3] is 3, which divides all the elements of numsDivide.
// It can be shown that 2 is the minimum number of deletions needed.
//
// Constraints:
// 1 <= nums.length, numsDivide.length <= 105
// 	1 <= nums[i], numsDivide[i] <= 109
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minOperations(vector<int>& nums, vector<int>& numsDivide) {
        // Step 1: Find the GCD of all elements in numsDivide
        int gcd = numsDivide[0];
        for (int i = 1; i < numsDivide.size(); ++i) {
            gcd = std::__gcd(gcd, numsDivide[i]);
        }

        // Step 2: Sort nums to find the smallest element that divides the GCD
        std::sort(nums.begin(), nums.end());

        // Step 3: Find the minimum deletions required
        for (int i = 0; i < nums.size(); ++i) {
            if (gcd % nums[i] == 0) {
                return i; // The index of the first element that divides the GCD is the number of deletions
            }
        }

        return -1; // If no element in nums divides the GCD, return -1          
    }
};
