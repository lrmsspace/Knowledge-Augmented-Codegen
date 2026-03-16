// Source: https://leetcode.com/problems/count-complete-substrings/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string word and an integer k.
//
// A substring s of word is complete if:
//
//
// 	Each character in s occurs exactly k times.
// 	The difference between two adjacent characters is at most 2. That is, for any two adjacent characters c1 and c2 in s, the absolute difference in their positions in the alphabet is at most 2.
//
//
// Return the number of complete substrings of word.
//
// A substring is a non-empty contiguous sequence of characters in a string.
//
// Example:
// Input: word = "igigee", k = 2
// Output: 3
// Explanation: The complete substrings where each character appears exactly twice and the difference between adjacent characters is at most 2 are: igigee, igigee, igigee.
//
// Constraints:
// 1 <= word.length <= 105
// 	word consists only of lowercase English letters.
// 	1 <= k <= word.length
//

class Solution {
public:
    int countCompleteSubstrings(string word, int k) {
        int n = word.size();
        int result = 0;
        
        for (int i = 0; i < n; i++) {
            vector<int> freq(26, 0);
            int uniqueCount = 0;
            int countK = 0;
            
            for (int j = i; j < n; j++) {
                int idx = word[j] - 'a';
                
                // Check adjacent character difference
                if (j > i) {
                    int prevIdx = word[j - 1] - 'a';
                    if (abs(idx - prevIdx) > 2) {
                        break;
                    }
                }
                
                freq[idx]++;
                
                if (freq[idx] == 1) {
                    uniqueCount++;
                }
                if (freq[idx] == k) {
                    countK++;
                }
                if (freq[idx] > k) {
                    break;
                }
                
                if (uniqueCount == countK) {
                    result++;
                }
            }
        }
        
        return result;          
    }
};
