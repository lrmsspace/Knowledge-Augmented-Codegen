// Source: https://leetcode.com/problems/number-of-ways-to-divide-a-long-corridor/   |   Difficulty: Hard
//
// Problem Description:
// Along a long library corridor, there is a line of seats and decorative plants. You are given a 0-indexed string corridor of length n consisting of letters 'S' and 'P' where each 'S' represents a seat and each 'P' represents a plant.
//
// One room divider has already been installed to the left of index 0, and another to the right of index n - 1. Additional room dividers can be installed. For each position between indices i - 1 and i (1 <= i <= n - 1), at most one divider can be installed.
//
// Divide the corridor into non-overlapping sections, where each section has exactly two seats with any number of plants. There may be multiple ways to perform the division. Two ways are different if there is a position with a room divider installed in the first way but not in the second way.
//
// Return the number of ways to divide the corridor. Since the answer may be very large, return it modulo 109 + 7. If there is no way, return 0.
//
// Example:
// Input: corridor = "SSPPSPS"
// Output: 3
// Explanation: There are 3 different ways to divide the corridor.
// The black bars in the above image indicate the two room dividers already installed.
// Note that in each of the ways, each section has exactly two seats.
//
// Constraints:
// n == corridor.length
// 	1 <= n <= 105
// 	corridor[i] is either 'S' or 'P'.
//

class Solution {
public:
    int numberOfWays(string corridor) {
        const int MOD = 1e9 + 7;
        long long seatCount = 0;
        long long ways = 1;
        long long plantCount = 0;
        
        for (char c : corridor) {
            if (c == 'S') {
                seatCount++;
                if (seatCount % 2 == 0) {
                    // Completed a pair of seats
                    if (plantCount > 0) {
                        ways = (ways * (plantCount + 1)) % MOD;
                    }
                    plantCount = 0;  // Reset plant count for next section
                }
            } else if (c == 'P') {
                if (seatCount % 2 == 1) {
                    // Count plants only between pairs of seats
                    plantCount++;
                }
            }
        }
        
        // If total seats is not even, return 0
        if (seatCount % 2 != 0) {
            return 0;
        }
        
        return (seatCount == 0) ? 0 : ways;         
    }
};
