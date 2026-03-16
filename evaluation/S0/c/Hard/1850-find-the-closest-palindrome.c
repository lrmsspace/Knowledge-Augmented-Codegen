// Source: https://leetcode.com/problems/find-the-closest-palindrome/   |   Difficulty: Hard
//
// Problem Description:
// Given a string n representing an integer, return the closest integer (not including itself), which is a palindrome. If there is a tie, return the smaller one.
//
// The closest is defined as the absolute difference minimized between two integers.
//
// Example:
// Input: n = "123"
// Output: "121"
//
// Constraints:
// 1 <= n.length <= 18
// 	n consists of only digits.
// 	n does not have leading zeros.
// 	n is representing an integer in the range [1, 1018 - 1].
//

char* nearestPalindromic(char* n) {
    long long num = atoll(n);
    int len = strlen(n);
    long long candidates[5];
    candidates[0] = (long long)pow(10, len - 1) - 1; // 999...9
    candidates[1] = (long long)pow(10, len) + 1;     // 100...001

    long long prefix = atoll(n) / (long long)pow(10, (len + 1) / 2);
    for (int i = -1; i <= 1; i++) {
        long long newPrefix = prefix + i;
        char newPrefixStr[20];
        sprintf(newPrefixStr, "%lld", newPrefix);
        int newLen = strlen(newPrefixStr);
        char palinStr[40];
        strcpy(palinStr, newPrefixStr);
        for (int j = (len % 2 == 0 ? newLen - 1 : newLen - 2); j >= 0; j--) {
            palinStr[newLen + (newLen - 1 - j)] = newPrefixStr[j];
        }
        palinStr[newLen + (len % 2 == 0 ? newLen : newLen - 1)] = '\0';
        candidates[i + 2] = atoll(palinStr);
    }

    long long closest = -1;
    for (int i = 0; i < 5; i++) {
        if (candidates[i] != num) {
            if (closest == -1 ||
                llabs(candidates[i] - num) < llabs(closest - num) ||
                (llabs(candidates[i] - num) == llabs(closest - num) && candidates[i] < closest)) {
                closest = candidates[i];
            }
        }
    }

    char *result = (char *)malloc(20 * sizeof(char));
    sprintf(result, "%lld", closest);
    return result;      
}
