// Source: https://leetcode.com/problems/zigzag-conversion/   |   Difficulty: Medium
//
// Problem Description:
// The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)
//
//
// P   A   H   N
// A P L S I I G
// Y   I   R
//
//
// And then read line by line: "PAHNAPLSIIGYIR"
//
// Write the code that will take a string and make this conversion given a number of rows:
//
//
// string convert(string s, int numRows);
//
// Example:
// Input: s = "PAYPALISHIRING", numRows = 3
// Output: "PAHNAPLSIIGYIR"
//
// Constraints:
// 1 <= s.length <= 1000
// 	s consists of English letters (lower-case and upper-case), ',' and '.'.
// 	1 <= numRows <= 1000
//

char* convert(char* s, int numRows) {
    int len = 0;
    while (s[len]) len++;
    if (numRows == 1 || numRows >= len) return s;

    char* result = (char*)malloc((len + 1) * sizeof(char));
    int cycleLen = 2 * numRows - 2;
    int index = 0;

    for (int row = 0; row < numRows; row++) {
        for (int j = 0; j + row < len; j += cycleLen) {
            result[index++] = s[j + row];
            if (row != 0 && row != numRows - 1 && j + cycleLen - row < len) {
                result[index++] = s[j + cycleLen - row];
            }
        }
    }
    result[index] = '\0';
    return result;      
}
