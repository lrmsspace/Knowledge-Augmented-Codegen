// Source: https://leetcode.com/problems/brace-expansion-ii/   |   Difficulty: Hard
//
// Problem Description:
// Under the grammar given below, strings can represent a set of lowercase words. Let R(expr) denote the set of words the expression represents.
//
// The grammar can best be understood through simple examples:
//
//
// 	Single letters represent a singleton set containing that word.
// 	
// 		R("a") = {"a"}
// 		R("w") = {"w"}
// 	
// 	
// 	When we take a comma-delimited list of two or more expressions, we take the union of possibilities.
// 	
// 		R("{a,b,c}") = {"a","b","c"}
// 		R("{{a,b},{b,c}}") = {"a","b","c"} (notice the final set only contains each word at most once)
// 	
// 	
// 	When we concatenate two expressions, we take the set of possible concatenations between two words where the first word comes from the first expression and the second word comes from the second expression.
// 	
// 		R("{a,b}{c,d}") = {"ac","ad","bc","bd"}
// 		R("a{b,c}{d,e}f{g,h}") = {"abdfg", "abdfh", "abefg", "abefh", "acdfg", "acdfh", "acefg", "acefh"}
// 	
// 	
//
//
// Formally, the three rules for our grammar:
//
//
// 	For every lowercase letter x, we have R(x) = {x}.
// 	For expressions e1, e2, ... , ek with k >= 2, we have R({e1, e2, ...}) = R(e1) ∪ R(e2) ∪ ...
// 	For expressions e1 and e2, we have R(e1 + e2) = {a + b for (a, b) in R(e1) × R(e2)}, where + denotes concatenation, and × denotes the cartesian product.
//
//
// Given an expression representing a set of words under the given grammar, return the sorted list of words that the expression represents.
//
// Example:
// Input: expression = "{a,b}{c,{d,e}}"
// Output: ["ac","ad","ae","bc","bd","be"]
//
// Constraints:
// 1 <= expression.length <= 60
// 	expression[i] consists of '{', '}', ','or lowercase English letters.
// 	The given expression represents a set of words based on the grammar given in the description.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** braceExpansionII(char* expression, int* returnSize) {
    // Implementation of brace expansion II using a stack-based approach

    #define MAX_WORDS 1000
    #define MAX_WORD_LEN 60

    typedef struct {
        char words[MAX_WORDS][MAX_WORD_LEN];
        int size;
    } WordSet;

    WordSet stack[100];
    int stackTop = -1;

    void push(WordSet ws) {
        stack[++stackTop] = ws;
    }

    WordSet pop() {
        return stack[stackTop--];
    }

    WordSet unionSets(WordSet a, WordSet b) {
        WordSet result;
        result.size = 0;
        for (int i = 0; i < a.size; i++) {
            strcpy(result.words[result.size++], a.words[i]);
        }
        for (int i = 0; i < b.size; i++) {
            int found = 0;
            for (int j = 0; j < a.size; j++) {
                if (strcmp(b.words[i], a.words[j]) == 0) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                strcpy(result.words[result.size++], b.words[i]);
            }
        }
        return result;
    }

    WordSet concatSets(WordSet a, WordSet b) {
        WordSet result;
        result.size = 0;
        for (int i = 0; i < a.size; i++) {
            for (int j = 0; j < b.size; j++) {
                char combined[MAX_WORD_LEN];
                snprintf(combined, sizeof(combined), "%s%s", a.words[i], b.words[j]);
                strcpy(result.words[result.size++], combined);
            }
        }
        return result;
    }

    WordSet currentSet;
    currentSet.size = 0;

    for (int i = 0; expression[i] != '\0'; ) {
        if (expression[i] == '{') {
            push(currentSet);
            currentSet.size = 0;
            i++;
        } else if (expression[i] == '}') {
            WordSet prevSet = pop();
            currentSet = unionSets(prevSet, currentSet);
            i++;
        } else if (expression[i] == ',') {
            push(currentSet);
            currentSet.size = 0;
            i++;
        } else {
            WordSet newSet;
            newSet.size = 1;
            newSet.words[0][0] = expression[i];
            newSet.words[0][1] = '\0';
            currentSet = concatSets(currentSet.size == 0 ? (WordSet){{"",
0}} : currentSet, newSet);

            i++;
        }
    }

    // Collect results
    char** result = (char**)malloc(currentSet.size * sizeof(char*));
    for (int i = 0; i < currentSet.size; i++) {
        result[i] = strdup(currentSet.words[i]);
    }

    // Sort results
    int compare(const void* a, const void* b) {
        return strcmp(*(const char**)a, *(const char**)b);
    }
    qsort(result, currentSet.size, sizeof(char*), compare);

    *returnSize = currentSet.size;
    return result;  
}
