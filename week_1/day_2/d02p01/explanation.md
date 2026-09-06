# Day 2 Problem 1: Protein Folding Pattern Matching

## Problem Statement
Find all occurrences of amino acid patterns in a protein sequence. This is a bioinformatics problem where we need to identify specific motifs (patterns) within a larger protein sequence.

## Core Concepts

### What is Pattern Matching in Proteins?
- **Protein Sequence**: A string of amino acids represented by single letters (A, C, D, E, etc.)
- **Pattern/Motif**: A specific sequence that is functionally or structurally important
- **Goal**: Locate all positions where this pattern appears in the protein sequence

### Why KMP Algorithm?
The KMP (Knuth-Morris-Pratt) algorithm is optimal for this because:
- Time complexity: **O(n + m)** where n = text length, m = pattern length
- Avoids redundant comparisons using a failure function
- Better than naive approach: **O(n * m)**

### Key Components of KMP
1. **Failure Function (Prefix Table)**: Stores information about overlapping prefixes/suffixes
   - Helps skip unnecessary comparisons
   - Pre-computed before searching
   
2. **Searching Phase**: Uses failure function to jump ahead when mismatch occurs
   - No backtracking in the text string

## Example Scenario

```
Protein Sequence: ACDFGACDKACDEFG
Pattern:          ACD

Expected Output: Positions [0, 7, 10] (0-indexed)

Breakdown:
Position 0:  ACD FG... ← Match found
Position 7:  ...ACD K... ← Match found
Position 10: ...ACD EFG ← Match found
```

## Understanding the Problem

### Input
- Large protein sequence (millions of characters possible)
- Pattern motif to search for

### Output
- List of all starting positions where pattern is found
- OR count of total occurrences

### Constraints to Consider
- Sequences can be very long (entire genomes)
- May need to find multiple patterns efficiently
- Real-time analysis requirements

## Algorithm Intuition

### Step 1: Build Failure Function
- For each position in pattern, compute longest proper prefix that is also suffix
- Example: Pattern "ABAB"
  - Position 0: ""
  - Position 1: "A" → no match → 0
  - Position 2: "AB" → no match → 0
  - Position 3: "ABA" → "A" matches → 1

### Step 2: Search Using Failure Function
- Start comparing from beginning
- On mismatch, use failure function to determine where to continue
- Avoid re-comparing characters we already know match

## What You Should Think About

1. **Edge Cases**:
   - Pattern longer than sequence
   - Pattern equals entire sequence
   - Empty pattern
   - Pattern with repeating characters

2. **Optimization Opportunities**:
   - Can you handle multiple patterns in one pass?
   - How would you handle overlapping matches?

3. **Biological Accuracy**:
   - Should "X" (unknown amino acid) match anything?
   - Should "B" (Asp or Asn) match specifically?

## Implementation Hints (Without Code)

- First, understand what a failure function represents
- Think about how to construct it for a pattern
- Consider how position in the failure function changes during search
- What happens when you find a mismatch vs. match?

## Practice Questions to Explore

1. How would you modify KMP to find overlapping matches?
2. What if you needed to find patterns with wildcards (like "A*D" matching ACD, ACCD, etc.)?
3. How would you extend this to search multiple patterns simultaneously?

## Related Algorithms
- **Boyer-Moore**: Better practical performance for long patterns
- **Rabin-Karp (Rolling Hash)**: Good for multiple pattern search
- **Aho-Corasick**: Excellent for searching many patterns in one text

## Real-World Applications
- Gene annotation databases (BLAST-like searches)
- Identifying functional domains in proteins
- Finding disease-causing mutations
- Protein homology detection
