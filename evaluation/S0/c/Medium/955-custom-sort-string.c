// Source: https://leetcode.com/problems/custom-sort-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings order and s. All the characters of order are unique and were sorted in some custom order previously.
//
// Permute the characters of s so that they match the order that order was sorted. More specifically, if a character x occurs before a character y in order, then x should occur before y in the permuted string.
//
// Return any permutation of s that satisfies this property.
//
// Example:
// Input:   order = "cba", s = "abcd" 
//
// Output:   "cbad" 
//
// Explanation:  "a", "b", "c" appear in order, so the order of "a", "b", "c" should be "c", "b", and "a".
//
// Since "d" does not appear in order, it can be at any position in the returned string. "dcba", "cdba", "cbda" are also valid outputs.
//
// Constraints:
// 1 <= order.length <= 26
// 	1 <= s.length <= 200
// 	order and s consist of lowercase English letters.
// 	All the characters of order are unique.
//

char* customSortString(char* order, char* s) {
    int order_map[26] = {0};
    for (int i = 0; order[i] != '\0'; i++) {
        order_map[order[i] - 'a'] = i + 1; // Store the index + 1 to differentiate from default 0
    }

    int s_len = 0;
    while (s[s_len] != '\0') {
        s_len++;
    }

    // Simple bubble sort based on custom order
    for (int i = 0; i < s_len - 1; i++) {
        for (int j = 0; j < s_len - i - 1; j++) {
            int order_j = order_map[s[j] - 'a'];
            int order_j1 = order_map[s[j + 1] - 'a'];
            if (order_j > order_j1) {
                // Swap characters
                char temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }

    return s;       
}
