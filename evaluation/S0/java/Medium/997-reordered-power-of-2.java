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
    public boolean reorderedPowerOf2(int n) {
        String sortedN = sortDigits(n);
        for (int i = 0; i < 31; i++) {
            if (sortDigits(1 << i).equals(sortedN)) {
                return true;
            }
        }
        return false;           
    }
}
