// Source: https://leetcode.com/problems/masking-personal-information/   |   Difficulty: Medium
//
// Problem Description:
// You are given a personal information string s, representing either an email address or a phone number. Return the masked personal information using the below rules.
//
// Email address:
//
// An email address is:
//
//
// 	A name consisting of uppercase and lowercase English letters, followed by
// 	The '@' symbol, followed by
// 	The domain consisting of uppercase and lowercase English letters with a dot '.' somewhere in the middle (not the first or last character).
//
//
// To mask an email:
//
//
// 	The uppercase letters in the name and domain must be converted to lowercase letters.
// 	The middle letters of the name (i.e., all but the first and last letters) must be replaced by 5 asterisks "*****".
//
//
// Phone number:
//
// A phone number is formatted as follows:
//
//
// 	The phone number contains 10-13 digits.
// 	The last 10 digits make up the local number.
// 	The remaining 0-3 digits, in the beginning, make up the country code.
// 	Separation characters from the set {'+', '-', '(', ')', ' '} separate the above digits in some way.
//
//
// To mask a phone number:
//
//
// 	Remove all separation characters.
// 	The masked phone number should have the form:
// 	
// 		"***-***-XXXX" if the country code has 0 digits.
// 		"+*-***-***-XXXX" if the country code has 1 digit.
// 		"+**-***-***-XXXX" if the country code has 2 digits.
// 		"+***-***-***-XXXX" if the country code has 3 digits.
// 	
// 	
// 	"XXXX" is the last 4 digits of the local number.
//
// Example:
// Input: s = "LeetCode@LeetCode.com"
// Output: "l*****e@leetcode.com"
// Explanation: s is an email address.
// The name and domain are converted to lowercase, and the middle of the name is replaced by 5 asterisks.
//
// Constraints:
// s is either a valid email or a phone number.
// 	If s is an email:
// 	
// 		8 <= s.length <= 40
// 		s consists of uppercase and lowercase English letters and exactly one '@' symbol and '.' symbol.
// 	
// 	
// 	If s is a phone number:
// 	
// 		10 <= s.length <= 20
// 		s consists of digits, spaces, and the symbols '(', ')', '-', and '+'.
//

class Solution {
    public String maskPII(String s) {
        if (s.indexOf('@') != -1) {
            s = s.toLowerCase();
            String[] parts = s.split("@");
            String name = parts[0];
            String domain = parts[1];
            return name.charAt(0) + "*****" + name.charAt(name.length() - 1) + "@" + domain;
        } else {
            String digits = s.replaceAll("[^0-9]", "");
            String local = "***-***-" + digits.substring(digits.length() - 4);
            int countryCodeLength = digits.length() - 10;
            if (countryCodeLength == 0) {
                return local;
            } else {
                StringBuilder sb = new StringBuilder("+");
                for (int i = 0; i < countryCodeLength; i++) {
                    sb.append("*");
                }
                sb.append("-").append(local);
                return sb.toString();
            }
        }           
    }
}
