// Source: https://leetcode.com/problems/print-words-vertically/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s. Return all the words vertically in the same order in which they appear in s.
// Words are returned as a list of strings, complete with spaces when is necessary. (Trailing spaces are not allowed).
// Each word would be put on only one column and that in one column there will be only one word.
//
// Example:
// Input: s = "HOW ARE YOU"
// Output: ["HAY","ORO","WEU"]
// Explanation: Each word is printed vertically. 
//  "HAY"
//  "ORO"
//  "WEU"
//
// Constraints:
// 1 <= s.length <= 200
// 	s contains only upper case English letters.
// 	It's guaranteed that there is only one space between 2 words.
//

class Solution {
    public List<String> printVertically(String s) {
        String[] words = s.split(" ");
        int maxLen = 0;
        for (String word : words) {
            maxLen = Math.max(maxLen, word.length());
        }

        List<String> result = new ArrayList<>();
        for (int i = 0; i < maxLen; i++) {
            StringBuilder sb = new StringBuilder();
            for (String word : words) {
                if (i < word.length()) {
                    sb.append(word.charAt(i));
                } else {
                    sb.append(' ');
                }
            }
            // Remove trailing spaces
            int end = sb.length() - 1;
            while (end >= 0 && sb.charAt(end) == ' ') {
                end--;
            }
            result.add(sb.substring(0, end + 1));
        }

        return result;          
    }
}
