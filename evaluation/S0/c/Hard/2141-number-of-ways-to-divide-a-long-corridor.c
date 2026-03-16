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

int numberOfWays(char* corridor) {
    const int MOD = 1000000007;
    int seatCount = 0;
    int n = strlen(corridor);
    for (int i = 0; i < n; ++i) {
        if (corridor[i] == 'S') {
            seatCount++;
        }
    }
    if (seatCount == 0 || seatCount % 2 != 0) {
        return 0;
    }
    if (seatCount == 2) {
        return 1;
    }

    long long result = 1;
    int seatsSeen = 0;
    int plantsBetween = 0;
    for (int i = 0; i < n; ++i) {
        if (corridor[i] == 'S') {
            seatsSeen++;
            if (seatsSeen % 2 == 0 && seatsSeen < seatCount) {
                result = (result * (plantsBetween + 1)) % MOD;
                plantsBetween = 0;
            }
        } else if (seatsSeen % 2 == 1) {
            plantsBetween++;
        }
    }
    return (int)result;     
}
