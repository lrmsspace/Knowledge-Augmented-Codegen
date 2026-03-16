// Source: https://leetcode.com/problems/max-difference-you-can-get-from-changing-an-integer/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer num. You will apply the following steps to num two separate times:
//
//
// 	Pick a digit x (0 <= x <= 9).
// 	Pick another digit y (0 <= y <= 9). Note y can be equal to x.
// 	Replace all the occurrences of x in the decimal representation of num by y.
//
//
// Let a and b be the two results from applying the operation to num independently.
//
// Return the max difference between a and b.
//
// Note that neither a nor b may have any leading zeros, and must not be 0.
//
// Example:
// Input: num = 555
// Output: 888
// Explanation: The first time pick x = 5 and y = 9 and store the new integer in a.
// The second time pick x = 5 and y = 1 and store the new integer in b.
// We have now a = 999 and b = 111 and max difference = 888
//
// Constraints:
// 1 <= num <= 108
//

class Solution {
public:
    int maxDiff(int num) {
        string numStr = to_string(num);

        // Generate maximum number
        string maxNumStr = numStr;
        char toReplaceMax = ' ';
        for (char digit : maxNumStr) {
            if (digit != '9') {
                toReplaceMax = digit;
                break;
            }
        }
        if (toReplaceMax != ' ') {
            for (char& digit : maxNumStr) {
                if (digit == toReplaceMax) {
                    digit = '9';
                }
            }
        }

        // Generate minimum number
        string minNumStr = numStr;
        char toReplaceMin = ' ';
        if (minNumStr[0] != '1') {
            toReplaceMin = minNumStr[0];
            for (char& digit : minNumStr) {
                if (digit == toReplaceMin) {
                    digit = '1';
                }
            }
        } else {
            for (size_t i = 1; i < minNumStr.size(); ++i) {
                if (minNumStr[i] != '0' && minNumStr[i] != '1') {
                    toReplaceMin = minNumStr[i];
                    break;
                }
            }
            if (toReplaceMin != ' ') {
                for (size_t i = 1; i < minNumStr.size(); ++i) {
                    if (minNumStr[i] == toReplaceMin) {
                        minNumStr[i] = '0';
                    }
                }
            }
        }

        int maxNum = stoi(maxNumStr);
        int minNum = stoi(minNumStr);

        return maxNum - minNum;         
    }
};
