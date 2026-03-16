// Source: https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/   |   Difficulty: Medium
//
// Problem Description:
// Given the string s, return the size of the longest substring containing each vowel an even number of times. That is, 'a', 'e', 'i', 'o', and 'u' must appear an even number of times.
//
// Example:
// Input: s = "eleetminicoworoep"
// Output: 13
// Explanation: The longest substring is "leetminicowor" which contains two each of the vowels: e, i and o and zero of the vowels: a and u.
//
// Constraints:
// 1 <= s.length <= 5 x 10^5
// 	s contains only lowercase English letters.
//

class Solution {
public:
    int findTheLongestSubstring(string s) {
        unordered_map<int, int> stateIndexMap;
        stateIndexMap[0] = -1; // Initial state before processing any character

        int maxLength = 0;
        int currentState = 0;

        for (int i = 0; i < s.length(); ++i) {
            char ch = s[i];
            switch (ch) {
                case 'a':
                    currentState ^= (1 << 0);
                    break;
                case 'e':
                    currentState ^= (1 << 1);
                    break;
                case 'i':
                    currentState ^= (1 << 2);
                    break;
                case 'o':
                    currentState ^= (1 << 3);
                    break;
                case 'u':
                    currentState ^= (1 << 4);
                    break;
                default:
                    break;
            }

            if (stateIndexMap.find(currentState) != stateIndexMap.end()) {
                maxLength = max(maxLength, i - stateIndexMap[currentState]);
            } else {
                stateIndexMap[currentState] = i;
            }
        }

        return maxLength;           
    }
};
