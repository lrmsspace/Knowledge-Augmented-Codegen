// Source: https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s and an integer k, return the maximum number of vowel letters in any substring of s with length k.
//
// Vowel letters in English are 'a', 'e', 'i', 'o', and 'u'.
//
// Example:
// Input: s = "abciiidef", k = 3
// Output: 3
// Explanation: The substring "iii" contains 3 vowel letters.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters.
// 	1 <= k <= s.length
//

int maxVowels(char* s, int k) {
    int max_vowels = 0;
    int current_vowels = 0;
    int left = 0;
    int right = 0;
    
    while (s[right] != '\0') {
        // Add the right character if it's a vowel
        if (s[right] == 'a' || s[right] == 'e' || s[right] == 'i' || s[right] == 'o' || s[right] == 'u') {
            current_vowels++;
        }
        
        // If the window size exceeds k, remove the left character
        if (right - left + 1 > k) {
            if (s[left] == 'a' || s[left] == 'e' || s[left] == 'i' || s[left] == 'o' || s[left] == 'u') {
                current_vowels--;
            }
            left++;
        }
        
        // Update max_vowels if the current window size is k
        if (right - left + 1 == k) {
            if (current_vowels > max_vowels) {
                max_vowels = current_vowels;
            }
        }
        
        right++;
    }
    
    return max_vowels;      
}
