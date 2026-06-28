/*
 * Copyright 2026 Molino Rosario Walter
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * --- IMPORTANT NOTICE ---
 * THIS SOFTWARE IS PROVIDED SOLELY FOR EDUCATIONAL AND ACADEMIC PURPOSES.
 * IT IS NOT INTENDED AND MUST NOT BE USED IN PRODUCTION ENVIRONMENTS.
 */



#include <stdio.h>
#include <stdint.h>
#include "wdictionary.h"
#include "hash_fnv1a_64.h"
#include <string.h>
#include <stdlib.h>




/*
    Create node with key and value string.
    This function is colled by insert_value function
*/
Node * _create_node_string(const char * key, const char * value){

    Node * mystruct = (Node *) malloc(sizeof(Node));
    
    mystruct->key = (char *) malloc(strlen(key)+1);
    strcpy(mystruct->key,key);
    mystruct->type = TEXT;
    mystruct->value.text = (char *) malloc(strlen(value)+1);
    strcpy(mystruct->value.text,value);

    mystruct->next = NULL;

    return mystruct;



}

/*
    Create node with key and value Dict.
    This function is colled by insert_value function
*/
Node * _create_node_dict(const char * key, Dict * value){

    Node * mystruct = (Node *) malloc(sizeof(Node));
    mystruct->type = DICTIONARY;
    mystruct->key = (char *) malloc(strlen(key)+1);
    strcpy(mystruct->key,key);
    
    mystruct->value.dict = value;

    mystruct->next = NULL;

    return mystruct;



}

/*
    insert node with value String into dictionary and check collision.
    If exists collision for a specific slot, append in the list the node created
    If exists already a key then update the value
*/
void _insert_string(Dict * dict,const char * key, const char * value){
    int capacity = dict->capacity;
    Node * next_node = NULL;

    uint64_t myhash2=  hashing_fnv1a(key,capacity);
    
    //new slot without collision
    if (dict->slots[myhash2] == NULL)
        dict->slots[myhash2]=_create_node_string(key,value);
    else{
        //append node in slot with collisition
        
        //get first slot
        next_node = dict->slots[myhash2];

        //search the last element in the list
        while(1){
            if(strcmp(next_node->key,key)==0){

                if(next_node->type==TEXT)
                    free(next_node->value.text);
                if(next_node->type==DICTIONARY)
                    free(next_node->value.dict);
                
                next_node->value.text = (char *) malloc(strlen(value)+1);
                strcpy(next_node->value.text ,value); 
                next_node->type = TEXT;
                return;
            }
            if(next_node->next==NULL){
                next_node->next=_create_node_string(key,value);
                return;
            }
            next_node = next_node->next;
        }

        
            
    }

}


/*
    insert node with value Dictionary into dictionary and check collision.
    If exists collision for a specific slot, append in the list the node created
*/
void _insert_dict(Dict * dict,const char * key, Dict * value){
    int capacity = dict->capacity;
    Node * next_node = NULL;

    uint64_t myhash2=  hashing_fnv1a(key,capacity);
    
    //new slot without collision
    if (dict->slots[myhash2] == NULL)
        dict->slots[myhash2]=_create_node_dict(key,value);
    else{
        //append node in slot with collisition
        
        //get first slot
        next_node = dict->slots[myhash2];

        //search the last element in the list
        while(1){
            if(strcmp(next_node->key,key)==0){
                if(next_node->type==TEXT)
                    free(next_node->value.text);
                if(next_node->type==DICTIONARY)
                    free(next_node->value.dict);
                next_node->value.dict = value;
                next_node->type = DICTIONARY;
                return;
            }
            if(next_node->next==NULL){
                next_node->next=_create_node_dict(key,value);
                return;
            }
            next_node = next_node->next;
        }
        
        
            
    }

}


/*
    return the value for a specific key.
    Remember that in dict[key] could be a list value with the same hash (collition)
    so to extract the correct value, the function find the slot with the same key
*/
void * get_value(Dict * dict,const char * key){
    int capacity = dict->capacity;
    uint64_t myhash2=  hashing_fnv1a(key,capacity);

    Node * slot = dict->slots[myhash2];

    /*
        find the slot with the same key;
        if the key is different check in the next slot
    */
    while(slot != NULL){
        if(strcmp(key,slot->key)==0){
            if (slot->type==TEXT)
                return slot->value.text;
            else
                return slot->value.dict;
        }
        slot=slot->next;

    }
    printf("key doesn't exists \n");
    return NULL;
    
}


/*
    Create dictionary for specific capacity
*/
Dict * create_dictionary(int capacity){
    Dict * dict = (Dict *) malloc(sizeof(Dict));
    dict->capacity = capacity;

    dict->slots = (Node **) malloc(capacity * sizeof(Node *));

    for(int i =0; i<capacity; i++)
        dict->slots[i]=NULL;

    return dict;

}


void free_dict(Dict * dict);

void free_node(Node * node){
    if(node->next!=NULL)
        free_node(node->next);
    if(node->type==TEXT)
        free(node->value.text);
    else
        free_dict(node->value.dict);
    free(node->key);
    free(node);

}

void free_dict(Dict * dict){
    printf("hello");
    int capacity=dict->capacity;
    printf("%i",capacity);
    for(int i=0;i<capacity;i++){
        printf("ciao %i",i);
        if (dict->slots[i]!=NULL){
            free_node(dict->slots[i]);
            
        }
    }
    free(dict->slots);
    free(dict);
    
}

