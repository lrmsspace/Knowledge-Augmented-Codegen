// Source: https://leetcode.com/problems/simplified-fractions/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return a list of all simplified fractions between 0 and 1 (exclusive) such that the denominator is less-than-or-equal-to n. You can return the answer in any order.
//
// Example:
// Input: n = 2
// Output: ["1/2"]
// Explanation: "1/2" is the only unique fraction with a denominator less-than-or-equal-to 2.
//
// Constraints:
// 1 <= n <= 100
//

class Solution {
public:
    vector<string> simplifiedFractions(int n) {
        vector<string> result;
        for (int denom = 2; denom <= n; ++denom) {
            for (int numer = 1; numer < denom; ++numer) {
                if (gcd(numer, denom) == 1) {
                    result.push_back(to_string(numer) + "/" + to_string(denom));
                }
            }
        }
        return result;          
    }
};
