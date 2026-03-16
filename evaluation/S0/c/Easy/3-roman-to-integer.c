// Source: https://leetcode.com/problems/roman-to-integer/   |   Difficulty: Easy
//
// Problem Description:
// Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.
//
//
// Symbol       Value
// I             1
// V             5
// X             10
// L             50
// C             100
// D             500
// M             1000
//
// For example, 2 is written as II in Roman numeral, just two ones added together. 12 is written as XII, which is simply X + II. The number 27 is written as XXVII, which is XX + V + II.
//
// Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not IIII. Instead, the number four is written as IV. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as IX. There are six instances where subtraction is used:
//
//
// 	I can be placed before V (5) and X (10) to make 4 and 9. 
// 	X can be placed before L (50) and C (100) to make 40 and 90. 
// 	C can be placed before D (500) and M (1000) to make 400 and 900.
//
//
// Given a roman numeral, convert it to an integer.
//
// Example:
// Input: s = "III"
// Output: 3
// Explanation: III = 3.
//
// Constraints:
// 1 <= s.length <= 15
// 	s contains only the characters ('I', 'V', 'X', 'L', 'C', 'D', 'M').
// 	It is guaranteed that s is a valid roman numeral in the range [1, 3999].
//

int romanToInt(char* s) {
    int map[26] = {0};
    map['I' - 'A'] = 1;
    map['V' - 'A'] = 5;
    map['X' - 'A'] = 10;
    map['L' - 'A'] = 50;
    map['C' - 'A'] = 100;
    map['D' - 'A'] = 500;
    map['M' - 'A'] = 1000;

    int total = 0;
    int prev_value = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        int current_value = map[s[i] - 'A'];

        if (current_value > prev_value) {
            total += current_value - 2 * prev_value;
        } else {
            total += current_value;
        }

        prev_value = current_value;
    }

    return total;       
}
