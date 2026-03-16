// Source: https://leetcode.com/problems/thousand-separator/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer n, add a dot (".") as the thousands separator and return it in string format.
//
// Example:
// Input: n = 987
// Output: "987"
//
// Constraints:
// 0 <= n <= 231 - 1
//

char* thousandSeparator(int n) {
    if (n == 0) {
        char* result = (char*)malloc(2 * sizeof(char));
        result[0] = '0';
        result[1] = '\0';
        return result;
    }

    char buffer[20];
    int index = 0;
    int count = 0;

    while (n > 0) {
        if (count == 3) {
            buffer[index++] = '.';
            count = 0;
        }
        buffer[index++] = (n % 10) + '0';
        n /= 10;
        count++;
    }

    char* result = (char*)malloc((index + 1) * sizeof(char));
    for (int i = 0; i < index; i++) {
        result[i] = buffer[index - i - 1];
    }
    result[index] = '\0';

    return result;      
}
