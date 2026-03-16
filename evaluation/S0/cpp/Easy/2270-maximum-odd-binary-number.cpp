// Source: https://leetcode.com/problems/maximum-odd-binary-number/   |   Difficulty: Easy
//
// Problem Description:
// You are given a binary string s that contains at least one '1'.
//
// You have to rearrange the bits in such a way that the resulting binary number is the maximum odd binary number that can be created from this combination.
//
// Return a string representing the maximum odd binary number that can be created from the given combination.
//
// Note that the resulting string can have leading zeros.
//
// Example:
// Input: s = "010"
// Output: "001"
// Explanation: Because there is just one '1', it must be in the last position. So the answer is "001".
//
// Constraints:
// 1 <= s.length <= 100
// 	s consists only of '0' and '1'.
// 	s contains at least one '1'.
//

class Solution {
public:
    string maximumOddBinaryNumber(string s) {
        int count0 = 0, count1 = 0;
        for (char c : s) {
            if (c == '0') {
                count0++;
            } else {
                count1++;
            }
        }
        // To make the binary number odd, we need to place one '1' at the end
        count1--; // Place one '1' at the end
        string result(count1, '1'); // Add all remaining '1's at the front
        result.append(count0, '0'); // Add all '0's in the middle
        result.push_back('1'); // Finally add the last '1' to make it odd
        return result;          
    }
};
