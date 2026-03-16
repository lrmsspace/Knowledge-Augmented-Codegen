// Source: https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s and an integer k, a k duplicate removal consists of choosing k adjacent and equal letters from s and removing them, causing the left and the right side of the deleted substring to concatenate together.
//
// We repeatedly make k duplicate removals on s until we no longer can.
//
// Return the final string after all such duplicate removals have been made. It is guaranteed that the answer is unique.
//
// Example:
// Input: s = "abcd", k = 2
// Output: "abcd"
// Explanation: There's nothing to delete.
//
// Constraints:
// 1 <= s.length <= 105
// 	2 <= k <= 104
// 	s only contains lowercase English letters.
//

char* removeDuplicates(char* s, int k) {
    int len = strlen(s);
    int *count = (int *)malloc(len * sizeof(int));
    int j = 0;  // Pointer for the position in the modified string

    for (int i = 0; i < len; i++, j++) {
        s[j] = s[i];
        if (j == 0 || s[j] != s[j - 1]) {
            count[j] = 1;  // Start a new count
        } else {
            count[j] = count[j - 1] + 1;  // Increment the count
            if (count[j] == k) {
                j -= k;  // Remove the last k characters
            }
        }
    }

    s[j] = '\0';  // Null-terminate the modified string
    free(count);
    return s;       
}
