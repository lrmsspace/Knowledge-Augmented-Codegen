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

int findKthNumber(int n, int k) {
    int curr = 1;
    k -= 1; /* we start from number 1 */
    while (k > 0) {
        long long step = 0;
        long long first = curr;
        long long last = curr + 1;
        while (first <= n) {
            step += (last <= n + 1) ? (last - first) : (n + 1 - first);
            first *= 10;
            last *= 10;
        }
        if (step <= k) {
            curr += 1;
            k -= step;
        } else {
            curr *= 10;
            k -= 1;
        }
    }
    return curr;        
}
