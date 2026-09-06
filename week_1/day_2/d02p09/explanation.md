# Day 2 Problem 9: Codon Usage Optimization

## Problem Statement
Transform a protein sequence into a DNA sequence optimized for expression in target organisms using greedy string replacement techniques based on codon usage patterns.

## Core Concepts

### Genetic Code
- **Codon**: 3-nucleotide sequence coding for amino acid
- **Degeneracy**: Most amino acids encoded by multiple codons
- **Wobble Position**: Third position most variable
- **Start Codon**: ATG (methionine)
- **Stop Codons**: TAA, TAG, TGA

### Codon Usage Bias
- **Organism-Specific**: Each organism prefers certain codons
- **Expression Efficiency**: Preferred codons translated faster
- **Fitness Cost**: Non-preferred codons cause slow/stalled translation
- **Codon Adaptation Index (CAI)**: Measure of codon optimization

### Example
```
Amino Acid: Leucine (Leu)
Possible Codons: TTA, TTG, CTT, CTC, CTA, CTG

In E. coli (prefers):
- CTG (frequency 0.50)
- TTG (frequency 0.13)
- TTA (frequency 0.04)

In Yeast (prefers):
- CTT (frequency 0.34)
- CTG (frequency 0.27)
- CTT (frequency 0.20)

Same amino acid, different codon choice for each organism!
```

## Understanding the Problem

### Input
- Protein sequence (amino acids)
- Target organism
- Codon usage table for organism
- Constraints (avoid problematic sequences)

### Output
- DNA sequence (codons)
- Optimization score
- Sequence properties (GC content, structure)

### Constraints
- **Codon Choice**: Pick optimal codon for each amino acid
- **Avoid Patterns**: Prevent secondary structures
- **Balanced Composition**: Maintain proper GC content
- **No Repeats**: Avoid homopolymer runs

## Algorithm Intuition: Greedy String Replacement

### Simple Greedy Approach
```
Algorithm:
1. Build map: Amino acid → list of codons (sorted by usage frequency)
2. For each amino acid in protein:
   a. Pick most frequently used codon for that amino acid
   b. Check constraints (repeats, GC content)
   c. If constraint violated: try next best codon
3. Continue until entire sequence transformed
```

### Example
```
Protein:    M   A   P   L
Codons:   ATG + GCG + CCG + CTG

If greedy choice creates ATGTTG (unwanted repeat TG):
Try alternative: ATGGGG (creates homopolymer)
Try another: ATGCAC (different AA, not valid)

Must backtrack or explore alternatives
```

## Greedy Strategy Details

### Selection Process
```
For each amino acid AA:
  available_codons = [codons for AA sorted by frequency]
  
  for codon in available_codons:
    current_dna += codon
    
    if is_valid(current_dna):  // Check all constraints
      break  // Take first valid
    else:
      current_dna = current_dna[:-3]  // Remove last codon
```

### Constraint Checking
```
Check for:
1. Homopolymer runs (AAAA, TTTT, etc.)
2. Secondary structure formation
3. GC content balance
4. Restriction sites (unwanted for cloning)
5. Repeats exceeding threshold
```

## What You Should Think About

1. **Greedy Limitations**:
   - Greedy may not be globally optimal
   - Local choice may create problems later
   - Trade-off between optimization and constraints

2. **Multiple Objectives**:
   - Expression level (codon frequency)
   - Secondary structure (avoid hairpins)
   - GC content (organism-dependent)
   - Translation rate (rare codons cause pauses)

3. **Biological Realism**:
   - Some rare codons may be preferred (optimization)
   - Variation better than uniformity (cellular adaptation)
   - Codon pair usage (coupling between adjacent codons)

4. **Optimization Depth**:
   - Single-level: Each codon independently
   - Pair-level: Consider interactions with adjacent codons
   - Region-level: Consider functional domains

5. **Edge Cases**:
   - Start codon (must be ATG, no choice)
   - Stop codon (must be one of TAA/TAG/TGA)
   - Rare amino acids with limited codons
   - Conflicting constraints (can't satisfy all)

## Implementation Hints (Without Code)

- Create codon usage frequency table from organism database
- For each amino acid, sort its possible codons by frequency
- Implement constraint checks as separate functions
- Use backtracking if greedy choice violates constraints
- Calculate CAI score for final sequence

## Practice Questions

1. How would you handle competing constraints (GC content vs. codon preference)?
2. Can you optimize for codon pair usage instead of individual codons?
3. How would you handle genes from multiple organisms?
4. What if perfect optimization is impossible?

## Advanced Optimization

```
Simple Greedy: O(n) - very fast, decent results
With Backtracking: O(n * k^n) worst case - slower, better results
Dynamic Programming: O(n * m^2) - balance speed/quality
Simulated Annealing: Heuristic - good for large problems
```

## CAI Scoring

```
CAI = (∏ W_i)^(1/n)

Where:
W_i = usage frequency of chosen codon / max frequency for that AA
n = number of amino acids
Range: 0 to 1 (1 = perfect optimization)
```

## Real-World Applications
- **Synthetic biology**: Designing synthetic genes
- **Protein expression**: Improving yield in fermentation
- **Vaccine development**: Optimizing antigen genes
- **Metabolic engineering**: Improving enzyme expression
- **Diagnostic kits**: Optimizing detection genes

## Practical Considerations
- Reference organism codon usage tables (NCBI, EnsEMBL)
- Pre-optimized libraries available (GeneArt, GenScript)
- Experimental validation often needed
- Not all optimization improves expression (context-dependent)

## Comparison: Before vs After Optimization

```
Original (suboptimal codons):
CAI = 0.42, Expression Level: 30%

Optimized (greedy approach):
CAI = 0.78, Expression Level: 75%

Optimized (with constraints):
CAI = 0.72, GC content: 50%, Expression Level: 70%
```
