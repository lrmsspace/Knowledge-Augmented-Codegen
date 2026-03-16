// Source: https://leetcode.com/problems/beautiful-array/   |   Difficulty: Medium
//
// Problem Description:
// An array nums of length n is beautiful if:
//
//
// 	nums is a permutation of the integers in the range [1, n].
// 	For every 0 <= i < j < n, there is no index k with i < k < j where 2 * nums[k] == nums[i] + nums[j].
//
//
// Given the integer n, return any beautiful array nums of length n. There will be at least one valid answer for the given n.
//
// Example:
// Input: n = 4
// Output: [2,1,4,3]
//
// Constraints:
// 1 <= n <= 1000
//

class Solution {
public:
    vector<int> beautifulArray(int n) {
        if (n == 1) {
            return {1};
        }

        vector<int> odd = beautifulArray((n + 1) / 2);
        vector<int> even = beautifulArray(n / 2);

        vector<int> result;
        for (int x : odd) {
            result.push_back(2 * x - 1);
        }
        for (int x : even) {
            result.push_back(2 * x);
        }

        return result;          
    }
};
