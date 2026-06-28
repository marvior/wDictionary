#include "wdictionary.h"
#include "hash_fnv1a_64.h"
#include <stdio.h>

int main(){
    const char *c = "ciaoreredef";
    int CAPACITY = 3;
    uint64_t myhash=  hashing_fnv1a(c,CAPACITY);
    printf("%llu\n", (unsigned long long)myhash);
    printf("\n");
    
    
    const char * key = "prova";
    const char * value = "ciao mamma";
    
    Dict * mydict = create_dictionary(CAPACITY);
    Dict * mydict2 = create_dictionary(CAPACITY);
    insert(mydict2,"hi2","Babies");

    insert(mydict,key,value);
    insert(mydict,"hi","Baby");
    insert(mydict,"re","Baby1");
    insert(mydict,"ree","Baby3");
    insert(mydict,"ree","Baby13");
    //insert(mydict,"tte","Baby4");
    insert(mydict,"tte",mydict2);
    insert(mydict,"tee","Baby5");
    
    Dict * val = (Dict *)get_value(mydict,"tte");
    char * val1_2 = (char *)get_value(val,"hi2");
    printf("hello %s\n",val1_2);

    

    char * val2 = (char * ) get_value(mydict,key);
    printf("hello2 %s\n",val2);
    free_dict(mydict);
    return 0;
}