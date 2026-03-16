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
public:
    int findKthNumber(int n, int k) {
        int curr = 1;
        k--;  // since we start from number 1
        
        while (k > 0) {
            long long steps = 0;
            long long first = curr;
            long long last = curr + 1;
            
            // Count steps between first and last
            while (first <= n) {
                steps += std::min((long long)n + 1, last) - first;
                first *= 10;
                last *= 10;
            }
            
            if (steps <= k) {
                // Move to next sibling
                curr += 1;
                k -= steps;
            } else {
                // Move to first child
                curr *= 10;
                k -= 1;
            }
        }
        
        return curr;            
    }
};
