// Source: https://leetcode.com/problems/using-a-robot-to-print-the-lexicographically-smallest-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s and a robot that currently holds an empty string t. Apply one of the following operations until s and t are both empty:
//
//
// 	Remove the first character of a string s and give it to the robot. The robot will append this character to the string t.
// 	Remove the last character of a string t and give it to the robot. The robot will write this character on paper.
//
//
// Return the lexicographically smallest string that can be written on the paper.
//
// Example:
// Input: s = "zza"
// Output: "azz"
// Explanation: Let p denote the written string.
// Initially p="", s="zza", t="".
// Perform first operation three times p="", s="", t="zza".
// Perform second operation three times p="azz", s="", t="".
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of only English lowercase letters.
//

class Solution {
    public String robotWithString(String s) {
        int n = s.length();
        char[] arr = s.toCharArray();
        int[] minFromRight = new int[n];
        minFromRight[n - 1] = arr[n - 1] - 'a';

        for (int i = n - 2; i >= 0; i--) {
            minFromRight[i] = Math.min(minFromRight[i + 1], arr[i] - 'a');
        }

        StringBuilder result = new StringBuilder();
        StringBuilder t = new StringBuilder();
        int index = 0;

        while (index < n || t.length() > 0) {
            while (index < n && (t.length() == 0 || (arr[index] - 'a') <= minFromRight[index])) {
                t.append(arr[index]);
                index++;
            }

            char smallestCharInT = t.charAt(t.length() - 1);
            result.append(smallestCharInT);
            t.deleteCharAt(t.length() - 1);
        }

        return result.toString();           
    }
}
