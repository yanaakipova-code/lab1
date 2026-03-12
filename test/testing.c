#include "maintest.h"

static _test* head = NULL;
static _test* tail = NULL;

void register_test(const char* name, test_func test) {
    _test* tmp = malloc(sizeof(_test));
    tmp->name = name;
    tmp->test = test;
    tmp->next = NULL;
    
    if (head == NULL && tail == NULL) {
        head = tmp;
        tail = tmp;
        return;
    }
    tail->next = tmp;
    tail = tmp;
}

void run_test() {
    for (_test* t = head; t != NULL; t = t->next) {
        fprintf(stderr, "\n========= ТЕСТ: %s =========\n\n", t->name);
        t->test();
        
        int succs = pop_success();
        int all = pop_fail() + succs;
        float percent = (all > 0) ? (float)succs / (float)all * 100 : 0;
        
        fprintf(stderr, "\n=== %d из %d тестов пройдено (%.2f%%) ===\n\n", 
                succs, all, percent);
    }
}