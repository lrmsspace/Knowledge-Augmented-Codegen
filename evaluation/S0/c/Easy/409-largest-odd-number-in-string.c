// Source: https://leetcode.com/problems/largest-odd-number-in-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string num, representing a large integer. Return the largest-valued odd integer (as a string) that is a non-empty substring of num, or an empty string "" if no odd integer exists.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: num = "52"
// Output: "5"
// Explanation: The only non-empty substrings are "5", "2", and "52". "5" is the only odd number.
//
// Constraints:
// 1 <= num.length <= 105
// 	num only consists of digits and does not contain any leading zeros.
//

char* largestOddNumber(char* num) {
    int len = strlen(num);
    for (int i = len - 1; i >= 0; i--) {
        if ((num[i] - '0') % 2 == 1) {
            num[i + 1] = '\0';
            return num;
        }
    }
    return "";      
}
