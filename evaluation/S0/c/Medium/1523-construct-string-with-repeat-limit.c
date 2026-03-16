// Source: https://leetcode.com/problems/construct-string-with-repeat-limit/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s and an integer repeatLimit. Construct a new string repeatLimitedString using the characters of s such that no letter appears more than repeatLimit times in a row. You do not have to use all characters from s.
//
// Return the lexicographically largest repeatLimitedString possible.
//
// A string a is lexicographically larger than a string b if in the first position where a and b differ, string a has a letter that appears later in the alphabet than the corresponding letter in b. If the first min(a.length, b.length) characters do not differ, then the longer string is the lexicographically larger one.
//
// Example:
// Input: s = "cczazcc", repeatLimit = 3
// Output: "zzcccac"
// Explanation: We use all of the characters from s to construct the repeatLimitedString "zzcccac".
// The letter 'a' appears at most 1 time in a row.
// The letter 'c' appears at most 3 times in a row.
// The letter 'z' appears at most 2 times in a row.
// Hence, no letter appears more than repeatLimit times in a row and the string is a valid repeatLimitedString.
// The string is the lexicographically largest repeatLimitedString possible so we return "zzcccac".
// Note that the string "zzcccca" is lexicographically larger but the letter 'c' appears more than 3 times in a row, so it is not a valid repeatLimitedString.
//
// Constraints:
// 1 <= repeatLimit <= s.length <= 105
// 	s consists of lowercase English letters.
//

char* repeatLimitedString(char* s, int repeatLimit) {
    int count[26] = {0};
    for (char *p = s; *p; ++p) {
        count[*p - 'a']++;
    }

    char *result = (char *)malloc((strlen(s) + 1) * sizeof(char));
    int pos = 0;

    while (1) {
        int i;
        for (i = 25; i >= 0; --i) {
            if (count[i] > 0) {
                break;
            }
        }
        if (i < 0) {
            break;
        }

        int use = (count[i] > repeatLimit) ? repeatLimit : count[i];
        for (int j = 0; j < use; ++j) {
            result[pos++] = 'a' + i;
        }
        count[i] -= use;

        if (count[i] > 0) {
            int k;
            for (k = i - 1; k >= 0; --k) {
                if (count[k] > 0) {
                    break;
                }
            }
            if (k < 0) {
                break;
            }
            result[pos++] = 'a' + k;
            count[k]--;
        }
    }

    result[pos] = '\0';
    return result;      
}
