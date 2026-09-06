# Day 2 Problem 5: CRISPR Guide RNA Design

## Problem Statement
Design CRISPR guide RNA sequences by finding minimal unique subsequences in the genome that will specifically target the desired location without off-target binding.

## Core Concepts

### CRISPR System Basics
- **CRISPR**: Clustered Regularly Interspaced Short Palindromic Repeats
- **Guide RNA**: ~20 nucleotide sequence that directs Cas9 to target
- **Target Specificity**: Must be unique in genome to avoid unintended cuts
- **Challenge**: Find shortest unique sequence to minimize off-target effects

### Unique Subsequence Problem
- Want: Shortest sequence that appears only once in genome
- Why: Minimizes chance of accidental cuts elsewhere
- Tradeoff: Longer sequence = more specific but harder to design
- Rolling Hash: Efficient way to check uniqueness quickly

### Why Rolling Hash?
- Check many potential guide sequences efficiently
- Hash comparison is O(1) if hash precomputed
- Detect collisions (false positives) with actual comparison
- Better than substring search for each candidate

## Example Scenario

```
Target Region: ...GCTAGCTAGCTA GCTAGCT AGCTAGC...
                               ^target^

Possible guides:
"GCTAGCTA" → appears 5 times (too many off-targets)
"GCTAGCTAG" → appears 2 times (still risky)
"GCTAGCTAGC" → appears 1 time only (GOOD!)

Selected guide: "GCTAGCTAGC" (10 bases, minimum for specificity)
```

## Understanding the Problem

### Input
- Entire reference genome (very large)
- Target sequence location
- Region around target to check
- Desired guide length or range

### Output
- Shortest unique subsequence
- OR all valid guide candidates
- Specificity score
- Off-target predictions

### Key Constraints
- Guide must be near target (within promoter/regulatory region)
- Must not create secondary structures
- Cannot contain too many repeats
- Should have balanced GC content

## Algorithm Intuition: Rolling Hash

### Hash Function Concept
```
String: "ACGT"
Hash value = A*256^3 + C*256^2 + G*256 + T

This converts each window into a numeric value
Fast to compute incrementally by "rolling"
```

### Rolling Window Technique
```
Text: "ACGTACGTACGT"

Window 1: "ACGT" → hash1
Window 2: "CGTA" → hash2
  Instead of recomputing from scratch:
  hash2 = (hash1 - A*256^3) * 256 + A
          (remove leftmost) (shift left) (add rightmost)

Window 3: "GTAC" → hash3
  hash3 = (hash2 - C*256^3) * 256 + C
  
Continuous O(1) updates instead of O(length) recomputation
```

### Finding Unique Subsequence
1. Iterate through increasing lengths (start with shortest)
2. Hash all subsequences of that length
3. If all hashes unique: found minimum
4. If collisions: try next length
5. Verify with actual string comparison (rare false positives)

## Biological Constraints in Practice

```
Off-target risk factors:
- Exact matches in genome: HIGH RISK
- High similarity (mismatches): MEDIUM RISK
- Low GC content: May not bind properly
- High GC content: May cause off-targets
- Repeats (AAAA, GCGC): May cause problems

20-22 bp is typical guide length in practice
```

## What You Should Think About

1. **Genome Size**:
   - Human genome: ~3 billion bases
   - Cannot store all hashes in memory
   - Need efficient streaming/chunking

2. **Hash Collision Handling**:
   - When hashes match, must verify actual strings
   - Rare but important for correctness
   - Strategy: Use multiple hash functions

3. **Optimization**:
   - Start small (8 bp), go up to ~20 bp
   - Stop at first unique length
   - Cache results for common regions

4. **Edge Cases**:
   - Highly repetitive regions (difficult)
   - Near chromosome boundaries
   - In pseudogene regions (unexpected matches)
   - Mitochondrial sequences (extra copies)

## Implementation Hints (Without Code)

- Choose a good hash base (prime number like 31 or 256)
- Pre-compute base powers (base^n for all n)
- Rolling hash updates remove old char contribution, add new
- Use modulo arithmetic to prevent integer overflow
- Store hashes in hash set for O(1) lookup

## Practice Questions

1. How would you handle multiple guides (if one is not viable)?
2. Can you design guides for sequences with repeating elements?
3. How would you score off-target potential (mismatch profile)?
4. What about avoiding specific secondary structures?

## Efficiency Comparison

```
Method                 | Time           | Space
Naive (substring)      | O(n * m^2)     | O(1)
KMP each candidate     | O(n * m)       | O(m)
Rolling Hash           | O(n + m)       | O(m) for hash table
```
Where n = genome size, m = guide length

## Real-World Complexity
- CRISPR off-target prediction uses sophisticated ML models
- CFD (cutting frequency determination) score from Doench et al.
- Multiple hash functions and alignment tools
- Integration with functional genomics data

## Applications
- Genetic disease correction
- Cancer cell immunotherapy
- Agricultural trait improvement
- Functional genomics research
- Quality control in clinical CRISPR applications
