// Source: https://leetcode.com/problems/faulty-keyboard/   |   Difficulty: Easy
//
// Problem Description:
// Your laptop keyboard is faulty, and whenever you type a character 'i' on it, it reverses the string that you have written. Typing other characters works as expected.
//
// You are given a 0-indexed string s, and you type each character of s using your faulty keyboard.
//
// Return the final string that will be present on your laptop screen.
//
// Example:
// Input: s = "string"
// Output: "rtsng"
// Explanation: 
// After typing first character, the text on the screen is "s".
// After the second character, the text is "st". 
// After the third character, the text is "str".
// Since the fourth character is an 'i', the text gets reversed and becomes "rts".
// After the fifth character, the text is "rtsn". 
// After the sixth character, the text is "rtsng". 
// Therefore, we return "rtsng".
//
// Constraints:
// 1 <= s.length <= 100
// 	s consists of lowercase English letters.
// 	s[0] != 'i'
//

char* finalString(char* s) {
    char stack[101];
    int top = -1;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == 'i') {
            // Reverse the stack
            for (int left = 0, right = top; left < right; left++, right--) {
                char temp = stack[left];
                stack[left] = stack[right];
                stack[right] = temp;
            }
        } else {
            // Push character onto the stack
            stack[++top] = s[i];
        }
    }

    // Null-terminate the resulting string
    stack[top + 1] = '\0';

    // Allocate memory for the result and copy the stack content
    char* result = (char*)malloc((top + 2) * sizeof(char));
    strcpy(result, stack);

    return result;      
}
