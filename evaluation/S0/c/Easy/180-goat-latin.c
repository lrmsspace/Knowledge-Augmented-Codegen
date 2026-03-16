// Source: https://leetcode.com/problems/goat-latin/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string sentence that consist of words separated by spaces. Each word consists of lowercase and uppercase letters only.
//
// We would like to convert the sentence to "Goat Latin" (a made-up language similar to Pig Latin.) The rules of Goat Latin are as follows:
//
//
// 	If a word begins with a vowel ('a', 'e', 'i', 'o', or 'u'), append "ma" to the end of the word.
//
// 	
// 		For example, the word "apple" becomes "applema".
// 	
// 	
// 	If a word begins with a consonant (i.e., not a vowel), remove the first letter and append it to the end, then add "ma".
// 	
// 		For example, the word "goat" becomes "oatgma".
// 	
// 	
// 	Add one letter 'a' to the end of each word per its word index in the sentence, starting with 1.
// 	
// 		For example, the first word gets "a" added to the end, the second word gets "aa" added to the end, and so on.
// 	
// 	
//
//
// Return the final sentence representing the conversion from sentence to Goat Latin.
//
// Example:
// Input: sentence = "I speak Goat Latin"
// Output: "Imaa peaksmaaa oatGmaaaa atinLmaaaaa"
//
// Constraints:
// 1 <= sentence.length <= 150
// 	sentence consists of English letters and spaces.
// 	sentence has no leading or trailing spaces.
// 	All the words in sentence are separated by a single space.
//

char* toGoatLatin(char* sentence) {
    int n = strlen(sentence);
    char* result = (char*)malloc(3 * n + 1); // Allocate enough space
    int resIndex = 0;
    int wordIndex = 1;
    int i = 0;

    while (i < n) {
        // Skip spaces
        while (i < n && sentence[i] == ' ') {
            i++;
        }
        if (i >= n) break;

        int start = i;
        // Find the end of the word
        while (i < n && sentence[i] != ' ') {
            i++;
        }
        int end = i;

        // Process the word
        char firstChar = sentence[start];
        if (firstChar == 'a' || firstChar == 'e' || firstChar == 'i' || firstChar == 'o' || firstChar == 'u' ||
            firstChar == 'A' || firstChar == 'E' || firstChar == 'I' || firstChar == 'O' || firstChar == 'U') {
            // Word starts with a vowel
            for (int j = start; j < end; j++) {
                result[resIndex++] = sentence[j];
            }
        } else {
            // Word starts with a consonant
            for (int j = start + 1; j < end; j++) {
                result[resIndex++] = sentence[j];
            }
            result[resIndex++] = firstChar;
        }

        // Append "ma"
        result[resIndex++] = 'm';
        result[resIndex++] = 'a';

        // Append 'a's based on word index
        for (int j = 0; j < wordIndex; j++) {
            result[resIndex++] = 'a';
        }

        // Add a space if not the last word
        if (i < n) {
            result[resIndex++] = ' ';
        }

        wordIndex++;
    }

    result[resIndex] = '\0'; // Null-terminate the string
    return result;      
}
