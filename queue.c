#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TOADY: What if malloc returned NULL? */
    if (!q) {
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TOADY: How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q) {
        list_ele_t *tmp = q->head;
        list_ele_t *tok;
        while (tmp) {
            tok = tmp->next;
            free(tmp);
            tmp = tok;
        }
    }
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (!q) {
        return false;
    }
    list_ele_t *newh;
    /* TOADY: What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    char *val = malloc(sizeof(strlen(s)) + 1);
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if (!newh || !val) {
        return false;
    }
    strncpy(val, s, strlen(s));
    newh->value = val;
    if (q->size != 0) { /*if q is not empty.*/
        newh->next = q->head;
        q->head = newh;
    } else {
        q->head = newh;
        q->tail = newh;
    }
    q->size++;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (!q) {
        return false;
    }

    list_ele_t *appendix = malloc(sizeof(list_ele_t));
    char *val = malloc(strlen(s) + 1);
    if (!appendix || !val) {
        return false;
    }
    strncpy(val, s, strlen(s));
    appendix->value = val;
    appendix->next = NULL;
    /* TOADY: You need to write the complete code for this function */
    if (q->size != 0) { /*if q is not empty.*/
        q->tail->next = appendix;
        q->tail = appendix;
    } else {
        q->head = appendix;
        q->tail = appendix;
    }
    q->size++;
    /* Remember: It should operate in O(1) time */
    /* TOADY: Remove the above comment when you are about to implement. */
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful. (V)
 * Return false if queue is NULL or empty. (V)
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (!q || q->size == 0) {
        return false;
    }
    list_ele_t *rm = q->head;
    q->head = rm->next;
    q->size--;

    if (sp) {
        strncpy(sp, rm->value, bufsize - 1);
    }
    free(rm->value);
    free(rm);
    /* TOADY: You need to fix up this code. */
    /* TOADY: Remove the above comment when you are about to implement. */
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* TOADY: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TOADY: Remove the above comment when you are about to implement. */
    if (!q) {
        return 0;
    }
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* TOADY: You need to write the code for this function */
    /* TOADY: Remove the above comment when you are about to implement. */
    if (q->size == 0 || q->size == 1) {
        return;
    }
    list_ele_t *current = q->head;
    list_ele_t *prev = NULL;
    list_ele_t *upcoming = current->next;
    while (upcoming != NULL) {
        current->next = prev;
        prev = current;
        current = upcoming;
        upcoming = current->next;
    }
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}

/*void _swap(queue_t *q, int a, int b)
{
    if (q->size < a || q->size < b) {
        return;
    }
}
*/

/*void merge(queue_t *q, int *tmp, int s, int m, int r)
{
    if (r - s == 2) {
    }
    if
        > 2 : s and m + 1 as index 1 and 2
}
*/
/*
void merge_sort(queue_t *q)
{
    int curr_size, left_start;
    int *tmp;
    tmp = malloc(sizeof(int) * (q->size));
    if (!tmp)
        return;
    for (curr_size = 1; curr_size < q->size; curr_size *= 2) {
        for (left_start = 0; left_start < q->size;
             left_start += 2 * curr_size) {
            int right_end = min(q->size - 1, left_start + 2 * curr_size);
            int mid = (left_start + right_end) / 2;
            merge(q, tmp, left_start, mid, right_end);
        }
    }
}
*/
