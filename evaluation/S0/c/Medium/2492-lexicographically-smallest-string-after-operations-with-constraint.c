// Source: https://leetcode.com/problems/lexicographically-smallest-string-after-operations-with-constraint/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s and an integer k.
//
// Define a function distance(s1, s2) between two strings s1 and s2 of the same length n as:
//
//
// 	The sum of the minimum distance between s1[i] and s2[i] when the characters from 'a' to 'z' are placed in a cyclic order, for all i in the range [0, n - 1].
//
//
// For example, distance("ab", "cd") == 4, and distance("a", "z") == 1.
//
// You can change any letter of s to any other lowercase English letter, any number of times.
//
// Return a string denoting the lexicographically smallest string t you can get after some changes, such that distance(s, t) <= k.
//
// Example:
// Input: s = "zbbz", k = 3
//
// Output: "aaaz"
//
// Explanation:
//
// Change s to "aaaz". The distance between "zbbz" and "aaaz" is equal to k = 3.
//
// Constraints:
// 1 <= s.length <= 100
// 	0 <= k <= 2000
// 	s consists only of lowercase English letters.
//

char* getSmallestString(char* s, int k) {
    int n = strlen(s);
    char* result = (char*)malloc((n + 1) * sizeof(char));
    result[n] = '\0';

    for (int i = 0; i < n; i++) {
        char current_char = s[i];
        int distance_to_a = current_char - 'a';
        int distance_to_z = 'z' - current_char;

        if (distance_to_a <= distance_to_z) {
            if (k >= distance_to_a) {
                result[i] = 'a';
                k -= distance_to_a;
            } else {
                result[i] = current_char - k;
                k = 0;
            }
        } else {
            if (k >= distance_to_z) {
                result[i] = 'z';
                k -= distance_to_z;
            } else {
                result[i] = current_char + k;
                k = 0;
            }
        }
    }

    return result;      
}
