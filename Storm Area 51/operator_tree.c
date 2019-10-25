#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
#include<string.h>

typedef struct Node{
    struct Node *left;
    struct Node *right;
    int variable;
    int operator;
    char ope[10];
}Node;

int str2int(char ch){
    int temp=0;
    temp=temp+(ch-'0');
    return temp;
}

char str[100];

Node* initially(Node* e,char *d){
    e->operator=0;
    e->variable=0;
    strcpy(e->ope,d);
    e->right=e->left=NULL;
    return e;
}
void build_tree(Node **root,char *s,int a1,int a2,int a3){
    static int index;
    *root=(Node*) malloc(sizeof(Node));
    if(isspace(s[index]) && s[index]!='\0'){
        index++;
    }
    if(s[index]=='x' || s[index]=='y' || s[index]=='z'){
        if(s[index]=='x'){
            char *tmp = "x";
            *root=initially(*root,tmp);
            (*root)->operator=1;
            (*root)->variable=a1;
        }
        else if(s[index]=='y'){
            char *tmp = "y";
            *root=initially(*root,tmp);
            (*root)->operator=1;
            (*root)->variable=a2;
        }
        else {
            char *tmp = "z";
            *root=initially(*root,tmp);
            (*root)->operator=1;
            (*root)->variable=a3;
        }
        index++;
    }
    else if(s[index] == '+' || s[index]== '-' || s[index]=='*' || s[index] == '/'){
        char tmp[2];
        ungetc(s[index],stdin);
        scanf("%s",tmp);
        *root=initially(*root,tmp);
        index++;
        (*root)->operator=0;
        build_tree(&(*root)->left,s,a1,a2,a3);
        build_tree(&(*root)->right,s,a1,a2,a3);
    }
    else if (s[index]=='\0'){
        return;
    }
    else if(isdigit(s[index])){
        char cont[10];
        int idx=0;
        int queue[4]={-1,-1,-1,-1};
        while(isdigit(s[index])){
            ungetc(s[index],stdin);
            queue[idx]=str2int(s[index]);
            idx++;
            index++;
        }
        scanf("%s",cont);
        if(queue[2]==-1 && queue[1]!=-1 ){
            queue[3]=queue[1]+queue[0]*10;
        }
        else if(queue[1]==-1 && queue[2]==-1 ){
            queue[3]=queue[0];
            
        }
        else{
            queue[3]=queue[2]+queue[1]*10+queue[0]*100;
        }
        
        *root = initially(*root,cont);
        (*root)->variable=queue[3];
        (*root)->operator=2;  
    }

}

int evaluate(Node **root){
    if((*root)->operator==0){
        int value1,value2,ans;
        value1=evaluate(&(*root)->left);
        value2=evaluate(&(*root)->right);
        if(!strcmp((*root)->ope,"+")){
            ans=value1+value2;   
        }
        else if(!strcmp((*root)->ope,"-")){
            ans=value1-value2;
        }
        else if(!strcmp((*root)->ope,"*")){
            ans=value1*value2;
        } 
        else{
            ans=value1/value2;
        }   
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
        if(isdigit(a->ope[0])){
            int idx=0;
            char tmp[10];
            char output[10];
            while(a->ope[idx]!='\0'){
                ungetc(a->ope[idx],stdin);
                idx++;
            }
            scanf("%s",output);
            printf("%s",output);
        }
        else{
            printf("%s",a->ope);
        }
        inorder(a->right);
    }
}
int main(){
    int x,y,z;
    fgets(str,sizeof(str),stdin);
    scanf("%d%d%d",&x,&y,&z);
    Node *root;
    build_tree(&root,str,x,y,z);
    inorder(root);
    printf("\n");
    printf("%d\n",evaluate(&root));
    return 0;
}