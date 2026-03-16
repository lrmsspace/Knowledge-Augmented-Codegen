// Source: https://leetcode.com/problems/find-palindrome-with-fixed-length/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array queries and a positive integer intLength, return an array answer where answer[i] is either the queries[i]th smallest positive palindrome of length intLength or -1 if no such palindrome exists.
//
// A palindrome is a number that reads the same backwards and forwards. Palindromes cannot have leading zeros.
//
// Example:
// Input: queries = [1,2,3,4,5,90], intLength = 3
// Output: [101,111,121,131,141,999]
// Explanation:
// The first few palindromes of length 3 are:
// 101, 111, 121, 131, 141, 151, 161, 171, 181, 191, 202, ...
// The 90th palindrome of length 3 is 999.
//
// Constraints:
// 1 <= queries.length <= 5 * 104
// 	1 <= queries[i] <= 109
// 	1 <= intLength <= 15
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
long long* kthPalindrome(int* queries, int queriesSize, int intLength, int* returnSize) {
    long long* result = (long long*)malloc(sizeof(long long) * queriesSize);
    *returnSize = queriesSize;

    int halfLength = (intLength + 1) / 2;
    long long start = 1;
    for (int i = 1; i < halfLength; i++) {
        start *= 10;
    }
    long long maxCount = 9 * start;

    for (int i = 0; i < queriesSize; i++) {
        long long k = queries[i];
        if (k > maxCount) {
            result[i] = -1;
            continue;
        }

        long long firstHalf = start + k - 1;
        char buffer[20];
        sprintf(buffer, "%lld", firstHalf);

        int len = strlen(buffer);
        if (intLength % 2 == 0) {
            for (int j = len - 1; j >= 0; j--) {
                buffer[len + (len - 1 - j)] = buffer[j];
            }
            buffer[len * 2] = '\0';
        } else {
            for (int j = len - 2; j >= 0; j--) {
                buffer[len + (len - 2 - j)] = buffer[j];
            }
            buffer[len * 2 - 1] = '\0';
        }

        result[i] = atoll(buffer);
    }

    return result;      
}
