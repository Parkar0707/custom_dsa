# DNA Sequence Mutation Detection

## Problem Overview

Genomic researchers study DNA sequences from different organisms or time points to detect mutations and evolutionary changes. A key task is finding the **longest common subsequence (LCS)** between two genome segments—the longest sequence of genetic material they share (not necessarily contiguous).

Your task is to find the **LCS of two DNA sequences** using a combination of **sliding window and hashing** techniques for optimization.

## Context & Real-World Application

In bioinformatics and genetics:
- DNA sequences are represented as strings (A, T, G, C nucleotides)
- Comparing genome versions reveals mutations and evolution
- LCS helps identify conserved regions (functionally important)
- Sequence alignment is fundamental to:
  - Disease diagnosis (viral mutations)
  - Drug development (protein targets)
  - Evolutionary tree construction
- Naive approach is expensive; optimizations critical for large genomes

## Key Concepts to Understand

### Longest Common Subsequence (LCS)
- A subsequence doesn't need to be contiguous in the original string
- Example: "AGGTAB" and "GXTXAYB" share LCS "GTAB" (length 4)
- Unlike substring or subarray, elements can be non-adjacent

### Classic Dynamic Programming Approach
- Build a 2D DP table: dp[i][j] = length of LCS of first i chars of seq1 and first j chars of seq2
- Time: O(m × n), Space: O(m × n)
- Works well for moderate sequence lengths

### Sliding Window + Hashing Optimization
- **Hashing**: Convert subsequences to hash values for fast comparison
- **Sliding window**: Maintain windows of candidate LCS candidates
- **Rolling hash**: Efficiently compute hash for next window (avoid recomputing from scratch)
- Reduces constant factors or enables different algorithmic approaches
- Useful when m, n are large (billions of bases in whole genome)

## Example Scenario

DNA sequences from two species:

```
Species A: AGGTAB
Species B: GXTXAYB

Comparing for common genetic material (LCS):

Visual alignment (one possible LCS):
A G G T A B
  G     T A   
  G X T X A Y B
  
Common subsequence: G T A (length 3)
But also: A T A B (non-obvious)
And: G T A B (length 4) ← Longest

LCS = "GTAB" (length 4)

This tells researchers:
- These sequences share core genetic material "GTAB"
- The A and B nucleotides in different positions suggest evolution
- Mutations: B to X at position 3, insertion of Y
```

## What You Should Explore

1. **Problem definition**:
   - Subsequence vs. substring: Do elements need to be contiguous?
   - For LCS: No, they can be interspersed (skip characters allowed)
   - Example: LCS("AGGTAB", "GXTXAYB") = "GTAB"

2. **Naive approach (baseline)**:
   - Generate all subsequences of one string (exponential: 2^m subsequences)
   - Check which are present in the other (could use hashing)
   - Time: O(2^m × n) — prohibitively expensive
   - Good for understanding, bad for large sequences

3. **DP approach (standard)**:
   - 2D table: dp[i][j] = LCS length of seq1[0...i-1] and seq2[0...j-1]
   - Recurrence: If seq1[i-1] == seq2[j-1], dp[i][j] = 1 + dp[i-1][j-1]
   - Otherwise: dp[i][j] = max(dp[i-1][j], dp[i][j-1])
   - Space can be optimized to O(min(m, n)) using two rows

4. **Sliding window + hashing optimization**:
   - Why would you use this over DP?
     - Specific LCS length constraint? (e.g., must find LCS of exactly length k)
     - Approximate LCS? (e.g., hashing finds candidates)
     - Multiple query sequences? (preprocess hashes of seq1, query seq2)
   - Consider: Rolling hash for efficient sliding of windows

5. **Output requirements**:
   - Just the length of LCS? (easier)
   - Reconstruct the actual LCS string? (requires backtracking)
   - All possible LCS of maximum length? (multiple solutions)

6. **Genome-scale considerations**:
   - Human genome: ~3 billion base pairs
   - DP table of 3e9 × 3e9 is infeasible (memory explosion)
   - Real systems use: suffix trees, space-efficient DP, approximate methods

## Example Input/Output Format

**Input:**
- Two DNA sequences (strings of A, T, G, C)
- Optionally: length constraint or window size for sliding window approach

**Output:**
- Length of the longest common subsequence
- The LCS string itself (reconstructed from path)
- Optionally: starting indices in each sequence

## Hints on Approach

- Start with the classic DP solution to verify correctness
- Understand how to reconstruct the LCS string from the DP table (backtracking)
- Research rolling hash for efficient window sliding
- Consider: Why combine sliding window with hashing?
  - Is the goal to find candidates then verify?
  - Or reduce constant factors in the DP approach?
- Think about preprocessing: Hash all windows of seq1, then scan seq2

## Why This Matters in DSA

This problem teaches:
- **Dynamic programming** for string problems
- **Subsequence vs. substring** distinction
- **Hashing for pattern matching** and candidate generation
- **Sliding window** for efficient candidate enumeration
- **Space-time tradeoffs** in algorithms
- **Real-world constraints**: Genome-scale data requires optimization

---

**Difficulty:** Medium to Hard  
**Primary Concept:** Longest Common Subsequence, Dynamic Programming  
**Secondary Concepts:** Hashing, Sliding window, String manipulation
