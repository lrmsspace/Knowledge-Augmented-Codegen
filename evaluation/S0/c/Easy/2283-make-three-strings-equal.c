// Source: https://leetcode.com/problems/make-three-strings-equal/   |   Difficulty: Easy
//
// Problem Description:
// You are given three strings: s1, s2, and s3. In one operation you can choose one of these strings and delete its rightmost character. Note that you cannot completely empty a string.
//
// Return the minimum number of operations required to make the strings equal. If it is impossible to make them equal, return -1.
//
// Example:
// Input: s1 = "abc", s2 = "abb", s3 = "ab"
//
// Output: 2
//
// Explanation: Deleting the rightmost character from both s1 and s2 will result in three equal strings.
//
// Constraints:
// 1 <= s1.length, s2.length, s3.length <= 100
// 	s1, s2 and s3 consist only of lowercase English letters.
//

int findMinimumOperations(char* s1, char* s2, char* s3) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int len3 = strlen(s3);
    int i = len1 - 1;
    int j = len2 - 1;
    int k = len3 - 1;
    int commonLength = 0;

    while (i >= 0 && j >= 0 && k >= 0 && s1[i] == s2[j] && s2[j] == s3[k]) {
        commonLength++;
        i--;
        j--;
        k--;
    }

    if (commonLength == 0) {
        return -1;
    }

    return (len1 - commonLength) + (len2 - commonLength) + (len3 - commonLength);       
}
