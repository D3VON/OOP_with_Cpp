#ifndef MERGESORT_HPP
#define MERGESORT_HPP

#if 0

I found this implementation of merge sort for linked list
at http://www.geeksforgeeks.org/archives/7740
Merge Sort for Linked Lists
June 6, 2010
Merge sort is often preferred for sorting a linked list. 
The slow random-access performance of a linked list makes 
some other algorithms (such as quicksort) perform poorly, 
and others (such as heapsort) completely impossible.

Let head be the first Link of the linked list to be sorted 
and headRef be the pointer to head. Note that we need a 
reference to head in MergeSort() as the below implementation 
changes next links to sort the linked lists (not data at the 
Links), so head Link has to be changed if the data at original 
head is not the smallest value in linked list.

MergeSort(headRef)
1) If head is NULL or there is only one element in the Linked List
    then return.
2) Else divide the linked list into two halves.
      FrontBackSplit(head, &a, &b); /* a and b are two halves */
3) Sort the two halves a and b.
      MergeSort(a);
      MergeSort(b);
4) Merge the sorted a and b (using SortedMerge() discussed here)
   and update the head pointer using headRef.
     *headRef = SortedMerge(a, b);
     
#endif

#include<stdio.h>
#include<stdlib.h>
 
/* function prototypes */
struct Link* SortedMerge(struct Link* a, struct Link* b);
void FrontBackSplit(struct Link* source,
          struct Link** frontRef, struct Link** backRef);
 
/* sorts the linked list by changing next pointers (not data) */
void MergeSort(struct Link** headRef)
{
  struct Link* head = *headRef;
  struct Link* a;
  struct Link* b;
 
  /* Base case -- length 0 or 1 */
  if ((head == NULL) || (head->next == NULL))
  {
    return;
  }
 
  /* Split head into 'a' and 'b' sublists */
  FrontBackSplit(head, &a, &b); 
 
  /* Recursively sort the sublists */
  MergeSort(&a);
  MergeSort(&b);
 
  /* answer = merge the two sorted lists together */
  *headRef = SortedMerge(a, b);
}
 
/* See http://geeksforgeeks.org/?p=3622 for details of this
   function */
struct Link* SortedMerge(struct Link* a, struct Link* b)
{
  struct Link* result = NULL;
 
  /* Base cases */
  if (a == NULL)
     return(b);
  else if (b==NULL)
     return(a);
 
  /* Pick either a or b, and recur */
  if (a->data <= b->data)
  {
     result = a;
     result->next = SortedMerge(a->next, b);
  }
  else
  {
     result = b;
     result->next = SortedMerge(a, b->next);
  }
  return(result);
}
 
/* UTILITY FUNCTIONS */
/* Split the Links of the given list into front and back halves,
     and return the two lists using the reference parameters.
     If the length is odd, the extra Link should go in the front list.
     Uses the fast/slow pointer strategy.  */
void FrontBackSplit(struct Link* source,
          struct Link** frontRef, struct Link** backRef)
{
  struct Link* fast;
  struct Link* slow;
  if (source==NULL || source->next==NULL)
  {
    /* length < 2 cases */
    *frontRef = source;
    *backRef = NULL;
  }
  else
  {
    slow = source;
    fast = source->next;
 
    /* Advance 'fast' two Links, and advance 'slow' one Link */
    while (fast != NULL)
    {
      fast = fast->next;
      if (fast != NULL)
      {
        slow = slow->next;
        fast = fast->next;
      }
    }
 
    /* 'slow' is before the midpoint in the list, so split it in two
      at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
  }
}
 
/* Function to print Links in a given linked list */
void printList(struct Link *link)
{
  while(link!=NULL)
  {
   printf("%d ", link->data);
   link = link->next;
  }
}
 
/* Function to insert a link at the beginging of the linked list */
void push(struct Link** head_ref, int new_data)
{
  /* allocate link */
  struct Link* new_Link =
            (struct Link*) malloc(sizeof(struct Link));
 
  /* put in the data  */
  new_Link->data  = new_data;
 
  /* link the old list off the new link */
  new_Link->next = (*head_ref);    
 
  /* move the head to point to the new Link */
  (*head_ref)    = new_Link;
} 
 
/* Drier program to test above functions*/
int main()
{
  /* Start with the empty list */
  struct Link* res = NULL;
  struct Link* a = NULL;
  struct Link* b = NULL; 
 
  /* Let us create a unsorted linked lists to test the functions
   Created lists shall be a: 2->3->20->5->10->15 */
  push(&a, 15);
  push(&a, 10);
  push(&a, 5);
  push(&a, 20);
  push(&a, 3);
  push(&a, 2); 
 
  /* Remove duplicates from linked list */
  MergeSort(&a);
 
  printf("\n Sorted Linked List is: \n");
  printList(a);           
 
  getchar();
  return 0;
}