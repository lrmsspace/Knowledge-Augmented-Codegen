// Source: https://leetcode.com/problems/shortest-uncommon-substring-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array arr of size n consisting of non-empty strings.
//
// Find a string array answer of size n such that:
//
//
// 	answer[i] is the shortest substring of arr[i] that does not occur as a substring in any other string in arr. If multiple such substrings exist, answer[i] should be the lexicographically smallest. And if no such substring exists, answer[i] should be an empty string.
//
//
// Return the array answer.
//
// Example:
// Input: arr = ["cab","ad","bad","c"]
// Output: ["ab","","ba",""]
// Explanation: We have the following:
// - For the string "cab", the shortest substring that does not occur in any other string is either "ca" or "ab", we choose the lexicographically smaller substring, which is "ab".
// - For the string "ad", there is no substring that does not occur in any other string.
// - For the string "bad", the shortest substring that does not occur in any other string is "ba".
// - For the string "c", there is no substring that does not occur in any other string.
//
// Constraints:
// n == arr.length
// 	2 <= n <= 100
// 	1 <= arr[i].length <= 20
// 	arr[i] consists only of lowercase English letters.
//

class Solution {
    public String[] shortestSubstrings(String[] arr) {
        int n = arr.length;
        String[] result = new String[n];

        for (int i = 0; i < n; i++) {
            String currentString = arr[i];
            int len = currentString.length();
            String shortestSubstring = null;

            for (int subLen = 1; subLen <= len; subLen++) {
                for (int start = 0; start <= len - subLen; start++) {
                    String substring = currentString.substring(start, start + subLen);
                    boolean foundInOther = false;

                    for (int j = 0; j < n; j++) {
                        if (j != i && arr[j].contains(substring)) {
                            foundInOther = true;
                            break;
                        }
                    }

                    if (!foundInOther) {
                        if (shortestSubstring == null || substring.compareTo(shortestSubstring) < 0) {
                            shortestSubstring = substring;
                        }
                    }
                }

                if (shortestSubstring != null) {
                    break; // Found the shortest possible substring
                }
            }

            result[i] = shortestSubstring != null ? shortestSubstring : "";
        }

        return result;          
    }
}
