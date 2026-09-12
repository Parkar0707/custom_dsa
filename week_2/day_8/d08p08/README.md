# Day 8 Problem 8: Compiler Abstract Syntax Tree - Code Generation from AST

## Problem Statement
Build a compiler that parses source code into an Abstract Syntax Tree (AST) and generates code. Transform high-level code into lower-level instructions while preserving semantics.

## Core Concepts

### AST (Abstract Syntax Tree)
- **Abstract**: Ignores syntax details (whitespace, parentheses)
- **Syntax**: Captures program structure
- **Tree**: Hierarchical representation
- **Used By**: Compilers, interpreters, linters, IDEs

### Compilation Phases
1. **Lexical Analysis**: Tokenize source → tokens
2. **Syntax Analysis**: Parse tokens → AST
3. **Semantic Analysis**: Type checking, scope resolution
4. **Code Generation**: AST → target code
5. **Optimization**: Improve generated code

### Why Tree Traversal?
- **Structure Matches Code**: Nested structure matches nested code blocks
- **Post-order Traversal**: Process children before parent (like expression evaluation)
- **Code Generation**: Generate code for subtrees, combine results
- **Recursive Nature**: Each statement contains substatements

## Key Concepts to Understand

1. **Statement Nodes**:
   - Variable declarations
   - Assignments
   - Conditionals (if/else)
   - Loops (for/while)
   - Function definitions

2. **Expression Nodes**:
   - Literals (numbers, strings)
   - Variables
   - Binary operations
   - Function calls

3. **Symbol Table**:
   - Maps variable names to memory locations
   - Tracks variable types
   - Manages scope

4. **Code Emission**:
   - Generate instructions (bytecode, assembly)
   - Manage registers/memory
   - Resolve addresses

## Problem Variations to Consider

- **Different Target Languages**: Generate C, Assembly, Bytecode
- **Optimization Passes**: Constant folding, dead code elimination
- **Error Recovery**: Continue compilation after errors
- **Type Inference**: Determine types from usage
- **Intermediate Representation**: Multi-stage compilation

## Example Walkthrough

### Simple Language: Variable Declaration and Arithmetic

**Source Code:**
```
int x;
x = 5 + 3;
```

### Lexical Analysis
Tokens:
```
[INT, IDENT(x), SEMICOLON, IDENT(x), ASSIGN, INT(5), PLUS, INT(3), SEMICOLON]
```

### Syntax Analysis (Parse to AST)

```
       Program
         |
    VarDeclaration
         |
      type: INT
      name: x
         
       Assignment
         |
      variable: x
      value: BinaryOp
             /  \
            +   
           / \
          5   3
```

Or more detailed:

```
Program
├── Declaration
│   ├── type: INT
│   └── name: x
└── Assignment
    ├── target: Identifier(x)
    └── value: BinaryExpression
        ├── operator: +
        ├── left: Literal(5)
        └── right: Literal(3)
```

### Code Generation (to simple bytecode)

**Symbol Table:**
```
x → memory location 0
```

**Generated Code:**
```
LOAD_CONST 5        # Push 5 on stack
LOAD_CONST 3        # Push 3 on stack
ADD                 # Pop 2, push sum (8)
STORE_VAR x         # Pop, store in x
```

Or assembly-like:
```
MOV eax, 5          ; eax = 5
ADD eax, 3          ; eax += 3
MOV [x], eax        ; store eax to x
```

### More Complex Example: If Statement

**Source:**
```
if (x > 5) {
    y = 10;
}
```

**AST:**
```
If
├── condition: BinaryOp (>)
│   ├── left: Identifier(x)
│   └── right: Literal(5)
└── thenBranch: Block
    └── Assignment
        ├── target: Identifier(y)
        └── value: Literal(10)
```

**Generated Code:**
```
LOAD_VAR x          # Load x
LOAD_CONST 5        # Load 5
CMP                 # Compare
JLE skip_block      # Jump if not >
LOAD_CONST 10       # Load 10
STORE_VAR y         # Store y
skip_block:         # Label for jump
```

## Algorithm Outline

```
function compile(sourceCode):
    tokens = lex(sourceCode)
    ast = parse(tokens)
    symbolTable = analyzeSemantics(ast)
    code = generate(ast, symbolTable)
    return code

function generate(node, symbolTable):
    if node is Literal:
        return [LOAD_CONST node.value]
    
    if node is Identifier:
        location = symbolTable.lookup(node.name)
        return [LOAD_VAR location]
    
    if node is BinaryOp:
        leftCode = generate(node.left, symbolTable)
        rightCode = generate(node.right, symbolTable)
        opCode = getOpCode(node.operator)
        return leftCode + rightCode + [opCode]
    
    if node is Assignment:
        valueCode = generate(node.value, symbolTable)
        location = symbolTable.lookup(node.target.name)
        return valueCode + [STORE_VAR location]
    
    if node is IfStatement:
        condCode = generate(node.condition, symbolTable)
        thenCode = generate(node.thenBranch, symbolTable)
        elseCode = null
        if node.elseBranch != null:
            elseCode = generate(node.elseBranch, symbolTable)
        
        skipLabel = generateLabel()
        endLabel = generateLabel()
        
        code = condCode
        code += [JEQ skipLabel]
        code += thenCode
        if elseCode != null:
            code += [JUMP endLabel]
            code += [LABEL skipLabel]
            code += elseCode
            code += [LABEL endLabel]
        else:
            code += [LABEL skipLabel]
        
        return code
    
    if node is Block:
        code = []
        for each statement in node.statements:
            code += generate(statement, symbolTable)
        return code

function analyzeSemantics(ast):
    symbolTable = new SymbolTable()
    analyzeSemanticsHelper(ast, symbolTable)
    return symbolTable

function analyzeSemanticsHelper(node, symbolTable):
    if node is VarDeclaration:
        symbolTable.define(node.name, node.type)
    
    // Recursively analyze children
    for each child in node.children:
        analyzeSemanticsHelper(child, symbolTable)
```

## Implementation Hints

1. **Symbol Table**: Maintain scope with stack of symbol tables
2. **Label Generation**: Create unique labels for jumps
3. **Post-order Traversal**: Generate code for subtrees first
4. **Stack Management**: Track what's on stack for expressions
5. **Type Checking**: Ensure operations are type-safe

## Follow-up Questions

- How would you handle function definitions and calls?
- How would you manage memory (stack/heap allocation)?
- How would you implement loops?
- How would you handle variable scope?
- How would you perform optimizations?

## Common Pitfalls to Avoid

1. ❌ Not defining variables before use
2. ❌ Type mismatches (adding int and string)
3. ❌ Jump label conflicts or missing labels
4. ❌ Not handling operator precedence
5. ❌ Forgetting to emit code for sub-expressions

## Complexity Analysis to Consider

- **Parsing**: O(n) where n = token count
- **Code Generation**: O(n) where n = AST node count
- **Total Compilation**: O(n) linear in source size
- **Space**: O(d) for recursion depth (AST depth)

## Test Cases to Think Through

1. Variable declarations
2. Simple assignments
3. Arithmetic expressions
4. If statements
5. If-else statements
6. Nested if statements
7. While loops
8. Function definitions
9. Function calls
10. Type checking errors
