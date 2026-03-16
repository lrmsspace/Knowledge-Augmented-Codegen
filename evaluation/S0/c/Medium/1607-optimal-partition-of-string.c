// Source: https://leetcode.com/problems/optimal-partition-of-string/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, partition the string into one or more substrings such that the characters in each substring are unique. That is, no letter appears in a single substring more than once.
//
// Return the minimum number of substrings in such a partition.
//
// Note that each character should belong to exactly one substring in a partition.
//
// Example:
// Input: s = "abacaba"
// Output: 4
// Explanation:
// Two possible partitions are ("a","ba","cab","a") and ("ab","a","ca","ba").
// It can be shown that 4 is the minimum number of substrings needed.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of only English lowercase letters.
//

int partitionString(char* s) {
    int count = 1; // At least one substring is needed
    int seen[26] = {0}; // Array to track seen characters

    for (int i = 0; s[i] != '\0'; i++) {
        int index = s[i] - 'a'; // Calculate index for the character

        if (seen[index]) {
            // Character already seen in current substring, start a new substring
            count++;
            // Reset seen array for new substring
            for (int j = 0; j < 26; j++) {
                seen[j] = 0;
            }
        }

        // Mark the character as seen in the current substring
        seen[index] = 1;
    }

    return count;       
}
