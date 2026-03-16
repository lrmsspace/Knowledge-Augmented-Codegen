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

int minCharacters(char* a, char* b) {
    int countA[26] = {0}, countB[26] = {0};
    int lenA = 0, lenB = 0;

    for (int i = 0; a[i] != '\0'; i++) {
        countA[a[i] - 'a']++;
        lenA++;
    }

    for (int i = 0; b[i] != '\0'; i++) {
        countB[b[i] - 'a']++;
        lenB++;
    }

    int prefixA[26] = {0}, prefixB[26] = {0};
    prefixA[0] = countA[0];
    prefixB[0] = countB[0];

    for (int i = 1; i < 26; i++) {
        prefixA[i] = prefixA[i - 1] + countA[i];
        prefixB[i] = prefixB[i - 1] + countB[i];
    }

    int minOperations = lenA + lenB; // Initialize with a large number

    // Condition 1 and 2
    for (int i = 0; i < 25; i++) {
        int operationsForCondition1 = (lenA - prefixA[i]) + prefixB[i];
        int operationsForCondition2 = (lenB - prefixB[i]) + prefixA[i];
        if (operationsForCondition1 < minOperations) {
            minOperations = operationsForCondition1;
        }
        if (operationsForCondition2 < minOperations) {
            minOperations = operationsForCondition2;
        }
    }

    // Condition 3
    for (int i = 0; i < 26; i++) {
        int operationsForCondition3 = (lenA - countA[i]) + (lenB - countB[i]);
        if (operationsForCondition3 < minOperations) {
            minOperations = operationsForCondition3;
        }
    }

    return minOperations;       
}
