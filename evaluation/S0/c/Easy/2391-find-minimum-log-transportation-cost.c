// Source: https://leetcode.com/problems/find-minimum-log-transportation-cost/   |   Difficulty: Easy
//
// Problem Description:
// You are given integers n, m, and k.
//
// There are two logs of lengths n and m units, which need to be transported in three trucks where each truck can carry one log with length at most k units.
//
// You may cut the logs into smaller pieces, where the cost of cutting a log of length x into logs of length len1 and len2 is cost = len1 * len2 such that len1 + len2 = x.
//
// Return the minimum total cost to distribute the logs onto the trucks. If the logs don't need to be cut, the total cost is 0.
//
// Example:
// Input: n = 6, m = 5, k = 5
//
// Output: 5
//
// Explanation:
//
// Cut the log with length 6 into logs with length 1 and 5, at a cost equal to 1 * 5 == 5. Now the three logs of length 1, 5, and 5 can fit in one truck each.
//
// Constraints:
// 2 <= k <= 105
// 	1 <= n, m <= 2 * k
// 	The input is generated such that it is always possible to transport the logs.
//

long long minCuttingCost(int n, int m, int k) {
    long long cost = 0;

    if (n > k && m > k) {
        // Both logs need to be cut
        if (n + m <= 3 * k) {
            // Cut both logs to fit in trucks
            cost += (long long)(n - k) * k; // Cut n to k and (n-k)
            cost += (long long)(m - k) * k; // Cut m to k and (m-k)
        } else {
            // Impossible case based on problem constraints
            return -1;
        }
    } else if (n > k) {
        // Only log n needs to be cut
        cost += (long long)(n - k) * k; // Cut n to k and (n-k)
    } else if (m > k) {
        // Only log m needs to be cut
        cost += (long long)(m - k) * k; // Cut m to k and (m-k)
    }

    return cost;        
}
