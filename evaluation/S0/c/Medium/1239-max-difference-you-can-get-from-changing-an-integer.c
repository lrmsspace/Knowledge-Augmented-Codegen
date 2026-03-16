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

int maxDiff(int num) {
    char numStr[12];
    sprintf(numStr, "%d", num);

    // Create maxNum by replacing the first non-'9' digit with '9'
    char maxNumStr[12];
    strcpy(maxNumStr, numStr);
    for (int i = 0; maxNumStr[i] != '\0'; i++) {
        if (maxNumStr[i] != '9') {
            char toReplace = maxNumStr[i];
            for (int j = 0; maxNumStr[j] != '\0'; j++) {
                if (maxNumStr[j] == toReplace) {
                    maxNumStr[j] = '9';
                }
            }
            break;
        }
    }

    // Create minNum by replacing the first digit with '1' or the first non-'0' digit with '0'
    char minNumStr[12];
    strcpy(minNumStr, numStr);
    if (minNumStr[0] != '1') {
        char toReplace = minNumStr[0];
        for (int j = 0; minNumStr[j] != '\0'; j++) {
            if (minNumStr[j] == toReplace) {
                minNumStr[j] = '1';
            }
        }
    } else {
        for (int i = 1; minNumStr[i] != '\0'; i++) {
            if (minNumStr[i] != '0' && minNumStr[i] != '1') {
                char toReplace = minNumStr[i];
                for (int j = 0; minNumStr[j] != '\0'; j++) {
                    if (minNumStr[j] == toReplace) {
                        minNumStr[j] = '0';
                    }
                }
                break;
            }
        }
    }

    int maxNum = atoi(maxNumStr);
    int minNum = atoi(minNumStr);

    return maxNum - minNum;     
}
