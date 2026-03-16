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
// Helpful references (internal KB):
// - Suffix Automaton (graph, tree, string, recursion)
//   • When to use: When needing to efficiently represent all substrings of a string and perform various string operations like counting occurrences, finding distinct substrings, or pattern matching. It is particularly useful for problems involving properties of all substrings or suffixes.
//   • Idea: A Suffix Automaton is a minimal deterministic finite automaton that accepts all suffixes of a given string. It efficiently encodes all substrings and their occurrences, typically constructed in O(N) time and space for a string of length N.
//   • Invariants: Each state in the automaton corresponds to a unique endpos set.; All substrings represented by a state are suffixes of the longest string in that state's endpos set.
//   • Tips: Understand the endpos equivalence classes and suffix links.; Construction is typically incremental, character by character.
//   • Pitfalls: Complexity of implementation can be high due to many edge cases.; Incorrectly handling suffix links during construction.
// - Disjoint Set Union (ds, linked-list, union-find, dfs)
//   • When to use: Use when you need to maintain a collection of disjoint sets and perform union operations to merge sets or find the representative of an element's set efficiently. It's suitable for problems involving dynamic connectivity or grouping elements.
//   • Idea: Disjoint Set Union (DSU) is a data structure that stores a collection of disjoint sets and supports two primary operations: finding the representative of an element's set and merging two sets. It achieves nearly constant time complexity for these operations with path compression and union by rank/size optimizations.
//   • Invariants: Every element `i` belongs to exactly one set, represented by `find(i)`.; If `parent[i] == i`, then `i` is the representative (root) of its set.
//   • Tips: Implement path compression in `find` for optimal performance.; Use union by size or rank to maintain balanced trees.
//   • Pitfalls: Omitting path compression or union by rank/size can degrade performance to O(N).; Failing to correctly update auxiliary data stored at representatives during a union operation.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdlib.h>
#include <string.h>

typedef struct {
    char** data;
    int size;
    int capacity;
} StringSet;

StringSet* createSet() {
    StringSet* set = (StringSet*)malloc(sizeof(StringSet));
    set->data = (char**)malloc(sizeof(char*) * 100);
    set->size = 0;
    set->capacity = 100;
    return set;
}

void addToSet(StringSet* set, char* str) {
    if (set->size >= set->capacity) {
        set->capacity *= 2;
        set->data = (char**)realloc(set->data, sizeof(char*) * set->capacity);
    }
    set->data[set->size] = (char*)malloc(strlen(str) + 1);
    strcpy(set->data[set->size], str);
    set->size++;
}

int compareStrings(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

StringSet* parseExpression(char* expr, int* pos);

StringSet* parseGroup(char* expr, int* pos) {
    StringSet* result = createSet();
    addToSet(result, "");
    
    while (*pos < strlen(expr) && expr[*pos] != '}') {
        if (expr[*pos] == ',') {
            (*pos)++;
            continue;
        }
        
        StringSet* current = parseExpression(expr, pos);
        
        // Cartesian product
        StringSet* newResult = createSet();
        for (int i = 0; i < result->size; i++) {
            for (int j = 0; j < current->size; j++) {
                char buffer[100] = {0};
                strcpy(buffer, result->data[i]);
                strcat(buffer, current->data[j]);
                addToSet(newResult, buffer);
            }
        }
        
        // Free old result
        for (int i = 0; i < result->size; i++) {
            free(result->data[i]);
        }
        free(result->data);
        free(result);
        result = newResult;
        
        // Free current
        for (int i = 0; i < current->size; i++) {
            free(current->data[i]);
        }
        free(current->data);
        free(current);
    }
    
    return result;
}

StringSet* parseExpression(char* expr, int* pos) {
    StringSet* result = createSet();
    addToSet(result, "");
    
    while (*pos < strlen(expr) && expr[*pos] != '}' && expr[*pos] != ',') {
        if (expr[*pos] == '{') {
            (*pos)++;
            StringSet* group = parseGroup(expr, pos);
            (*pos)++; // Skip '}'
            
            // Cartesian product
            StringSet* newResult = createSet();
            for (int i = 0; i < result->size; i++) {
                for (int j = 0; j < group->size; j++) {
                    char buffer[100] = {0};
                    strcpy(buffer, result->data[i]);
                    strcat(buffer, group->data[j]);
                    addToSet(newResult, buffer);
                }
            }
            
            // Free old result
            for (int i = 0; i < result->size; i++) {
                free(result->data[i]);
            }
            free(result->data);
            free(result);
            result = newResult;
            
            // Free group
            for (int i = 0; i < group->size; i++) {
                free(group->data[i]);
            }
            free(group->data);
            free(group);
        } else {
            char c = expr[*pos];
            (*pos)++;
            
            // Cartesian product with single character
            StringSet* newResult = createSet();
            char buffer[100] = {0};
            for (int i = 0; i < result->size; i++) {
                strcpy(buffer, result->data[i]);
                buffer[strlen(result->data[i])] = c;
                buffer[strlen(result->data[i]) + 1] = '\0';
                addToSet(newResult, buffer);
            }
            
            // Free old result
            for (int i = 0; i < result->size; i++) {
                free(result->data[i]);
            }
            free(result->data);
            free(result);
            result = newResult;
        }
    }
    
    return result;
}

char** braceExpansionII(char* expression, int* returnSize) {
    int pos = 0;
    StringSet* result = parseExpression(expression, &pos);
    
    // Remove duplicates and sort
    qsort(result->data, result->size, sizeof(char*), compareStrings);
    
    // Remove duplicates
    int writeIdx = 0;
    for (int i = 0; i < result->size; i++) {
        if (i == 0 || strcmp(result->data[i], result->data[writeIdx - 1]) != 0) {
            if (writeIdx != i) {
                free(result->data[writeIdx]);
                result->data[writeIdx] = result->data[i];
            }
            writeIdx++;
        } else {
            free(result->data[i]);
        }
    }
    
    result->size = writeIdx;
    
    *returnSize = result->size;
    char** finalResult = result->data;
    free(result);
    
    return finalResult;
}
