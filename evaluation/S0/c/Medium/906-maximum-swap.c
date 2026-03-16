// Source: https://leetcode.com/problems/maximum-swap/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer num. You can swap two digits at most once to get the maximum valued number.
//
// Return the maximum valued number you can get.
//
// Example:
// Input: num = 2736
// Output: 7236
// Explanation: Swap the number 2 and the number 7.
//
// Constraints:
// 0 <= num <= 108
//

int maximumSwap(int num) {
    char digits[10];
    int len = 0;
    int n = num;

    // Extract digits from the number and store them in reverse order
    while (n > 0) {
        digits[len++] = (n % 10) + '0';
        n /= 10;
    }

    // Reverse the digits to get the correct order
    for (int i = 0; i < len / 2; i++) {
        char temp = digits[i];
        digits[i] = digits[len - 1 - i];
        digits[len - 1 - i] = temp;
    }

    // Create an array to store the last occurrence of each digit
    int last[10] = {0};
    for (int i = 0; i < len; i++) {
        last[digits[i] - '0'] = i;
    }

    // Try to find a swap that maximizes the number
    for (int i = 0; i < len; i++) {
        for (int d = 9; d > digits[i] - '0'; d--) {
            if (last[d] > i) {
                // Swap the digits
                char temp = digits[i];
                digits[i] = digits[last[d]];
                digits[last[d]] = temp;

                // Convert back to integer
                int result = 0;
                for (int j = 0; j < len; j++) {
                    result = result * 10 + (digits[j] - '0');
                }
                return result;
            }
        }
    }

    return num; // No swap made, return original number     
}
