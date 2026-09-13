# Day 15 Problem 2: DNA Sequence Alignment - Needleman-Wunsch Algorithm

## Problem Statement
Implement the Needleman-Wunsch algorithm to find the optimal global alignment of two DNA sequences. Calculate similarity scores and trace back to find the actual alignment with gap penalties.

## Core Concepts

### Needleman-Wunsch Algorithm
- **Definition**: Dynamic programming algorithm for global sequence alignment
- **Goal**: Find optimal alignment of entire sequences (not just substrings)
- **Scoring**: Match/mismatch scores + gap penalties
- **Traceback**: Reconstructs alignment from DP table
- **Biological Relevance**: Aligns entire genes or proteins

### Scoring System
```
Match (same letter): +1 or higher
Mismatch (different): -1
Gap (insertion/deletion): -1 or -2
```

### DP Table Structure
- **Dimensions**: (len(seq1)+1) × (len(seq2)+1)
- **dp[i][j]**: Best alignment score for first i chars of seq1 and first j chars of seq2
- **Recurrence**: Considers match, mismatch, or gap options

## Key Concepts to Understand

1. **Global vs Local**: Needleman-Wunsch is global (Smith-Waterman is local)
2. **Traceback**: Reconstruct alignment by backtracking through DP table
3. **Gap Penalties**: Can be constant or affine (depends on gap length)
4. **Multiple Alignments**: Single DP finds one optimal, may have ties
5. **Complexity**: Quadratic in sequence length

## Problem Variations to Consider

- **Local Alignment**: Smith-Waterman for finding similar regions
- **Affine Gaps**: Different cost for gap opening vs extension
- **Substitution Matrix**: BLOSUM/PAM for protein alignment
- **Multiple Sequences**: Progressive alignment algorithms
- **Approximate Matching**: Allow some gaps/mismatches at ends

## Example Walkthrough

### Input: Two DNA Sequences
```
seq1 = "AGGTAB"
seq2 = "GXTXAYB"

Scoring:
  Match: +1
  Mismatch: -1
  Gap: -1
```

### Step 1: Initialize DP Table
```
        ""  G   X   T   X   A   Y   B
    ""   0  -1  -2  -3  -4  -5  -6  -7
    A   -1
    G   -2
    G   -3
    T   -4
    A   -5
    B   -6
```

### Step 2: Fill DP Table
For each cell dp[i][j]:
```
Option 1: Match/Mismatch from dp[i-1][j-1]
  Cost = dp[i-1][j-1] + score(seq1[i-1], seq2[j-1])

Option 2: Delete from seq1 (gap in seq2)
  Cost = dp[i-1][j] - 1

Option 3: Insert to seq1 (gap in seq1)
  Cost = dp[i][j-1] - 1

dp[i][j] = max(Option1, Option2, Option3)
```

### Completed DP Table
```
        ""  G   X   T   X   A   Y   B
    ""   0  -1  -2  -3  -4  -5  -6  -7
    A   -1  -1  -2  -3  -4  -4  -5  -6
    G   -2   0  -1  -2  -3  -4  -5  -6
    G   -3  -1   0  -1  -2  -3  -4  -5
    T   -4  -2  -1   1   0  -1  -2  -3
    A   -5  -3  -2   0   1   1   0  -1
    B   -6  -4  -3  -1   0   0   1   1
```

### Step 3: Traceback
Starting from dp[6][7] = 1, follow arrows backwards

### Resulting Alignment
```
Seq1: A G G T A - B
      | | | | | | |
Seq2: G - X T X A Y B

Score: 1 (optimal alignment score)
```

## Algorithm Outline

```
function needlemanWunsch(seq1, seq2, match=1, mismatch=-1, gap=-1):
    m = len(seq1)
    n = len(seq2)
    
    // Initialize DP table
    dp = array[m+1][n+1]
    traceback = array[m+1][n+1]
    
    for i in 0 to m:
        dp[i][0] = i * gap
    for j in 0 to n:
        dp[0][j] = j * gap
    
    // Fill DP table
    for i in 1 to m:
        for j in 1 to n:
            score = match if seq1[i-1] == seq2[j-1] else mismatch
            
            option1 = dp[i-1][j-1] + score
            option2 = dp[i-1][j] + gap
            option3 = dp[i][j-1] + gap
            
            dp[i][j] = max(option1, option2, option3)
    
    // Traceback and construct alignment
    alignment1 = ""
    alignment2 = ""
    i = m
    j = n
    
    while i > 0 or j > 0:
        // Follow optimal path backwards
```

## Implementation Hints

1. **DP Table Initialization**: First row/column are gap penalties
2. **Score Calculation**: Compare characters properly
3. **Direction Tracking**: Store pointers for traceback
4. **Traceback Loop**: Follow stored directions from bottom-right to top-left
5. **Alignment Construction**: Build both aligned sequences simultaneously

## Follow-up Questions

- How would you implement Smith-Waterman for local alignment?
- How would you handle affine gap costs (opening + extension)?
- How would you use substitution matrices like BLOSUM?
- How would you find all optimal alignments (tie handling)?
- How would you align multiple sequences?

## Common Pitfalls to Avoid

1. ❌ Forgetting to initialize first row/column with gap penalties
2. ❌ Wrong recurrence relation (should maximize, not minimize)
3. ❌ Incorrect traceback direction
4. ❌ Not handling gap penalties consistently
5. ❌ Forgetting base case when traceback reaches boundaries

## Complexity Analysis to Consider

- **Time**: O(m × n) where m, n = sequence lengths
- **Space**: O(m × n) for DP table + O(m + n) for alignment strings
- **Optimization**: Can reduce space to O(min(m,n)) with rolling array

## Test Cases to Think Through

1. Identical sequences (should align perfectly, score = length)
2. Completely different sequences (mostly mismatches)
3. One sequence substring of other (handle gaps)
4. Empty sequence (edge case)
5. Single character sequences
6. Sequences with repeating patterns
7. Long sequences (efficiency check)
8. All same characters
9. Reverse sequences
10. Sequences with multiple optimal alignments
