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

char* robotWithString(char* s) {
    int n = strlen(s);
    int min_from_right[n];
    min_from_right[n - 1] = s[n - 1] - 'a';
    for (int i = n - 2; i >= 0; --i) {
        min_from_right[i] = fmin(min_from_right[i + 1], s[i] - 'a');
    }

    char* result = (char*)malloc((n + 1) * sizeof(char));
    int result_index = 0;

    char stack[n];
    int stack_top = -1;

    int s_index = 0;
    while (s_index < n || stack_top >= 0) {
        if (stack_top >= 0 && (s_index == n || stack[stack_top] - 'a' <= min_from_right[s_index])) {
            result[result_index++] = stack[stack_top--];
        } else {
            stack[++stack_top] = s[s_index++];
        }
    }

    result[result_index] = '\0';
    return result;      
}
