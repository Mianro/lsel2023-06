#include "build/test/mocks/mock_test_fsm.h"
#include "../common/include/fsm.h"
#include "/var/lib/gems/2.7.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"




void setUp(void)

{

}



void tearDown(void)

{

}



void test_fsm_new_nullWhenNullTransition(void)

{

    fsm_t *f = (fsm_t*)1;



    f = fsm_new(

               ((void *)0)

                   ,0,-1);



    UnityAssertEqualNumber((UNITY_INT)((

   ((void *)0)

   )), (UNITY_INT)((f)), (

   ((void *)0)

   ), (UNITY_UINT)(20), UNITY_DISPLAY_STYLE_INT);

}



void test_fsm_nullWhenEmptyTransition(void)

{

    fsm_trans_t tt[] = {{-1, 

                            ((void *)0)

                                , -1, 

                                      ((void *)0)

                                          }};



    fsm_t *f = (fsm_t*)1;



    int size = sizeof(tt)/sizeof(tt[0]);



    f = fsm_new(tt, size, -1);



    UnityAssertEqualNumber((UNITY_INT)((

   ((void *)0)

   )), (UNITY_INT)((f)), (

   ((void *)0)

   ), (UNITY_UINT)(33), UNITY_DISPLAY_STYLE_INT);



}



void test_fsm_validTransitionNoOutput(void)

{

    fsm_trans_t tt[] = {

        {0, is_true, 1, 

                       ((void *)0)

                           },

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          }

    };



    is_true_CMockExpectAnyArgsAndReturn(44, 1);



    fsm_t *f = (fsm_t*)1;



    int size = sizeof(tt)/sizeof(tt[0]);



    f = fsm_new(tt, size, 1);



    fsm_fire(f);



    do {if ((((f)) != 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(54))));}} while(0);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((f->current_state)), (

   ((void *)0)

   ), (UNITY_UINT)(55), UNITY_DISPLAY_STYLE_INT);



    fsm_destroy(f);

}



void test_fsm_validTransitionWithOutput(void)

{

    fsm_trans_t tt[] = {

        {0, is_true, 1, do_nothing},

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          }

    };



    is_true_CMockExpectAnyArgsAndReturn(67, 1);

    do_nothing_CMockExpectAnyArgs(68);



    fsm_t *f = (fsm_t*)1;



    int size = sizeof(tt)/sizeof(tt[0]);



    f = fsm_new(tt, size, 1);



    fsm_fire(f);



    do {if ((((f)) != 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(78))));}} while(0);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((f->current_state)), (

   ((void *)0)

   ), (UNITY_UINT)(79), UNITY_DISPLAY_STYLE_INT);



    fsm_destroy(f);

}









void test_fsm_validTransitionTable(void)

{

    fsm_trans_t tt[] = {

        {0, is_true, 1, do_nothing},

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          },

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          },

    };



    fsm_t *f = (fsm_t*)1;



    int size = sizeof(tt)/sizeof(tt[0]);



    f = fsm_new(tt, size, -1);



    UnityAssertEqualNumber((UNITY_INT)((

   ((void *)0)

   )), (UNITY_INT)((f)), (

   ((void *)0)

   ), (UNITY_UINT)(101), UNITY_DISPLAY_STYLE_INT);



    fsm_destroy(f);

}



void test_fsm_validLastTransition(void)

{

    fsm_trans_t tt[] = {

        {0, is_true, 1, do_nothing},

        {0, is_true, 2, do_nothing},

        {-1, 

            ((void *)0)

                , -1, do_nothing},

    };



    fsm_t *f = (fsm_t*)1;



    int size = sizeof(tt)/sizeof(tt[0]);



    f = fsm_new(tt, size, 2);



    UnityAssertEqualNumber((UNITY_INT)((

   ((void *)0)

   )), (UNITY_INT)((f)), (

   ((void *)0)

   ), (UNITY_UINT)(120), UNITY_DISPLAY_STYLE_INT);



    fsm_destroy(f);

}
