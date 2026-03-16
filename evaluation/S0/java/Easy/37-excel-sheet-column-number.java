// Source: https://leetcode.com/problems/excel-sheet-column-number/   |   Difficulty: Easy
//
// Problem Description:
// Given a string columnTitle that represents the column title as appears in an Excel sheet, return its corresponding column number.
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
// Input: columnTitle = "A"
// Output: 1
//
// Constraints:
// 1 <= columnTitle.length <= 7
// 	columnTitle consists only of uppercase English letters.
// 	columnTitle is in the range ["A", "FXSHRXW"].
//

class Solution {
    public int titleToNumber(String columnTitle) {
        int result = 0;
        for (int i = 0; i < columnTitle.length(); i++) {
            char c = columnTitle.charAt(i);
            result = result * 26 + (c - 'A' + 1);
        }
        return result;          
    }
}
