#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct List_ *List;

// Creates a new list.
List list_create();

// Destroys a list.
void list_destroy(List list, void (*free_element)(void *));

// Returns true iff the list contains no elements.
bool list_is_empty(List list);

// Returns the number of elements in the list.
size_t list_size(List list);

// Returns the first element of the list.
void *list_get_first(List list);

// Returns the last element of the list.
void *list_get_last(List list);

// Returns the element at the specified position in the list.
// Range of valid positions: 0, ..., size()-1.
void *list_get(List list, size_t position);

// Returns the position in the list of the
// first occurrence of the specified element,
// or -1 if the specified element does not
// occur in the list.
int list_find(List list, bool (*equal)(void *, void *), void *element);

// Inserts the specified element at the first position in the list.
void list_insert_first(List list, void *element);

// Inserts the specified element at the last position in the list.
void list_insert_last(List list, void *element);

// Inserts the specified element at the specified position in the list.
// Range of valid positions: 0, ..., size().
// If the specified position is 0, insert corresponds to insertFirst.
// If the specified position is size(), insert corresponds to insertLast.
void list_insert(List list, void *element, size_t position);

// Removes and returns the element at the first position in the list.
void *list_remove_first(List list);

// Removes and returns the element at the last position in the list.
void *list_remove_last(List list);

// Removes and returns the element at the specified position in the list.
// Range of valid positions: 0, ..., size()-1.
void *list_remove(List list, size_t position);

// Removes all elements from the list.
void list_make_empty(List list, void (*free_element)(void *));

// Returns an array with the elements of the list.
void list_to_array(List list, void **out_array);

#endif