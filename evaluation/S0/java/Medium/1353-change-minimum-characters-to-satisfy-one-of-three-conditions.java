// Source: https://leetcode.com/problems/change-minimum-characters-to-satisfy-one-of-three-conditions/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings a and b that consist of lowercase letters. In one operation, you can change any character in a or b to any lowercase letter.
//
// Your goal is to satisfy one of the following three conditions:
//
//
// 	Every letter in a is strictly less than every letter in b in the alphabet.
// 	Every letter in b is strictly less than every letter in a in the alphabet.
// 	Both a and b consist of only one distinct letter.
//
//
// Return the minimum number of operations needed to achieve your goal.
//
// Example:
// Input: a = "aba", b = "caa"
// Output: 2
// Explanation: Consider the best way to make each condition true:
// 1) Change b to "ccc" in 2 operations, then every letter in a is less than every letter in b.
// 2) Change a to "bbb" and b to "aaa" in 3 operations, then every letter in b is less than every letter in a.
// 3) Change a to "aaa" and b to "aaa" in 2 operations, then a and b consist of one distinct letter.
// The best way was done in 2 operations (either condition 1 or condition 3).
//
// Constraints:
// 1 <= a.length, b.length <= 105
// 	a and b consist only of lowercase letters.
//

class Solution {
    public int minCharacters(String a, String b) {
        int n = a.length(), m = b.length();
        int[] countA = new int[26];
        int[] countB = new int[26];

        for (char c : a.toCharArray()) {
            countA[c - 'a']++;
        }
        for (char c : b.toCharArray()) {
            countB[c - 'a']++;
        }

        int minChanges = Integer.MAX_VALUE;

        // Condition 1: Every letter in a is strictly less than every letter in b
        for (int i = 0; i < 25; i++) {
            int changes = 0;
            for (int j = i + 1; j < 26; j++) {
                changes += countA[j];
            }
            for (int j = 0; j <= i; j++) {
                changes += countB[j];
            }
            minChanges = Math.min(minChanges, changes);
        }

        // Condition 2: Every letter in b is strictly less than every letter in a
        for (int i = 0; i < 25; i++) {
            int changes = 0;
            for (int j = i + 1; j < 26; j++) {
                changes += countB[j];
            }
            for (int j = 0; j <= i; j++) {
                changes += countA[j];
            }
            minChanges = Math.min(minChanges, changes);
        }

        // Condition 3: Both a and b consist of only one distinct letter
        int totalLength = n + m;
        for (int i = 0; i < 26; i++) {
            int changes = totalLength - (countA[i] + countB[i]);
            minChanges = Math.min(minChanges, changes);
        }

        return minChanges;          
    }
}
