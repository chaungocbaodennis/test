/*
 * linkedList.h
 *
 *  Created on: Apr 3, 2016
 *      Author: Dennis Chau
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

struct ListNode
{
	int val;
	struct ListNode *next,*prev;
};
struct ListNode* reverseList(struct ListNode* head);
void printList(struct ListNode *head);
void printList_partial(struct ListNode *head,int numOfNode);
void printList_reverse(struct ListNode* head);
void push(struct ListNode** head_ref, int new_data, unsigned char addToFront);
struct ListNode* removeNthFromEnd(struct ListNode* head, int n);
void deleteNode(struct ListNode* node_todelete);
void removeDuplicateNodes(struct ListNode *head);
static void reverse_linkedlist(struct ListNode** head_ref);
int cmp(struct ListNode *a, struct ListNode *b);
struct ListNode *listsort(struct ListNode *list, int is_circular, int is_double);
int pop(struct ListNode** head);

#endif /* LINKEDLIST_H_ */
