// Source: https://leetcode.com/problems/the-kth-factor-of-n/   |   Difficulty: Medium
//
// Problem Description:
// You are given two positive integers n and k. A factor of an integer n is defined as an integer i where n % i == 0.
//
// Consider a list of all factors of n sorted in ascending order, return the kth factor in this list or return -1 if n has less than k factors.
//
// Example:
// Input: n = 12, k = 3
// Output: 3
// Explanation: Factors list is [1, 2, 3, 4, 6, 12], the 3rd factor is 3.
//
// Constraints:
// 1 <= k <= n <= 1000
//
//
//  
// Follow up:
//
// Could you solve this problem in less than O(n) complexity?
//

int kthFactor(int n, int k) {
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            count++;
            if (count == k) {
                return i;
            }
        }
    }
    return -1;      
}
