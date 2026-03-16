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

bool checkZeroOnes(char* s) {
    int max_ones = 0, max_zeros = 0;
    int current_ones = 0, current_zeros = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '1') {
            current_ones++;
            current_zeros = 0;
        } else {
            current_zeros++;
            current_ones = 0;
        }

        if (current_ones > max_ones) {
            max_ones = current_ones;
        }
        if (current_zeros > max_zeros) {
            max_zeros = current_zeros;
        }
    }

    return max_ones > max_zeros;        
}
