// Source: https://leetcode.com/problems/minimum-operations-to-make-a-special-number/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed string num representing a non-negative integer.
//
// In one operation, you can pick any digit of num and delete it. Note that if you delete all the digits of num, num becomes 0.
//
// Return the minimum number of operations required to make num special.
//
// An integer x is considered special if it is divisible by 25.
//
// Example:
// Input: num = "2245047"
// Output: 2
// Explanation: Delete digits num[5] and num[6]. The resulting number is "22450" which is special since it is divisible by 25.
// It can be shown that 2 is the minimum number of operations required to get a special number.
//
// Constraints:
// 1 <= num.length <= 100
// 	num only consists of digits '0' through '9'.
// 	num does not contain any leading zeros.
//

int minimumOperations(char* num) {
    int len = strlen(num);
    int res = len; // Initialize result with maximum possible operations

    // Possible endings for a special number (divisible by 25)
    const char* endings[] = {"00", "25", "50", "75"};

    for (int i = 0; i < 4; i++) {
        char d1 = endings[i][0];
        char d2 = endings[i][1];
        int count = 0;
        int found_d2 = 0;

        // Traverse the string from the end to find the required digits
        for (int j = len - 1; j >= 0; j--) {
            if (!found_d2) {
                if (num[j] == d2) {
                    found_d2 = 1; // Found the second digit
                } else {
                    count++; // Count deletions
                }
            } else {
                if (num[j] == d1) {
                    // Found both digits, calculate total deletions
                    res = res < count ? res : count;
                    break;
                } else {
                    count++; // Count deletions
                }
            }
        }
    }

    return res;     
}
