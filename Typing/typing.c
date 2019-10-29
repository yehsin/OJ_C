#include<stdlib.h>
#include<stdio.h>
#include<string.h>
//#include"12350.h"

#define ll long long int
#define next ptr_to_next_node
#define prev ptr_to_prev_node
#define ch character
typedef struct _NODE
{
	char character;
	struct _NODE *ptr_to_next_node;
	struct _NODE *ptr_to_prev_node;
} Node;

int n, num;
char buf[10], intype;
Node *cursor;
Node *head, *tail;

void insert(Node**, char);
void deletion(Node**);
void backspace(Node**);
void go_left(Node**, int);
void go_right(Node**, int);
void go_home(Node**);
void go_end(Node**);
void show();

void show()
{
	if(head == NULL){
		printf("\n");
		return;
	}
	Node *now = head->next;
	while(now != head)
	{
		printf("%c ", now->ch);
		now = now->next;
	}
	printf("\n");
}

void insert(Node** cursor,char a){
    Node *cur = *cursor;
    Node *new = (Node*)malloc(sizeof(Node));
    new->character = a;
    Node *back = cur->next;
    back->prev = new;
    new->next = back;
    cur->next = new;
    new->prev = cur;
    if(cur == tail){
        tail = new;
    }
    

}

void deletion(Node** cursor){
    if(*cursor==tail){
        return;
    }
    else{
        Node * back = (*cursor)->next;
        back->next->prev = *cursor;
        (*cursor)->next = back->next;
        free(back);
        back = NULL;
    }
}

void backspace(Node **cursor){
    Node *cur = *cursor;
    if(*cursor!=head){
        Node *pre = (*cursor)->prev;
        Node *back = (*cursor)->next;
        pre->next = back;
        back->prev = pre;
        (*cursor) = pre;
        free(cur);
        cur = NULL;
    }
    else{
        return;
    }
    
}

void go_left(Node ** cursor,int a){
    while(a){
        a--;
        (*cursor) = (*cursor)->prev;
    }
}

void go_right(Node ** cursor,int a){
    while(a){
        a--;
        (*cursor) = (*cursor)->next;
    }
}

void go_home(Node **cursor){
    *cursor = head;
}

void go_end(Node **cursor){
    *cursor = tail;
}

int main()
{
	scanf("%d",&n);
	head = (Node*)malloc(sizeof(Node));
	head->next = head->prev = head;
	cursor = tail = head;
	while(n--)
	{
        
		scanf("%s",buf);
		if(!strcmp(buf,"insert"))
		{
			getchar();
			scanf("%c",&intype);
			insert(&cursor, intype); 
		}
		else if(!strcmp(buf,"deletion"))
		{
			deletion(&cursor); 
		}
		else if(!strcmp(buf,"backspace"))
		{
			backspace(&cursor); 
		}
		else if(!strcmp(buf,"go_left"))
		{
            scanf("%d", &num);
			go_left(&cursor, num); 
		}
        else if(!strcmp(buf,"go_right"))
		{
            scanf("%d", &num);
			go_right(&cursor, num); 
		}
        else if(!strcmp(buf,"go_home"))
		{
			go_home(&cursor); 
		}
        else if(!strcmp(buf,"go_end"))
		{
			go_end(&cursor); 
		}
		else if(!strcmp(buf,"show"))
		{
			show();
		}
	}
	return 0;
}