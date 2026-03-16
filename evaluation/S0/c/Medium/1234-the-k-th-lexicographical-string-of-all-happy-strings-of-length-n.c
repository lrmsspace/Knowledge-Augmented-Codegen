// Source: https://leetcode.com/problems/the-k-th-lexicographical-string-of-all-happy-strings-of-length-n/   |   Difficulty: Medium
//
// Problem Description:
// A happy string is a string that:
//
//
// 	consists only of letters of the set ['a', 'b', 'c'].
// 	s[i] != s[i + 1] for all values of i from 1 to s.length - 1 (string is 1-indexed).
//
//
// For example, strings "abc", "ac", "b" and "abcbabcbcb" are all happy strings and strings "aa", "baa" and "ababbc" are not happy strings.
//
// Given two integers n and k, consider a list of all happy strings of length n sorted in lexicographical order.
//
// Return the kth string of this list or return an empty string if there are less than k happy strings of length n.
//
// Example:
// Input: n = 1, k = 3
// Output: "c"
// Explanation: The list ["a", "b", "c"] contains all happy strings of length 1. The third string is "c".
//
// Constraints:
// 1 <= n <= 10
// 	1 <= k <= 100
//

char* getHappyString(int n, int k) {
    int total = 3 << (n - 1);
    if (k > total) {
        return "";
    }

    char *res = (char *)malloc((n + 1) * sizeof(char));
    res[n] = '\0';

    k -= 1; // convert to 0-based index
    int firstCharIndex = k / (1 << (n - 1));
    res[0] = 'a' + firstCharIndex;

    int prevCharIndex = firstCharIndex;
    for (int i = 1; i < n; i++) {
        int blockSize = 1 << (n - 1 - i);
        int indexInBlock = (k / blockSize) % 2;
        int nextCharIndex = (prevCharIndex + 1 + indexInBlock) % 3;
        res[i] = 'a' + nextCharIndex;
        prevCharIndex = nextCharIndex;
    }

    return res;     
}
