#include<stdlib.h>
#include<stdio.h>

typedef struct Node{
    struct Node *left;
    struct Node *right;
    int variable;
    int operator;
    char ope;
}Node;

int str2int(char ch){
    int temp=0;
    temp=temp+(ch-'0');
    return temp;
}

char str[100];

Node* initially(Node* e,char d){
    e->operator=0;
    e->variable=0;
    e->ope=d;
    e->right=e->left=NULL;
}
void build_tree(Node **root,char *s,int a1,int a2,int a3){
    static int index;
    *root=(Node*) malloc(sizeof(Node));
    if(s[index]=='x' || s[index]=='y' || s[index]=='z'){
        *root=initially(*root,s[index]);
        (*root)->operator=1;
        if(s[index]=='x'){
            (*root)->variable=a1;
        }
        else if(s[index]=='y'){
            (*root)->variable=a2;
        }
        else{
            (*root)->variable=a3;
        }
        index++;
    }
    else if(s[index] == '+' || s[index]== '-' || s[index]=='*' || s[index] == '/'){
        *root=initially(*root,s[index]);
        index++;
        (*root)->operator=0;
        build_tree(&(*root)->left,s,a1,a2,a3);
        build_tree(&(*root)->right,s,a1,a2,a3);
    }
    else if (s[index]=='\0'){
        return;
    }
    else{
        *root = initially(*root,s[index]);
        (*root)->operator=2;
        (*root)->variable=str2int(s[index]);
        index++;
    }

}

int evaluate(Node **root){
    if((*root)->operator==0){
        int value1,value2,ans;
        value1=evaluate(&(*root)->left);
        value2=evaluate(&(*root)->right);
        if((*root)->ope == '+')
            ans=value1+value2;
        else if((*root)->ope == '-')
            ans=value1-value2;
        else if((*root)->ope == '*')
            ans=value1*value2;
        else
            ans=value1/value2;
        return ans;
        
    }
    else{
        return (*root)->variable;
    }
}

void inorder(Node *a)
{
    if(a!=NULL){
        inorder(a->left);
        printf("%c",a->ope);
        inorder(a->right);
    }
}
int main(){
    int x,y,z;
    scanf("%s",&str);
    scanf("%d%d%d",&x,&y,&z);
    Node *root;
    printf("r\n");
    build_tree(&root,str,x,y,z);
    inorder(root);
    printf("%d\n",evaluate(&root));
    return 0;
}