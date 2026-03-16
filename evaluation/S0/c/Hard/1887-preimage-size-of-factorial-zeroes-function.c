// Source: https://leetcode.com/problems/preimage-size-of-factorial-zeroes-function/   |   Difficulty: Hard
//
// Problem Description:
// Let f(x) be the number of zeroes at the end of x!. Recall that x! = 1 * 2 * 3 * ... * x and by convention, 0! = 1.
//
//
// 	For example, f(3) = 0 because 3! = 6 has no zeroes at the end, while f(11) = 2 because 11! = 39916800 has two zeroes at the end.
//
//
// Given an integer k, return the number of non-negative integers x have the property that f(x) = k.
//
// Example:
// Input: k = 0
// Output: 5
// Explanation: 0!, 1!, 2!, 3!, and 4! end with k = 0 zeroes.
//
// Constraints:
// 0 <= k <= 109
//

int preimageSizeFZF(int k) {
    long long left = 0, right = 5LL * (k + 1);
    while (left < right) {
        long long mid = left + (right - left) / 2;
        long long count = 0, div = 5;
        while (mid / div > 0) {
            count += mid / div;
            div *= 5;
        }
        if (count < k) left = mid + 1;
        else right = mid;
    }
    long long first = left;
    left = 0; right = 5LL * (k + 1);
    while (left < right) {
        long long mid = left + (right - left) / 2;
        long long count = 0, div = 5;
        while (mid / div > 0) {
            count += mid / div;
            div *= 5;
        }
        if (count <= k) left = mid + 1;
        else right = mid;
    }
    long long last = left;
    return (int)(last - first);     
}
