// Source: https://leetcode.com/problems/smallest-good-base/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer n represented as a string, return the smallest good base of n.
//
// We call k >= 2 a good base of n, if all digits of n base k are 1's.
//
// Example:
// Input: n = "13"
// Output: "3"
// Explanation: 13 base 3 is 111.
//
// Constraints:
// n is an integer in the range [3, 1018].
// 	n does not contain any leading zeros.
//

char* smallestGoodBase(char* n) {
    unsigned long long num = strtoull(n, NULL, 10);
    for (int m = 63; m >= 2; m--) {
        unsigned long long left = 2, right = num - 1;
        while (left <= right) {
            unsigned long long mid = left + (right - left) / 2;
            unsigned long long sum = 1, curr = 1;
            for (int i = 1; i < m; i++) {
                if (curr > (num - sum) / mid) { // prevent overflow
                    sum = num + 1; // exceed num
                    break;
                }
                curr *= mid;
                sum += curr;
            }
            if (sum == num) {
                char *res = (char*)malloc(22 * sizeof(char));
                sprintf(res, "%llu", mid);
                return res;
            } else if (sum < num) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    // fallback to base (num - 1)
    char *res = (char*)malloc(22 * sizeof(char));
    sprintf(res, "%llu", num - 1);
    return res;     
}
