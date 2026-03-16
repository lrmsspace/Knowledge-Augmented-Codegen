// Source: https://leetcode.com/problems/reordered-power-of-2/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n. We reorder the digits in any order (including the original order) such that the leading digit is not zero.
//
// Return true if and only if we can do this so that the resulting number is a power of two.
//
// Example:
// Input: n = 1
// Output: true
//
// Constraints:
// 1 <= n <= 109
//

bool reorderedPowerOf2(int n) {
    int count[10] = {0};
    while (n) {
        count[n % 10]++;
        n /= 10;
    }

    for (int i = 0; i < 31; i++) {
        int powerOf2 = 1 << i;
        int tempCount[10] = {0};
        while (powerOf2) {
            tempCount[powerOf2 % 10]++;
            powerOf2 /= 10;
        }
        int j;
        for (j = 0; j < 10; j++) {
            if (count[j] != tempCount[j]) {
                break;
            }
        }
        if (j == 10) {
            return true;
        }
    }
    return false;       
}
