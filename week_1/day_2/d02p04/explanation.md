# Day 2 Problem 4: RNA Secondary Structure Validation

## Problem Statement
Validate whether an RNA sequence has properly balanced bracket-like structures. RNA molecules fold into secondary structures with matching base pairs, similar to balanced parentheses.

## Core Concepts

### RNA Base Pairing Rules
- **Adenine (A) - Uracil (U)**: Forms 2 hydrogen bonds
- **Guanine (G) - Cytosine (C)**: Forms 3 hydrogen bonds
- **Wobble Pairing**: G-U can also pair (less stable)

### Secondary Structure
- RNA folds back on itself
- Complementary bases pair up
- Creates stems (paired regions) and loops (unpaired regions)
- Represented as nested brackets:
  ```
  5' A U G C C G A U 3'
     ( ( ( ) ) ) ( )   ← Bracket notation
  ```

### Why Stack-Based Parsing?
- Nested matching is the problem
- Stack naturally handles nesting
- When opening bracket found, push to stack
- When closing bracket found, pop and validate match
- Stack empty at end = valid structure

## Example Scenario

```
RNA Sequence:    AUGCCGAU
Bracket Form:    ((()))()

Validation:
Position 0-2: Open brackets (A,U,G)
Position 3-5: Close brackets (C,C,G) match previous opens
Position 6-7: New open-close pair (A,U)

Result: VALID structure
```

## Understanding the Problem

### Input
- RNA sequence or its bracket representation
- May include unpaired bases (shown as '.')
- May include multiple structure types

### Output
- Is structure valid? (Boolean)
- OR position of first mismatch
- OR count of mismatches

### Complexity
- Simple pairing: just count opens and closes
- Specific pairing: must track which pairs match
- Multiple pair types: different rules per pair

## Algorithm Intuition: Stack-Based Parsing

### Basic Idea
```
Algorithm:
1. Create empty stack
2. For each character in RNA sequence:
   a. If opening base (A,G,C,U that start pair): push to stack
   b. If closing base: 
      - If stack empty: INVALID (extra close)
      - Pop from stack and check if they're compatible
      - If not compatible: INVALID
3. If stack not empty at end: INVALID (unclosed opens)
4. If all checks pass: VALID
```

### What Makes a Valid Structure?
- Every open has matching close
- Every close matches most recent unmatched open
- No opens without closes (and vice versa)
- Pairs follow biological rules

## Pair Types in RNA

```
Canonical pairs:
- A-U (2 H-bonds)
- G-C (3 H-bonds)

Non-canonical:
- G-U wobble (2 H-bonds)
- Other rare pairs

Multiple levels of nesting possible:
((( A-U, G-C, A-U )))
```

## What You Should Think About

1. **Input Format**:
   - Bracket representation vs. actual bases?
   - How to determine which bases pair?
   - What are valid open/close pairs?

2. **Validation Rules**:
   - Must every base be paired?
   - Are loops (unpaired regions) allowed?
   - What about pseudoknots (cross-paired)?

3. **Pair Specificity**:
   - Simple: any open matches any close?
   - Strict: only matching types (A-U, G-C)?
   - Wobble: allow G-U?

4. **Edge Cases**:
   - Empty sequence
   - All unpaired bases
   - Single pair
   - Very long sequence
   - Ambiguous bases

## Implementation Hints (Without Code)

- Stack operations: push (add), pop (remove), peek (look at top)
- When checking pairs, pop from stack and compare with current base
- Need to know which bases are "openers" and which are "closers"
- Consider what information to store in stack (full base or just type?)

## Practice Questions

1. How would you modify this for pseudoknots (non-nested crossings)?
2. Can you identify which bases are definitely unpaired?
3. How would you find the shortest sequence to add to make it valid?
4. What if you had to handle wobble pairs differently?

## Extended Problem: Finding Invalid Regions

```
Structure:  (()()))
            
Stack trace:
( → push
( → push
) → pop, check A-U: valid
) → pop, check A-U: valid
( → push
) → pop, check G-C: valid
) → pop, EMPTY STACK: INVALID at position 6
```

## Real-World Implications
- **Ribosomal RNA (rRNA)**: Critical for protein synthesis
- **Transfer RNA (tRNA)**: Must fold correctly for amino acid binding
- **Messenger RNA (mRNA)**: Secondary structure affects translation efficiency
- **Small RNA (miRNA)**: Hairpin structure required for processing
- **Regulatory RNA**: Structure determines binding and activity

## Time Complexity Analysis
- Single pass through sequence: O(n)
- Stack operations (push/pop): O(1)
- Overall: O(n) - very efficient even for large RNA molecules

## Related Problems
- Balanced parentheses checking
- Multiple bracket type validation
- Nested structure verification
- Constraint satisfaction with nesting
