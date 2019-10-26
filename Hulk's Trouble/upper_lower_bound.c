#include<stdio.h>
#include<stdlib.h>

int upper_bound(long long *,int,long long);
int lowwer_bound(long long *,int ,long long);
//void quicksort(long long *,int ,int );
long long query(long long *,long long ,int );
int cmp(const void *_a,const void *_b){
    long long *a = (long long *) _a;
    long long *b = (long long *) _b;
    return *a>*b ? 1:-1;
}

/*void quicksort(long long *arr,int l,int r){
    int pivot=arr[l];
    int left=l;
    int right=r;
    if(l<r){
        do{
            do{
                left++;
            }while(arr[l]<pivot);
            do{
                right--;
            }while(arr[r]>pivot); 
            if(left<right) swap(arr[l],arr[r]);
        }while(left<right);
        swap(arr[l],arr[right]);
        qsort(arr,l,right);
        qsort(arr,left,r);
    }
    
}*/

long long query(long long *arr, long long number, int end){
    int upper,lowwer;
    upper = upper_bound(arr, end,number);
    lowwer = lowwer_bound(arr , end,number);
    return upper-lowwer;
}

int upper_bound(long long *arr,int end,long long tar){
    int l = 0;
    int r=end;
    
    while(l<r){
        int mid=(l+r)/2;
        if(arr[mid]>tar) r=mid;
        else l=mid+1;
    }
    return r;
}

int lowwer_bound(long long *arr,int end,long long tar){
    int l=0;
    int r=end;
    
    while(l<r){
        int mid=(l+r)/2;
        if(arr[mid]>=tar) r=mid;
        else l=mid+1;
    }
    
    return r;
}





int main(){
    int equal;
    int lines;
    scanf("%d",&equal);
    long long arr[equal];
    for(int i=0;i<equal;i++){
        scanf("%lld",&arr[i]);
    }
    qsort(arr,equal,sizeof(arr[0]),cmp);
    
    scanf("%d",&lines);
    while(lines){
        int number;
        long long ans;
        scanf("%d",&number);
        ans=query(arr,number,equal);
        printf("%lld\n",ans);
        lines--;
    }
}