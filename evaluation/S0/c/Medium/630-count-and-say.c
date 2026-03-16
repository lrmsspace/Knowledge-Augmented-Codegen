// Source: https://leetcode.com/problems/count-and-say/   |   Difficulty: Medium
//
// Problem Description:
// The count-and-say sequence is a sequence of digit strings defined by the recursive formula:
//
//
// 	countAndSay(1) = "1"
// 	countAndSay(n) is the run-length encoding of countAndSay(n - 1).
//
//
// Run-length encoding (RLE) is a string compression method that works by replacing consecutive identical characters (repeated 2 or more times) with the concatenation of the character and the number marking the count of the characters (length of the run). For example, to compress the string "3322251" we replace "33" with "23", replace "222" with "32", replace "5" with "15" and replace "1" with "11". Thus the compressed string becomes "23321511".
//
// Given a positive integer n, return the nth element of the count-and-say sequence.
//
// Example:
// Input: n = 4
//
// Output: "1211"
//
// Explanation:
//
//
// countAndSay(1) = "1"
// countAndSay(2) = RLE of "1" = "11"
// countAndSay(3) = RLE of "11" = "21"
// countAndSay(4) = RLE of "21" = "1211"
//
// Constraints:
// 1 <= n <= 30
//
//
//  
// Follow up: Could you solve it iteratively?
//

char* countAndSay(int n) {
    if (n <= 0) return NULL;
    if (n == 1) {
        char *res = (char *)malloc(2 * sizeof(char));
        res[0] = '1';
        res[1] = '\0';
        return res;
    }

    char *prev = countAndSay(n - 1);
    int len = strlen(prev);
    char *res = (char *)malloc(2 * len * sizeof(char) + 1); // worst case scenario
    int index = 0;

    for (int i = 0; i < len;) {
        char current_char = prev[i];
        int count = 0;

        while (i < len && prev[i] == current_char) {
            count++;
            i++;
        }

        index += sprintf(res + index, "%d%c", count, current_char);
    }

    res[index] = '\0';
    free(prev);
    return res;     
}
