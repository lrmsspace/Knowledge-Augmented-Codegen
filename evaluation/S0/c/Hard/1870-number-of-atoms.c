// Source: https://leetcode.com/problems/number-of-atoms/   |   Difficulty: Hard
//
// Problem Description:
// Given a string formula representing a chemical formula, return the count of each atom.
//
// The atomic element always starts with an uppercase character, then zero or more lowercase letters, representing the name.
//
// One or more digits representing that element's count may follow if the count is greater than 1. If the count is 1, no digits will follow.
//
//
// 	For example, "H2O" and "H2O2" are possible, but "H1O2" is impossible.
//
//
// Two formulas are concatenated together to produce another formula.
//
//
// 	For example, "H2O2He3Mg4" is also a formula.
//
//
// A formula placed in parentheses, and a count (optionally added) is also a formula.
//
//
// 	For example, "(H2O2)" and "(H2O2)3" are formulas.
//
//
// Return the count of all elements as a string in the following form: the first name (in sorted order), followed by its count (if that count is more than 1), followed by the second name (in sorted order), followed by its count (if that count is more than 1), and so on.
//
// The test cases are generated so that all the values in the output fit in a 32-bit integer.
//
// Example:
// Input: formula = "H2O"
// Output: "H2O"
// Explanation: The count of elements are {'H': 2, 'O': 1}.
//
// Constraints:
// 1 <= formula.length <= 1000
// 	formula consists of English letters, digits, '(', and ')'.
// 	formula is always valid.
//

char* countOfAtoms(char* formula) {
    int len = strlen(formula);
    int *stack = (int*)malloc((len + 1) * sizeof(int));
    int top = -1;
    int *counts = (int*)calloc(52, sizeof(int)); // 26 lowercase + 26 uppercase
    int i = 0;

    while (i < len) {
        if (formula[i] == '(') {
            stack[++top] = -1; // Marker for '('
            i++;
        } else if (formula[i] == ')') {
            i++;
            int mult = 0;
            while (i < len && formula[i] >= '0' && formula[i] <= '9') {
                mult = mult * 10 + (formula[i] - '0');
                i++;
            }
            if (mult == 0) mult = 1;

            // Pop until '(' marker
            int tempCounts[52] = {0};
            while (top >= 0 && stack[top] != -1) {
                int idx = stack[top--];
                tempCounts[idx] += 1;
            }
            top--; // Pop the '(' marker

            // Multiply and push back
            for (int j = 0; j < 52; j++) {
                if (tempCounts[j] > 0) {
                    for (int k = 0; k < mult * tempCounts[j]; k++) {
                        stack[++top] = j;
                    }
                }
            }
        } else {
            // Parse element name
            int start = i;
            i++; // Move past uppercase letter
            while (i < len && formula[i] >= 'a' && formula[i] <= 'z') {
                i++;
            }
            char elem[3] = {0};
            strncpy(elem, &formula[start], i - start);

            // Parse count
            int count = 0;
            while (i < len && formula[i] >= '0' && formula[i] <= '9') {
                count = count * 10 + (formula[i] - '0');
                i++;
            }
            if (count == 0) count = 1;

            // Map element to index
            int idx;
            if (elem[1] == '\0') { // Single letter element
                idx = elem[0] - 'A';
            } else { // Two  
                idx = 26 + (elem[0] - 'A') * 26 + (elem[1] - 'a');
            }
            for (int j = 0; j < count; j++) {
                stack[++top] = idx;
            }
        }
    }
    // Count occurrences
    for (int i = 0; i <= top; i++) {
        counts[stack[i]] += 1;
    }
    free(stack);
    // Build result string
    char *result = (char*)malloc(3000 * sizeof(char));
    result[0] = '\0';
    char buffer[20];
    for (int i = 0; i < 52; i++) {
        if (counts[i] > 0) {
            char elem[3] = {0};
            if (i < 26) {
                elem[0] = 'A' + i;
            } else {
                elem[0] = 'A' + (i - 26) / 26;
                elem[1] = 'a' + (i - 26) % 26;
            }
            strcat(result, elem);
            if (counts[i] > 1) {
                sprintf(buffer, "%d", counts[i]);
                strcat(result, buffer);
            }
        }
    }
    free(counts);
    return result;   
}
