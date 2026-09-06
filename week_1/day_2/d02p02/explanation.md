# Day 2 Problem 2: DNA Palindrome Detection

## Problem Statement
Find all palindromic DNA sequences within a genome that may cause genetic diseases. Palindromic sequences in DNA can form secondary structures that lead to mutations and genetic disorders.

## Core Concepts

### What is a DNA Palindrome?
- **DNA Structure**: Double helix with complementary strands
- **Complementary Base Pairing**: A↔T, G↔C
- **Palindrome**: Sequence that reads the same on both strands (complement wise)
- Example: `5'-GAATTC-3'` paired with `3'-CTTAAG-5'` is a palindrome

### Biological Significance
- **Restriction sites**: Used in genetic engineering
- **Hairpin loops**: Can cause genomic instability
- **Disease association**: Some palindromes linked to genetic disorders
- **Repetitive sequences**: Can lead to expansions causing Huntington's disease

### Why Manacher's Algorithm?
- **Naive Approach**: O(n²) for finding all palindromes
- **Manacher's Algorithm**: O(n) - optimal and elegant
- Leverages mirror symmetry of palindromes to avoid redundant checks
- Can find both odd-length and even-length palindromes

## Example Scenario

```
DNA Sequence: ACGCTACGTACGTACGTA

Palindromes to find:
- "ACGTA" → reads same with complements
- "CGCG" → inverted repeats
- Single characters are technically palindromes

Expected Output: List of all palindromic substrings and their positions
```

## Understanding the Problem

### Input
- Long DNA sequence (string of A, T, G, C)
- Minimum length threshold (optional)
- Maximum length to search for

### Output
- All palindromic substrings
- OR palindromes above certain length threshold
- Positions and sequences

### Challenges
- Very long sequences (millions of bases)
- Many overlapping palindromes
- Different types of palindromes (odd vs even length)

## Algorithm Intuition: Manacher's Algorithm

### Key Insight
If we know palindromes around a center, we can use that information to quickly find palindromes elsewhere.

### Center Expansion
For each possible center in string:
- Try to expand left and right simultaneously
- Stop when characters don't match
- Record the palindrome length

### Optimization Technique
- Maintain a "center" and "right boundary" of previously found palindrome
- For new position, check if it's within a known palindrome
- If yes, use mirror position's information to start expansion
- This eliminates many redundant comparisons

### Why It's Tricky
- Must handle both odd-length (center on character) and even-length (center between characters)
- Common technique: Add a separator between characters to unify both cases

## Example Walkthrough

```
Original: ABACABA
With separators: #A#B#A#C#A#B#A#

Center at each position:
#A: radius 1 → "A"
#A#B: radius 1 → "A"
#A#B#A: radius 3 → "ABA" (odd palindrome found!)
... and so on

The radius tells you the expansion distance
```

## What You Should Think About

1. **Character Types**:
   - DNA has only 4 characters (A, T, G, C)
   - How does this limited alphabet affect palindrome frequency?

2. **Biological Constraints**:
   - Should you consider reverse complement as separate?
   - Are overlapping palindromes important?

3. **Efficiency Matters**:
   - Processing millions of bases requires O(n) solution
   - O(n²) will be too slow

4. **Edge Cases**:
   - Single character (trivial palindrome)
   - Entire sequence is palindrome
   - No palindromes except single chars
   - Repeated sequences (like "AAAA")

## Implementation Hints (Without Code)

- Create a helper function to check if two characters match
- Understand how to use previously computed information
- Think about what "mirror" means in the context of a known palindrome
- Consider how to track the rightmost boundary of expansion

## Practice Questions

1. How would you find only palindromes of length ≥ k?
2. Can you identify which palindromes might form stable hairpin loops?
3. How would you find the longest palindrome efficiently?
4. What if you needed overlapping palindromes?

## Related Algorithms
- **Naive Expansion**: O(n²) - simpler but slower
- **Suffix Tree/Array**: Can find palindromes in O(n) with preprocessing
- **Rolling Hash**: O(n) average case, though less elegant

## Real-World Applications
- Identifying genomic instability hotspots
- Finding restriction enzyme sites
- Detecting tandem repeats
- Locating hairpin sequences in molecular biology
- Identifying genomic rearrangement points
