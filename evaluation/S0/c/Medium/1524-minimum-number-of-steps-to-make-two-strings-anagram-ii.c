// Source: https://leetcode.com/problems/minimum-number-of-steps-to-make-two-strings-anagram-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings s and t. In one step, you can append any character to either s or t.
//
// Return the minimum number of steps to make s and t anagrams of each other.
//
// An anagram of a string is a string that contains the same characters with a different (or the same) ordering.
//
// Example:
// Input: s = "leetcode", t = "coats"
// Output: 7
// Explanation: 
// - In 2 steps, we can append the letters in "as" onto s = "leetcode", forming s = "leetcodeas".
// - In 5 steps, we can append the letters in "leede" onto t = "coats", forming t = "coatsleede".
// "leetcodeas" and "coatsleede" are now anagrams of each other.
// We used a total of 2 + 5 = 7 steps.
// It can be shown that there is no way to make them anagrams of each other with less than 7 steps.
//
// Constraints:
// 1 <= s.length, t.length <= 2 * 105
// 	s and t consist of lowercase English letters.
//

int minSteps(char* s, char* t) {
    int count[26] = {0};
    int steps = 0;
    
    for (int i = 0; s[i] != '\0'; i++) {
        count[s[i] - 'a']++;
    }
    
    for (int i = 0; t[i] != '\0'; i++) {
        count[t[i] - 'a']--;
    }
    
    for (int i = 0; i < 26; i++) {
        if (count[i] > 0) {
            steps += count[i];
        }
    }
    
    return steps;       
}
