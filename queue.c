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
    return true;
}


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
        prev = current;
        current = upcoming;
        upcoming = current->next;
    }
    current->next = prev;
    q->tail = q->head;
    q->head = current;
}

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
*/
