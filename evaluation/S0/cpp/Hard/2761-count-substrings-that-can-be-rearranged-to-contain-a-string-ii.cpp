// Source: https://leetcode.com/problems/count-substrings-that-can-be-rearranged-to-contain-a-string-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given two strings word1 and word2.
//
// A string x is called valid if x can be rearranged to have word2 as a prefix.
//
// Return the total number of valid substrings of word1.
//
// Note that the memory limits in this problem are smaller than usual, so you must implement a solution with a linear runtime complexity.
//
// Example:
// Input: word1 = "bcca", word2 = "abc"
//
// Output: 1
//
// Explanation:
//
// The only valid substring is "bcca" which can be rearranged to "abcc" having "abc" as a prefix.
//
// Constraints:
// 1 <= word1.length <= 106
// 	1 <= word2.length <= 104
// 	word1 and word2 consist only of lowercase English letters.
//

class Solution {
public:
    long long validSubstringCount(string word1, string word2) {
        vector<int> count2(26, 0);
        for (char c : word2) {
            count2[c - 'a']++;
        }
        
        int required = 0;
        for (int cnt : count2) {
            if (cnt > 0) required++;
        }
        
        vector<int> windowCount(26, 0);
        int formed = 0;
        long long result = 0;
        int left = 0;
        
        for (int right = 0; right < word1.size(); right++) {
            char c = word1[right];
            windowCount[c - 'a']++;
            
            if (count2[c - 'a'] > 0 && windowCount[c - 'a'] == count2[c - 'a']) {
                formed++;
            }
            
            while (formed == required) {
                result += word1.size() - right;
                
                char leftChar = word1[left];
                windowCount[leftChar - 'a']--;
                
                if (count2[leftChar - 'a'] > 0 && windowCount[leftChar - 'a'] < count2[leftChar - 'a']) {
                    formed--;
                }
                
                left++;
            }
        }
        
        return result;          
    }
};
