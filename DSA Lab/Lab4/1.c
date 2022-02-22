#include <stdio.h>
int bits;
void p(int n);
void g();
void h();
void d();
void p(int n){
    // if (n==0){
    //     return;
    // }
    // printf("Pilani:\t\t%p\n", &pilani);
    printf("%p\n",&n);
    p(n-1);
}
void g(){
    int goa;
    printf("Goa:\t\t%p\n", &goa);
    h();
    d();
}
void h(){
    int hyderabad;
    printf("Hyderabad:\t%p\n", &hyderabad);
    
}
void d(){
    int dubai;
    printf("Dubai:\t\t%p\n", &dubai);
}


int main(){
    // p();
    // g();
    // h();
    // d();
    p(5);
}