# Singly Linked List Implementation in C++

This directory contains a comprehensive implementation of a singly linked list data structure in C++.

## Features

### Core Operations
- **Insertion**: At beginning, end, and specific position
- **Deletion**: From beginning, end, and specific position
- **Search**: Find if a value exists in the list
- **Access**: Get value at specific position
- **Display**: Print the entire linked list
- **Reverse**: Reverse the order of elements
- **Size**: Get the current size of the list
- **Empty Check**: Check if the list is empty

### Advanced Features
- **Template-based**: Works with any data type (int, string, custom classes, etc.)
- **Memory Management**: Automatic cleanup with destructor
- **Cycle Detection**: Floyd's Cycle Finding Algorithm
- **Error Handling**: Proper validation for edge cases

## File Structure

- `singly_linked_list.cpp` - Main implementation with example usage

## Usage Example

```cpp
#include "singly_linked_list.cpp"

int main() {
    // Create a linked list of integers
    SinglyLinkedList<int> list;
    
    // Insert elements
    list.insertAtEnd(10);
    list.insertAtBeginning(5);
    list.insertAtPosition(15, 1);
    
    // Display the list
    list.display(); // Output: Linked List: 5 -> 15 -> 10
    
    // Search for elements
    bool found = list.search(15); // Returns true
    
    // Delete elements
    list.deleteFromBeginning();
    list.deleteFromEnd();
    
    // Get size
    int size = list.getSize();
    
    // Reverse the list
    list.reverse();
    
    return 0;
}
```

## Time Complexity

| Operation | Time Complexity |
|-----------|-----------------|
| Insert at beginning | O(1) |
| Insert at end | O(n) |
| Insert at position | O(n) |
| Delete from beginning | O(1) |
| Delete from end | O(n) |
| Delete from position | O(n) |
| Search | O(n) |
| Access by position | O(n) |
| Reverse | O(n) |

## Space Complexity

- **Space**: O(n) where n is the number of elements
- **Each Node**: Contains data + pointer to next node

## Compilation

```bash
g++ -o singly_linked_list singly_linked_list.cpp
./singly_linked_list
```

## Key Implementation Details

1. **Node Structure**: Each node contains data and a pointer to the next node
2. **Head Pointer**: Points to the first node in the list
3. **Size Tracking**: Maintains count of elements for efficient size queries
4. **Memory Safety**: Destructor ensures proper cleanup to prevent memory leaks
5. **Template Support**: Generic implementation works with any data type

## Common Use Cases

- Dynamic data storage where size is unknown
- Implementing stacks and queues
- Polynomial arithmetic
- Memory-efficient data structures
- Interview problems and algorithm practice
