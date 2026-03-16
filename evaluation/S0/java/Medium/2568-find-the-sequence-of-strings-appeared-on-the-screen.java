// Source: https://leetcode.com/problems/find-the-sequence-of-strings-appeared-on-the-screen/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string target.
//
// Alice is going to type target on her computer using a special keyboard that has only two keys:
//
//
// 	Key 1 appends the character "a" to the string on the screen.
// 	Key 2 changes the last character of the string on the screen to its next character in the English alphabet. For example, "c" changes to "d" and "z" changes to "a".
//
//
// Note that initially there is an empty string "" on the screen, so she can only press key 1.
//
// Return a list of all strings that appear on the screen as Alice types target, in the order they appear, using the minimum key presses.
//
// Example:
// Input: target = "abc"
//
// Output: ["a","aa","ab","aba","abb","abc"]
//
// Explanation:
//
// The sequence of key presses done by Alice are:
//
//
// 	Press key 1, and the string on the screen becomes "a".
// 	Press key 1, and the string on the screen becomes "aa".
// 	Press key 2, and the string on the screen becomes "ab".
// 	Press key 1, and the string on the screen becomes "aba".
// 	Press key 2, and the string on the screen becomes "abb".
// 	Press key 2, and the string on the screen becomes "abc".
//
// Constraints:
// 1 <= target.length <= 400
// 	target consists only of lowercase English letters.
//

class Solution {
    public List<String> stringSequence(String target) {
        List<String> result = new ArrayList<>();
        StringBuilder current = new StringBuilder();

        for (char ch : target.toCharArray()) {
            // Press key 1 to append 'a'
            current.append('a');
            result.add(current.toString());

            // Press key 2 to change last character to the target character
            while (current.charAt(current.length() - 1) != ch) {
                char lastChar = current.charAt(current.length() - 1);
                char nextChar = lastChar == 'z' ? 'a' : (char) (lastChar + 1);
                current.setCharAt(current.length() - 1, nextChar);
                result.add(current.toString());
            }
        }

        return result;          
    }
}
