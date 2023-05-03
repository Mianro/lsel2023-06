#include "unity.h"

#include "fsm.h"
#include "mock_test_fsm.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_fsm_new_nullWhenNullTransition(void)
{
    fsm_t *f = (fsm_t*)1;

    f = fsm_new(NULL,0,-1);

    TEST_ASSERT_EQUAL (NULL, f);
}

void test_fsm_nullWhenEmptyTransition(void)
{
    fsm_trans_t tt[] = {{-1, NULL, -1, NULL}};

    fsm_t *f = (fsm_t*)1;

    int size = sizeof(tt)/sizeof(tt[0]);

    f = fsm_new(tt, size, -1);

    TEST_ASSERT_EQUAL (NULL, f);
    //TEST_FAIL_MESSAGE("Implement the test");
}

void test_fsm_validTransitionNoOutput(void)
{
    fsm_trans_t tt[] = {
        {0, is_true, 1, NULL},
        {-1, NULL, -1, NULL}
    };

    is_true_ExpectAnyArgsAndReturn(1);

    fsm_t *f = (fsm_t*)1;

    int size = sizeof(tt)/sizeof(tt[0]);

    f = fsm_new(tt, size, 1);

    fsm_fire(f);

    TEST_ASSERT_NOT_NULL (f);
    TEST_ASSERT_EQUAL (1, f->current_state);

    fsm_destroy(f);
}

void test_fsm_validTransitionWithOutput(void)
{
    fsm_trans_t tt[] = {
        {0, is_true, 1, do_nothing},
        {-1, NULL, -1, NULL}
    };

    is_true_ExpectAnyArgsAndReturn(1);
    do_nothing_ExpectAnyArgs();

    fsm_t *f = (fsm_t*)1;

    int size = sizeof(tt)/sizeof(tt[0]);

    f = fsm_new(tt, size, 1);
    
    fsm_fire(f);

    TEST_ASSERT_NOT_NULL (f);
    TEST_ASSERT_EQUAL (1, f->current_state);

    fsm_destroy(f);
}




void test_fsm_validTransitionTable(void)
{
    fsm_trans_t tt[] = {
        {0, is_true, 1, do_nothing},
        {-1, NULL, -1, NULL},
        {-1, NULL, -1, NULL},
    };

    fsm_t *f = (fsm_t*)1;

    int size = sizeof(tt)/sizeof(tt[0]);

    f = fsm_new(tt, size, -1);

    TEST_ASSERT_EQUAL (NULL, f);

    fsm_destroy(f);
}

void test_fsm_validLastTransition(void)
{
    fsm_trans_t tt[] = {
        {0, is_true, 1, do_nothing},
        {0, is_true, 2, do_nothing},
        {-1, NULL, -1, do_nothing},
    };

    fsm_t *f = (fsm_t*)1;

    int size = sizeof(tt)/sizeof(tt[0]);

    f = fsm_new(tt, size, 2);

    TEST_ASSERT_EQUAL (NULL, f);

    fsm_destroy(f);
}
