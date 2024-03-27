#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

#include "list.h"

ListNode* createListNode(ListInfo* info, void* item, va_list args) {
    if (info == NULL) {
        LOG_ERROR("ListInfo is NULL in createListNode");
        return NULL;
    }

    ListNode* node = malloc(sizeof(ListNode));
    if (node == NULL) {
        LOG_ERROR("Memory allocation failed in createListNode");
        return NULL;
    }

    node->item = info->createItemInfo(item, args);
    node->next = NULL;
    va_end(args);
    return node;
}

ListNode* getListNode(List* list, U64 index) {
    if (list == NULL) {
        LOG_ERROR("List is NULL in getListNode");
        return NULL;
    }

    if (index > list->size || index < 1) {
        LOG_WARNING("Invalid index in getListNode");
        return NULL;
    }

    U64 i = 1;
    ListNode* temp = list->head;
    while (i < index && temp != NULL) {
        temp = temp->next;
        ++i;
    }

    return temp;
}

ListNode* addListNode(List* list, void* item, va_list args) {
    if (list == NULL) {
        LOG_ERROR("List is NULL in addListNode");
        return NULL;
    }

    ListNode* node = createListNode(list->info, item, args);
    if (node == NULL) {
        LOG_ERROR("Failed to create list node in addListNode");
        return NULL;
    }

    if (list->head == NULL) {
        list->head = node;
        list->tail = list->head;
    } else {
        list->tail->next = node;
        list->tail = node;
    }

    ++list->size;
    return list->tail;
}

List* initList(ListInfo* info) {
    if (info == NULL) {
        LOG_ERROR("ListInfo is NULL in initList");
        return NULL;
    }

    List* list = malloc(sizeof(List));
    if (list == NULL) {
        LOG_ERROR("Memory allocation failed in initList");
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->info = info;
    list->size = 0;

    return list;
}

List* createList(ListInfo* info, U64 size, ...) {
    if (info == NULL) {
        LOG_ERROR("ListInfo is NULL in createList");
        return NULL;
    }

    List* list = initList(info);
    if (list == NULL) {
        LOG_ERROR("Failed to initialize list in createList");
        return NULL;
    }

    if (size == 0) {
        return list;
    }

    list->size = size;

    ListNode* temp = NULL;

    va_list args;
    va_start(args, size);
    for (U64 i = 0; i < size; ++i) {
        va_list copyargs;
        va_copy(copyargs, args);
        if (temp == NULL) {
            list->head = createListNode(info, NULL, copyargs);
            temp = list->head;
        } else {
            temp->next = createListNode(info, NULL, copyargs);
            temp = temp->next;
        }
    }
    va_end(args);

    list->tail = temp;

    return list;
}

bool debugList(List* list) {
    if (list == NULL) {
        LOG_ERROR("List is NULL in debugList");
        return false;
    }

    ListNode* temp = list->head;
    U64 count = 0;

    while (temp != NULL) {
        ++count;

        if (temp->item == NULL) {
            LOG_WARNING("Item is NULL in debugList");
        } else {
            list->info->debugItemInfo(temp->item);
        }

        temp = temp->next;
    }

    if (count == list->size) {
        return true;
    } else {
        LOG_WARNING("Mismatch in list size and counted nodes in debugList");
        return false;
    }
}

U64 freeItems(List* list) {
    if (list == NULL) {
        LOG_ERROR("List is NULL in freeItems");
        return 0;
    }

    if (debugList(list) == false) {
        LOG_WARNING("Invalid list in freeItems");
        return 0;
    }

    U64 count = 0;
    ListNode* temp = list->head;
    ListNode* next;
    while (temp != NULL) {
        next = temp->next;
        free(temp);
        temp = next;
        ++count;
    }

    list->size -= count;
    list->head = NULL;
    list->tail = NULL;

    return count;
}

U64 shrinkList(List* list, U64 index) {
    if (list == NULL) {
        LOG_ERROR("List is NULL in shrinkList");
        return 0;
    }

    if (debugList(list) == false) {
        LOG_WARNING("Invalid list in shrinkList");
        return 0;
    }

    if (index >= list->size || index < 1) {
        LOG_WARNING("Invalid index in shrinkList");
        return 0;
    }

    ListNode* node = getListNode(list, index);
    if (node == NULL) {
        LOG_WARNING("ListNode not found at index in shrinkList");
        return 0;
    }
    list->tail = node;

    node = node->next;
    ListNode* temp;
    U64 i = 0;
    while (node != NULL) {
        temp = node->next;
        free(node);
        node = temp;
        ++i;
    }

    list->tail->next = NULL;
    list->size -= i;

    return i;
}

List* splitList(List* list, U64 index) {
    ISNULL(list);

    if (index >= list->size) {
        LOG_WARNING("Index greater than or equal to the list size");
        return NULL;
    }

    List* newList = initList(list->info);
    ISNULL(newList);

    ListNode* newListHead = getListNode(list, index);
    ISNULL(newListHead);

    newList->size = list->size - index;

    newList->head = newListHead->next;
    newList->tail = list->tail;

    newListHead->next = NULL;

    list->tail = newListHead;
    list->size = index;

    return newList;
}

