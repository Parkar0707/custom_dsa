# Day 8 Problem 6: Expression Tree Evaluator - Evaluate Symbolic Math

## Problem Statement
Build an expression tree from a mathematical expression and evaluate it. Handle operator precedence, parentheses, and different numeric operations.

## Core Concepts

### Expression Tree Structure
- **Leaf Nodes**: Operands (numbers, variables)
- **Internal Nodes**: Operators (+, -, *, /, ^, etc.)
- **Evaluation**: Recursive traversal computing subexpressions

### Why Trees for Expressions?
- **Precedence**: Tree structure encodes operator precedence
- **Parentheses**: Handled naturally by tree structure
- **Reusability**: Parse once, evaluate many times
- **Simplification**: Can perform algebraic simplification

## Key Concepts to Understand

1. **Infix Notation**: Standard math notation (2 + 3 * 4)
2. **Postfix Notation**: Operands before operators (2 3 4 * +)
3. **Precedence**: *, / before +, - before = 
4. **Associativity**: Left or right (determines grouping)
5. **Operator Overloading**: Handle different data types

## Problem Variations to Consider

- **Variables**: Support unknown values (y = 2x + 3)
- **Functions**: Add sin, cos, sqrt, etc.
- **Symbolic Differentiation**: Take derivatives
- **Simplification**: Reduce expression (0*x = 0, 1*x = x)
- **Polynomial Evaluation**: Horner's method for efficiency

## Example Walkthrough

### Expression: 2 + 3 * 4 - 5

**Operator Precedence**:
- * has higher precedence than + and -
- + and - have same precedence (left-associative)
- So: (2 + (3 * 4)) - 5

### Parse Tree:
```
           -
          / \
         +   5
        / \
       2   *
          / \
         3   4
```

### Evaluation Steps:
1. Evaluate left subtree of -: 
   - Evaluate left of +: 2
   - Evaluate right of +: 3 * 4 = 12
   - Result: 2 + 12 = 14
2. Evaluate right subtree of -: 5
3. Result: 14 - 5 = 9

### Another Example: (2 + 3) * (4 - 1)

**Expression**: "(2 + 3) * (4 - 1)"

Parse Tree:
```
         *
        / \
       +   -
      / \ / \
     2  3 4  1
```

Evaluation:
1. Left: 2 + 3 = 5
2. Right: 4 - 1 = 3
3. Result: 5 * 3 = 15

## Algorithm Outline

```
function evaluate(node):
    if node is leaf:
        return node.value
    
    leftValue = evaluate(node.left)
    rightValue = evaluate(node.right)
    
    switch node.operator:
        case '+': return leftValue + rightValue
        case '-': return leftValue - rightValue
        case '*': return leftValue * rightValue
        case '/': return leftValue / rightValue
        case '^': return leftValue ^ rightValue

function parseExpression(string):
    tokens = tokenize(string)
    return parseExpr(tokens, 0).node

function parseExpr(tokens, minPrecedence):
    left = parsePrimary(tokens)
    
    while hasMoreTokens(tokens):
        op = peek(tokens)
        if precedence(op) < minPrecedence:
            break
        
        consume(tokens)  // consume operator
        
        right = parseExpr(tokens, precedence(op) + 1)
        left = createNode(op, left, right)
    
    return left

function parsePrimary(tokens):
    if peek(tokens) is '(':
        consume '('
        expr = parseExpr(tokens, 0)
        consume ')'
        return expr
    else:
        return createLeaf(parseNumber(tokens))

function precedence(operator):
    switch operator:
        case '+', '-': return 1
        case '*', '/': return 2
        case '^': return 3 (right-associative)
```

## Implementation Hints

1. **Tokenization**: Break string into operators, numbers, parentheses
2. **Recursive Descent**: Parse respecting precedence
3. **Stack-based Alternative**: Use operator/operand stacks
4. **Postfix Conversion**: Convert to postfix then evaluate
5. **Error Handling**: Handle division by zero, invalid expressions

## Follow-up Questions

- How would you handle variable expressions?
- How would you implement differentiation?
- How would you simplify algebraic expressions?
- How would you handle function calls (sin, cos, sqrt)?
- How would you support user-defined functions?

## Common Pitfalls to Avoid

1. ❌ Ignoring operator precedence
2. ❌ Not handling parentheses correctly
3. ❌ Wrong associativity (especially for ^ and /)
4. ❌ Division by zero without checking
5. ❌ Not converting string to numeric tokens properly

## Complexity Analysis to Consider

- **Parsing**: O(n) where n = length of expression
- **Evaluation**: O(n) where n = number of nodes in tree
- **Space**: O(h) for recursion depth, O(n) for tree

## Test Cases to Think Through

1. Single number (5)
2. Simple operations (2 + 3)
3. Multiple operations with same precedence (2 + 3 + 4)
4. Mixed precedence (2 + 3 * 4)
5. Parentheses overriding precedence ((2 + 3) * 4)
6. Nested parentheses (((2 + 3) * 4) / 2)
7. Negative numbers (-5 + 3)
8. Division by zero
9. Large expressions
10. Exponentiation (right-associative: 2^3^2 = 2^(3^2) = 512)
