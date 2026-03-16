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

/**
 * @param {string} sentence
 * @return {string}
 */
var toGoatLatin = function(sentence) {
    const vowels = new Set(['a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U']);
    const words = sentence.split(' ');
    const result = [];
    for (let i = 0; i < words.length; i++) {
        let word = words[i];
        if (vowels.has(word[0])) {
            word += 'ma';
        } else {
            word = word.slice(1) + word[0] + 'ma';
        }
        word += 'a'.repeat(i + 1);
        result.push(word);
    }
    return result.join(' ');
};
