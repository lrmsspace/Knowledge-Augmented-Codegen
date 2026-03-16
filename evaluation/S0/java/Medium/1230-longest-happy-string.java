// Source: https://leetcode.com/problems/longest-happy-string/   |   Difficulty: Medium
//
// Problem Description:
// A string s is called happy if it satisfies the following conditions:
//
//
// 	s only contains the letters 'a', 'b', and 'c'.
// 	s does not contain any of "aaa", "bbb", or "ccc" as a substring.
// 	s contains at most a occurrences of the letter 'a'.
// 	s contains at most b occurrences of the letter 'b'.
// 	s contains at most c occurrences of the letter 'c'.
//
//
// Given three integers a, b, and c, return the longest possible happy string. If there are multiple longest happy strings, return any of them. If there is no such string, return the empty string "".
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: a = 1, b = 1, c = 7
// Output: "ccaccbcc"
// Explanation: "ccbccacc" would also be a correct answer.
//
// Constraints:
// 0 <= a, b, c <= 100
// 	a + b + c > 0
//

class Solution {
    public String longestDiverseString(int a, int b, int c) {
        StringBuilder result = new StringBuilder();
        int[] counts = new int[]{a, b, c};
        char[] chars = new char[]{'a', 'b', 'c'};

        while (true) {
            int maxIndex = -1;
            for (int i = 0; i < 3; i++) {
                if (maxIndex == -1 || counts[i] > counts[maxIndex]) {
                    maxIndex = i;
                }
            }

            if (counts[maxIndex] == 0) {
                break;
            }

            int len = result.length();
            if (len >= 2 && result.charAt(len - 1) == chars[maxIndex] && result.charAt(len - 2) == chars[maxIndex]) {
                int secondMaxIndex = -1;
                for (int i = 0; i < 3; i++) {
                    if (i != maxIndex && (secondMaxIndex == -1 || counts[i] > counts[secondMaxIndex])) {
                        secondMaxIndex = i;
                    }
                }

                if (counts[secondMaxIndex] == 0) {
                    break;
                }

                result.append(chars[secondMaxIndex]);
                counts[secondMaxIndex]--;
            } else {
                result.append(chars[maxIndex]);
                counts[maxIndex]--;
            }
        }

        return result.toString();           
    }
}
