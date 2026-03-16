// Source: https://leetcode.com/problems/find-mirror-score-of-a-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s.
//
// We define the mirror of a letter in the English alphabet as its corresponding letter when the alphabet is reversed. For example, the mirror of 'a' is 'z', and the mirror of 'y' is 'b'.
//
// Initially, all characters in the string s are unmarked.
//
// You start with a score of 0, and you perform the following process on the string s:
//
//
// 	Iterate through the string from left to right.
// 	At each index i, find the closest unmarked index j such that j < i and s[j] is the mirror of s[i]. Then, mark both indices i and j, and add the value i - j to the total score.
// 	If no such index j exists for the index i, move on to the next index without making any changes.
//
//
// Return the total score at the end of the process.
//
// Example:
// Input: s = "aczzx"
//
// Output: 5
//
// Explanation:
//
//
// 	i = 0. There is no index j that satisfies the conditions, so we skip.
// 	i = 1. There is no index j that satisfies the conditions, so we skip.
// 	i = 2. The closest index j that satisfies the conditions is j = 0, so we mark both indices 0 and 2, and then add 2 - 0 = 2 to the score.
// 	i = 3. There is no index j that satisfies the conditions, so we skip.
// 	i = 4. The closest index j that satisfies the conditions is j = 1, so we mark both indices 1 and 4, and then add 4 - 1 = 3 to the score.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists only of lowercase English letters.
//

long long calculateScore(char* s) {
    int n = 0;
    while (s[n]) n++;

    int stack[26][n];
    int stack_size[26];
    for (int i = 0; i < 26; i++) {
        stack_size[i] = 0;
    }

    long long score = 0;

    for (int i = 0; i < n; i++) {
        int ch_index = s[i] - 'a';
        int mirror_index = 25 - ch_index;

        if (stack_size[mirror_index] > 0) {
            // Found a mirror character
            int j = stack[mirror_index][--stack_size[mirror_index]];
            score += (i - j);
        } else {
            // Push current index onto the stack
            stack[ch_index][stack_size[ch_index]++] = i;
        }
    }

    return score;       
}
