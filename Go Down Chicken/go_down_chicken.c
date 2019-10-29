#include<stdio.h>
#include<stdlib.h>

typedef struct moz{
    long long int value;
    long long int position;
}moz;

long long int ways(long long int );
long long int find(moz *,long long int ,long long int );
long long lowwer_bound(moz *,long long int ,long long int );



int cmp(const void *_a,const void *_b){
    struct moz *a = (struct moz *) _a;
    struct moz *b = (struct moz *) _b;
    if(a->value == b->value){
        return a->position - b->position;  //avoid unstable sort
    }
    else
        return a->value - b->value;
    
}


long long int lowwer_bound(moz *ans,long long int end,long long int Ans){
    long long int l=0;
    long long int r=end;
    long long int mid;
    while(l<r){
        mid = (l+r)/2;
        if(ans[mid].value>=Ans) r=mid;
        else l=mid+1;
    }
    return r;
}

long long int ways(long long int a){
    if(a%2==0){
        long long int pow = a/2;
        long long int power = 2;
        long long int r=1;
        while(pow){
            
            int base = pow & 1;
            if(base){
                r = ((r%1000000007)*(power%1000000007))%1000000007;
                //printf("%lld ",r);
            }
            power = ((power%1000000007)*(power%1000000007))%1000000007;
            //printf("%lld\n",power);
            pow=pow>>1;
        }
        return r;
    }
    else{
        return 0;
    }
}

long long int find(moz *ans,long long int Ans,long long int n){
    long long int lower = lowwer_bound(ans,n,Ans);
    //printf("lower:%d \n",lower);
    if(lower == n){
        return -1;
    }
    else{
        if(Ans == ans[lower].value){
            return ans[lower].position;
        }
        else{
            return -1;
        }
        
    }
    
}


int main(){
    long long int lines;
    long long int games;
    while(scanf("%lld",&lines)!=EOF){
        scanf("%lld",&games);
        //long long int arra[lines];
        moz ans[lines];
        for(long long int i=0;i<lines;i++){
            scanf("%lld(/`A`)/ ~I__I", &ans[i].value);
            ans[i].value=ways(ans[i].value);
            ans[i].position = i+1;
            
        }
        qsort(ans,lines,sizeof(ans[0]),cmp);
        //for(int i=0;i<lines;i++) printf("%lld\n",ans[i].value);
        while(games){
            games--;
            long long int way;
            long long int Ans;
            scanf("%lld",&way);
            Ans = find(ans,way,lines);
            if(Ans<0){
                printf("Go Down Chicken 404\n");
            }
            else{
                printf("%lld\n",Ans);
            }
        }
    }
}