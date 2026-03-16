// Source: https://leetcode.com/problems/unique-morse-code-words/   |   Difficulty: Easy
//
// Problem Description:
// International Morse Code defines a standard encoding where each letter is mapped to a series of dots and dashes, as follows:
//
//
// 	'a' maps to ".-",
// 	'b' maps to "-...",
// 	'c' maps to "-.-.", and so on.
//
//
// For convenience, the full table for the 26 letters of the English alphabet is given below:
//
//
// [".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."]
//
// Given an array of strings words where each word can be written as a concatenation of the Morse code of each letter.
//
//
// 	For example, "cab" can be written as "-.-..--...", which is the concatenation of "-.-.", ".-", and "-...". We will call such a concatenation the transformation of a word.
//
//
// Return the number of different transformations among all words we have.
//
// Example:
// Input: words = ["gin","zen","gig","msg"]
// Output: 2
// Explanation: The transformation of each word is:
// "gin" -> "--...-."
// "zen" -> "--...-."
// "gig" -> "--...--."
// "msg" -> "--...--."
// There are 2 different transformations: "--...-." and "--...--.".
//
// Constraints:
// 1 <= words.length <= 100
// 	1 <= words[i].length <= 12
// 	words[i] consists of lowercase English letters.
//

int uniqueMorseRepresentations(char** words, int wordsSize) {
    const char* morse[26] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",
                             ".---","-.-",".-..","--","-.","---",".--.","--.-",
                             ".-.","...","-","..-","...-",".--","-..-","-.--",
                             "--.."};
    char transformations[wordsSize][49]; // max length 12 * 4 + 1 for null terminator
    int uniqueCount = 0;

    for (int i = 0; i < wordsSize; i++) {
        transformations[i][0] = '\0'; // Initialize empty string
        for (int j = 0; words[i][j] != '\0'; j++) {
            strcat(transformations[i], morse[words[i][j] - 'a']);
        }
    }

    for (int i = 0; i < wordsSize; i++) {
        int isUnique = 1;
        for (int j = 0; j < i; j++) {
            if (strcmp(transformations[i], transformations[j]) == 0) {
                isUnique = 0;
                break;
            }
        }
        if (isUnique) {
            uniqueCount++;
        }
    }

    return uniqueCount;     
}
