// Source: https://leetcode.com/problems/restore-ip-addresses/   |   Difficulty: Medium
//
// Problem Description:
// A valid IP address consists of exactly four integers separated by single dots. Each integer is between 0 and 255 (inclusive) and cannot have leading zeros.
//
//
// 	For example, "0.1.2.201" and "192.168.1.1" are valid IP addresses, but "0.011.255.245", "192.168.1.312" and "192.168@1.1" are invalid IP addresses.
//
//
// Given a string s containing only digits, return all possible valid IP addresses that can be formed by inserting dots into s. You are not allowed to reorder or remove any digits in s. You may return the valid IP addresses in any order.
//
// Example:
// Input: s = "25525511135"
// Output: ["255.255.11.135","255.255.111.35"]
//
// Constraints:
// 1 <= s.length <= 20
// 	s consists of digits only.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** restoreIpAddresses(char* s, int* returnSize) {
    int len = strlen(s);
    char** result = (char**)malloc(1000 * sizeof(char*));
    *returnSize = 0;

    for (int i = 1; i < 4 && i < len - 2; i++) {
        for (int j = i + 1; j < i + 4 && j < len - 1; j++) {
            for (int k = j + 1; k < j + 4 && k < len; k++) {
                if (len - k > 3) continue;

                char part1[4], part2[4], part3[4], part4[4];
                strncpy(part1, s, i);
                part1[i] = '\0';
                strncpy(part2, s + i, j - i);
                part2[j - i] = '\0';
                strncpy(part3, s + j, k - j);
                part3[k - j] = '\0';
                strncpy(part4, s + k, len - k);
                part4[len - k] = '\0';

                if ((part1[0] == '0' && strlen(part1) > 1) || (part2[0] == '0' && strlen(part2) > 1) ||
                    (part3[0] == '0' && strlen(part3) > 1) || (part4[0] == '0' && strlen(part4) > 1))
                    continue;

                int num1 = atoi(part1);
                int num2 = atoi(part2);
                int num3 = atoi(part3);
                int num4 = atoi(part4);

                if (num1 <= 255 && num2 <= 255 && num3 <= 255 && num4 <= 255) {
                    char* ipAddress = (char*)malloc(16 * sizeof(char));
                    sprintf(ipAddress, "%d.%d.%d.%d", num1, num2, num3, num4);
                    result[*returnSize] = ipAddress;
                    (*returnSize)++;
                }
            }
        }
    }

    return result;      
}
