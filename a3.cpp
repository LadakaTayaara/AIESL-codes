/*
 * Problem: Cryptarithmetic Problem (Assignment 3)
 * Algorithm: Backtracking Search / Constraint Satisfaction Problem (CSP)
 *
 * Problem Description:
 * - Given an equation of words: Word1 + Word2 = Word3 (e.g. SEND + MORE = MONEY).
 * - Each distinct letter must be mapped to a unique digit from 0 to 9.
 * - Leading letters of words cannot be zero (d[w[0]] != 0).
 * - The mathematical equation value(Word1) + value(Word2) == value(Word3) must hold true.
 *
 * Algorithm Strategy (Backtracking CSP):
 * - Extract all unique characters from w1, w2, w3 into vector 'ch'.
 * - Recursively assign an unused digit (0..9) to each character one-by-one.
 * - Once all letters have been assigned digits (i == ch.size()), verify:
 *   1. No leading zeros: d[w1[0]] != 0, d[w2[0]] != 0, d[w3[0]] != 0.
 *   2. Arithmetic constraint: val(w1) + val(w2) == val(w3).
 * - If valid, return true; otherwise backtrack and try the next available digit.
 */

#include <iostream>
#include <vector>
using namespace std;

string w1, w2, w3;  // The three input words (e.g. SEND, MORE, MONEY)
vector<char> ch;     // List of all unique letters that need digits
int d[128];          // Mapping table: d[char] = assigned digit (0..9)
bool used[10];       // Tracks which digits (0..9) have already been assigned

// Converts a word string to its numeric value based on current digit assignments
long long val(string s) {
    long long v = 0;
    for (char c : s)
        v = v * 10 + d[(unsigned char)c];
    return v;
}

// Recursive backtracking solver: assigns a digit to the i-th unique character
bool solve(size_t i) {
    // Base Case: All unique characters have been assigned a digit
    if (i == ch.size()) {
        // Leading letters cannot be zero, and arithmetic equation must balance
        return d[(unsigned char)w1[0]] && 
               d[(unsigned char)w2[0]] && 
               d[(unsigned char)w3[0]] && 
               (val(w1) + val(w2) == val(w3));
    }

    // Try assigning each available digit (0 to 9) to character ch[i]
    for (int dig = 0; dig < 10; dig++) {
        if (!used[dig]) {
            used[dig] = 1;                     // Mark digit as used
            d[(unsigned char)ch[i]] = dig;     // Assign digit to letter

            if (solve(i + 1)) return true;     // Recurse to assign next letter

            used[dig] = 0;                     // Backtrack: unmark digit
        }
    }
    return false; // No valid assignment found in this branch
}

int main() {
    // Input format: SEND MORE MONEY
    if (!(cin >> w1 >> w2 >> w3)) return 0;

    // Collect all unique characters from the three words
    bool seen[128] = {0};
    for (char c : w1 + w2 + w3) {
        if (!seen[(unsigned char)c]) {
            seen[(unsigned char)c] = 1;
            ch.push_back(c);
        }
    }

    // If more than 10 unique letters exist, it is impossible (only digits 0-9)
    if (ch.size() > 10) {
        cout << "No solution (more than 10 unique letters)\n";
        return 0;
    }

    // Run backtracking search starting from the first character (index 0)
    if (solve(0)) {
        // Print character to digit mapping
        for (char c : ch) cout << c << "=" << d[(unsigned char)c] << " ";
        // Print verified numerical equation
        cout << "\n" << val(w1) << " + " << val(w2) << " = " << val(w3) << "\n";
    } else {
        cout << "No solution found.\n";
    }
}
