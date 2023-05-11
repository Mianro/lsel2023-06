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

   ), (UNITY_UINT)(104), UNITY_DISPLAY_STYLE_INT);

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

   ), (UNITY_UINT)(120), UNITY_DISPLAY_STYLE_INT);



}



void test_fsm_validTransitionNoOutput(void)

{

    fsm_trans_t tt[] = {

        {0, check_func, 1, do_nothing},

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          }

    };



    check_func_CMockExpectAnyArgsAndReturn(131, 1);

    do_nothing_CMockExpectAnyArgs(132);





    fsm_t *f = (fsm_t*)1;



    int size = sizeof(tt)/sizeof(tt[0]);



    f = fsm_new(tt, size, 1);



    fsm_fire(f);



    do {if ((((f)) != 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(143))));}} while(0);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((f->current_state)), (

   ((void *)0)

   ), (UNITY_UINT)(144), UNITY_DISPLAY_STYLE_INT);



    fsm_destroy(f);

}



void test_fsm_validTransitionWithOutput(void)

{

    fsm_trans_t tt[] = {

        {0, check_func, 1, do_nothing},

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          }

    };



    check_func_CMockExpectAnyArgsAndReturn(156, 1);

    do_nothing_CMockExpectAnyArgs(157);



    fsm_t *f = (fsm_t*)1;



    int size = sizeof(tt)/sizeof(tt[0]);



    f = fsm_new(tt, size, 1);



    fsm_fire(f);



    do {if ((((f)) != 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(167))));}} while(0);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((f->current_state)), (

   ((void *)0)

   ), (UNITY_UINT)(168), UNITY_DISPLAY_STYLE_INT);



    fsm_destroy(f);

}









void test_fsm_validTransitionTable(void)

{

    fsm_trans_t tt[] = {

        {0, check_func, 1, do_nothing},

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

   ), (UNITY_UINT)(190), UNITY_DISPLAY_STYLE_INT);



    fsm_destroy(f);

}





void test_fsm_validLastTransition(void)

{

    fsm_trans_t tt[] = {

        {0, check_func, 1, do_nothing},

        {0, check_func, 2, do_nothing},

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

   ), (UNITY_UINT)(211), UNITY_DISPLAY_STYLE_INT);



    fsm_destroy(f);

}







void test_fsm_valid_state(void)

{

    fsm_trans_t tt[] = {

        {0, check_func, 1, do_nothing},

        {0, check_func, 3, do_nothing},

        {0, check_func, 3, do_nothing},

        {-1, 

            ((void *)0)

                , -1, do_nothing},

    };





    fsm_t *f = (fsm_t*)1;



    int size = sizeof(tt)/sizeof(tt[0]);



    f = fsm_new(tt, size, 3);



    UnityAssertEqualNumber((UNITY_INT)((

   ((void *)0)

   )), (UNITY_INT)((f)), (

   ((void *)0)

   ), (UNITY_UINT)(234), UNITY_DISPLAY_STYLE_INT);



    fsm_destroy(f);

}





void test_fsm_NULL_argument_valid_InOut(void)

{

    fsm_trans_t tt[] = {

        {0, check_func, 1, do_nothing},

        {0, 

           ((void *)0)

               , 2, 

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



    f = fsm_new(tt, size, 2);



    do {if ((((f)) != 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(255))));}} while(0);



    fsm_destroy(f);

}





void test_fsm_NULL_IF_WRONG_DATA(void)

{

    fsm_trans_t tt[] = {

        {-1, check_func, 1, do_nothing},

        {0, check_func, 2, do_nothing},

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          },

    };





    fsm_t *f = (fsm_t*)1;



    int size = sizeof(tt)/sizeof(tt[0]);



    f = fsm_new(tt, size, 2);



    UnityAssertEqualNumber((UNITY_INT)((

   ((void *)0)

   )), (UNITY_INT)((f)), (

   ((void *)0)

   ), (UNITY_UINT)(276), UNITY_DISPLAY_STYLE_INT);



    fsm_destroy(f);

}





void test_fsm_NULL_IFWRONGDATA_INIT(void)

{

    fsm_trans_t tt[] = {

        {-1, check_func, 1, do_nothing},

        {0, check_func, 2, do_nothing},

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          },

    };



    fsm_t* f = (fsm_t*) malloc (sizeof (fsm_t));



    int size = sizeof(tt)/sizeof(tt[0]);







    UnityAssertEqualNumber((UNITY_INT)((

   0

   )), (UNITY_INT)((fsm_init(f,tt,size,2))), (

   ((void *)0)

   ), (UNITY_UINT)(296), UNITY_DISPLAY_STYLE_INT);



    fsm_destroy(f);

}



void test_fsm_INPUT_FUNC_VALID_T(void)

{

    fsm_trans_t tt[] = {

        {0, check_func, 1, do_nothing},

        {1, check_func, 2, do_nothing},

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          },

    };



    check_func_CMockExpectAnyArgsAndReturn(309, 1);



    fsm_t *f = (fsm_t*)1;



    int size = sizeof(tt)/sizeof(tt[0]);



    f = fsm_new(tt, size, 2);



    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((fsm_fire(f))), (

   ((void *)0)

   ), (UNITY_UINT)(317), UNITY_DISPLAY_STYLE_INT);



    fsm_destroy(f);

}







void test_fsm_ORIG_STATE_NOT_EQUAL_CURRENT_STATE(void)

{

    fsm_trans_t tt[] = {

        {0, check_func, 1, do_nothing},

        {1, check_func, 2, do_nothing},

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          },

    };





    fsm_t *f = (fsm_t*)1;



    int size = sizeof(tt)/sizeof(tt[0]);



    f = fsm_new(tt, size, 2);



    f->current_state = 3;



    UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((fsm_fire(f))), (

   ((void *)0)

   ), (UNITY_UINT)(341), UNITY_DISPLAY_STYLE_INT);



    fsm_destroy(f);

}







void test_fsm_VALID_T_NO_INPUT_FUNC(void)

{

    fsm_trans_t tt[] = {

        {0, check_func, 1, do_nothing},

        {1, check_func, 2, do_nothing},

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          },

    };



    check_func_CMockExpectAnyArgsAndReturn(356, 0);



    fsm_t *f = (fsm_t*)1;



    int size = sizeof(tt)/sizeof(tt[0]);



    f = fsm_new(tt, size, 2);



    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((fsm_fire(f))), (

   ((void *)0)

   ), (UNITY_UINT)(364), UNITY_DISPLAY_STYLE_INT);



    fsm_destroy(f);

}
