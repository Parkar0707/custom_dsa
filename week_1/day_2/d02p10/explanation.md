# Day 2 Problem 10: Phylogenetic Tree String Encoding

## Problem Statement
Encode an evolutionary tree structure as a string representation using depth-first search and serialization techniques for efficient storage and comparison of phylogenetic data.

## Core Concepts

### Phylogenetic Trees
- **Purpose**: Represent evolutionary relationships between organisms
- **Nodes**: Species, populations, or sequences
- **Branches**: Evolutionary lineages
- **Root**: Common ancestor
- **Leaves**: Extant (current) species

### Why Serialize to String?
- **Storage**: Easier to store/transmit than tree data structure
- **Comparison**: String comparison easier than tree comparison
- **Databases**: Can index and query tree strings
- **Standardization**: Newick, Nexus formats in biology

### Example Tree Structure
```
           ┌─── Human
       ┌───┤
       │   └─── Chimp
    ───┤
       │   ┌─── Cat
       └───┤
           └─── Dog

Represents: Humans and chimps closer related; cats/dogs form another clade
```

## Understanding the Problem

### Input
- Tree structure (nodes and edges)
- Branch lengths (evolutionary distances)
- Node labels (species names)
- Tree properties (rooted/unrooted)

### Output
- String representation (e.g., Newick format)
- Can parse back to reconstruct tree
- Compact encoding
- Human-readable (ideally)

### Common Formats
```
Newick: ((Human:0.1,Chimp:0.1):0.2,(Cat:0.2,Dog:0.2):0.1):0.0;

Parentheses indicate clades (groups)
Numbers = branch lengths
Commas separate siblings
Semicolon = end

Newick format read: (child1, child2) format
```

## Algorithm Intuition: DFS-based Serialization

### Depth-First Search Traversal
```
Algorithm:
1. Start at root
2. For each node:
   a. If leaf (no children): write label
   b. If internal node:
      - Write opening parenthesis
      - Process all children recursively
      - Write closing parenthesis
      - Write node label (if exists)
   c. Write branch length
   d. Write comma (if not last sibling)
3. End with semicolon at root
```

### Example Walkthrough
```
Tree:
        R
       / \
      A   B
     /|   |\
    C D   E F

DFS traversal and encoding:

Visit R:
  - Not a leaf, write "("
  - Recursively process child A:
    - Visit A: "("
    - Recursively process C: "C"
    - Write ","
    - Recursively process D: "D"
    - Visit A end: ")"
    - Write "A"
  - Write ","
  - Recursively process child B:
    - Visit B: "("
    - ... process E, F ...
    - ")"
    - Write "B"
  - Visit R end: ")"

Result: ((C,D)A,(E,F)B)R;
```

## String Representation Variants

### Newick Format
```
Standard:  ((A:0.1,B:0.2):0.1,C:0.3);
- Branch lengths as decimals
- Species/node names (optional)
- Mostly unambiguous if balanced parentheses
```

### Extended Newick
```
With bootstrap values: ((A:0.1,B:0.2)95:0.1,C:0.3)100;
- 95 = bootstrap support (likelihood)
- 100 = root bootstrap
```

### Other Formats
```
PAUP: brackets and semicolons
Nexus: more metadata (genes, organisms, etc.)
PhyloXML: XML-based (verbose but comprehensive)
```

## What You Should Think About

1. **Rooted vs. Unrooted**:
   - Rooted: One clear ancestor (directional)
   - Unrooted: No direction specified (relationships only)
   - String encoding different for each

2. **Branch Lengths**:
   - Represent evolutionary distance
   - Could be number of substitutions
   - Could be time estimates
   - Affect comparison/analysis

3. **Node Attributes**:
   - Species names (leaves)
   - Internal node labels (bootstrap values?)
   - Unique identifiers
   - Confidence values

4. **Parsing Challenges**:
   - Balanced parentheses validation
   - Parsing branch lengths and labels
   - Handling missing data
   - Ambiguous trees (polytomies)

5. **Efficiency**:
   - DFS is O(n) for n nodes
   - String construction: O(n) or O(n²) depending on implementation
   - Can optimize with StringBuilder/StringBuffer

6. **Edge Cases**:
   - Single node (no branches)
   - Single lineage (linear tree)
   - Polytomies (>2 children per node)
   - Identical branch lengths

## Implementation Hints (Without Code)

- Implement recursive DFS traversal
- For each node, build its Newick representation
- Concatenate child representations with proper separators
- Handle branch length formatting (precision)
- Validate parentheses balance

## Practice Questions

1. How would you parse a Newick string back into tree structure?
2. Can you validate if a Newick string is correctly formatted?
3. How would you handle unrooted trees?
4. Can you compute tree distance between two phylogenies?

## Tree Reconstruction from String

```
Algorithm to parse Newick:
1. Use stack for parentheses matching
2. When see "(": push new node
3. When see ",": mark sibling separation
4. When see ")": pop and connect children
5. Extract labels and branch lengths during parsing

Challenges:
- Handling unbalanced parentheses
- Parsing floating point numbers
- Managing node connections properly
```

## Real-World Examples

```
Phylogeny of Primates (simplified):
((Human:0.1,Chimp:0.1):0.05,(Gorilla:0.12,Orang:0.15):0.04):0.0;

Interpretation:
- Human & Chimp most recent common ancestor (0.1 distance each)
- Gorilla & Orang form another clade
- Both clades share common ancestor further back
```

## Applications
- **Evolutionary biology**: Tracking species divergence
- **Molecular evolution**: Protein/gene tree construction
- **Comparative genomics**: Finding orthologs
- **Conservation biology**: Understanding population structure
- **Disease epidemiology**: Tracking pathogen evolution
- **Cancer evolution**: Tumor heterogeneity analysis

## Related Concepts
- **Multiple sequence alignment**: Input to phylogenetic trees
- **Likelihood calculation**: Evaluating tree probability
- **Tree topology**: Different possible arrangements
- **Molecular clock**: Estimating divergence times

## Performance Considerations
- String encoding: O(n) time, O(n) space
- Parsing: O(n) with proper algorithm
- Tree reconstruction: O(n) with stack-based parser
- Scalability: Can handle thousands of species
