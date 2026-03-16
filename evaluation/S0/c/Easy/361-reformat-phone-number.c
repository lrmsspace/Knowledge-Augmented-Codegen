// Source: https://leetcode.com/problems/reformat-phone-number/   |   Difficulty: Easy
//
// Problem Description:
// You are given a phone number as a string number. number consists of digits, spaces ' ', and/or dashes '-'.
//
// You would like to reformat the phone number in a certain manner. Firstly, remove all spaces and dashes. Then, group the digits from left to right into blocks of length 3 until there are 4 or fewer digits. The final digits are then grouped as follows:
//
//
// 	2 digits: A single block of length 2.
// 	3 digits: A single block of length 3.
// 	4 digits: Two blocks of length 2 each.
//
//
// The blocks are then joined by dashes. Notice that the reformatting process should never produce any blocks of length 1 and produce at most two blocks of length 2.
//
// Return the phone number after formatting.
//
// Example:
// Input: number = "1-23-45 6"
// Output: "123-456"
// Explanation: The digits are "123456".
// Step 1: There are more than 4 digits, so group the next 3 digits. The 1st block is "123".
// Step 2: There are 3 digits remaining, so put them in a single block of length 3. The 2nd block is "456".
// Joining the blocks gives "123-456".
//
// Constraints:
// 2 <= number.length <= 100
// 	number consists of digits and the characters '-' and ' '.
// 	There are at least two digits in number.
//

char* reformatNumber(char* number) {
    char digits[100] = {0};
    int len = 0;
    for (int i = 0; number[i]; i++) {
        if (number[i] >= '0' && number[i] <= '9') {
            digits[len++] = number[i];
        }
    }

    char* result = (char*)malloc(150 * sizeof(char));
    int index = 0;
    int i = 0;

    while (len - i > 4) {
        result[index++] = digits[i++];
        result[index++] = digits[i++];
        result[index++] = digits[i++];
        result[index++] = '-';
    }

    if (len - i == 4) {
        result[index++] = digits[i++];
        result[index++] = digits[i++];
        result[index++] = '-';
        result[index++] = digits[i++];
        result[index++] = digits[i++];
    } else {
        while (i < len) {
            result[index++] = digits[i++];
        }
    }

    if (index > 0 && result[index - 1] == '-') {
        index--; // Remove trailing dash if exists
    }

    result[index] = '\0';
    return result;      
}
