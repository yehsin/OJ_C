#include<stdio.h>
#include"12388.h"
#include<stdlib.h>

Node *creatRoot(Node *b,int a){
    b->level=a;
    b->left_child=NULL;
    b->right_child=NULL;
    return b;
    
}

void insert(Node**now,int x){
    Node *parent=NULL;
    Node *current=*now;
    while(current!=NULL){
        if(x<current->level){
            parent=current;
            current=current->left_child;
        }
        else{
            parent=current;
            current=current->right_child;
        }
    }
    if(x<=parent->level){
        Node *new = (Node*) malloc(sizeof(Node));
        parent->left_child = new;
        new=creatRoot(new,x);
    }
    else{
        Node *new = (Node*) malloc(sizeof(Node));
        parent->right_child = new;
        new=creatRoot(new,x);
    }
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


void inorder(Node *A){
    if (A != NULL) {
        inorder(A->left_child);
        printf("3%d ", A->level);
        inorder(A->right_child);

    }
}

int query_heatstroke(Node *now, int x){
    if(x>now->level){
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

/*void replace_r(Node *Root,Node *pre,Node **root){ 
    Node * prev=Root;
    if((Root->left_child)->right_child==NULL){
        if(pre->right_child==Root){
            pre->right_child=Root->left_child;
        }
        else{
            pre->left_child=Root->left_child;
        }
        
        (Root->left_child)->right_child=prev->right_child;
        free(prev);
    }
    else{
        Node*tmp=Root->left_child;
        Node *past;
        while(tmp->right_child!=NULL){
            past=tmp;
            tmp=tmp->right_child;
        }
        prev->level=Root->level;
        past->right_child=Root->left_child;
        free(Root);

    }
}*/

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
        int val;
        while(small->right_child){
            small=small->right_child;
            val=small->level;
        }
        eat_rat(&(Root->left_child),val);
        Root->level=val;
    }
    else if(Root->left_child==NULL && Root->right_child!=NULL){
        if(x!=(*root)->level){ //Node deleted is root Node.
            Node* k = Root->right_child;
            pre->right_child=k;
            free(Root);
        }
        else{
            Node *y = *root;
            Root=Root->right_child;
            if(Root->left_child==NULL){  //When there are no left tree, which means this node is smallest Node.
                *root=Root;
                free(y);
            }
            else{ /*replacing deleted Node from this node and free this Node.*/
                while(Root->left_child){
                    pre=Root;
                    Root=Root->left_child;
                }
                (*root)->level=Root->level; //whose left tree connect to parent.
                pre->left_child=Root->right_child;
                free(Root);
            }
            
        }

    }
    else if(Root->right_child==NULL && Root->left_child!=NULL){
        if(x!=(*root)->level){
            Node* k = Root->left_child;
            pre->left_child=k;
            free(Root);
        }
        else{
            Node *y = Root;
            Root=Root->left_child;
            if(Root->right_child==NULL){
                *root=Root;
                free(y);
            }
            else{
                while(Root->right_child){
                    pre=Root;
                    Root=Root->right_child;
                }
                (*root)->level=Root->level;
                pre->right_child=Root->left_child;
                free(Root);
            }
            
        }
        
    }
    else if(Root->right_child==NULL && Root->left_child==NULL){ //leaf Node
        if(Root==*root){
            (*root)=NULL;
            free(Root);
        }
        else if(pre->left_child==Root){
            free(pre->left_child);
            pre->left_child=NULL;
            Root=NULL;
        }
        else if(pre->right_child==Root){
            //free(Root);
            free(pre->right_child);
            pre->right_child=NULL;
            Root=NULL;
        }
    }
}