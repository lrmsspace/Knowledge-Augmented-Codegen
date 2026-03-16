// Source: https://leetcode.com/problems/sentence-similarity-iii/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings sentence1 and sentence2, each representing a sentence composed of words. A sentence is a list of words that are separated by a single space with no leading or trailing spaces. Each word consists of only uppercase and lowercase English characters.
//
// Two sentences s1 and s2 are considered similar if it is possible to insert an arbitrary sentence (possibly empty) inside one of these sentences such that the two sentences become equal. Note that the inserted sentence must be separated from existing words by spaces.
//
// For example,
//
//
// 	s1 = "Hello Jane" and s2 = "Hello my name is Jane" can be made equal by inserting "my name is" between "Hello" and "Jane" in s1.
// 	s1 = "Frog cool" and s2 = "Frogs are cool" are not similar, since although there is a sentence "s are" inserted into s1, it is not separated from "Frog" by a space.
//
//
// Given two sentences sentence1 and sentence2, return true if sentence1 and sentence2 are similar. Otherwise, return false.
//
// Example:
// Input: sentence1 = "My name is Haley", sentence2 = "My Haley"
//
// Output: true
//
// Explanation:
//
// sentence2 can be turned to sentence1 by inserting "name is" between "My" and "Haley".
//
// Constraints:
// 1 <= sentence1.length, sentence2.length <= 100
// 	sentence1 and sentence2 consist of lowercase and uppercase English letters and spaces.
// 	The words in sentence1 and sentence2 are separated by a single space.
//

bool areSentencesSimilar(char* sentence1, char* sentence2) {
    char* words1[101];
    char* words2[101];
    int len1 = 0, len2 = 0;

    char* token = strtok(sentence1, " ");
    while (token) {
        words1[len1++] = token;
        token = strtok(NULL, " ");
    }

    token = strtok(sentence2, " ");
    while (token) {
        words2[len2++] = token;
        token = strtok(NULL, " ");
    }

    int i = 0, j = 0;

    while (i < len1 && j < len2 && strcmp(words1[i], words2[j]) == 0) {
        i++;
        j++;
    }

    while (i < len1 && j < len2 && strcmp(words1[len1 - 1], words2[len2 - 1]) == 0) {
        len1--;
        len2--;
    }

    return i == len1 || j == len2;      
}
