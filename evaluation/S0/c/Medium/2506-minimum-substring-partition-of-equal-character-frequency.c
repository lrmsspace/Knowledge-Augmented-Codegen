// Source: https://leetcode.com/problems/minimum-substring-partition-of-equal-character-frequency/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, you need to partition it into one or more balanced substrings. For example, if s == "ababcc" then ("abab", "c", "c"), ("ab", "abc", "c"), and ("ababcc") are all valid partitions, but ("a", "bab", "cc"), ("aba", "bc", "c"), and ("ab", "abcc") are not. The unbalanced substrings are bolded.
//
// Return the minimum number of substrings that you can partition s into.
//
// Note: A balanced string is a string where each character in the string occurs the same number of times.
//
// Example:
// Input: s = "fabccddg"
//
// Output: 3
//
// Explanation:
//
// We can partition the string s into 3 substrings in one of the following ways: ("fab, "ccdd", "g"), or ("fabc", "cd", "dg").
//
// Constraints:
// 1 <= s.length <= 1000
// 	s consists only of English lowercase letters.
//

int minimumSubstringsInPartition(char* s) {
    int n = strlen(s);
    int count[26] = {0};
    for (int i = 0; i < n; i++) {
        count[s[i] - 'a']++;
    }

    int result = 0;
    int currentCount[26] = {0};
    for (int i = 0; i < n; i++) {
        currentCount[s[i] - 'a']++;
        int balanced = 1;
        for (int j = 0; j < 26; j++) {
            if (currentCount[j] != 0 && currentCount[j] != count[j]) {
                balanced = 0;
                break;
            }
        }
        if (balanced) {
            result++;
            memset(currentCount, 0, sizeof(currentCount));
        }
    }

    return result;      
}
