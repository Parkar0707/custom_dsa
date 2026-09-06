# Day 2 Problem 6: Molecular Barcode Generation

## Problem Statement
Generate error-correcting DNA barcodes for molecular tracking and improve reliability using Hamming distance to ensure barcodes can be distinguished even with sequencing errors.

## Core Concepts

### What are Molecular Barcodes?
- **Purpose**: Unique identifiers for tracking DNA/RNA molecules
- **Application**: Cell tracking, mutation detection, duplicate read removal
- **Constraint**: Barcodes must be distinguishable even with sequencing errors

### Error-Correcting Codes
- **Sequencing Error Rate**: ~0.1-1% per base
- **Barcode Length**: Typically 12-30 bases
- **Goal**: If barcode receives 1-2 errors, still identify original
- **Tool**: Hamming distance for error correction

### Hamming Distance
```
Barcode1: ACGTACGTACGT
Barcode2: ACGTACGTACGA
          ___________*
Hamming Distance = 1 (one position differs)

With error-correcting code:
If min distance between barcodes = 3,
Then can correct 1 error: (3-1)/2 = 1
```

## Example Scenario

```
Generate 1000 unique barcodes with minimum Hamming distance = 3:

Example valid set:
- ACGTACGTACGT
- ACGTACGTACGC (distance 1 from first: NOT VALID)
- ACGTACGTACGA (distance 1 from first: NOT VALID)
- TGCATGCATGCA (distance 12 from first: VALID)
- GCTAGCTAGCTA (distance 8 from first: VALID)

Property: Any error in barcode can uniquely identify original
```

## Understanding the Problem

### Input
- Desired number of barcodes (N)
- Desired minimum Hamming distance (d_min)
- Alphabet: {A, T, G, C} (4 nucleotides)
- Barcode length: n

### Output
- Set of N non-overlapping barcodes
- All pairwise distances ≥ d_min
- Optimized for length (shorter is better)

### Theoretical Limits
- Hamming bound (sphere-packing): Upper limit on barcodes
- Gilbert-Varshamov bound: Lower limit guaranteed achievable
- These determine feasibility of design

## Algorithm Intuition

### Brute Force Approach
```
1. Generate random candidate barcode
2. Check distance from all previously selected
3. If all distances ≥ d_min: add to set
4. Repeat until N barcodes found
```

Challenges:
- Slow for large N or large d_min
- May fail to find solution
- Lots of wasted attempts

### Greedy Construction
```
1. Start with fixed barcode (e.g., all As)
2. For next barcode:
   - Systematically try positions/changes
   - Pick first that satisfies distance constraint
3. Continue until N barcodes
```

Benefits:
- Faster, more deterministic
- Guarantees reasonable solutions
- Can optimize for minimal length

## String Manipulation Techniques

### Generating Variations
```python
Original: ACGTACGTACGT

Variations with 1 change from position i:
- Position 0 changed to T: TCGTACGTACGT (differs at 1 position)
- Position 0 changed to G: GCGTACGTACGT
- Position 0 changed to C: CCGTACGTACGT

Calculate Hamming distance between variations and all existing barcodes
```

### Hamming Distance Calculation
- Count positions where characters differ
- Can optimize with early termination if exceeds threshold

## What You Should Think About

1. **Efficiency**:
   - Checking all pairs: O(N²)
   - For each pair: O(n) comparison
   - Can you prune search space?

2. **Trade-offs**:
   - Longer barcodes: Easier to make diverse
   - More barcodes needed: Harder constraints
   - Error correction: Requires larger distances
   - Barcode length: Increases with d_min

3. **Biological Constraints**:
   - Secondary structure (avoid hairpins)
   - Homopolymer runs (AAAA problematic)
   - GC content bias (balance needed)
   - Avoid known motifs

4. **Optimization**:
   - Symmetry: ACGT and its reverse complement
   - Greedy construction order matters
   - Can start from known good patterns

5. **Edge Cases**:
   - d_min = 1: Only need unique barcodes
   - d_min = n: Only 4 possible barcodes (AAAA, TTTT, GGGG, CCCC)
   - Very large N with large d_min: May be impossible

## Implementation Hints (Without Code)

- Create function to calculate Hamming distance
- Generate barcodes or variations systematically
- Store selected barcodes in set for fast lookup
- Check new candidates against all existing
- Consider greedy vs. random approaches

## Practice Questions

1. What's the minimum barcode length for N barcodes with distance d?
2. How would you handle secondary structure constraints?
3. Can you verify if a given set meets the distance requirement?
4. How would you optimize for minimum total length?

## Theoretical Background

```
Singleton bound: N ≤ 4^n / (1 + (n-1)*⌊d/2⌋)

For n=20, d=3:
Maximum barcodes ≈ 4^20 / 21 ≈ 200 million (theoretical)

For n=12, d=3:
Maximum barcodes ≈ 4^12 / 21 ≈ 80,000 (practical)
```

## Real-World Applications
- **Single-cell sequencing**: Cell barcoding
- **Error correction**: PCR/sequencing errors
- **Mutation tracking**: Lineage tracing
- **Duplicate removal**: Collapsing redundant reads
- **Quantification**: UMI (Unique Molecular Identifier)

## Related Concepts
- Hamming codes (classical error correction)
- Reed-Solomon codes (stronger correction)
- BCH codes (block codes)
- Constraint satisfaction problems
