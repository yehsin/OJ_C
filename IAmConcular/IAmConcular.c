#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define MAX_LENGTH 1000

// Token / AST kinds
enum {
    // Non-operators
    Value,
    // Operators
    /// Precedence 1
    Mul, Div, Rem,
    /// Precedence 2
    Add, Sub,
};
typedef struct _TOKEN {
    int kind;
    int param; // Value
    struct _TOKEN *prev, *next;
} Token;
typedef struct _AST {
    int type;
    int val; // Value
    struct _AST *lhs, *rhs;
} AST;

// Utility Interface

// Used to create a new Token.
Token *new_token(int kind, int param);
// Used to create a new AST node.
AST *new_AST(Token *mid);
// Convert Token linked list into array form.
int list_to_arr(Token **head);
// Use to check if the kind can be determined as a value section.
int isValueSection(int kind);
// Function called when an unexpected expression occurs.
void err();

// Used to find a appropriate operator that split the expression half.
int find_Tmid(Token *arr, int l, int r);
//get the Precedence of operator or value
int getOpLevel(int kind);
// calculate the answer 
int getanswer(AST *ast);

// Main Function

char input[MAX_LENGTH];
int regis[1000], now_reg = -1;

// Convert the inputted string into multiple tokens.
Token *lexer(char *in);
// Use tokens to build the binary expression tree.
AST *parser(Token *arr, int l, int r);
// calculate the answer
void calculate(AST **ast);

void preorder(AST *a){
    if(a){
        preorder(a->lhs);
        preorder(a->rhs);
        printf("%d",a->type);
    }
}

int main() {
    //printf("%d",Add);
    while(fgets(input, MAX_LENGTH, stdin) != NULL) {
        // build token list by lexer
        Token *content = lexer(input);
        // convert token list into array
        int length = list_to_arr(&content);

        // build abstract syntax tree by parser
        AST *ast_root = parser(content, 0, length-1);
        //AST *tmp = ast_root;
        //preorder(ast_root);


        // calculate the answer
        calculate(&ast_root);
        getanswer(ast_root);
        /*Todo*/
        // print the answer here.

        /*Todo*/
        // do some reset??
    }
    return 0;
}
AST *parser(Token *arr, int l, int r) {
    if(l > r) return NULL;
    // covered in parentheses
    int mid = find_Tmid(arr, l, r);
    //printf("%d",mid);
    AST *newN = new_AST(arr + mid);
    
    if(l == r || newN->type == Value){
        return newN;
    }   
    if(getOpLevel(arr[mid].kind) == 1){
        //puts("2");
        newN->lhs = parser(arr,l,mid-1);
        newN->rhs = parser(arr,mid+1,r);
    }
    if(getOpLevel(arr[mid].kind) == 2){
        //puts("1");
        newN->lhs = parser(arr,l,mid-1);
        newN->rhs = parser(arr,mid+1,r);
    }
    /*Todo*/
    //finish the parser
    return newN;
}
AST* new_AST(Token *mid) {
    AST *newN = (AST*)malloc(sizeof(AST));
    newN->lhs = newN->rhs = NULL;
    newN->type = mid->kind;
    newN->val = mid->param;
    return newN;
}
int find_Tmid(Token *arr, int l, int r) {
    int left = l;
    int right = r;
    while(r>l){
       // printf("%d%d\n",arr[r].kind,getOpLevel(arr[r].kind));
        if(getOpLevel(arr[r].kind) == 2){
            return r;
        }
        r--;
    }
   // puts("F");
    r = right;
    while(l<r){
        if(getOpLevel(arr[r].kind) == 1){
            return r;
        }
        r--;
    }
    return r;
    /*Todo*/
    //find the node to be contructed
}
int getOpLevel(int kind) {
    if(kind ==0){
        return 0; //value
    }
    else if(kind>=1 && kind<4) return 1; // */
    else if(kind >= 4) return 2;  // +-
    /*Todo*/
    // you may use this finction in find_Tmid
}
void calculate(AST **ast) {

    if((*ast)->type == 1){
        calculate(&(*ast)->lhs);
        calculate(&(*ast)->rhs);
        (*ast)->val = (*ast)->lhs->val * (*ast)->rhs->val;
        (*ast)->type = Value;
    }
    else if((*ast)->type == 2){
        calculate(&(*ast)->lhs);
        calculate(&(*ast)->rhs);
        (*ast)->val = (*ast)->lhs->val / (*ast)->rhs->val;
        (*ast)->type = Value;
    }
    else if((*ast)->type == 3){
        calculate(&(*ast)->lhs);
        calculate(&(*ast)->rhs);
        (*ast)->val = (*ast)->lhs->val % (*ast)->rhs->val;
        (*ast)->type = Value;
    }
    else if((*ast)->type == 4){
        calculate(&(*ast)->lhs);
        calculate(&(*ast)->rhs);
        (*ast)->val = (*ast)->lhs->val + (*ast)->rhs->val;
        (*ast)->type = Value;
    }
    else if((*ast)->type == 5){
        calculate(&(*ast)->lhs);
        calculate(&(*ast)->rhs);
        (*ast)->val = (*ast)->lhs->val - (*ast)->rhs->val;
        (*ast)->type = Value;
    }
    
    if((*ast)->type == 0){
        return;
    }
    //getanswer(ast);
    /*Todo*/
    // traverse the tree by postorder
}

int getanswer(AST *ast){
    printf("%d\n",ast->val);
    /*Todo*/
    // calculate the answer here.
    // you can calculate the answer by simulating the registers
}

Token *lexer(char *in) {
    Token *head = NULL;
    Token **now = &head, *prev = NULL;
    for(int i = 0; in[i]; i++) {
        if(in[i] == ' ' || in[i] == '\n')
            continue;

        else if(isdigit(in[i])) {
            int val = 0, oi = i;
            for(; isdigit(in[i]); i++)
                val = val * 10 + (in[i] - '0');
            i--;
            // Detect illegal number inputs such as "01"
            if(oi != i && in[oi] == '0')
                err();
            (*now) = new_token(Value, val);
        }

        else {
            switch(in[i]) {
                case '+': // '+'
                    (*now) = new_token(Add, 0);
                    break;
                case '-':
                    (*now) = new_token(Sub, 0);
                    break;
                case '*':
                    (*now) = new_token(Mul, 0);
                    break;
                case '/':
                    (*now) = new_token(Div, 0);
                    break;
                case '%':
                    (*now) = new_token(Rem, 0);
                    break;
                default:
                    err();
            }
        }
        (*now)->prev = prev;
        if(prev != NULL) prev->next = (*now);
        prev = (*now);
        now = &((*now)->next);
    }
    return head;
}
Token *new_token(int kind, int param) {
    Token *res = (Token*)malloc(sizeof(Token));
    res->kind = kind;
    res->param = param;
    res->prev = res->next = NULL;
    return res;
}
int list_to_arr(Token **head) {
    int res = 0;
    Token *now = (*head), *t_head = NULL, *del;
    while(now!=NULL) {
        res++;
        now = now->next;
    }
    now = (*head);
    t_head = (Token*)malloc(sizeof(Token)*res);
    for(int i = 0; i < res; i++) {
        t_head[i] = (*now);
        del = now;
        now = now->next;
        free(del);
    }
    (*head) = t_head;
    return res;
}
int isValueSection(int kind) {
    if(kind == Value) return 1;
    return 0;
}
void err(){
    exit(0);
}