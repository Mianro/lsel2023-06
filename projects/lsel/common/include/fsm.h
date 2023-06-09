#ifndef FSM_H_
#define FSM_H_

#include <stdbool.h>

typedef struct fsm_t fsm_t;

typedef int (*fsm_input_func_t) (fsm_t*);
typedef void (*fsm_output_func_t) (fsm_t*);

typedef struct fsm_trans_t {
  int orig_state;
  fsm_input_func_t in;
  int dest_state;
  fsm_output_func_t out;
} fsm_trans_t;

struct fsm_t {
  int current_state;
  fsm_trans_t* tt;
};

fsm_t* fsm_new (fsm_trans_t* tt, int size, int max_state);
bool fsm_init (fsm_t* f, fsm_trans_t* tt, int size, int max_state);
int fsm_fire (fsm_t* f);
void fsm_destroy (fsm_t* f);
fsm_trans_t* fsm_valid_tt(fsm_trans_t* tt,int size,int max_state);

#ifdef __GNUC__
#define UNUSED(d) d __attribute__((unused))
#else
#define UNUSED(d) d
#endif

#endif /* FSM_H_ */
