// Source: https://leetcode.com/problems/decrypt-string-from-alphabet-to-integer-mapping/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s formed by digits and '#'. We want to map s to English lowercase characters as follows:
//
//
// 	Characters ('a' to 'i') are represented by ('1' to '9') respectively.
// 	Characters ('j' to 'z') are represented by ('10#' to '26#') respectively.
//
//
// Return the string formed after mapping.
//
// The test cases are generated so that a unique mapping will always exist.
//
// Example:
// Input: s = "10#11#12"
// Output: "jkab"
// Explanation: "j" -> "10#" , "k" -> "11#" , "a" -> "1" , "b" -> "2".
//
// Constraints:
// 1 <= s.length <= 1000
// 	s consists of digits and the '#' letter.
// 	s will be a valid string such that mapping is always possible.
//

char* freqAlphabets(char* s) {
    int n = strlen(s);
    char* result = (char*)malloc((n + 1) * sizeof(char));
    int index = 0;
    
    for (int i = 0; i < n; ) {
        if (i + 2 < n && s[i + 2] == '#') {
            int num = (s[i] - '0') * 10 + (s[i + 1] - '0');
            result[index++] = (char)('a' + num - 1);
            i += 3;
        } else {
            int num = s[i] - '0';
            result[index++] = (char)('a' + num - 1);
            i += 1;
        }
    }
    
    result[index] = '\0';
    return result;      
}
