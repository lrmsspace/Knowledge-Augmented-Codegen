// Source: https://leetcode.com/problems/maximum-number-of-balloons/   |   Difficulty: Easy
//
// Problem Description:
// Given a string text, you want to use the characters of text to form as many instances of the word "balloon" as possible.
//
// You can use each character in text at most once. Return the maximum number of instances that can be formed.
//
// Example:
// Input: text = "nlaebolko"
// Output: 1
//
// Constraints:
// 1 <= text.length <= 104
// 	text consists of lower case English letters only.
//
//
//  
// Note: This question is the same as  2287: Rearrange Characters to Make Target String.
//

int maxNumberOfBalloons(char* text) {
    int count[26] = {0};
    for (int i = 0; text[i]; i++) {
        count[text[i] - 'a']++;
    }
    int res = count['b' - 'a'];
    res = res < count['a' - 'a'] ? res : count['a' - 'a'];
    res = res < count['l' - 'a'] / 2 ? res : count['l' - 'a'] / 2;
    res = res < count['o' - 'a'] / 2 ? res : count['o' - 'a'] / 2;
    res = res < count['n' - 'a'] ? res : count['n' - 'a'];
    return res;     
}
