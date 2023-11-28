/***
* compile: g++ -std=c++17 -Wall -o test Dictionary.cpp DictionaryTest.cpp
***/
#include<iostream>
#include<string>
#include"Dictionary.h"

int main(){

    Dictionary blank;
    blank.setValue("b", 5);
    std::cout<< blank;
    blank.setValue("a", 6);
    blank.setValue("asher", 1);
    blank.setValue("ashe", 1);
    blank.setValue("c", 1);
    if(blank.contains("hell")){
        printf("\ncontains\n");
    }    
    std::cout<< blank;
    try
    {
        printf("\nvalue of hello: %d\n", blank.getValue("hello"));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    printf("printing the keys using a preorder traversal: \n");
    std::cout << blank.pre_string() << std::endl;

    Dictionary newdict;

    newdict.setValue("hello", 5);
    newdict.setValue("my name is asher", 1);
    if(blank==newdict){
        printf("\nthey are equal\n");
    }else{
        printf("\nthey are not equal\n");
    }
    std::cout<< blank;
    blank.begin();
    printf("\nfirst keys value = %d\n", blank.currentVal());
    blank.end();
    printf("\nlast keys value = %d\n", blank.currentVal());
    printf("number of pairs: %d\n", blank.size());

    printf("copy of dictionary: \n");
    Dictionary copy;
    copy=blank;
    std::cout<< copy;
    if(blank==copy){
        printf("\nthey are equal\n");
    }else{
        printf("\nthey are not equal\n");
    }

    //walk forwards
    copy.begin();
    printf("value of current=%d\n", copy.currentVal());
    copy.next();
    printf("value of current=%d\n", copy.currentVal());
    copy.next();
    printf("value of current=%d\n", copy.currentVal());
    copy.next();
    printf("value of current=%d\n", copy.currentVal());
    copy.next();
    printf("value of current=%d\n", copy.currentVal());

    //walk backwards
    copy.end();
    printf("\n\nvalue of current=%d\n", copy.currentVal());
    copy.prev();
    printf("value of current=%d\n", copy.currentVal());
    copy.prev();
    printf("value of current=%d\n", copy.currentVal());
    copy.prev();
    printf("value of current=%d\n", copy.currentVal());
    copy.prev();
    printf("value of current=%d\n", copy.currentVal());
    return 0;
}