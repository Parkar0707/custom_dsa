# Day 2 Problem 7: Protein Sequence Alignment

## Problem Statement
Find the minimum edit distance (Levenshtein distance) between two protein sequences to measure evolutionary distance and identify similar proteins.

## Core Concepts

### Edit Distance (Levenshtein Distance)
- **Definition**: Minimum number of operations to transform one string to another
- **Operations**: Insert, Delete, Replace (each costs 1)
- **Application**: Protein similarity, evolutionary distance, homology detection

### Biological Significance
- **Evolutionary Distance**: Proteins from common ancestors have similar sequences
- **Functional Conservation**: Similar sequences often have similar function
- **Mutation Accumulation**: Number of edit operations ~ mutations over time
- **Alignment**: Shows which residues changed, deleted, or inserted

### Example
```
Protein 1: ACGTACGT
Protein 2: ACGTAGCT

Operations:
- Delete T at position 4
- Insert A at position 5
Edit Distance = 2
```

## Understanding the Problem

### Input
- Two protein sequences (strings of amino acids)
- Optional: Cost matrix for specific amino acid changes
- Optional: Gap penalties for insertions/deletions

### Output
- Minimum edit distance (integer)
- OR alignment showing operations
- Similarity score (normalized)

### Challenges
- Sequences can be very long (>1000 amino acids)
- Need efficient algorithm for large proteins
- Different costs for different operations
- Gap penalties vary by position

## Algorithm Intuition: Wagner-Fischer (Dynamic Programming)

### Key Insight
- Substructure: Optimal alignment of longer sequences comes from optimal alignment of shorter subsequences
- Recurrence: Can build solution from previously solved smaller problems

### DP Table Concept
```
      ""  A  C  G  T
  ""   0  1  2  3  4
  A    1  ?  ?  ?  ?
  C    2  ?  ?  ?  ?
  G    3  ?  ?  ?  ?
  T    4  ?  ?  ?  ?

Table[i][j] = minimum edit distance to transform first i characters of string1
                into first j characters of string2
```

### Building the Table
1. Base cases: Empty string to anything (just insertions)
2. For each cell [i][j]:
   - If characters match: take value from [i-1][j-1] (no operation needed)
   - If don't match, take minimum of:
     - [i-1][j] + 1 (delete from string1)
     - [i][j-1] + 1 (insert into string1)
     - [i-1][j-1] + 1 (replace)

### Why This Works
- Each cell represents solved subproblem
- Bottom-right cell = solution for full strings
- Can reconstruct alignment by backtracking

## Example Walkthrough

```
String1: CAT
String2: DOG

      ""  D  O  G
  ""   0  1  2  3
  C    1  1  2  3
  A    2  2  2  3
  T    3  3  3  3

Process:
[0][0] = 0 (empty to empty)
[1][1]: C→D, chars differ: min(0+1, 1+1, 1+1) = 1 (replace)
[1][2]: C→DO, chars differ: min(1+1, 1+1, 2+1) = 2
[3][3]: CAT→DOG = 3 (all different)
```

## What You Should Think About

1. **Time Complexity**:
   - O(m*n) where m, n = sequence lengths
   - For large proteins: may need O(n*m) memory
   - Space optimization possible: O(min(m,n))

2. **Cost Variations**:
   - Simple: All operations cost 1
   - Weighted: Different amino acid substitutions have different costs
   - Affine gaps: Opening gap vs. extending gap
   - Position-specific: Gaps in certain positions more expensive

3. **Biological Accuracy**:
   - Some amino acids similar (hydrophobic group)
   - Transition mutations (A↔G, C↔T) more common
   - Indels (insertions/deletions) less common than substitutions
   - Should use Blosum or PAM matrices in practice

4. **Edge Cases**:
   - Empty sequences
   - Identical sequences
   - Completely different sequences
   - Very long sequences (performance)

5. **Optimization Opportunities**:
   - Only compute relevant region (banding)
   - Early termination if distance exceeds threshold
   - Hirschberg algorithm for linear space

## Implementation Hints (Without Code)

- Create 2D array of size (len1+1) × (len2+1)
- Initialize first row (0, 1, 2, ...) and first column (0, 1, 2, ...)
- Fill table using recurrence relation
- Handle character comparison carefully
- Backtrack from bottom-right to find alignment

## Practice Questions

1. How would you reconstruct the actual sequence of operations?
2. Can you compute edit distance with weighted operations?
3. How would you handle affine gap penalties (opening vs extension)?
4. What if you only need distance, not alignment?

## Advanced Variants

```
Levenshtein: All operations cost 1
Damerau-Levenshtein: Includes transposition (swap adjacent)
Longest Common Subsequence (LCS): Related problem
Smith-Waterman: Local alignment (similar subsequences)
Needleman-Wunsch: Global alignment (full sequences)
```

## Real-World Complexity
- Scoring matrices (Blosum62, PAM250) based on evolution statistics
- Gap penalties vary by secondary structure
- Position-specific scoring (conservation)
- Multiple sequence alignment for families

## Applications
- **Homology detection**: Finding similar proteins in database
- **Evolutionary analysis**: Measuring divergence time
- **Protein function prediction**: Similar → similar function
- **Quality control**: Checking sequence accuracy
- **Phylogenetics**: Building evolutionary trees

## Algorithmic Family
- Classic dynamic programming application
- Foundation for many bioinformatics tools (BLAST, FASTA)
- Used in many string-matching applications beyond biology
