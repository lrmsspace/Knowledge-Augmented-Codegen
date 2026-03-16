// Source: https://leetcode.com/problems/separate-black-and-white-balls/   |   Difficulty: Medium
//
// Problem Description:
// There are n balls on a table, each ball has a color black or white.
//
// You are given a 0-indexed binary string s of length n, where 1 and 0 represent black and white balls, respectively.
//
// In each step, you can choose two adjacent balls and swap them.
//
// Return the minimum number of steps to group all the black balls to the right and all the white balls to the left.
//
// Example:
// Input: s = "101"
// Output: 1
// Explanation: We can group all the black balls to the right in the following way:
// - Swap s[0] and s[1], s = "011".
// Initially, 1s are not grouped together, requiring at least 1 step to group them to the right.
//
// Constraints:
// 1 <= n == s.length <= 105
// 	s[i] is either '0' or '1'.
//

long long minimumSteps(char* s) {
    long long white_count = 0;
    long long steps = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '0') {
            white_count++;
        } else {
            steps += white_count;
        }
    }

    return steps;       
}
