// Source: https://leetcode.com/problems/shortest-string-that-contains-three-strings/   |   Difficulty: Medium
//
// Problem Description:
// Given three strings a, b, and c, your task is to find a string that has the minimum length and contains all three strings as substrings.
// If there are multiple such strings, return the lexicographically smallest one.
//
// Return a string denoting the answer to the problem.
//
// Notes
//
//
// 	A string a is lexicographically smaller than a string b (of the same length) if in the first position where a and b differ, string a has a letter that appears earlier in the alphabet than the corresponding letter in b.
// 	A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: a = "abc", b = "bca", c = "aaa"
// Output: "aaabca"
// Explanation:  We show that "aaabca" contains all the given strings: a = ans[2...4], b = ans[3..5], c = ans[0..2]. It can be shown that the length of the resulting string would be at least 6 and "aaabca" is the lexicographically smallest one.
//
// Constraints:
// 1 <= a.length, b.length, c.length <= 100
// 	a, b, c consist only of lowercase English letters.
//

char* minimumString(char* a, char* b, char* c) {
    #define MAX_LEN 301
    #define MIN(a, b) ((a) < (b) ? (a) : (b))
    #define STRCMP(a, b) (strcmp(a, b) < 0 ? a : b)

    int overlap(char* s1, char* s2) {
        int len1 = strlen(s1);
        int len2 = strlen(s2);
        for (int i = MIN(len1, len2); i >= 0; i--) {
            if (strncmp(s1 + len1 - i, s2, i) == 0) {
                return i;
            }
        }
        return 0;
    }

    void merge(char* dest, char* s1, char* s2) {
        int ov = overlap(s1, s2);
        strcpy(dest, s1);
        strcat(dest, s2 + ov);
    }

    char* result = NULL;
    char buffer[MAX_LEN];

    char* strings[3] = {a, b, c};
    int perm[6][3] = {
        {0, 1, 2}, {0, 2, 1},
        {1, 0, 2}, {1, 2, 0},
        {2, 0, 1}, {2, 1, 0}
    };

    for (int i = 0; i < 6; i++) {
        char temp1[MAX_LEN], temp2[MAX_LEN];
        merge(temp1, strings[perm[i][0]], strings[perm[i][1]]);
        merge(temp2, temp1, strings[perm[i][2]]);

        if (result == NULL || strlen(temp2) < strlen(result) ||
            (strlen(temp2) == strlen(result) && strcmp(temp2, result) < 0)) {
            if (result != NULL) {
                free(result);
            }
            result = strdup(temp2);
        }
    }

    return result;      
}
