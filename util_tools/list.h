#ifndef __LIST_H__
#define __LIST_H__

#include <stddef.h>
//#include <typeinfo.h>

typedef struct list_head{
	struct list_head *next, *prev;
}LIST_HEAD, *PLIST_HEAD;

#define container_of(ptr, type, member)		(type *)((char *)ptr - offsetof(type, member))

#define LIST_HEAD_INIT(name) {&(name), &(name)}

static inline void INIT_LIST_HEAD(PLIST_HEAD list)
{
	list->next = list;
	list->prev = list;
}

static inline void __list_add(PLIST_HEAD cur, PLIST_HEAD prev, PLIST_HEAD next)
{
	cur->prev = prev;
	cur->next = next;
	next->prev = cur;
	prev->next = cur;
}

static inline void list_add(PLIST_HEAD cur, PLIST_HEAD head)
{
	__list_add(cur, head, head->next);
}

static inline void list_add_tail(PLIST_HEAD cur, PLIST_HEAD head)
{
	__list_add(cur, head->prev, head);
}

static inline void _list_del(PLIST_HEAD prev, PLIST_HEAD next)
{
	next->prev = prev;
	prev->next = next;
}

static inline void list_del(PLIST_HEAD entry)
{
	_list_del(entry->prev, entry->next);
	entry->next = NULL;
	entry->prev = NULL;
}

static inline int list_empty(const PLIST_HEAD head)
{
	return head->next == head;
}

static inline int list_empty_careful(const PLIST_HEAD head)
{
	PLIST_HEAD next = head->next;
	return (next == head) && (next == head->prev);
}

static inline PLIST_HEAD list_get_tail(PLIST_HEAD head)
{
	return head->prev;
}

#define list_entry(ptr, type, member)	\
	container_of(ptr, type, member)

#define list_get_entry(type, pos, head, member)	\
	pos = list_entry((head)->next, type, member);

#define list_for_each(pos, head)	\
	for(pos = (head)->next; pos != (head); pos = pos->next)

#define __list_for_each(pos, head)	\
	for(pos = (head)->next; pos != (head); pos = pos->next)

#define list_for_each_prev(pos, head)	\
	for(pos = (head)->prev; pos != (head); pos = pos->prev)

#define list_for_each_safe(pos, n, head)	\
	for(pos = (head)->next, n = pos->next; pos != (head); pos = n, n = pos->next)

#define list_for_each_entry_safe(type, pos, n, head, member)	\
	for(pos = list_entry((head)->next, type, member), n = list_entry(pos->member.next, type, member);	\
	&pos->member != (head);	\
	pos = n, n = list_entry(n->member.next,type, member))

#define list_for_each_entry(type, pos, head, member)	\
	for(pos = list_entry((head)->next, type, member);	\
		&pos->member != (head);	\
		pos = list_entry(pos->member.next, type, member))

#define list_for_each_entry_reverse(type, pos, head, member)	\
	for(pos = list_entry((head)->prev, type, member);	\
		pos->member != (head);	\
		pos = list_entry(pos->member.prev, type, member))

#endif