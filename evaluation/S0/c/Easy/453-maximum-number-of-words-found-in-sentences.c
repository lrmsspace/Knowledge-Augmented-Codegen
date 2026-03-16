// Source: https://leetcode.com/problems/maximum-number-of-words-found-in-sentences/   |   Difficulty: Easy
//
// Problem Description:
// A sentence is a list of words that are separated by a single space with no leading or trailing spaces.
//
// You are given an array of strings sentences, where each sentences[i] represents a single sentence.
//
// Return the maximum number of words that appear in a single sentence.
//
// Example:
// Input: sentences = ["alice and bob love leetcode", "i think so too", "this is great thanks very much"]
// Output: 6
// Explanation: 
// - The first sentence, "alice and bob love leetcode", has 5 words in total.
// - The second sentence, "i think so too", has 4 words in total.
// - The third sentence, "this is great thanks very much", has 6 words in total.
// Thus, the maximum number of words in a single sentence comes from the third sentence, which has 6 words.
//
// Constraints:
// 1 <= sentences.length <= 100
// 	1 <= sentences[i].length <= 100
// 	sentences[i] consists only of lowercase English letters and ' ' only.
// 	sentences[i] does not have leading or trailing spaces.
// 	All the words in sentences[i] are separated by a single space.
//

int mostWordsFound(char** sentences, int sentencesSize) {
    int max_words = 0;
    for (int i = 0; i < sentencesSize; i++) {
        int word_count = 1; // Start with 1 to count the first word
        for (char* p = sentences[i]; *p != '\0'; p++) {
            if (*p == ' ') {
                word_count++;
            }
        }
        if (word_count > max_words) {
            max_words = word_count;
        }
    }
    return max_words;       
}
