// Source: https://leetcode.com/problems/reorganize-string/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, rearrange the characters of s so that any two adjacent characters are not the same.
//
// Return any possible rearrangement of s or return "" if not possible.
//
// Example:
// Input: s = "aab"
// Output: "aba"
//
// Constraints:
// 1 <= s.length <= 500
// 	s consists of lowercase English letters.
//

char* reorganizeString(char* s) {
    int len = strlen(s);
    int count[26];
    memset(count, 0, sizeof(count));
    
    for (int i = 0; i < len; i++) {
        count[s[i] - 'a']++;
    }
    
    int maxCount = 0;
    int maxCharIndex = 0;
    for (int i = 0; i < 26; i++) {
        if (count[i] > maxCount) {
            maxCount = count[i];
            maxCharIndex = i;
        }
    }
    
    if (maxCount > (len + 1) / 2) {
        return "";
    }
    
    char* result = (char*)malloc((len + 1) * sizeof(char));
    memset(result, 0, (len + 1) * sizeof(char));
    
    int index = 0;
    while (count[maxCharIndex] > 0) {
        result[index] = 'a' + maxCharIndex;
        index += 2;
        count[maxCharIndex]--;
    }
    
    for (int i = 0; i < 26; i++) {
        while (count[i] > 0) {
            if (index >= len) {
                index = 1;
            }
            result[index] = 'a' + i;
            index += 2;
            count[i]--;
        }
    }
    
    return result;      
}
