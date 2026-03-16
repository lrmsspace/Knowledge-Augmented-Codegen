// Source: https://leetcode.com/problems/second-largest-digit-in-a-string/   |   Difficulty: Easy
//
// Problem Description:
// Given an alphanumeric string s, return the second largest numerical digit that appears in s, or -1 if it does not exist.
//
// An alphanumeric string is a string consisting of lowercase English letters and digits.
//
// Example:
// Input: s = "dfa12321afd"
// Output: 2
// Explanation: The digits that appear in s are [1, 2, 3]. The second largest digit is 2.
//
// Constraints:
// 1 <= s.length <= 500
// 	s consists of only lowercase English letters and digits.
//

class Solution {
    public int secondHighest(String s) {
        boolean[] digitsPresent = new boolean[10];
        
        // Mark the digits that are present in the string
        for (char c : s.toCharArray()) {
            if (Character.isDigit(c)) {
                digitsPresent[c - '0'] = true;
            }
        }
        
        int largest = -1;
        int secondLargest = -1;
        
        // Find the largest and second largest digits
        for (int i = 9; i >= 0; i--) {
            if (digitsPresent[i]) {
                if (largest == -1) {
                    largest = i;
                } else if (secondLargest == -1) {
                    secondLargest = i;
                    break; // Found both largest and second largest
                }
            }
        }
        
        return secondLargest;           
    }
}
