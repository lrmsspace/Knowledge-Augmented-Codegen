// Source: https://leetcode.com/problems/reordered-power-of-2/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n. We reorder the digits in any order (including the original order) such that the leading digit is not zero.
//
// Return true if and only if we can do this so that the resulting number is a power of two.
//
// Example:
// Input: n = 1
// Output: true
//
// Constraints:
// 1 <= n <= 109
//

class Solution {
public:
    bool reorderedPowerOf2(int n) {
        vector<int> count(10, 0);
        while (n > 0) {
            count[n % 10]++;
            n /= 10;
        }

        for (int i = 0; i < 31; ++i) {
            int powerOf2 = 1 << i;
            vector<int> powerCount(10, 0);
            while (powerOf2 > 0) {
                powerCount[powerOf2 % 10]++;
                powerOf2 /= 10;
            }
            if (powerCount == count) {
                return true;
            }
        }
        return false;           
    }
};
