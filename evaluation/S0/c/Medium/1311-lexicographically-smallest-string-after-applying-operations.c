// Source: https://leetcode.com/problems/lexicographically-smallest-string-after-applying-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s of even length consisting of digits from 0 to 9, and two integers a and b.
//
// You can apply either of the following two operations any number of times and in any order on s:
//
//
// 	Add a to all odd indices of s (0-indexed). Digits post 9 are cycled back to 0. For example, if s = "3456" and a = 5, s becomes "3951".
// 	Rotate s to the right by b positions. For example, if s = "3456" and b = 1, s becomes "6345".
//
//
// Return the lexicographically smallest string you can obtain by applying the above operations any number of times on s.
//
// A string a is lexicographically smaller than a string b (of the same length) if in the first position where a and b differ, string a has a letter that appears earlier in the alphabet than the corresponding letter in b. For example, "0158" is lexicographically smaller than "0190" because the first position they differ is at the third letter, and '5' comes before '9'.
//
// Example:
// Input: s = "5525", a = 9, b = 2
// Output: "2050"
// Explanation: We can apply the following operations:
// Start:  "5525"
// Rotate: "2555"
// Add:    "2454"
// Add:    "2353"
// Rotate: "5323"
// Add:    "5222"
// Add:    "5121"
// Rotate: "2151"
// Add:    "2050"​​​​​
// There is no way to obtain a string that is lexicographically smaller than "2050".
//
// Constraints:
// 2 <= s.length <= 100
// 	s.length is even.
// 	s consists of digits from 0 to 9 only.
// 	1 <= a <= 9
// 	1 <= b <= s.length - 1
//

char* findLexSmallestString(char* s, int a, int b) {
    int len = strlen(s);
    char* res = strdup(s);

    for (int rotate = 0; rotate < len; rotate += b) {
        for (int add_odd = 0; add_odd < 10; add_odd++) {
            int add_even_limit = (b % 2 == 0) ? 1 : 10;
            for (int add_even = 0; add_even < add_even_limit; add_even++) {
                char* t = strdup(s);
                // Apply addition to odd indices
                for (int i = 1; i < len; i += 2) {
                    t[i] = ((t[i] - '0' + add_odd * a) % 10) + '0';
                }
                // Apply addition to even indices if needed
                if (add_even_limit == 10) {
                    for (int i = 0; i < len; i += 2) {
                        t[i] = ((t[i] - '0' + add_even * a) % 10) + '0';
                    }
                }
                // Rotate the string
                char* rotated = (char*)malloc((len + 1) * sizeof(char));
                for (int i = 0; i < len; i++) {
                    rotated[i] = t[(i + rotate) % len];
                }
                rotated[len] = '\0';

                // Update result if we found a smaller string
                if (strcmp(rotated, res) < 0) {
                    free(res);
                    res = rotated;
                } else {
                    free(rotated);
                }
                free(t);
            }
        }
    }
    return res;     
}
