// Source: https://leetcode.com/problems/largest-multiple-of-three/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of digits digits, return the largest multiple of three that can be formed by concatenating some of the given digits in any order. If there is no answer return an empty string.
//
// Since the answer may not fit in an integer data type, return the answer as a string. Note that the returning answer must not contain unnecessary leading zeros.
//
// Example:
// Input: digits = [8,1,9]
// Output: "981"
//
// Constraints:
// 1 <= digits.length <= 104
// 	0 <= digits[i] <= 9
//

char* largestMultipleOfThree(int* digits, int digitsSize) {
    int count[10] = {0};
    int sum = 0;
    for (int i = 0; i < digitsSize; ++i) {
        count[digits[i]]++;
        sum += digits[i];
    }

    int mod = sum % 3;
    if (mod != 0) {
        int rem = mod;
        for (int i = 1; i <= 9; i += 3) {
            while (count[i] > 0 && rem > 0) {
                count[i]--;
                rem--;
            }
            if (rem == 0) break;
        }
        if (rem > 0) {
            rem = 3 - mod;
            for (int i = 2; i <= 8; i += 3) {
                while (count[i] > 0 && rem > 0) {
                    count[i]--;
                    rem--;
                }
                if (rem == 0) break;
            }
        }
    }

    char *result = (char*)malloc((digitsSize + 1) * sizeof(char));
    if (!result) return NULL;
    int pos = 0;
    for (int i = 9; i >= 0; --i) {
        while (count[i] > 0) {
            result[pos++] = '0' + i;
            count[i]--;
        }
    }
    if (pos == 0) {
        result[0] = '\0';
    } else if (result[0] == '0') {
        result[1] = '\0';
    } else {
        result[pos] = '\0';
    }
    return result;      
}
