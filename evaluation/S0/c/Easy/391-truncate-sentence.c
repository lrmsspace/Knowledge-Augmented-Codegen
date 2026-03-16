// Source: https://leetcode.com/problems/truncate-sentence/   |   Difficulty: Easy
//
// Problem Description:
// A sentence is a list of words that are separated by a single space with no leading or trailing spaces. Each of the words consists of only uppercase and lowercase English letters (no punctuation).
//
//
// 	For example, "Hello World", "HELLO", and "hello world hello world" are all sentences.
//
//
// You are given a sentence s​​​​​​ and an integer k​​​​​​. You want to truncate s​​​​​​ such that it contains only the first k​​​​​​ words. Return s​​​​​​ after truncating it.
//
// Example:
// Input: s = "Hello how are you Contestant", k = 4
// Output: "Hello how are you"
// Explanation:
// The words in s are ["Hello", "how" "are", "you", "Contestant"].
// The first 4 words are ["Hello", "how", "are", "you"].
// Hence, you should return "Hello how are you".
//
// Constraints:
// 1 <= s.length <= 500
// 	k is in the range [1, the number of words in s].
// 	s consist of only lowercase and uppercase English letters and spaces.
// 	The words in s are separated by a single space.
// 	There are no leading or trailing spaces.
//

char* truncateSentence(char* s, int k) {
    int space_count = 0;
    char* ptr = s;

    while (*ptr != '\0') {
        if (*ptr == ' ') {
            space_count++;
            if (space_count == k) {
                *ptr = '\0';
                break;
            }
        }
        ptr++;
    }

    return s;       
}
