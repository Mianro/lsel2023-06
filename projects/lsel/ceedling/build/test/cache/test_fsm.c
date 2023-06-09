#include "build/test/mocks/mock_test_fsm.h"
#include "../common/include/fsm.h"
#include "/var/lib/gems/2.7.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"








void setUp(void)

{

}



void tearDown(void)

{

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

   ), (UNITY_UINT)(133), UNITY_DISPLAY_STYLE_INT);



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

   ), (UNITY_UINT)(157), UNITY_DISPLAY_STYLE_INT);



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

   )) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(182))));}} while(0);



    fsm_destroy(f);

}











void test_fsm_FMS_NEW_INDEPENDENT_FSM(void)

{

    fsm_trans_t tt1[] = {

        {0, check_func, 1, do_nothing},

        {0, check_func, 2, do_nothing},

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          },

    };



    fsm_trans_t tt2[] = {

        {0, check_func, 1, do_nothing},

        {0, check_func, 2, do_nothing},

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          },

    };



    check_func_CMockExpectAnyArgsAndReturn(205, 1);

    do_nothing_CMockExpectAnyArgs(206);



    fsm_t *f1 = (fsm_t*)1;

    fsm_t *f2 = (fsm_t*)1;



    int size1 = sizeof(tt1)/sizeof(tt1[0]);

    int size2 = sizeof(tt2)/sizeof(tt2[0]);



    f1 = fsm_new(tt1, size1, 3);

    f2 = fsm_new(tt2, size2, 3);



    fsm_fire(f1);



    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((f1->current_state)), (

   ((void *)0)

   ), (UNITY_UINT)(219), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((f2->current_state)), (

   ((void *)0)

   ), (UNITY_UINT)(220), UNITY_DISPLAY_STYLE_INT);



    fsm_destroy(f1);

    fsm_destroy(f2);

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

   ), (UNITY_UINT)(244), UNITY_DISPLAY_STYLE_INT);



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

   ), (UNITY_UINT)(266), UNITY_DISPLAY_STYLE_INT);



    fsm_destroy(f);

}











void test_fsm__INIT_F_NOT_NULL(void)

{ fsm_trans_t tt[] = {

        {0, check_func, 1, do_nothing},

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          },

    };



    int size = sizeof(tt)/sizeof(tt[0]);



    UnityAssertEqualNumber((UNITY_INT)((

   ((void *)0)

   )), (UNITY_INT)((fsm_init(

   ((void *)0)

   ,tt,size,1))), (

   ((void *)0)

   ), (UNITY_UINT)(283), UNITY_DISPLAY_STYLE_INT);



}











void test_fsm_INIT_TT_NOT_NULL(void)

{ fsm_trans_t tt[] = {

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



    UnityAssertEqualNumber((UNITY_INT)((

   ((void *)0)

   )), (UNITY_INT)((fsm_init(f,

   ((void *)0)

   ,size,1))), (

   ((void *)0)

   ), (UNITY_UINT)(302), UNITY_DISPLAY_STYLE_INT);



}











void test_fsm_INIT_TT_IS_VALID_NULL(void)

{ fsm_trans_t tt[] = {

        {0, check_func, 1, do_nothing},

        {-1, check_func, 2, do_nothing},

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

   ), (UNITY_UINT)(321), UNITY_DISPLAY_STYLE_INT);



}











void test_fsm_INIT_LAST_TT_IS_INVALID(void)

{ fsm_trans_t tt[] = {

        {0, check_func, 1, do_nothing},

        {1, check_func, 2, do_nothing},

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          },

    };



    fsm_t* f = (fsm_t*) malloc (sizeof (fsm_t));



    int size = sizeof(tt)/sizeof(tt[0]);



    UnityAssertEqualNumber((UNITY_INT)((

   1

   )), (UNITY_INT)((fsm_init(f,tt,size,2))), (

   ((void *)0)

   ), (UNITY_UINT)(340), UNITY_DISPLAY_STYLE_INT);



}









