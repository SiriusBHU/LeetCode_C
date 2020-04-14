//
// Created by ID4 on 2020/3/9.
//

#include <stdio.h>
#include <stdlib.h>
#include "../include/src/x0002_add_two_num.h"


struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2)
{
    // judge input
    if(!l1 && !l2) {
        printf("input ListNode invalid");
        return NULL;
    } else if (!l1)
        return l2;
    else if (!l2)
        return l1;

    // preparation
    struct ListNode *head = malloc(sizeof(struct ListNode));
    struct ListNode *p1 = l1, *p2 = l2, *p=head;
    int fore = 0;

    // here divide the adding process into 2 while loop
    // aiming to reduce the judging time of "if ..." sentence
    while (p1 && p2) {

        p->val = p1->val + p2->val + fore;
        fore = (int)(p->val / 10);
        p->val = p->val % 10;
        p->next = NULL;

        if (fore || p1->next || p2->next) {
            p->next = malloc(sizeof(struct ListNode));
            if (!p->next) {
                printf("memory allocate error!\n");
                return NULL;
            }
        }
        p1 = p1->next; p2 = p2->next; p = p->next;
    }

    if (p2) p1 = p2;
    while (p1) {

        p->val = p1->val + fore;
        fore = (int)(p->val / 10);
        p->val = p->val % 10;
        p->next = NULL;


        if (fore || p1->next) {
            p->next = malloc(sizeof(struct ListNode));
            if (!p->next) {
                printf("memory allocate error!\n");
                return NULL;
            }
        }
        p1 = p1->next; p = p->next;
    }

    if (fore){
        p->val = fore;
        p->next = NULL;
    }

    return head;

}

void test_x0001()
{
    struct ListNode l11, l12, l13, l21, l22, l23, l24;
    l11.val = 2; l12.val = 4; l13.val = 7;
    l21.val = 5; l22.val = 6; l23.val = 4; l24.val = 9;
    l11.next = &l12; l12.next = &l13; l13.next=NULL;
    l21.next = &l22; l22.next = &l23; l23.next=&l24; l24.next = NULL;

    struct ListNode *l = addTwoNumbers(&l11, &l21);
    while (l) {
        printf("%d ", l->val);
        l = l->next;
    }
    printf("\n");

}