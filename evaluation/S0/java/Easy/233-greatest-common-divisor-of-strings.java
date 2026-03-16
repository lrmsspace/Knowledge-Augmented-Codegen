// Source: https://leetcode.com/problems/greatest-common-divisor-of-strings/   |   Difficulty: Easy
//
// Problem Description:
// For two strings s and t, we say "t divides s" if and only if s = t + t + t + ... + t + t (i.e., t is concatenated with itself one or more times).
//
// Given two strings str1 and str2, return the largest string x such that x divides both str1 and str2.
//
// Example:
// Input: str1 = "ABCABC", str2 = "ABC"
// Output: "ABC"
//
// Constraints:
// 1 <= str1.length, str2.length <= 1000
// 	str1 and str2 consist of English uppercase letters.
//

class Solution {
    public String gcdOfStrings(String str1, String str2) {
        if (!(str1 + str2).equals(str2 + str1)) {
            return "";
        }
        int gcdLength = gcd(str1.length(), str2.length());
        return str1.substring(0, gcdLength);            
    }
}
