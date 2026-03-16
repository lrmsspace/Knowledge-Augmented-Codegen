// Source: https://leetcode.com/problems/check-if-string-is-transformable-with-substring-sort-operations/   |   Difficulty: Hard
//
// Problem Description:
// Given two strings s and t, transform string s into string t using the following operation any number of times:
//
//
// 	Choose a non-empty substring in s and sort it in place so the characters are in ascending order.
//
// 	
// 		For example, applying the operation on the underlined substring in "14234" results in "12344".
// 	
// 	
//
//
// Return true if it is possible to transform s into t. Otherwise, return false.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "84532", t = "34852"
// Output: true
// Explanation: You can transform s into t using the following sort operations:
// "84532" (from index 2 to 3) -> "84352"
// "84352" (from index 0 to 2) -> "34852"
//
// Constraints:
// s.length == t.length
// 	1 <= s.length <= 105
// 	s and t consist of only digits.
//

bool isTransformable(char* s, char* t) {
    int count[10] = {0};
    int len = strlen(s);
    for (int i = 0; i < len; ++i) {
        count[s[i] - '0']++;
        count[t[i] - '0']--;
    }
    for (int i = 0; i < 10; ++i) {
        if (count[i] != 0) return false;
    }
    int pos[10][len];
    int posCount[10];
    memset(posCount, 0, sizeof(posCount));
    for (int i = 0; i < len; ++i) {
        int digit = s[i] - '0';
        pos[digit][posCount[digit]++] = i;
    }
    for (int i = 0; i < 10; ++i) {
        posCount[i] = 0;
    }
    for (int i = 0; i < len; ++i) {
        int digit = t[i] - '0';
        int sIndex = pos[digit][posCount[digit]++];
        for (int d = 0; d < digit; ++d) {
            if (posCount[d] < count[d]) {
                int otherIndex = pos[d][posCount[d]];
                if (otherIndex < sIndex) {
                    return false;
                }
            }
        }
    }
    return true;        
}
