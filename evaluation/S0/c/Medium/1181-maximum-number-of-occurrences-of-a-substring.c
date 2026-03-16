// Source: https://leetcode.com/problems/maximum-number-of-occurrences-of-a-substring/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, return the maximum number of occurrences of any substring under the following rules:
//
//
// 	The number of unique characters in the substring must be less than or equal to maxLetters.
// 	The substring size must be between minSize and maxSize inclusive.
//
// Example:
// Input: s = "aababcaab", maxLetters = 2, minSize = 3, maxSize = 4
// Output: 2
// Explanation: Substring "aab" has 2 occurrences in the original string.
// It satisfies the conditions, 2 unique letters and size 3 (between minSize and maxSize).
//
// Constraints:
// 1 <= s.length <= 105
// 	1 <= maxLetters <= 26
// 	1 <= minSize <= maxSize <= min(26, s.length)
// 	s consists of only lowercase English letters.
//

int maxFreq(char* s, int maxLetters, int minSize, int maxSize) {
    int len = strlen(s);
    int maxCount = 0;
    int freqMap[26] = {0};
    int substringCountMap[100000] = {0};
    
    for (int i = 0; i <= len - minSize; i++) {
        int uniqueCount = 0;
        for (int j = 0; j < 26; j++) {
            freqMap[j] = 0;
        }
        
        for (int j = i; j < i + minSize; j++) {
            if (freqMap[s[j] - 'a'] == 0) {
                uniqueCount++;
            }
            freqMap[s[j] - 'a']++;
        }
        
        if (uniqueCount <= maxLetters) {
            int hash = 0;
            for (int j = 0; j < 26; j++) {
                if (freqMap[j] > 0) {
                    hash = hash * 31 + (j + 1) * freqMap[j];
                }
            }
            substringCountMap[hash]++;
            if (substringCountMap[hash] > maxCount) {
                maxCount = substringCountMap[hash];
            }
        }
    }
    
    return maxCount;        
}
