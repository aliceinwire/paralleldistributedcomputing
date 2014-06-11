/* 
 * This is a kernel style - O(1) complexity linked list implementation.
 * Simple, doubly circular list.
 */
#ifndef _LIST_H
#define _LIST_H 

/*
 * Stand alone list-only data structure.
 * Can be included by any other structure.
 * We have a way to traverse backwards to find the container.
 */
struct list_head {
        struct list_head* next;
        struct list_head* prev;
};

/* Empty list simulation */
#define LIST_HEAD_INIT(name) { &(name), &(name) }

/* Empty list declaration */
#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

/* 
 * Internal-Generic 
 * Saves few cpu cycles if prev and next are already at hand.
 */ 
static inline void _list_add(struct list_head* new, 
                        struct list_head* prev,
                        struct list_head* next)
{
        next->prev = new;
        new->next = next;
        new->prev = prev;
        prev->next = new;
}

/*
 * This function only dereferences the list entries and invokes the generic,
 * post-dereferenced, fast routine. And that's it.
 */
static inline void list_add(struct list_head* new, struct list_head* head)
{
        _list_add(new, head, head->next);
}

/*
 * This function only dereferences the list entries and invokes the generic,
 * post-dereferenced, fast routine. Arguments are differently sequenced to
 * achieve addition at the back of the list.
 */
static inline void list_add_tail(struct list_head* new, struct list_head* head)
{
        _list_add(new, head->prev, head);
}

/* 
 * Internal-Generic 
 * Save few cpu cycles if prev and next are already at hand.
 */ 
static inline void _list_del(struct list_head* prev, struct list_head* next)
{
        next->prev = prev;
        prev->next = next;
}

/* This function removes the element entry from the list. Note, it does not
 * free any memory belonging to enTRy or the data structure in which it is
 * embedded; this function merely removes the element from the list. After
 * calling this, you would typically destroy your data structure and the
 * list_head inside it.
 */
static inline void list_del(struct list_head* entry)
{
        _list_del(entry->prev, entry->next);
}

#endif

