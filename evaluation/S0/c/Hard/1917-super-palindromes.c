// Source: https://leetcode.com/problems/super-palindromes/   |   Difficulty: Hard
//
// Problem Description:
// Let's say a positive integer is a super-palindrome if it is a palindrome, and it is also the square of a palindrome.
//
// Given two positive integers left and right represented as strings, return the number of super-palindromes integers in the inclusive range [left, right].
//
// Example:
// Input: left = "4", right = "1000"
// Output: 4
// Explanation: 4, 9, 121, and 484 are superpalindromes.
// Note that 676 is not a superpalindrome: 26 * 26 = 676, but 26 is not a palindrome.
//
// Constraints:
// 1 <= left.length, right.length <= 18
// 	left and right consist of only digits.
// 	left and right cannot have leading zeros.
// 	left and right represent integers in the range [1, 1018 - 1].
// 	left is less than or equal to right.
//

int superpalindromesInRange(char* left, char* right) {
    long long l = atoll(left);
    long long r = atoll(right);
    int count = 0;

    /* Generate palindromic roots and check their squares */
    for (int len = 1; len <= 9; len++) {
        int start = (len == 1) ? 1 : pow(10, (len - 1) / 2);
        int end = pow(10, (len + 1) / 2);
        for (int i = start; i < end; i++) {
            char str[20];
            sprintf(str, "%d", i);
            int strLen = strlen(str);

            /* Create odd-length palindrome */
            char palOdd[40];
            strcpy(palOdd, str);
            for (int j = strLen - 2; j >= 0; j--) {
                palOdd[strLen + (strLen - 2 - j)] = str[j];
            }
            palOdd[strLen + strLen - 1] = '\0';
            long long palNumOdd = atoll(palOdd);
            long long squareOdd = palNumOdd * palNumOdd;
            if (squareOdd > r) break;
            if (squareOdd >= l) {
                char squareStr[40];
                sprintf(squareStr, "%lld", squareOdd);
                int isPal = 1;
                int sqLen = strlen(squareStr);
                for (int k = 0; k < sqLen / 2; k++) {
                    if (squareStr[k] != squareStr[sqLen - 1 - k]) {
                        isPal = 0;
                        break;
                    }
                }
                if (isPal) count++;
            }

            /* Create even-length palindrome */
            char palEven[40];
            strcpy(palEven, str);
            for (int j = strLen - 1; j >= 0; j--) {
                palEven[strLen + (strLen - 1 - j)] = str[j];
            }
            palEven[strLen + strLen] = '\0';
            long long palNumEven = atoll(palEven);
            long long squareEven = palNumEven * palNumEven;
            if (squareEven > r) continue;
            if (squareEven >= l) {
                char squareStr[40];
                sprintf(squareStr, "%lld", squareEven);
                int isPal = 1;
                int sqLen = strlen(squareStr);
                for (int k = 0; k < sqLen / 2; k++) {
                    if (squareStr[k] != squareStr[sqLen - 1 - k]) {
                        isPal = 0;
                        break;
                    }
                if (isPal) count++;
                    
                }
                if (isPal) count++;
                }
                }
                }
}
