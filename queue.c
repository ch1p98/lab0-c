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
        list_ele_t *tok = NULL;
        while (tmp) {
            tok = tmp->next;
            free(tmp->value);
            free(tmp);
            tmp = tok;
        }
        free(q);
    }
    return;
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
    int x = strlen(s);
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    char *val = malloc(x + 1);
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if (!val) {
        free(newh);
        return false;
    }
    strncpy(val, s, x);
    val[x] = '\0';
    newh->value = val;
    newh->next = q->head;
    if (q->size == 0)
        q->tail = newh; /*if q is not empty.*/

    q->head = newh;
    q->size += 1;
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
    int x = strlen(s);
    list_ele_t *newt = malloc(sizeof(list_ele_t));
    if (!newt) {
        return false;
    }
    char *val = malloc(x + 1);
    if (!val) {
        free(newt);
        return false;
    }
    memcpy(val, s, x);
    val[x] = '\0';
    newt->value = val;
    if (q->size != 0) { /*if q is not empty.*/
        q->tail->next = newt;
    } else
        q->head = newt;
    newt->next = NULL;
    q->tail = newt;
    q->size += 1;
    /* Remember: It should operate in O(1) time */
    /* TOADY: Remove the above comment when you are about to implement. */
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful. (V)
 * Return false if queue is NULL or empty. (V)
 * If sp is not NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (!q || !q->size || !sp)
        return false;
    if (!memcpy(sp, q->head->value, bufsize - 1))
        return false;
    sp[bufsize - 1] = '\0';

    list_ele_t *temp = q->head;
    q->head = q->head->next;
    q->size--;
    free(temp->value);
    free(temp);
    temp = NULL;

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
    if (!q || !q->head) {
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
/*void _takeaddr(queue_t *q)
{
    if (!q || !q->head)
        return;
    list_ele_t *ptr = q->head;
    int count = 0;
    printf("queue's elements' addresses: \n");
    while (ptr) {
        printf("loc %d: %p\n", count, ptr);
        count++;
        ptr = ptr->next;
    }
}*/

void q_reverse(queue_t *q)
{
    if (!q || q->size <= 1 || !q->head)
        return;
    list_ele_t *current = q->head;
    list_ele_t *prev = NULL;
    list_ele_t *upcoming = current->next;
    /*_takeaddr(q);*/
    while (upcoming) {
        current->next = prev;
        /*printf("step 12: prev:%p, current:%p, upcoming:%p\n", prev, current,
               upcoming);*/
        prev = current;
        current = upcoming;
        upcoming = current->next;
        /*printf("step  4: prev:%p, current:%p, upcoming:%p\n", prev, current,
               upcoming);*/
    }
    current->next = prev;
    q->tail = q->head;
    q->head = current;
}

/*
list_ele_t *list_merge(list_ele_t *l1, list_ele_t *l2);


list_ele_t *list_split(list_ele_t *head)
{
    if (head == NULL || head->next == NULL)
        return head;

    list_ele_t *fast = head->next;
    list_ele_t *slow = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    fast = slow->next;
    slow->next = NULL;

    list_ele_t *l1 = list_split(head);
    list_ele_t *l2 = list_split(fast);

    return list_merge(l1, l2);
}

list_ele_t *list_merge(list_ele_t *l1, list_ele_t *l2)
{
    if (l1 == NULL)
        return l2;
    if (l2 == NULL)
        return l1;

    if (strcmp(l1->value, l2->value) < 0) {
        l1->next = list_merge(l1->next, l2);
        return l1;
    } else {
        l2->next = list_merge(l1, l2->next);
        return l2;
    }
}

void q_sort(queue_t *q)
{
    if (q == NULL || q->size <= 1)
        return;
    q->head = list_split(q->head);
    list_ele_t *t = q->head;
    while (t->next)
        t = t->next;
    q->tail = t;
}
*/


/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */

list_ele_t *merge_sort(list_ele_t *head);
list_ele_t *merge(list_ele_t *s, list_ele_t *e);
/*void print_node(list_ele_t *n);*/

void q_sort(queue_t *q)
{
    if (!q || !q->head || !q->tail || q->head == q->tail)
        return;
    q->head = merge_sort(q->head);
    list_ele_t *t = q->head;
    while (t->next)
        t = t->next;
    q->tail = t;
}

list_ele_t *merge_sort(list_ele_t *head)
{
    if (!head || !head->next)
        return head;
    list_ele_t *fast = head->next;
    list_ele_t *slow = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    fast = slow->next;
    slow->next = NULL;
    list_ele_t *h1 = merge_sort(head);
    list_ele_t *h2 = merge_sort(fast);
    return merge(h1, h2);
}

list_ele_t *merge(list_ele_t *s, list_ele_t *e)
{
    if (!s)
        return e;
    if (!e)
        return s;
    if (strcmp(s->value, e->value) < 0) { /*  */
        s->next = merge(s->next, e);
        return s;
    } else {
        e->next = merge(s, e->next);
        return e;
    }
}
/*
void print_node(list_ele_t *n)
{
    if (!n)
        return;

    printf("%s->", n->value);
    while (n->next) {
        printf("%s->", n->next->value);
        n = n->next;
    }
    printf("\nthe queue end here...\n\n");
}
/*


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
/*
int main()
{
    queue_t *deu = q_new();
    char *typ_a = "panther";
    char *typ_b = "tiger";
    q_insert_tail(deu, typ_a);
    q_insert_head(deu, typ_b);
    q_reverse(deu);
}
*/