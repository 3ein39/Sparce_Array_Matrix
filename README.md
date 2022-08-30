
# [Sparce 1D Array](https://github.com/3ein39/Sparce_Array_Matrix/blob/main/1d_sparce.cpp) 


Representing an array of very huge indicies (e.g. 10^8) using doubly linked list .. 

- In some applications, we might want to represent an array with indices very huge (e.g. 10^8), however, most of it are just zeros (e.g. 95%).
- Creating such huge arrays is very time & memory harmful with no return.
* The following functions are supported :
    - Set & Get positions.
    - Print & Add arrays.
---
# [Sparce 2D Array](https://github.com/3ein39/Sparce_Array_Matrix/blob/main/2d_sparce.cpp) 
A more severe/common case is a sparse matrix where most of it are zeros which is implemented here.

- Similarly, SparseMatrix acts like a 2D array.
* Now we can think of sparse matrix as linked list of linked list
    - 2 linked lists.
    - First: the 1D array linked list
    - Second: linked list, the data of each node is a 1D linked list
    - Again .. A double ll is used.
    
## Acknowledgements

 - [Mastering critical SKILLS in Data Structures using C++](https://www.udemy.com/course/dscpp-skills/)

