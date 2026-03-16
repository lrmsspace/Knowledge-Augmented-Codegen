// Source: https://leetcode.com/problems/minimum-penalty-for-a-shop/   |   Difficulty: Medium
//
// Problem Description:
// You are given the customer visit log of a shop represented by a 0-indexed string customers consisting only of characters 'N' and 'Y':
//
//
// 	if the ith character is 'Y', it means that customers come at the ith hour
// 	whereas 'N' indicates that no customers come at the ith hour.
//
//
// If the shop closes at the jth hour (0 <= j <= n), the penalty is calculated as follows:
//
//
// 	For every hour when the shop is open and no customers come, the penalty increases by 1.
// 	For every hour when the shop is closed and customers come, the penalty increases by 1.
//
//
// Return the earliest hour at which the shop must be closed to incur a minimum penalty.
//
// Note that if a shop closes at the jth hour, it means the shop is closed at the hour j.
//
// Example:
// Input: customers = "YYNY"
// Output: 2
// Explanation: 
// - Closing the shop at the 0th hour incurs in 1+1+0+1 = 3 penalty.
// - Closing the shop at the 1st hour incurs in 0+1+0+1 = 2 penalty.
// - Closing the shop at the 2nd hour incurs in 0+0+0+1 = 1 penalty.
// - Closing the shop at the 3rd hour incurs in 0+0+1+1 = 2 penalty.
// - Closing the shop at the 4th hour incurs in 0+0+1+0 = 1 penalty.
// Closing the shop at 2nd or 4th hour gives a minimum penalty. Since 2 is earlier, the optimal closing time is 2.
//
// Constraints:
// 1 <= customers.length <= 105
// 	customers consists only of characters 'Y' and 'N'.
//

class Solution {
public:
    int bestClosingTime(string customers) {
        int n = customers.size();
        vector<int> prefixY(n + 1, 0); // Number of 'Y's from start to i-1
        vector<int> suffixN(n + 1, 0); // Number of 'N's from i to end

        for (int i = 1; i <= n; ++i) {
            prefixY[i] = prefixY[i - 1] + (customers[i - 1] == 'Y' ? 1 : 0);
        }

        for (int i = n - 1; i >= 0; --i) {
            suffixN[i] = suffixN[i + 1] + (customers[i] == 'N' ? 1 : 0);
        }

        int minPenalty = INT_MAX;
        int bestHour = 0;

        for (int j = 0; j <= n; ++j) {
            int penalty = prefixY[j] + suffixN[j];
            if (penalty < minPenalty) {
                minPenalty = penalty;
                bestHour = j;
            }
        }

        return bestHour;            
    }
};
