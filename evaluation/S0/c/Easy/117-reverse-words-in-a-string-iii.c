// Source: https://leetcode.com/problems/reverse-words-in-a-string-iii/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order.
//
// Example:
// Input: s = "Let's take LeetCode contest"
// Output: "s'teL ekat edoCteeL tsetnoc"
//
// Constraints:
// 1 <= s.length <= 5 * 104
// 	s contains printable ASCII characters.
// 	s does not contain any leading or trailing spaces.
// 	There is at least one word in s.
// 	All the words in s are separated by a single space.
//

char* reverseWords(char* s) {
    char* start = s;
    char* end = s;
    char* temp;
    
    while (*end) {
        // Move end to the end of the current word
        while (*end && *end != ' ') {
            end++;
        }
        
        // Reverse the current word
        temp = end - 1;
        while (start < temp) {
            char ch = *start;
            *start++ = *temp;
            *temp-- = ch;
        }
        
        // Move to the next word
        if (*end) {
            end++; // Skip the space
        }
        start = end;
    }
    
    return s;       
}
