# Cpp-Algorithms
Algorithms adapted from Data Structures and Algorithms in C++ assignments

This repository has the source code of two assignments.

## [Simple Board Game](./SimpleBoardGame/SimpleBoardGame.cpp)

Jack and Jill move down a single path at the roll of a dice. If a player lands on
the same space as the other player, they are sent back three spaces from where they
were intended to land. ([readme](./SimpleBoardGame))


## [Singly Linked List Insertion Sort](./SinglyLinkedListInsertionSort/Asn4.cpp)

This code demonstrates how you can perform an self-insertion sort on a singly linked
list (without creating additional SLLs). Key features of this code are the ways it
uses Java-style iterators to improve its source-code readability. This implementation
of insertion sort is not based on another source code. Considering the structure of a
singly linked list, this insertion-sort algorithm differs from standard, by the way
the algorithm finds a place to insert each unsorted element. In a standard insertion
sort the unsorted element is compared with each element of the sorted list in a
descending direction, while here we find the insertion point by comparing in an
ascending direction (due to the way the SLL works). This makes sorting lists that are
already sorted in ascending order the worst case efficiency scenario, while sorting a
list already sorted in descending order the best case efficiency scenario.
