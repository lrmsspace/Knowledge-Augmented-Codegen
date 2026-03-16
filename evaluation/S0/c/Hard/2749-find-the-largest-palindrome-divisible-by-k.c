// Source: https://leetcode.com/problems/find-the-largest-palindrome-divisible-by-k/   |   Difficulty: Hard
//
// Problem Description:
// You are given two positive integers n and k.
//
// An integer x is called k-palindromic if:
//
//
// 	x is a palindrome.
// 	x is divisible by k.
//
//
// Return the largest integer having n digits (as a string) that is k-palindromic.
//
// Note that the integer must not have leading zeros.
//
// Example:
// Input: n = 3, k = 5
//
// Output: "595"
//
// Explanation:
//
// 595 is the largest k-palindromic integer with 3 digits.
//
// Constraints:
// 1 <= n <= 105
// 	1 <= k <= 9
//

char* largestPalindrome(int n, int k) {
    if (n == 1) {
        for (int d = 9; d >= 1; d--) {
            if (d % k == 0) {
                char *res = (char*)malloc(2 * sizeof(char));
                res[0] = (char)('0' + d);
                res[1] = '\0';
                return res;
            }
        }
        return "-1";
    }

    int halfLen = (n + 1) / 2;
    char *half = (char*)malloc((halfLen + 1) * sizeof(char));
    if (!half) return "-1";
    for (int i = 0; i < halfLen; i++) {
        half[i] = '9';
    }
    half[halfLen] = '\0';

    long long halfNum = atoll(half);
    free(half);

    while (halfNum >= (long long)pow(10, halfLen - 1)) {
        char halfStr[halfLen + 1];
        snprintf(halfStr, sizeof(halfStr), "%lld", halfNum);

        char *palindrome = (char*)malloc((n + 1) * sizeof(char));
        if (!palindrome) return "-1";

        strcpy(palindrome, halfStr);
        int idx = halfLen;
        for (int i = n % 2 == 0 ? halfLen - 1 : halfLen - 2; i >= 0; i--) {
            palindrome[idx++] = halfStr[i];
        }
        palindrome[n] = '\0';

        long long palNum = atoll(palindrome);
        if (palNum % k == 0) {
            return palindrome;
        }
        free(palindrome);
        halfNum--;
    }

    return "-1";        
}
