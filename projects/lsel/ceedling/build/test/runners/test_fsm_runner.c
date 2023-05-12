/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"
#include "cmock.h"
#include "mock_test_fsm.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_fsm_validLastTransition(void);
extern void test_fsm_valid_state(void);
extern void test_fsm_NULL_argument_valid_InOut(void);
extern void test_fsm_FMS_NEW_INDEPENDENT_FSM(void);
extern void test_fsm_NULL_IF_WRONG_DATA(void);
extern void test_fsm_NULL_IFWRONGDATA_INIT(void);
extern void test_fsm__INIT_F_NOT_NULL(void);
extern void test_fsm_INIT_TT_NOT_NULL(void);
extern void test_fsm_INIT_TT_IS_VALID_NULL(void);
extern void test_fsm_INIT_LAST_TT_IS_INVALID(void);
extern void test_fsm_INIT_VALID_STATES(void);
extern void test_fsm_FIRE_IN_NULL(void);
extern void test_fsm_FIRE_IN_VALID(void);
extern void test_fsm_FIRE_VALID_T(void);
extern void test_fsm_ORIG_STATE_NOT_EQUAL_CURRENT_STATE(void);
extern void test_fsm_VALID_T_NO_INPUT_FUNC(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
  mock_test_fsm_Init();
}
static void CMock_Verify(void)
{
  mock_test_fsm_Verify();
}
static void CMock_Destroy(void)
{
  mock_test_fsm_Destroy();
}

/*=======Test Reset Options=====*/
void resetTest(void);
void resetTest(void)
{
  tearDown();
  CMock_Verify();
  CMock_Destroy();
  CMock_Init();
  setUp();
}
void verifyTest(void);
void verifyTest(void)
{
  CMock_Verify();
}

/*=======Test Runner Used To Run Each Test=====*/
static void run_test(UnityTestFunction func, const char* name, UNITY_LINE_TYPE line_num)
{
    Unity.CurrentTestName = name;
    Unity.CurrentTestLineNumber = line_num;
#ifdef UNITY_USE_COMMAND_LINE_ARGS
    if (!UnityTestMatches())
        return;
#endif
    Unity.NumberOfTests++;
    UNITY_CLR_DETAILS();
    UNITY_EXEC_TIME_START();
    CMock_Init();
    if (TEST_PROTECT())
    {
        setUp();
        func();
    }
    if (TEST_PROTECT())
    {
        tearDown();
        CMock_Verify();
    }
    CMock_Destroy();
    UNITY_EXEC_TIME_STOP();
    UnityConcludeTest();
}

/*=======MAIN=====*/
int main(void)
{
  UnityBegin("test_fsm.c");
  run_test(test_fsm_validLastTransition, "test_fsm_validLastTransition", 86);
  run_test(test_fsm_valid_state, "test_fsm_valid_state", 107);
  run_test(test_fsm_NULL_argument_valid_InOut, "test_fsm_NULL_argument_valid_InOut", 130);
  run_test(test_fsm_FMS_NEW_INDEPENDENT_FSM, "test_fsm_FMS_NEW_INDEPENDENT_FSM", 150);
  run_test(test_fsm_NULL_IF_WRONG_DATA, "test_fsm_NULL_IF_WRONG_DATA", 186);
  run_test(test_fsm_NULL_IFWRONGDATA_INIT, "test_fsm_NULL_IFWRONGDATA_INIT", 207);
  run_test(test_fsm__INIT_F_NOT_NULL, "test_fsm__INIT_F_NOT_NULL", 227);
  run_test(test_fsm_INIT_TT_NOT_NULL, "test_fsm_INIT_TT_NOT_NULL", 240);
  run_test(test_fsm_INIT_TT_IS_VALID_NULL, "test_fsm_INIT_TT_IS_VALID_NULL", 256);
  run_test(test_fsm_INIT_LAST_TT_IS_INVALID, "test_fsm_INIT_LAST_TT_IS_INVALID", 272);
  run_test(test_fsm_INIT_VALID_STATES, "test_fsm_INIT_VALID_STATES", 288);
  run_test(test_fsm_FIRE_IN_NULL, "test_fsm_FIRE_IN_NULL", 306);
  run_test(test_fsm_FIRE_IN_VALID, "test_fsm_FIRE_IN_VALID", 333);
  run_test(test_fsm_FIRE_VALID_T, "test_fsm_FIRE_VALID_T", 360);
  run_test(test_fsm_ORIG_STATE_NOT_EQUAL_CURRENT_STATE, "test_fsm_ORIG_STATE_NOT_EQUAL_CURRENT_STATE", 386);
  run_test(test_fsm_VALID_T_NO_INPUT_FUNC, "test_fsm_VALID_T_NO_INPUT_FUNC", 412);

  CMock_Guts_MemFreeFinal();
  return UnityEnd();
}
