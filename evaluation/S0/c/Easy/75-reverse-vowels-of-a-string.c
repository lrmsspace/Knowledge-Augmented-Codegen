// Source: https://leetcode.com/problems/reverse-vowels-of-a-string/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s, reverse only all the vowels in the string and return it.
//
// The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in both lower and upper cases, more than once.
//
// Example:
// Input: s = "IceCreAm"
//
// Output: "AceCreIm"
//
// Explanation:
//
// The vowels in s are ['I', 'e', 'e', 'A']. On reversing the vowels, s becomes "AceCreIm".
//
// Constraints:
// 1 <= s.length <= 3 * 105
// 	s consist of printable ASCII characters.
//

char* reverseVowels(char* s) {
    int left = 0;
    int right = strlen(s) - 1;
    char vowels[] = "aeiouAEIOU";

    while (left < right) {
        while (left < right && !strchr(vowels, s[left])) {
            left++;
        }
        while (left < right && !strchr(vowels, s[right])) {
            right--;
        }
        if (left < right) {
            char temp = s[left];
            s[left] = s[right];
            s[right] = temp;
            left++;
            right--;
        }
    }
    return s;       
}
