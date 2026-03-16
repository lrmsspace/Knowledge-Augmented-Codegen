// Source: https://leetcode.com/problems/maximum-score-from-removing-substrings/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s and two integers x and y. You can perform two types of operations any number of times.
//
//
// 	Remove substring "ab" and gain x points.
//
// 	
// 		For example, when removing "ab" from "cabxbae" it becomes "cxbae".
// 	
// 	
// 	Remove substring "ba" and gain y points.
// 	
// 		For example, when removing "ba" from "cabxbae" it becomes "cabxe".
// 	
// 	
//
//
// Return the maximum points you can gain after applying the above operations on s.
//
// Example:
// Input: s = "cdbcbbaaabab", x = 4, y = 5
// Output: 19
// Explanation:
// - Remove the "ba" underlined in "cdbcbbaaabab". Now, s = "cdbcbbaaab" and 5 points are added to the score.
// - Remove the "ab" underlined in "cdbcbbaaab". Now, s = "cdbcbbaa" and 4 points are added to the score.
// - Remove the "ba" underlined in "cdbcbbaa". Now, s = "cdbcba" and 5 points are added to the score.
// - Remove the "ba" underlined in "cdbcba". Now, s = "cdbc" and 5 points are added to the score.
// Total score = 5 + 4 + 5 + 5 = 19.
//
// Constraints:
// 1 <= s.length <= 105
// 	1 <= x, y <= 104
// 	s consists of lowercase English letters.
//

int maximumGain(char* s, int x, int y) {
    int total = 0;
    char stack1[100005];
    int top1 = -1;
    char stack2[100005];
    int top2 = -1;

    // First pass: Remove the higher scoring substring first
    if (x >= y) {
        for (int i = 0; s[i] != '\0'; i++) {
            if (top1 >= 0 && stack1[top1] == 'a' && s[i] == 'b') {
                total += x;
                top1--;
            } else {
                stack1[++top1] = s[i];
            }
        }
        // Second pass: Remove the other substring
        for (int i = 0; i <= top1; i++) {
            if (top2 >= 0 && stack2[top2] == 'b' && stack1[i] == 'a') {
                total += y;
                top2--;
            } else {
                stack2[++top2] = stack1[i];
            }
        }
    } else {
        for (int i = 0; s[i] != '\0'; i++) {
            if (top1 >= 0 && stack1[top1] == 'b' && s[i] == 'a') {
                total += y;
                top1--;
            } else {
                stack1[++top1] = s[i];
            }
        }
        // Second pass: Remove the other substring
        for (int i = 0; i <= top1; i++) {
            if (top2 >= 0 && stack2[top2] == 'a' && stack1[i] == 'b') {
                total += x;
                top2--;
            } else {
                stack2[++top2] = stack1[i];
            }
        }
    }

    return total;       
}
