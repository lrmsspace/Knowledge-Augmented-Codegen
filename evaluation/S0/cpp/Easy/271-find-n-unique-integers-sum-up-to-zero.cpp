// Source: https://leetcode.com/problems/find-n-unique-integers-sum-up-to-zero/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer n, return any array containing n unique integers such that they add up to 0.
//
// Example:
// Input: n = 5
// Output: [-7,-1,1,3,4]
// Explanation: These arrays also are accepted [-5,-1,1,2,3] , [-3,-1,2,-2,4].
//
// Constraints:
// 1 <= n <= 1000
//

class Solution {
public:
    vector<int> sumZero(int n) {
        vector<int> result;
        for (int i = 1; i <= n / 2; ++i) {
            result.push_back(i);
            result.push_back(-i);
        }
        if (n % 2 != 0) {
            result.push_back(0);
        }
        return result;          
    }
};
