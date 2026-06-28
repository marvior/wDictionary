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

#ifndef WDICTIONARY_H
#define WDICTIONARY_H

#include <stdint.h>

typedef struct Dict Dict;

typedef enum {
    TEXT,
    DICTIONARY
}typeObject;


typedef struct Node{
    char * key;
    typeObject type;
    union {
        char * text;
        Dict * dict;
    } value;

    struct Node * next;
} Node;


struct Dict{
    Node ** slots;
    int capacity;

};





void free_dict(Dict * dict);
Dict * create_dictionary(int capacity);
void * get_value(Dict * dict,const char * key);
void _insert_string(Dict * dict,const char * key, const char * value);
void _insert_dict(Dict * dict,const char * key, Dict * value);

#define insert(dict, key, value) _Generic((value), \
    char*:        _insert_string,                  \
    const char*:  _insert_string,                  \
    Dict*:        _insert_dict                     \
)(dict, key, value)

#endif