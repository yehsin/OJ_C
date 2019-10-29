#include<stdlib.h>
#include<stdio.h>

typedef struct Node{
    int val;
    struct Node *left,*right;
}Node;


int find_position(int a,int *b,int equal){
    for(int i=0;i<=equal;i++){
        if(a==b[i]){
            return i;
            break;
        }
    }
}

Node *build_tree(int *in,int *post,int end){
    int equal=end;
    Node *root = (Node*)malloc(sizeof(Node));
    root->left=NULL;
    root->right=NULL;
    root->val=post[end];
    end--;
    while(end>=0){
        Node *cur=root; //偵測是否NULL
        Node *pre=cur;
        int pos=find_position(post[end],in,equal);
        while(cur){
            if(pos<find_position(cur->val,in,equal)){
                pre=cur;
                cur=cur->left;    
            }
            else{
                pre=cur; 
                cur=cur->right;
            }
        }
        if(pos<find_position(pre->val,in,equal)){
            cur=(Node*)malloc(sizeof(Node));
            //pre->left = cur;
            cur->val=post[end];
            cur->left = NULL;
            cur->right = NULL;
            pre->left = cur;
            
        }
        else{
            cur=(Node*)malloc(sizeof(Node));
            pre->right = cur;
            cur->val=post[end];
            cur->left = NULL;
            cur->right = NULL;
        }
        end--;  
    }
    return root;
}

void preorder(Node* q){
    if(q){
        printf("%d ",q->val);
        preorder(q->left);
        preorder(q->right);   
    }
}

void free_tree(Node *w){
    if(w){
        free_tree(w->left);
        free_tree(w->right);
        free(w);
        w=NULL;
    }
}

int main(){
    int equal;
    int ID=0;
    while(scanf("%d",&equal)!=EOF){
        ID++;
        int inorder[equal];
        int postorder[equal];
        for(int i=0;i<equal;i++){
            scanf("%d",&inorder[i]);
        }
        for(int i=0;i<equal;i++){
            scanf("%d",&postorder[i]);
        }
        Node *Root;
        Root=build_tree(inorder,postorder,equal-1);
        printf("testcase%d: ",ID);
        preorder(Root);
        free_tree(Root);
        printf("\n");
    }
    
    return 0;
}