# Day 8 Problem 3: Decision Tree Classifier - Build Classification Tree from Data

## Problem Statement
Implement a decision tree classifier that learns from training data to make predictions. Use the ID3 algorithm to recursively split data based on information gain.

## Core Concepts

### ID3 Algorithm (Iterative Dichotomiser 3)
- **Goal**: Build a decision tree that classifies data with minimum impurity
- **Key Metric**: Information Gain (reduction in entropy)
- **Approach**: Recursively choose the attribute that provides maximum information gain

### Entropy and Information Gain
- **Entropy**: Measure of disorder/uncertainty in a dataset
  - High entropy = mixed classes
  - Low entropy = pure classes
- **Information Gain**: Reduction in entropy after splitting
  - Choose split that maximizes information gain

## Key Concepts to Understand

1. **Attributes/Features**: Properties that describe data points
2. **Classes/Labels**: Categories to predict
3. **Splits**: Partitioning data based on feature values
4. **Leaf Nodes**: Terminal nodes with pure or majority class
5. **Internal Nodes**: Decision points with a feature condition
6. **Tree Depth**: Trade-off between accuracy and overfitting

## Problem Variations to Consider

- **Continuous Attributes**: How to handle real-valued features?
- **Missing Values**: How to handle incomplete data?
- **Pruning**: Remove branches that don't improve performance
- **Different Metrics**: Use Gini instead of entropy
- **Multi-way Splits**: Split into more than 2 branches

## Example Walkthrough

### Sample Dataset: Weather and Play Tennis
```
| Outlook  | Temperature | Humidity | Wind  | PlayTennis |
|----------|-------------|----------|-------|------------|
| Sunny    | Hot         | High     | Weak  | No         |
| Sunny    | Hot         | High     | Strong| No         |
| Overcast | Hot         | High     | Weak  | Yes        |
| Rain     | Mild        | High     | Weak  | Yes        |
| Rain     | Cool        | Normal   | Weak  | Yes        |
| Rain     | Cool        | Normal   | Strong| No         |
| Overcast | Cool        | Normal   | Strong| Yes        |
| Sunny    | Mild        | High     | Weak  | No         |
| Sunny    | Cool        | Normal   | Weak  | Yes        |
| Rain     | Mild        | Normal   | Weak  | Yes        |
```

### Decision Process:

1. **Calculate initial entropy**:
   - 6 Yes, 4 No → Entropy = -(6/10)log2(6/10) - (4/10)log2(4/10) ≈ 0.971

2. **Try splitting on each attribute**:
   - Outlook: Information Gain ≈ 0.247
   - Temperature: Information Gain ≈ 0.029
   - Humidity: Information Gain ≈ 0.152
   - Wind: Information Gain ≈ 0.048

3. **Choose Outlook** (highest gain):
   ```
                    Outlook
                   /   |   \
                Sunny / | \Overcast \ Rain
                 (2,4) (2,2)   (0,3)
   ```

4. **Recursively split** each branch until pure or stopping condition

### Resulting Tree:
```
           Outlook
          /   |    \
       Sunny  |    Overcast
       /      |      (Yes)
    Humidity  |
    /      \  |
   High    Normal
  (No)    (Yes)  

    Rain
     |
    Wind
   /  \
Weak Strong
(Yes) (No)
```

## Algorithm Outline

```
function buildTree(data, attributes):
    if all examples in data have same class:
        return Leaf(class)
    
    if attributes is empty:
        return Leaf(majority_class(data))
    
    bestAttribute = selectAttribute(data, attributes)
    root = Node(bestAttribute)
    
    for each value v of bestAttribute:
        subset = data where bestAttribute = v
        
        if subset is empty:
            add Leaf(majority_class(data)) to root
        else:
            newAttributes = attributes - {bestAttribute}
            subtree = buildTree(subset, newAttributes)
            add subtree to root
    
    return root

function selectAttribute(data, attributes):
    maxGain = -infinity
    bestAttr = null
    
    baseEntropy = calculateEntropy(data)
    
    for each attribute in attributes:
        gain = baseEntropy
        
        for each value v of attribute:
            subset = data where attribute = v
            gain -= (|subset|/|data|) * calculateEntropy(subset)
        
        if gain > maxGain:
            maxGain = gain
            bestAttr = attribute
    
    return bestAttr
```

## Implementation Hints

1. **Entropy Calculation**: Use logarithm base 2
2. **Information Gain**: Carefully compute weighted sums
3. **Recursive Structure**: Each subtree is also a valid tree
4. **Base Cases**: Pure sets, empty sets, no attributes left
5. **Data Representation**: Use arrays/lists of examples with features

## Follow-up Questions

- How would you handle continuous (real-valued) attributes?
- How would you prevent overfitting?
- How would you make predictions with an unseen example?
- How would you handle missing attribute values?
- How would you determine when to stop splitting?

## Common Pitfalls to Avoid

1. ❌ Not handling base cases properly
2. ❌ Incorrect entropy calculation
3. ❌ Wrong weighted average in information gain
4. ❌ Not removing selected attribute from recursive call
5. ❌ Creating empty subsets without handling

## Complexity Analysis to Consider

- **Building Tree**: O(n * m * log n) where n = examples, m = attributes
- **Space**: O(number of nodes in tree)
- **Prediction**: O(depth of tree)

## Test Cases to Think Through

1. All examples same class (should return immediately)
2. Single attribute
3. Single example
4. Balanced vs imbalanced classes
5. Multiple attributes with different gains
