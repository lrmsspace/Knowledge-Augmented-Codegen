// Source: https://leetcode.com/problems/excel-sheet-column-title/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer columnNumber, return its corresponding column title as it appears in an Excel sheet.
//
// For example:
//
//
// A -> 1
// B -> 2
// C -> 3
// ...
// Z -> 26
// AA -> 27
// AB -> 28 
// ...
//
// Example:
// Input: columnNumber = 1
// Output: "A"
//
// Constraints:
// 1 <= columnNumber <= 231 - 1
//

char* convertToTitle(int columnNumber) {
    char* result = (char*)malloc(8 * sizeof(char)); // Allocate enough space for the result
    int index = 0;

    while (columnNumber > 0) {
        columnNumber--; // Adjust for 0-based indexing
        int remainder = columnNumber % 26;
        result[index++] = 'A' + remainder; // Convert to corresponding character
        columnNumber /= 26;
    }

    result[index] = '\0'; // Null-terminate the string

    // Reverse the string to get the correct order
    for (int i = 0; i < index / 2; i++) {
        char temp = result[i];
        result[i] = result[index - i - 1];
        result[index - i - 1] = temp;
    }

    return result;      
}
