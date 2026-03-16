// Source: https://leetcode.com/problems/longest-repeating-character-replacement/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s and an integer k. You can choose any character of the string and change it to any other uppercase English character. You can perform this operation at most k times.
//
// Return the length of the longest substring containing the same letter you can get after performing the above operations.
//
// Example:
// Input: s = "ABAB", k = 2
// Output: 4
// Explanation: Replace the two 'A's with two 'B's or vice versa.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of only uppercase English letters.
// 	0 <= k <= s.length
//

int characterReplacement(char* s, int k) {
    int count[26] = {0};
    int maxCount = 0;
    int left = 0;
    int result = 0;
    
    for (int right = 0; s[right] != '\0'; right++) {
        count[s[right] - 'A']++;
        maxCount = fmax(maxCount, count[s[right] - 'A']);
        
        while (right - left + 1 - maxCount > k) {
            count[s[left] - 'A']--;
            left++;
        }
        
        result = fmax(result, right - left + 1);
    }
    
    return result;      
}
