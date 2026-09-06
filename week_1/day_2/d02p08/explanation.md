# Day 2 Problem 8: Viral Genome Compression

## Problem Statement
Design an optimal compression algorithm for genomic data using LZ77 variant techniques to reduce storage requirements for viral genomes.

## Core Concepts

### Genomic Data Storage Challenge
- **Viral Genome Size**: 10 KB to 10 MB (varies widely)
- **Reference Genome**: ~3 billion bases for humans
- **Storage Cost**: Significant for databases and distribution
- **Solution**: Find repeated patterns and compress

### LZ77 Algorithm Principles
- **Dictionary-based**: Uses previously seen data as dictionary
- **Sliding Window**: Maintains window of seen characters
- **Phrase Encoding**: Represent new data as reference + new characters
- **Format**: (offset, length, next_character)

### Why LZ77 for Genomes?
- **Repetitive Structure**: Genomes have tandem repeats
- **Conserved Regions**: Functional regions highly conserved
- **Viral Genomes**: Often similar to reference genome
- **No Loss of Information**: Lossless compression

## Example Scenario

```
Original: ACGTACGTACGTNNACGTACGT

Compression with LZ77:
A,C,G,T → literal (first occurrence)
ACGTACGTACGT → reference to earlier "ACGTACGT" + new
NN → literals (novel)
ACGTACGT → reference to position 0, length 8

Compressed representation:
A,C,G,T,(0,8),N,N,(0,8)
Much shorter than original!
```

## Understanding the Problem

### Input
- Genomic sequence (string of A, T, G, C, N)
- Reference genome (optional)
- Compression parameters (window size, lookahead, etc.)

### Output
- Compressed representation
- Compression ratio (original size / compressed size)
- Decompression must recover original exactly

### Key Decisions
1. **Window Size**: How far back can we reference?
2. **Lookahead Buffer**: How far forward to search?
3. **Encoding**: How to represent (offset, length, char)?
4. **Threshold**: Minimum match length to encode

## Algorithm Intuition: LZ77

### Basic Approach
```
Algorithm:
1. Maintain sliding window of recently seen characters
2. For current position:
   a. Search window for longest match to upcoming text
   b. If match found: encode (offset, length, next_char)
   c. If no match: encode literal character
   d. Slide window forward by length + 1
3. Continue until end of text
```

### Example Step-by-Step
```
Text: ACGTACGTACGTNN...
Window: [empty initially]

Step 1:
- Current position: A
- Window: []
- No match found
- Output: 'A' (literal)
- Window: [A]

Step 2:
- Current position: C
- Window: [A]
- No match
- Output: 'C'
- Window: [AC]

...

Step 5:
- Current position: A
- Window: [ACGTA]
- Search for longest match starting at A
- Found: "ACGT" at offset 0, length 4
- Next char after match: A
- Output: (0, 4, A)
- Advance by 5 positions
```

## Practical Considerations

### Genome-Specific Optimization
```
Standard Genomes:
- A, T, G, C: 4 nucleotides → 2 bits each
- Can pre-compress to 0.5 bits per base

With repeats (using LZ77):
- Tandem repeats: Very common
- Introns: Often skipped
- Reference genome matching: Major wins
```

### Encoding Efficiency
```
Tradeoff: Larger window = better matches but more storage for offset

Option 1: 16-bit offset, 8-bit length, 8-bit literal
  - Window: 64 KB
  - Match: up to 256 bases

Option 2: 24-bit offset, 16-bit length, 8-bit literal
  - Window: 16 MB
  - Match: up to 65K bases
```

## What You Should Think About

1. **Performance**:
   - Speed: O(n*w) where w = window size
   - Can optimize with hash tables for faster matching
   - Many implementations use hash chains

2. **Optimization**:
   - Greedy matching (take first match) vs. optimal
   - Lazy matching: Check if better match exists ahead
   - Pre-processing: Sort common k-mers

3. **Genome Specifics**:
   - Consider using reference genome
   - Handle N (unknown) bases
   - Account for strand orientation

4. **Edge Cases**:
   - Very repetitive regions
   - Unique regions (no compression)
   - End of sequence (short tail)
   - Maximum offset/length exceeded

5. **Decompression Verification**:
   - Must reproduce original exactly
   - Handle boundary conditions
   - Validate offset/length within bounds

## Implementation Hints (Without Code)

- Maintain sliding window efficiently (array or circular buffer)
- For each position, search window for longest match
- Can use rolling hash to speed matching
- Store matches as tuples (offset, length, next_char)
- Decompress by reading instructions sequentially

## Practice Questions

1. How would you implement lazy matching to improve compression?
2. Can you use reference genome to extend matches?
3. How would you handle variable-length encoding for offsets?
4. What's optimal window size for typical viral genomes?

## Compression Ratios in Practice

```
Scenario                 | Ratio    | Notes
Random DNA              | ~0.99    | No patterns
Typical genomic         | ~0.80    | Some repeats
Viral (with reference)  | ~0.40    | High similarity
Tandem repeats only     | ~0.10    | Extreme compression
```

## Related Compression Techniques
- **DEFLATE**: Combines LZ77 + Huffman
- **LZMA**: Better compression, slower
- **GZIP**: LZ77 variant for files
- **Bzip2**: Burrows-Wheeler + RLE

## Real-World Applications
- **Genome databases**: NCBI sequence storage
- **DNA backup services**: Long-term storage
- **Next-gen sequencing**: Read compression
- **Viral surveillance**: Database efficiency
- **Pandemic preparedness**: Variant tracking

## Performance Analysis
- Time: O(n * w) for sliding window
- Space: O(w + output)
- Can optimize to O(n + w log n) with clever indexing
