// Source: https://leetcode.com/problems/repeated-string-match/   |   Difficulty: Medium
//
// Problem Description:
// Given two strings a and b, return the minimum number of times you should repeat string a so that string b is a substring of it. If it is impossible for b​​​​​​ to be a substring of a after repeating it, return -1.
//
// Notice: string "abc" repeated 0 times is "", repeated 1 time is "abc" and repeated 2 times is "abcabc".
//
// Example:
// Input: a = "abcd", b = "cdabcdab"
// Output: 3
// Explanation: We return 3 because by repeating a three times "abcdabcdabcd", b is a substring of it.
//
// Constraints:
// 1 <= a.length, b.length <= 104
// 	a and b consist of lowercase English letters.
//

int repeatedStringMatch(char* a, char* b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    int count = (len_b + len_a - 1) / len_a; // Minimum repeats needed

    // Create a new string by repeating 'a' count times
    char* repeated = (char*)malloc((len_a * (count + 2) + 1) * sizeof(char));
    repeated[0] = '\0';
    for (int i = 0; i < count; i++) {
        strcat(repeated, a);
    }

    // Check if 'b' is a substring of the repeated string
    if (strstr(repeated, b) != NULL) {
        free(repeated);
        return count;
    }

    // Add one more repetition of 'a' and check again
    strcat(repeated, a);
    if (strstr(repeated, b) != NULL) {
        free(repeated);
        return count + 1;
    }

    free(repeated);
    return -1;      
}
