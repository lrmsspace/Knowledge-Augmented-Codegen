// Source: https://leetcode.com/problems/unique-3-digit-even-numbers/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of digits called digits. Your task is to determine the number of distinct three-digit even numbers that can be formed using these digits.
//
// Note: Each copy of a digit can only be used once per number, and there may not be leading zeros.
//
// Example:
// Input: digits = [1,2,3,4]
//
// Output: 12
//
// Explanation: The 12 distinct 3-digit even numbers that can be formed are 124, 132, 134, 142, 214, 234, 312, 314, 324, 342, 412, and 432. Note that 222 cannot be formed because there is only 1 copy of the digit 2.
//
// Constraints:
// 3 <= digits.length <= 10
// 	0 <= digits[i] <= 9
//

int totalNumbers(int* digits, int digitsSize) {
    int count = 0;
    int used[10] = {0};

    for (int i = 0; i < digitsSize; i++) {
        used[digits[i]]++;
    }

    for (int hundred = 1; hundred <= 9; hundred++) {
        if (used[hundred] == 0) continue;
        used[hundred]--;

        for (int ten = 0; ten <= 9; ten++) {
            if (used[ten] == 0) continue;
            used[ten]--;

            for (int unit = 0; unit <= 8; unit += 2) {
                if (used[unit] == 0) continue;
                count++;
            }

            used[ten]++;
        }

        used[hundred]++;
    }

    return count;       
}
