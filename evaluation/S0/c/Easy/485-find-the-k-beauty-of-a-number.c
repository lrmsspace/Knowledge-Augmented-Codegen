// Source: https://leetcode.com/problems/find-the-k-beauty-of-a-number/   |   Difficulty: Easy
//
// Problem Description:
// The k-beauty of an integer num is defined as the number of substrings of num when it is read as a string that meet the following conditions:
//
//
// 	It has a length of k.
// 	It is a divisor of num.
//
//
// Given integers num and k, return the k-beauty of num.
//
// Note:
//
//
// 	Leading zeros are allowed.
// 	0 is not a divisor of any value.
//
//
// A substring is a contiguous sequence of characters in a string.
//
// Example:
// Input: num = 240, k = 2
// Output: 2
// Explanation: The following are the substrings of num of length k:
// - "24" from "240": 24 is a divisor of 240.
// - "40" from "240": 40 is a divisor of 240.
// Therefore, the k-beauty is 2.
//
// Constraints:
// 1 <= num <= 109
// 	1 <= k <= num.length (taking num as a string)
//

int divisorSubstrings(int num, int k) {
    char str[12];
    sprintf(str, "%d", num);
    int len = strlen(str);
    int count = 0;

    for (int i = 0; i <= len - k; i++) {
        char substr[12];
        strncpy(substr, str + i, k);
        substr[k] = '\0';
        int subNum = atoi(substr);

        if (subNum != 0 && num % subNum == 0) {
            count++;
        }
    }

    return count;       
}
