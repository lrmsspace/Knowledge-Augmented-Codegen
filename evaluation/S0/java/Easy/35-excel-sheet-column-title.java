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
    public String convertToTitle(int columnNumber) {
        StringBuilder result = new StringBuilder();

        while (columnNumber > 0) {
            columnNumber--; // Adjust for 0-based index
            int remainder = columnNumber % 26;
            char currentChar = (char) ('A' + remainder);
            result.insert(0, currentChar); // Prepend character
            columnNumber /= 26;
        }

        return result.toString();           
    }
}
