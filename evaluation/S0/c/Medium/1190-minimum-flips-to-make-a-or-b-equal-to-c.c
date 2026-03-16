// Source: https://leetcode.com/problems/minimum-flips-to-make-a-or-b-equal-to-c/   |   Difficulty: Medium
//
// Problem Description:
// Given 3 positives numbers a, b and c. Return the minimum flips required in some bits of a and b to make ( a OR b == c ). (bitwise OR operation).
// Flip operation consists of change any single bit 1 to 0 or change the bit 0 to 1 in their binary representation.
//
// Example:
// Input: a = 2, b = 6, c = 5
// Output: 3
// Explanation: After flips a = 1 , b = 4 , c = 5 such that (a OR b == c)
//
// Constraints:
// 1 <= a <= 10^9
// 	1 <= b <= 10^9
// 	1 <= c <= 10^9
//



int minFlips(int a, int b, int c){
    int flips = 0;
    for (int i = 0; i < 32; i++) {
        int bitA = (a >> i) & 1;
        int bitB = (b >> i) & 1;
        int bitC = (c >> i) & 1;

        if (bitC == 0) {
            flips += bitA + bitB; // Both bits need to be flipped to 0
        } else {
            if (bitA == 0 && bitB == 0) {
                flips += 1; // At least one bit needs to be flipped to 1
            }
        }
    }
    return flips;
}
