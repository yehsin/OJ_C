#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include"12392.h"
#define MAX_N 10004

int n, q;
int a[MAX_N];

typedef struct _NODE {
	int level;
	struct _NODE *left_child, *right_child;
} Node;

void build_tree(Node **now, int *arr, int l, int r);
int query_heatstroke(Node *now, int x);
void eat_rat(Node **root, int x);
void buy_rat(Node **root,int x);

void buy_rat(Node **Root,int new){
    Node **cur = Root;
    while(*cur){
        if(new>(*cur)->level){
            cur = &((*cur)->right_child);
        }
        else {
            cur = &((*cur)->left_child);
        }
    }
    *cur = (Node*)malloc(sizeof(Node));
    (*cur)->level = new;
    (*cur)->left_child = (*cur)->right_child = NULL;
    
}

void build_tree(Node **now, int *arr, int l, int r){
    if(l>r) {
        return;
    }
    (*now)=(Node*)malloc(sizeof(Node));
    if(l==r){
        (*now)->level=arr[l];
        (*now)->left_child=(*now)->right_child=NULL;
    }
    else{
        int mid=(l+r)/2;
        (*now)->level=arr[mid];
        (*now)->left_child=(*now)->right_child=NULL;
        build_tree(&((*now)->left_child),arr,l,mid-1);
        build_tree(&((*now)->right_child),arr,mid+1,r);
    }
}


/*void inorder(Node *A){
    if (A != NULL) {
        inorder(A->left_child);
        printf("%d ", A->level);
        inorder(A->right_child);

    }
}*/

int query_heatstroke(Node *now, int x){
    if(now==NULL){
        return 0;
    }
    else if(x>now->level){
        if(now->right_child){
            query_heatstroke(now->right_child,x);
        }
        else{
            return 0;
        }
    }
    else if(x<now->level){
        if(now->left_child){
            query_heatstroke(now->left_child,x);
        }
        else{
            return 0;
        }
        
    }
    else if(x==now->level){
        return 1;
    }
}

void eat_rat(Node **root, int x){
    Node *Root=*root; //explore next node
    Node *pre=Root;
    
    while(x!=Root->level && Root!=NULL){
        if(x<Root->level){
            pre=Root;
            Root=Root->left_child;
        }
        else if(x>Root->level){
            pre=Root;
            Root=Root->right_child;
        }
    }
    //找到x了
    
    if(Root->left_child!=NULL && Root->right_child!=NULL){ //we choose to take biggest from left tree.
        Node *small=Root->left_child;
        int val=small->level;
        while(small->right_child!=NULL){
            small=small->right_child;
            val=small->level;
        }
        eat_rat(&(Root->left_child),val);
        Root->level=val;
    }
    else if(Root->left_child==NULL && Root->right_child!=NULL){
        if(Root!=(*root)){ //Node deleted is root Node.
            Node* k = Root->right_child;
            if(pre->right_child==Root){
                pre->right_child=k;
                free(Root);
                Root=NULL;
            }
            else{
                pre->left_child=k;
                free(Root);
                Root=NULL;
            }
            
        }
        else{
            Node *y = *root;
            Root=Root->right_child;
            *root=Root;
            free(y);
            y=NULL;
        }

    }
    else if(Root->right_child==NULL && Root->left_child!=NULL){
        if(Root!=(*root)){
            Node* k = Root->left_child;
            if(pre->left_child==Root){
                pre->left_child=k;
                free(Root);
                Root=NULL;
            }
            else{
                pre->right_child=k;
                free(Root);
                Root=NULL;
            }
            
        }
        else{
            Node *y = Root;
            Root=Root->left_child;
            *root=Root;
            free(y);
            y=NULL;
            
        }
        
    }
    else if(Root->right_child==NULL && Root->left_child==NULL){ //leaf Node
        if(Root==*root){
            (*root)=NULL;
        }
        else if(pre->left_child==Root){
            pre->left_child=NULL;
        }
        else if(pre->right_child==Root){
            //free(Root);
            pre->right_child=NULL;
        }
        free(Root);
        Root=NULL;
    }
}

int main() {
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	Node *root = NULL;
	build_tree(&root,a,0,n-1);
	scanf("%d",&q);
	char op[20];
	while(q--) {
		int x;
		scanf("%s",op);
		scanf("%d",&x);
		if(strcmp(op,"heatstroke")==0) {
			if(query_heatstroke(root,x)!=0) {
				puts("We might as well eat it.");
				eat_rat(&root,x);
			}
			else puts("No dinner tonight.");
		}
		else if(strcmp(op,"buy")==0) {
			buy_rat(&root,x);
		}
	}
	return 0;
}
