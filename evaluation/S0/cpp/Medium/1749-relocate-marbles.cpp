// Source: https://leetcode.com/problems/relocate-marbles/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums representing the initial positions of some marbles. You are also given two 0-indexed integer arrays moveFrom and moveTo of equal length.
//
// Throughout moveFrom.length steps, you will change the positions of the marbles. On the ith step, you will move all marbles at position moveFrom[i] to position moveTo[i].
//
// After completing all the steps, return the sorted list of occupied positions.
//
// Example:
// Input: nums = [1,6,7,8], moveFrom = [1,7,2], moveTo = [2,9,5]
// Output: [5,6,8,9]
// Explanation: Initially, the marbles are at positions 1,6,7,8.
// At the i = 0th step, we move the marbles at position 1 to position 2. Then, positions 2,6,7,8 are occupied.
// At the i = 1st step, we move the marbles at position 7 to position 9. Then, positions 2,6,8,9 are occupied.
// At the i = 2nd step, we move the marbles at position 2 to position 5. Then, positions 5,6,8,9 are occupied.
// At the end, the final positions containing at least one marbles are [5,6,8,9].
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= moveFrom.length <= 105
// 	moveFrom.length == moveTo.length
// 	1 <= nums[i], moveFrom[i], moveTo[i] <= 109
// 	The test cases are generated such that there is at least a marble in moveFrom[i] at the moment we want to apply the ith move.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> relocateMarbles(vector<int>& nums, vector<int>& moveFrom, vector<int>& moveTo) {
        unordered_map<int, int> positionCount;
        for (int num : nums) {
            positionCount[num]++;
        }

        int n = moveFrom.size();
        for (int i = 0; i < n; ++i) {
            int from = moveFrom[i];
            int to = moveTo[i];
            if (positionCount.find(from) != positionCount.end()) {
                int count = positionCount[from];
                positionCount[to] += count;
                positionCount.erase(from);
            }
        }

        vector<int> result;
        for (const auto& entry : positionCount) {
            result.push_back(entry.first);
        }
        sort(result.begin(), result.end());
        return result;          
    }
};
