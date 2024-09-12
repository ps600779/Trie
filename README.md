# Trie-Based Dictionary with Spell Check, Autocomplete, and Autocorrect

## Overview

This project implements a Trie data structure to support three main functionalities:

1. **Spell Check**: Verifies if a given word exists in the dictionary.
2. **Autocomplete**: Suggests words from the dictionary that begin with a given prefix.
3. **Autocorrect**: Suggests words from the dictionary that are within an edit (Levenshtein) distance of 3 from a given word.

The Trie is populated with words from a user-provided dictionary, and queries are processed to perform one of the three operations.

## Features

- **Efficient search and insert operations** using the Trie data structure.
- **Autocomplete** suggestions for words starting with a specific prefix.
- **Autocorrect** suggestions based on the Levenshtein distance.
- Handles up to **1000 words** in the dictionary and **1000 queries** efficiently.

## Input Format

The program expects input in the following format:

1. The first line contains two space-separated integers: `n` (number of words in the dictionary) and `q` (number of queries).
2. The next `n` lines contain words (`s`) which are added to the dictionary.
3. The next `q` lines contain two values:
    - An integer `ai`:
      - `1`: Spell check operation.
      - `2`: Autocomplete operation.
      - `3`: Autocorrect operation.
    - A string `ti`:
      - Word or prefix for the corresponding query.

### Example Input:

```txt
10 4
consider
filters
filers
entitled
tilers
litter
dames
filling
grasses
fitter
1 litter
1 dame
2 con
3 filter
