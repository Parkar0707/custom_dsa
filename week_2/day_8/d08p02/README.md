# Day 8 Problem 2: XML/JSON Parser - Parse Nested Documents

## Problem Statement
Build a parser that can handle nested XML or JSON structures. Parse complex, hierarchical data formats and validate their structure while extracting information.

## Core Concepts

### Recursive Descent Parsing
- **Definition**: A top-down parser that uses recursive functions to handle grammar rules
- **Key Idea**: Each grammar rule becomes a function
- **Flow**: Start from the top level and recursively handle nested elements

### Why Recursive Descent?
- Natural fit for nested structures
- Easy to understand and implement
- Efficient for most practical use cases
- Good for maintaining context/state during parsing

## Key Concepts to Understand

1. **Tokenization**: Breaking input into meaningful units (tokens)
   - Example: `{ "name": "John" }` → `[LBRACE, STRING, COLON, STRING, RBRACE]`

2. **Parsing**: Converting tokens into a tree structure
   - Each element becomes a node
   - Nesting creates parent-child relationships

3. **Validation**: Ensuring structure follows rules
   - Matching opening/closing tags
   - Type consistency
   - Required fields

4. **Tree Building**: Creating an Abstract Syntax Tree (AST) or DOM tree

## Problem Variations to Consider

- **Partial Parsing**: Only extract specific fields
- **Error Recovery**: Continue parsing after errors
- **Transformation**: Convert parsed structure to different format
- **Streaming**: Handle very large files that don't fit in memory
- **Schema Validation**: Validate against a defined schema

## Example Walkthrough

### JSON Example:
```json
{
  "user": {
    "name": "Alice",
    "age": 30,
    "hobbies": ["reading", "coding", "gaming"],
    "address": {
      "city": "Boston",
      "zip": "02101"
    }
  },
  "active": true
}
```

### Parsing Steps:
1. **Tokenize**: `{ "user" : { ... }, "active" : true }`
2. **Start parsing object**: Expect `{`
3. **Parse key-value pairs**:
   - Key: "user", Value: Parse nested object
   - Key: "active", Value: Parse boolean
4. **Recursive calls** for nested structures
5. **Build tree** showing relationships

### Tree Structure:
```
Root (Object)
├── "user" → (Object)
│   ├── "name" → "Alice"
│   ├── "age" → 30
│   ├── "hobbies" → (Array)
│   │   ├── "reading"
│   │   ├── "coding"
│   │   └── "gaming"
│   └── "address" → (Object)
│       ├── "city" → "Boston"
│       └── "zip" → "02101"
└── "active" → true
```

## Algorithm Outline

```
function parseObject():
    consume '{'
    while current token != '}':
        key = parseString()
        consume ':'
        value = parseValue()
        store (key, value)
        if next token is ',':
            consume ','
    consume '}'
    return object

function parseArray():
    consume '['
    while current token != ']':
        value = parseValue()
        store value
        if next token is ',':
            consume ','
    consume ']'
    return array

function parseValue():
    if current token is '{':
        return parseObject()
    else if current token is '[':
        return parseArray()
    else if current token is string:
        return parseString()
    else if current token is number:
        return parseNumber()
    else if current token is boolean:
        return parseBoolean()
    else if current token is null:
        return null
```

## Implementation Hints

1. **Position Tracking**: Keep an index/pointer to current position
2. **Error Handling**: Check for expected tokens before consuming
3. **Recursive Calls**: Use recursion to handle nesting
4. **Data Structure**: Use objects/dictionaries to store parsed data
5. **Stack Usage**: Recursion implicitly uses call stack

## Follow-up Questions

- How would you handle malformed input (missing closing braces)?
- How would you add line/column numbers to error messages?
- What if the document is too large to fit in memory?
- How would you validate against a JSON schema?
- How would you pretty-print a parsed structure?

## Common Pitfalls to Avoid

1. ❌ Not consuming tokens properly (getting stuck in infinite loops)
2. ❌ Not handling the base case (primitive values)
3. ❌ Not checking for expected tokens before using them
4. ❌ Ignoring whitespace incorrectly
5. ❌ Not tracking recursion depth properly

## Complexity Analysis to Consider

- **Time**: O(N) where N is length of input (each token parsed once)
- **Space**: O(D) where D is maximum nesting depth (recursion stack)
  - Worst case: O(N) for very nested structure

## Test Cases to Think Through

1. Empty object `{}`
2. Empty array `[]`
3. Single key-value pair
4. Deeply nested objects
5. Arrays containing objects
6. Mixed data types
7. Empty strings and null values
