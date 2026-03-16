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

class Solution {
public:
    string convertToTitle(int columnNumber) {
        string result;
        while (columnNumber > 0) {
            columnNumber--; // Adjust for 0-based index
            char ch = 'A' + (columnNumber % 26);
            result = ch + result; // Prepend character
            columnNumber /= 26;
        }
        return result;          
    }
};
