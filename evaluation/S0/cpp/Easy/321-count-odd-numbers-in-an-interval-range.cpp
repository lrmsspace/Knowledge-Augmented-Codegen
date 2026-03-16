// Source: https://leetcode.com/problems/count-odd-numbers-in-an-interval-range/   |   Difficulty: Easy
//
// Problem Description:
// Given two non-negative integers low and high. Return the count of odd numbers between low and high (inclusive).
//
// Example:
// Input: low = 3, high = 7
// Output: 3
// Explanation: The odd numbers between 3 and 7 are [3,5,7].
//
// Constraints:
// 0 <= low <= high <= 10^9
//

class Solution {
public:
    int countOdds(int low, int high) {
        int count = (high - low) / 2;
        if (low % 2 == 1 || high % 2 == 1) {
            count++;
        }
        return count;           
    }
};
