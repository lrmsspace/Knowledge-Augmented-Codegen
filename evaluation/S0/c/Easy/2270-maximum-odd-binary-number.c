// Source: https://leetcode.com/problems/maximum-odd-binary-number/   |   Difficulty: Easy
//
// Problem Description:
// You are given a binary string s that contains at least one '1'.
//
// You have to rearrange the bits in such a way that the resulting binary number is the maximum odd binary number that can be created from this combination.
//
// Return a string representing the maximum odd binary number that can be created from the given combination.
//
// Note that the resulting string can have leading zeros.
//
// Example:
// Input: s = "010"
// Output: "001"
// Explanation: Because there is just one '1', it must be in the last position. So the answer is "001".
//
// Constraints:
// 1 <= s.length <= 100
// 	s consists only of '0' and '1'.
// 	s contains at least one '1'.
//

char* maximumOddBinaryNumber(char* s) {
    int count0 = 0, count1 = 0;
    for (int i = 0; s[i]; i++) {
        if (s[i] == '0') {
            count0++;
        } else {
            count1++;
        }
    }

    char* result = (char*)malloc((count0 + count1 + 1) * sizeof(char));
    for (int i = 0; i < count0; i++) {
        result[i] = '1';
    }
    for (int i = count0; i < count0 + count1 - 1; i++) {
        result[i] = '0';
    }
    result[count0 + count1 - 1] = '1';
    result[count0 + count1] = '\0';

    return result;      
}
