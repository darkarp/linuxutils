#include <stddef.h>
#include <stdlib.h>

#include "list.h"

typedef struct Node_ *Node;
struct Node_ {
    Node next;
    void *element;
};

struct List_ {
    Node head;
    Node tail;
    size_t size;
};

Node _create_node(void *element) {
    Node node = malloc(sizeof(struct Node_));
    node->next = NULL;
    node->element = element;
    return node;
}

void _destroy_node(Node node, void (*free_element)(void *)) {
    if (free_element != NULL) {
        free_element(node->element);
    }
    free(node);
}

// Creates a new list.
List list_create() {
    List list = malloc(sizeof(struct List_));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

// Destroys a list.
void list_destroy(List list, void (*free_element)(void *)) {
    Node node = list->head;
    while (node != NULL) {
        Node next = node->next;
        _destroy_node(node, free_element);
        node = next;
    }
    free(list);
}

// Returns true iff the list contains no elements.
bool list_is_empty(List list) { return list->size == 0; }

// Returns the number of elements in the list.
size_t list_size(List list) { return list->size; }

// Returns the first element of the list.
void *list_get_first(List list) {
    if (list_is_empty(list)) {
        return NULL;
    }
    return list->head->element;
}

// Returns the last element of the list.
void *list_get_last(List list) {
    if (list_is_empty(list)) {
        return NULL;
    }
    return list->tail->element;
}

// Returns the element at the specified position in the list.
// Range of valid positions: 0, ..., size()-1.
void *list_get(List list, size_t position) {
    if (position >= list->size) {
        return NULL;
    }
    Node node = list->head;
    for (size_t i = 0; i < position; i++) {
        node = node->next;
    }
    return node->element;
}

// Returns the position in the list of the
// first occurrence of the specified element,
// or -1 if the specified element does not
// occur in the list.
int list_find(List list, bool (*equal)(void *, void *), void *element) {
    Node node = list->head;
    for (size_t i = 0; i < list->size; i++) {
        if (equal(node->element, element)) {
            return i;
        }
        node = node->next;
    }
    return -1;
}

// Inserts the specified element at the first position in the list.
void list_insert_first(List list, void *element) {
    Node node = _create_node(element);
    node->next = list->head;
    list->head = node;
    if (list_is_empty(list)) {
        list->tail = node;
    }
    list->size++;
}

// Inserts the specified element at the last position in the list.
void list_insert_last(List list, void *element) {
    Node node = _create_node(element);
    if (list_is_empty(list)) {
        list->head = node;
    } else {
        list->tail->next = node;
    }
    list->tail = node;
    list->size++;
}

// Inserts the specified element at the specified position in the list.
// Range of valid positions: 0, ..., size().
// If the specified position is 0, insert corresponds to insertFirst.
// If the specified position is size(), insert corresponds to insertLast.
void list_insert(List list, void *element, size_t position) {
    if (position > list->size) {
        return;
    }
    if (position == 0) {
        list_insert_first(list, element);
    } else if (position == list->size) {
        list_insert_last(list, element);
    } else {
        Node node = _create_node(element);
        Node prev = list->head;
        for (size_t i = 0; i < position - 1; i++) {
            prev = prev->next;
        }
        node->next = prev->next;
        prev->next = node;
        list->size++;
    }
}

// Removes and returns the element at the first position in the list.
void *list_remove_first(List list) {
    if (list_is_empty(list)) {
        return NULL;
    }
    Node node = list->head;
    list->head = node->next;
    if (list->head == NULL) {
        list->tail = NULL;
    }
    void *element = node->element;
    _destroy_node(node, NULL);
    list->size--;
    return element;
}

// Removes and returns the element at the last position in the list.
void *list_remove_last(List list) {
    if (list_is_empty(list)) {
        return NULL;
    }
    void *element = list->tail->element;
    if (list_size(list) == 1) {
        list_make_empty(list, NULL);
    } else {
        Node node = list->head;
        while (node->next != list->tail) {
            node = node->next;
        }
        list->tail = node;
        list->size--;
    }
    return element;
}

// Removes and returns the element at the specified position in the list.
// Range of valid positions: 0, ..., size()-1.
void *list_remove(List list, size_t position) {
    if (position >= list_size(list)) {
        return NULL;
    } else if (position == 0) {
        return list_remove_first(list);
    } else if (position == list_size(list) - 1) {
        return list_remove_last(list);
    }

    Node prev = list->head;
    for (size_t i = 0; i < position - 1; i++) {
        prev = prev->next;
    }
    Node node = prev->next;
    void *element = node->element;
    prev->next = node->next;
    _destroy_node(node, NULL);
    list->size--;
    return element;
}

// Removes all elements from the list.
void list_make_empty(List list, void (*free_element)(void *)) {
    Node node = list->head;
    while (node != NULL) {
        Node next = node->next;
        _destroy_node(node, free_element);
        node = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

// Returns an array with the elements of the list.
void list_to_array(List list, void **out_array) {
    Node node = list->head;
    for (size_t i = 0; i < list->size; i++) {
        out_array[i] = node->element;
        node = node->next;
    }
}

// Andre Sabino