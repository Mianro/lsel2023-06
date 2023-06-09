/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCK_TEST_FSM_H
#define _MOCK_TEST_FSM_H

#include "unity.h"
#include "test_fsm.h"

/* Ignore the following warnings, since we are copying code */
#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic push
#endif
#if !defined(__clang__)
#pragma GCC diagnostic ignored "-Wpragmas"
#endif
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wduplicate-decl-specifier"
#endif

void mock_test_fsm_Init(void);
void mock_test_fsm_Destroy(void);
void mock_test_fsm_Verify(void);




#define check_func_IgnoreAndReturn(cmock_retval) check_func_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void check_func_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, int cmock_to_return);
#define check_func_StopIgnore() check_func_CMockStopIgnore()
void check_func_CMockStopIgnore(void);
#define check_func_ExpectAnyArgsAndReturn(cmock_retval) check_func_CMockExpectAnyArgsAndReturn(__LINE__, cmock_retval)
void check_func_CMockExpectAnyArgsAndReturn(UNITY_LINE_TYPE cmock_line, int cmock_to_return);
#define check_func_ExpectAndReturn(f, cmock_retval) check_func_CMockExpectAndReturn(__LINE__, f, cmock_retval)
void check_func_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, fsm_t* f, int cmock_to_return);
typedef int (* CMOCK_check_func_CALLBACK)(fsm_t* f, int cmock_num_calls);
void check_func_AddCallback(CMOCK_check_func_CALLBACK Callback);
void check_func_Stub(CMOCK_check_func_CALLBACK Callback);
#define check_func_StubWithCallback check_func_Stub
#define check_func_ReturnThruPtr_f(f) check_func_CMockReturnMemThruPtr_f(__LINE__, f, sizeof(fsm_t))
#define check_func_ReturnArrayThruPtr_f(f, cmock_len) check_func_CMockReturnMemThruPtr_f(__LINE__, f, cmock_len * sizeof(*f))
#define check_func_ReturnMemThruPtr_f(f, cmock_size) check_func_CMockReturnMemThruPtr_f(__LINE__, f, cmock_size)
void check_func_CMockReturnMemThruPtr_f(UNITY_LINE_TYPE cmock_line, fsm_t* f, size_t cmock_size);
#define check_func_IgnoreArg_f() check_func_CMockIgnoreArg_f(__LINE__)
void check_func_CMockIgnoreArg_f(UNITY_LINE_TYPE cmock_line);
#define do_nothing_Ignore() do_nothing_CMockIgnore()
void do_nothing_CMockIgnore(void);
#define do_nothing_StopIgnore() do_nothing_CMockStopIgnore()
void do_nothing_CMockStopIgnore(void);
#define do_nothing_ExpectAnyArgs() do_nothing_CMockExpectAnyArgs(__LINE__)
void do_nothing_CMockExpectAnyArgs(UNITY_LINE_TYPE cmock_line);
#define do_nothing_Expect(f) do_nothing_CMockExpect(__LINE__, f)
void do_nothing_CMockExpect(UNITY_LINE_TYPE cmock_line, fsm_t* f);
typedef void (* CMOCK_do_nothing_CALLBACK)(fsm_t* f, int cmock_num_calls);
void do_nothing_AddCallback(CMOCK_do_nothing_CALLBACK Callback);
void do_nothing_Stub(CMOCK_do_nothing_CALLBACK Callback);
#define do_nothing_StubWithCallback do_nothing_Stub
#define do_nothing_ReturnThruPtr_f(f) do_nothing_CMockReturnMemThruPtr_f(__LINE__, f, sizeof(fsm_t))
#define do_nothing_ReturnArrayThruPtr_f(f, cmock_len) do_nothing_CMockReturnMemThruPtr_f(__LINE__, f, cmock_len * sizeof(*f))
#define do_nothing_ReturnMemThruPtr_f(f, cmock_size) do_nothing_CMockReturnMemThruPtr_f(__LINE__, f, cmock_size)
void do_nothing_CMockReturnMemThruPtr_f(UNITY_LINE_TYPE cmock_line, fsm_t* f, size_t cmock_size);
#define do_nothing_IgnoreArg_f() do_nothing_CMockIgnoreArg_f(__LINE__)
void do_nothing_CMockIgnoreArg_f(UNITY_LINE_TYPE cmock_line);

#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic pop
#endif
#endif

#endif