void test_fsm_INIT_VALID_STATES(void)

{ fsm_trans_t tt[] = {

        {0, check_func, 1, do_nothing},

        {1, check_func, 2, do_nothing},

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          },

    };



    fsm_t* f = (fsm_t*) malloc (sizeof (fsm_t));



    int size = sizeof(tt)/sizeof(tt[0]);



    UnityAssertEqualNumber((UNITY_INT)((

   1

   )), (UNITY_INT)((fsm_init(f,tt,size,2))), (

   ((void *)0)

   ), (UNITY_UINT)(358), UNITY_DISPLAY_STYLE_INT);



}













void test_fsm_FIRE_IN_NULL(void)

{ fsm_trans_t tt[] = {

        {0, 

           ((void *)0)

               , 1, do_nothing},

        {1, check_func, 2, do_nothing},

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          },

    };



    do_nothing_CMockExpectAnyArgs(374);



    fsm_t *f = (fsm_t*)1;



    int size = sizeof(tt)/sizeof(tt[0]);



    f = fsm_new(tt, size, 2);



    fsm_fire(f);



    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((f->current_state)), (

   ((void *)0)

   ), (UNITY_UINT)(384), UNITY_DISPLAY_STYLE_INT);



    fsm_destroy(f);



}















void test_fsm_FIRE_IN_VALID(void)

{ fsm_trans_t tt[] = {

        {0, check_func, 1, do_nothing},

        {1, check_func, 2, do_nothing},

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          },

    };



    check_func_CMockExpectAnyArgsAndReturn(403, 1);

    do_nothing_CMockExpectAnyArgs(404);



    fsm_t *f = (fsm_t*)1;



    int size = sizeof(tt)/sizeof(tt[0]);



    f = fsm_new(tt, size, 2);



    fsm_fire(f);



    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((f->current_state)), (

   ((void *)0)

   ), (UNITY_UINT)(414), UNITY_DISPLAY_STYLE_INT);



    fsm_destroy(f);

}











void test_fsm_FIRE_VALID_T(void)

{ fsm_trans_t tt[] = {

        {0, check_func, 1, do_nothing},

        {1, check_func, 2, do_nothing},

        {-1, 

            ((void *)0)

                , -1, 

                      ((void *)0)

                          },

    };



    check_func_CMockExpectAnyArgsAndReturn(430, 1);

    do_nothing_CMockExpectAnyArgs(431);



    fsm_t *f = (fsm_t*)1;



    int size = sizeof(tt)/sizeof(tt[0]);



    f = fsm_new(tt, size, 2);



    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((fsm_fire(f))), (

   ((void *)0)

   ), (UNITY_UINT)(439), UNITY_DISPLAY_STYLE_INT);



    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((f->current_state)), (

   ((void *)0)

   ), (UNITY_UINT)(441), UNITY_DISPLAY_STYLE_INT);



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



    check_func_CMockExpectAnyArgsAndReturn(459, 0);

    check_func_CMockExpectAnyArgsAndReturn(460, 0);



    fsm_t *f = (fsm_t*)1;



    int size = sizeof(tt)/sizeof(tt[0]);



    f = fsm_new(tt, size, 2);



    f->current_state = 3;



    UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((fsm_fire(f))), (

   ((void *)0)

   ), (UNITY_UINT)(470), UNITY_DISPLAY_STYLE_INT);



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



    check_func_CMockExpectAnyArgsAndReturn(486, 0);



    fsm_t *f = (fsm_t*)1;



    int size = sizeof(tt)/sizeof(tt[0]);



    f = fsm_new(tt, size, 2);



    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((fsm_fire(f))), (

   ((void *)0)

   ), (UNITY_UINT)(494), UNITY_DISPLAY_STYLE_INT);



    fsm_destroy(f);

}
