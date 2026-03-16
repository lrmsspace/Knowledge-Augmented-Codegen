// Source: https://leetcode.com/problems/minimum-operations-to-reduce-an-integer-to-0/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer n, you can do the following operation any number of times:
//
//
// 	Add or subtract a power of 2 from n.
//
//
// Return the minimum number of operations to make n equal to 0.
//
// A number x is power of 2 if x == 2i where i >= 0.
//
// Example:
// Input: n = 39
// Output: 3
// Explanation: We can do the following operations:
// - Add 20 = 1 to n, so now n = 40.
// - Subtract 23 = 8 from n, so now n = 32.
// - Subtract 25 = 32 from n, so now n = 0.
// It can be shown that 3 is the minimum number of operations we need to make n equal to 0.
//
// Constraints:
// 1 <= n <= 105
//

int minOperations(int n) {
    int operations = 0;
    while (n > 0) {
        // Check if the least significant bit is 1
        if (n & 1) {
            // If the next bit is also 1, we can add 1 to make a carry
            if ((n & 2) && (n != 3)) {
                n += 1; // This effectively adds a power of 2
            } else {
                n -= 1; // Subtracting the least significant power of 2
            }
            operations++;
        }
        n >>= 1; // Right shift to process the next bit
    }
    return operations;      
}
