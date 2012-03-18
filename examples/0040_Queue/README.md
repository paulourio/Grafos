Queue
=====

There are two examples here.

Both try one solution to the same problem: process priority sorting.

The instable uses a "priority_queue" which is implemented with a heap.
Heap is not a stable algorithm, so the solution will fail.

The second uses a "deque" and the STL function "stable_sort".  This
solution will work.

Probably, using a std::stable_sort is a good call in marathon.

