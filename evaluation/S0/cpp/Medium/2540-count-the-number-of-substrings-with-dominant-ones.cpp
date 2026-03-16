// Source: https://leetcode.com/problems/count-the-number-of-substrings-with-dominant-ones/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary string s.
//
// Return the number of substrings with dominant ones.
//
// A string has dominant ones if the number of ones in the string is greater than or equal to the square of the number of zeros in the string.
//
// Example:
// Input: s = "00011"
//
// Output: 5
//
// Explanation:
//
// The substrings with dominant ones are shown in the table below.
//
//
//
// 	
// 		
// 			i
// 			j
// 			s[i..j]
// 			Number of Zeros
// 			Number of Ones
// 		
// 	
// 	
// 		
// 			3
// 			3
// 			1
// 			0
// 			1
// 		
// 		
// 			4
// 			4
// 			1
// 			0
// 			1
// 		
// 		
// 			2
// 			3
// 			01
// 			1
// 			1
// 		
// 		
// 			3
// 			4
// 			11
// 			0
// 			2
// 		
// 		
// 			2
// 			4
// 			011
// 			1
// 			2
//
// Constraints:
// 1 <= s.length <= 4 * 104
// 	s consists only of characters '0' and '1'.
//

class Solution {
public:
    int numberOfSubstrings(string s) {
        int n = s.size();
        int result = 0;

        for (int i = 0; i < n; ++i) {
            int countZeros = 0;
            int countOnes = 0;

            for (int j = i; j < n; ++j) {
                if (s[j] == '0') {
                    countZeros++;
                } else {
                    countOnes++;
                }

                if (countOnes >= countZeros * countZeros) {
                    result++;
                }
            }
        }

        return result;          
    }
};
