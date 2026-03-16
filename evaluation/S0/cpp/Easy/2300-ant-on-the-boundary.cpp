// Source: https://leetcode.com/problems/ant-on-the-boundary/   |   Difficulty: Easy
//
// Problem Description:
// An ant is on a boundary. It sometimes goes left and sometimes right.
//
// You are given an array of non-zero integers nums. The ant starts reading nums from the first element of it to its end. At each step, it moves according to the value of the current element:
//
//
// 	If nums[i] < 0, it moves left by -nums[i] units.
// 	If nums[i] > 0, it moves right by nums[i] units.
//
//
// Return the number of times the ant returns to the boundary.
//
// Example:
// Input: nums = [2,3,-5]
// Output: 1
// Explanation: After the first step, the ant is 2 steps to the right of the boundary.
// After the second step, the ant is 5 steps to the right of the boundary.
// After the third step, the ant is on the boundary.
// So the answer is 1.
//
// Constraints:
// 1 <= nums.length <= 100
// 	-10 <= nums[i] <= 10
// 	nums[i] != 0
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int returnToBoundaryCount(vector<int>& nums) {
        int position = 0;
        int returnCount = 0;

        for (int move : nums) {
            position += move;
            if (position == 0) {
                returnCount++;
            }
        }

        return returnCount;         
    }
};
