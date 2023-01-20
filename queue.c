#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */

struct list_head *q_mid(struct list_head *head);


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *head = malloc(sizeof(struct list_head));
    if (head)
        INIT_LIST_HEAD(head);
    return head;
}

/* Free all storage used by queue */
void q_free(struct list_head *l)
{
    if (!l)
        return;

    element_t *del_e = NULL, *nxt_e = NULL;
    list_for_each_entry_safe (del_e, nxt_e, l, list) {
        list_del(&del_e->list);
        q_release_element(del_e);
    }
    free(l);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head)
        return false;
    element_t *new_e = malloc(sizeof(element_t));
    if (!new_e)
        return false;
    int s_len = strlen(s);
    new_e->value = malloc(s_len + 1);
    if (!new_e->value) {
        free(new_e);
        return false;
    }
    strncpy(new_e->value, s, s_len);
    *(new_e->value + s_len) = '\0';
    list_add(&new_e->list, head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head)
        return false;
    element_t *new_e = malloc(sizeof(element_t));
    if (!new_e)
        return false;
    int s_len = strlen(s);
    new_e->value = malloc(s_len + 1);
    if (!new_e->value) {
        free(new_e);
        return false;
    }
    strncpy(new_e->value, s, s_len);
    *(new_e->value + s_len) = '\0';
    list_add_tail(&new_e->list, head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;
    element_t *rmv_e = list_first_entry(head, element_t, list);
    list_del_init(&rmv_e->list);
    if (sp && bufsize) {
        strncpy(sp, rmv_e->value, bufsize - 1);
        *(sp + bufsize - 1) = '\0';
    }
    return rmv_e;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;
    element_t *rmv_e = list_last_entry(head, element_t, list);
    list_del_init(&rmv_e->list);
    if (sp && bufsize) {
        strncpy(sp, rmv_e->value, bufsize - 1);
        *(sp + bufsize - 1) = '\0';
    }
    return rmv_e;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head || list_empty(head))
        return 0;
    int len = 0;
    struct list_head *n;
    list_for_each (n, head)
        len++;
    return len;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    if (!head || list_empty(head))
        return false;
    element_t *mid_e = list_entry(q_mid(head), element_t, list);
    list_del(&mid_e->list);
    q_release_element(mid_e);
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head) {}

/* Sort elements of queue in ascending order */
void q_sort(struct list_head *head) {}
/****************************************************************************/
struct list_head *q_mid(struct list_head *head)
{
    struct list_head *n = head->next, *p = head->prev;
    while (n != p && n->next != p) {
        n = n->next;
        p = p->prev;
    }
    return p;
}
