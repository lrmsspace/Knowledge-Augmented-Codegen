// Source: https://leetcode.com/problems/count-items-matching-a-rule/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array items, where each items[i] = [typei, colori, namei] describes the type, color, and name of the ith item. You are also given a rule represented by two strings, ruleKey and ruleValue.
//
// The ith item is said to match the rule if one of the following is true:
//
//
// 	ruleKey == "type" and ruleValue == typei.
// 	ruleKey == "color" and ruleValue == colori.
// 	ruleKey == "name" and ruleValue == namei.
//
//
// Return the number of items that match the given rule.
//
// Example:
// Input: items = [["phone","blue","pixel"],["computer","silver","lenovo"],["phone","gold","iphone"]], ruleKey = "color", ruleValue = "silver"
// Output: 1
// Explanation: There is only one item matching the given rule, which is ["computer","silver","lenovo"].
//
// Constraints:
// 1 <= items.length <= 104
// 	1 <= typei.length, colori.length, namei.length, ruleValue.length <= 10
// 	ruleKey is equal to either "type", "color", or "name".
// 	All strings consist only of lowercase letters.
//

int countMatches(char*** items, int itemsSize, int* itemsColSize, char* ruleKey, char* ruleValue) {
    int count = 0;
    int ruleIndex;

    if (strcmp(ruleKey, "type") == 0) {
        ruleIndex = 0;
    } else if (strcmp(ruleKey, "color") == 0) {
        ruleIndex = 1;
    } else { // ruleKey == "name"
        ruleIndex = 2;
    }

    for (int i = 0; i < itemsSize; i++) {
        if (strcmp(items[i][ruleIndex], ruleValue) == 0) {
            count++;
        }
    }

    return count;       
}
