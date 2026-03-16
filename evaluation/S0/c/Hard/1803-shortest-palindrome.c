// Source: https://leetcode.com/problems/shortest-palindrome/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s. You can convert s to a palindrome by adding characters in front of it.
//
// Return the shortest palindrome you can find by performing this transformation.
//
// Example:
// Input: s = "aacecaaa"
// Output: "aaacecaaa"
//
// Constraints:
// 0 <= s.length <= 5 * 104
// 	s consists of lowercase English letters only.
//

char* shortestPalindrome(char* s) {
    int n = strlen(s);
    if (n == 0) return s;

    // Create the modified string for KMP
    int modLen = 2 * n + 1;
    char *modStr = (char*)malloc(modLen + 1);
    for (int i = 0; i < n; i++) {
        modStr[2 * i] = s[i];
        modStr[2 * i + 1] = '#';
    }
    modStr[modLen - 1] = '#';
    modStr[modLen] = '\0';

    // Compute KMP table
    int *kmpTable = (int*)malloc(modLen * sizeof(int));
    kmpTable[0] = 0;
    for (int i = 1, j = 0; i < modLen; ) {
        if (modStr[i] == modStr[j]) {
            j++;
            kmpTable[i] = j;
            i++;
        } else {
            if (j > 0) {
                j = kmpTable[j - 1];
            } else {
                kmpTable[i] = 0;
                i++;
            }
        }
    }

    // Length of the longest palindromic prefix
    int palinLen = kmpTable[modLen - 1];
    free(kmpTable);
    free(modStr);

    // Construct the result
    int addLen = n - palinLen;
    char *result = (char*)malloc(n + addLen + 1);
    for (int i = 0; i < addLen; i++) {
        result[i] = s[n - 1 - i];
    }
    strcpy(result + addLen, s);

    return result;      
}
