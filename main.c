#include "wdictionary.h"
#include "hash_fnv1a_64.h"
#include <stdio.h>

int main(){
    const char *c = "ciaoreredef";
    int CAPACITY = 10;
    uint64_t myhash=  hashing_fnv1a(c,CAPACITY);
    printf("%llu\n", (unsigned long long)myhash);
    printf("\n");
    
    
    const char * key = "prova";
    const char * value = "ciao mamma";
    
    Dict * mydict = create_dictionary(CAPACITY);
    Dict * mydict2 = create_dictionary(CAPACITY);
    insert(mydict2,"hi2","Babies");

    insert(mydict,key,value);
    insert(mydict,"hi",10);
    insert(mydict,"re","Baby1");
    insert(mydict,"ree","Baby3");
    insert(mydict,"ree","Baby13");
    insert(mydict,"tte",mydict2);
    insert(mydict,"tee","Baby5");
    
    int * myint = (int *)get_value(mydict,"hi");
    printf("hello int %i",*myint);

    Dict * val = (Dict *)get_value(mydict,"tte");
    char * val1_2 = (char *)get_value(val,"hi2");
    printf("hello %s\n",val1_2);

    

    char * val2 = (char * ) get_value(mydict,key);
    printf("hello2 %s\n",val2);
    ListKeys * mylist = get_keys(mydict);
    while(mylist!=NULL){
        printf("ecco key %s\n",mylist->key);
        mylist=mylist->next;
    }
    printf("FINE \n");
    free_dict(mydict);
    return 0;
}