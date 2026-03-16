// Source: https://leetcode.com/problems/k-th-smallest-in-lexicographical-order/   |   Difficulty: Hard
//
// Problem Description:
// Given two integers n and k, return the kth lexicographically smallest integer in the range [1, n].
//
// Example:
// Input: n = 13, k = 2
// Output: 10
// Explanation: The lexicographical order is [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9], so the second smallest number is 10.
//
// Constraints:
// 1 <= k <= n <= 109
//

class Solution {
    public int findKthNumber(int n, int k) {
        int curr = 1;
        k--;
        
        while (k > 0) {
            long steps = calculateSteps(n, curr, curr + 1);
            if (steps <= k) {
                k -= steps;
                curr++;
            } else {
                k--;
                curr *= 10;
            }
        }
        
        return curr;            
    }
}
