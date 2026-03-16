// Source: https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s and an integer k, return the length of the longest substring of s such that the frequency of each character in this substring is greater than or equal to k.
//
// if no such substring exists, return 0.
//
// Example:
// Input: s = "aaabb", k = 3
// Output: 3
// Explanation: The longest substring is "aaa", as 'a' is repeated 3 times.
//
// Constraints:
// 1 <= s.length <= 104
// 	s consists of only lowercase English letters.
// 	1 <= k <= 105
//

int longestSubstring(char* s, int k) {
    int maxLen = 0;
    int n = strlen(s);
    
    for (int uniqueTarget = 1; uniqueTarget <= 26; uniqueTarget++) {
        int count[26] = {0};
        int left = 0, right = 0;
        int uniqueCount = 0;
        int countAtLeastK = 0;
        
        while (right < n) {
            if (uniqueCount <= uniqueTarget) {
                int index = s[right] - 'a';
                if (count[index] == 0) uniqueCount++;
                count[index]++;
                if (count[index] == k) countAtLeastK++;
                right++;
            } else {
                int index = s[left] - 'a';
                if (count[index] == k) countAtLeastK--;
                count[index]--;
                if (count[index] == 0) uniqueCount--;
                left++;
            }
            
            if (uniqueCount == uniqueTarget && uniqueCount == countAtLeastK) {
                maxLen = fmax(maxLen, right - left);
            }
        }
    }
    
    return maxLen;      
}
