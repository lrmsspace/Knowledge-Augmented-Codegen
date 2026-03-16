// Source: https://leetcode.com/problems/longer-contiguous-segments-of-ones-than-zeros/   |   Difficulty: Easy
//
// Problem Description:
// Given a binary string s, return true if the longest contiguous segment of 1's is strictly longer than the longest contiguous segment of 0's in s, or return false otherwise.
//
//
// 	For example, in s = "110100010" the longest continuous segment of 1s has length 2, and the longest continuous segment of 0s has length 3.
//
//
// Note that if there are no 0's, then the longest continuous segment of 0's is considered to have a length 0. The same applies if there is no 1's.
//
// Example:
// Input: s = "1101"
// Output: true
// Explanation:
// The longest contiguous segment of 1s has length 2: "1101"
// The longest contiguous segment of 0s has length 1: "1101"
// The segment of 1s is longer, so return true.
//
// Constraints:
// 1 <= s.length <= 100
// 	s[i] is either '0' or '1'.
//

class Solution {
public:
    bool checkZeroOnes(string s) {
        int maxOnes = 0, maxZeros = 0;
        int countOnes = 0, countZeros = 0;

        for (char c : s) {
            if (c == '1') {
                countOnes++;
                countZeros = 0;
            } else {
                countZeros++;
                countOnes = 0;
            }

            maxOnes = max(maxOnes, countOnes);
            maxZeros = max(maxZeros, countZeros);
        }

        return maxOnes > maxZeros;          
    }
};
