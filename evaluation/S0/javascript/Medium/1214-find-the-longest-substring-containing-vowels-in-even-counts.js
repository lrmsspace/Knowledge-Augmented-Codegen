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

/**
 * @param {string} s
 * @return {number}
 */
var findTheLongestSubstring = function(s) {
    const vowelToBit = {
        'a': 1 << 0,
        'e': 1 << 1,
        'i': 1 << 2,
        'o': 1 << 3,
        'u': 1 << 4,
    };
    let state = 0;
    const stateToIndex = {0: -1};
    let maxLength = 0;
        
    for (let i = 0; i < s.length; i++) {
        const char = s[i];
        if (vowelToBit.hasOwnProperty(char)) {
            state ^= vowelToBit[char];
        }

        if (stateToIndex.hasOwnProperty(state)) {
            const prevIndex = stateToIndex[state];
            const length = i - prevIndex;
            maxLength = Math.max(maxLength, length);
        }
        else {
            stateToIndex[state] = i;
        }

    }

    return maxLength;   
    
};
