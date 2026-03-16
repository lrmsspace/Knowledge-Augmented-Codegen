// Source: https://leetcode.com/problems/construct-string-with-repeat-limit/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s and an integer repeatLimit. Construct a new string repeatLimitedString using the characters of s such that no letter appears more than repeatLimit times in a row. You do not have to use all characters from s.
//
// Return the lexicographically largest repeatLimitedString possible.
//
// A string a is lexicographically larger than a string b if in the first position where a and b differ, string a has a letter that appears later in the alphabet than the corresponding letter in b. If the first min(a.length, b.length) characters do not differ, then the longer string is the lexicographically larger one.
//
// Example:
// Input: s = "cczazcc", repeatLimit = 3
// Output: "zzcccac"
// Explanation: We use all of the characters from s to construct the repeatLimitedString "zzcccac".
// The letter 'a' appears at most 1 time in a row.
// The letter 'c' appears at most 3 times in a row.
// The letter 'z' appears at most 2 times in a row.
// Hence, no letter appears more than repeatLimit times in a row and the string is a valid repeatLimitedString.
// The string is the lexicographically largest repeatLimitedString possible so we return "zzcccac".
// Note that the string "zzcccca" is lexicographically larger but the letter 'c' appears more than 3 times in a row, so it is not a valid repeatLimitedString.
//
// Constraints:
// 1 <= repeatLimit <= s.length <= 105
// 	s consists of lowercase English letters.
//

class Solution {
    public String repeatLimitedString(String s, int repeatLimit) {
        int[] count = new int[26];
        for (char c : s.toCharArray()) {
            count[c - 'a']++;
        }

        StringBuilder result = new StringBuilder();
        int lastAppendedIndex = -1;
        while (true) {
            int currentIndex = -1;
            for (int i = 25; i >= 0; i--) {
                if (count[i] > 0 && i != lastAppendedIndex) {
                    currentIndex = i;
                    break;
                }
            }

            if (currentIndex == -1) {
                break;
            }

            int timesToAppend = Math.min(count[currentIndex], repeatLimit);
            for (int i = 0; i < timesToAppend; i++) {
                result.append((char) (currentIndex + 'a'));
            }
            count[currentIndex] -= timesToAppend;

            if (count[currentIndex] > 0) {
                int nextIndex = -1;
                for (int i = currentIndex - 1; i >= 0; i--) {
                    if (count[i] > 0) {
                        nextIndex = i;
                        break;
                    }
                }

                if (nextIndex == -1) {
                    break;
                }

                result.append((char) (nextIndex + 'a'));
                count[nextIndex]--;
                lastAppendedIndex = nextIndex;
            } else {
                lastAppendedIndex = -1;
            }
        }

        return result.toString();           
    }
}
