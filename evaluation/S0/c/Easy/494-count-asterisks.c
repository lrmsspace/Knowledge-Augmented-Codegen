// Source: https://leetcode.com/problems/count-asterisks/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s, where every two consecutive vertical bars '|' are grouped into a pair. In other words, the 1st and 2nd '|' make a pair, the 3rd and 4th '|' make a pair, and so forth.
//
// Return the number of '*' in s, excluding the '*' between each pair of '|'.
//
// Note that each '|' will belong to exactly one pair.
//
// Example:
// Input: s = "l|*e*et|c**o|*de|"
// Output: 2
// Explanation: The considered characters are underlined: "l|*e*et|c**o|*de|".
// The characters between the first and second '|' are excluded from the answer.
// Also, the characters between the third and fourth '|' are excluded from the answer.
// There are 2 asterisks considered. Therefore, we return 2.
//
// Constraints:
// 1 <= s.length <= 1000
// 	s consists of lowercase English letters, vertical bars '|', and asterisks '*'.
// 	s contains an even number of vertical bars '|'.
//

int countAsterisks(char* s) {
    int count = 0;
    int inBar = 0; // Flag to indicate if we are between '|'

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '|') {
            inBar = !inBar; // Toggle the inBar flag
        } else if (s[i] == '*' && !inBar) {
            count++; // Count '*' only if not between '|'
        }
    }

    return count;       
}
