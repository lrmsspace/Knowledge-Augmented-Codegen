// Source: https://leetcode.com/problems/maximum-product-of-the-length-of-two-palindromic-substrings/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed string s and are tasked with finding two non-intersecting palindromic substrings of odd length such that the product of their lengths is maximized.
//
// More formally, you want to choose four integers i, j, k, l such that 0 <= i <= j < k <= l < s.length and both the substrings s[i...j] and s[k...l] are palindromes and have odd lengths. s[i...j] denotes a substring from index i to index j inclusive.
//
// Return the maximum possible product of the lengths of the two non-intersecting palindromic substrings.
//
// A palindrome is a string that is the same forward and backward. A substring is a contiguous sequence of characters in a string.
//
// Example:
// Input: s = "ababbb"
// Output: 9
// Explanation: Substrings "aba" and "bbb" are palindromes with odd length. product = 3 * 3 = 9.
//
// Constraints:
// 2 <= s.length <= 105
// 	s consists of lowercase English letters.
//

long long maxProduct(char* s) {
    int n = strlen(s);
    int *d1 = (int*)calloc(n, sizeof(int));
    if (!d1) return 0; // allocation
    // Manacher's algorithm to find all odd-length palindromes
    int l = 0, r = -1;
    for (int i = 0; i < n; i++) {
        int k = (i > r) ? 1 : fmin(d1[l + r - i], r - i + 1);
        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) {
            k++;
        }
        d1[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
    // Precompute max palindrome lengths from left and right
    int *maxLeft = (int*)calloc(n, sizeof(int));
    int *maxRight = (int*)calloc(n, sizeof(int));
    if (!maxLeft || !maxRight) {
        free(d1);
        free(maxLeft);
        free(maxRight);
        return 0; // allocation
    }
    for (int i = 0; i < n; i++) {
        int len = 2 * d1[i] - 1;
        int start = i - (len - 1) / 2;
        int end = i + (len - 1) / 2;
        if (start == 0 || (start > 0 && maxLeft[start - 1] < len)) {
            maxLeft[end] = len;
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        int len = 2 * d1[i] - 1;
        int start = i - (len - 1) / 2;
        int end = i + (len - 1) / 2;
        if (end == n - 1 || (end < n - 1 && maxRight[end + 1] < len)) {
            maxRight[start] = len;
        }
    }
    // Fill maxLeft and maxRight to have max palindrome lengths up to each index
    for (int i = 1; i < n; i++) {           
        if (maxLeft[i] < maxLeft[i - 1]) {
            maxLeft[i] = maxLeft[i - 1];
        }

    for (int i = n - 2; i >= 0; i--) {
        if (maxRight[i] < maxRight[i + 1]) {
            maxRight[i] = maxRight[i + 1];
        }
    }
    // Calculate maximum product
    long long maxProduct = 0;
    for (int i = 0; i < n - 1; i++) {
        long long product = (long long)maxLeft[i] * (long long)maxRight[i + 1];
        if (product > maxProduct) {
            maxProduct = product;
        }
    }
    free(d1);
    free(maxLeft);
    free(maxRight);
    return maxProduct;
}
