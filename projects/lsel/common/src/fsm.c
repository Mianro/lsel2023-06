#include <stdlib.h>
#include <stdbool.h>
#include "fsm.h"

fsm_t*
fsm_new (fsm_trans_t* tt, int size, int max_state)
{
  
  tt = fsm_valid_tt(tt,size,max_state);

  if (tt==NULL) 
  {
  return NULL;   
  }else if(tt->dest_state == -1 && tt->orig_state == -1 && tt->in == NULL && tt->out==NULL) 
    {
    return NULL; 
    }else 
        {
        fsm_t* f = (fsm_t*) malloc (sizeof (fsm_t));
          if(f == NULL)
          {
             return NULL;
          }else
          {
        
          if(fsm_init (f, tt, size, max_state)){
            return f;
          }else{
            return NULL; 
          }
        }
      }
}

bool
fsm_init (fsm_t* f, fsm_trans_t* tt, int size, int max_state)
{
        if (!f || !tt) {
          return false;
        }

        if (!fsm_valid_tt(tt,size,max_state)){
          return false;
        }

        for (int i = 0; i < (size-1); i++) {
          if (tt[i].orig_state < 0 || tt[i].dest_state < 0 || tt[i].orig_state > max_state || tt[i].dest_state > max_state) {
            return false;
          }
        }

        f->tt = tt;
        f->current_state = tt[0].orig_state;  
        return true;   
}

void
fsm_destroy (fsm_t* f)
{
  free(f);
}

int
fsm_fire (fsm_t* f)
{
  fsm_trans_t* t;

  for (t = f->tt; t->orig_state >= 0; ++t) {
    if ((f->current_state == t->orig_state) && t->in(f)) {
      f->current_state = t->dest_state;
      return 1; 
      if (t->out)
        t->out(f);
      break;
    }else if(f->current_state != t->orig_state){
      return -1; 
    }
  }

  return 0; 
}

fsm_trans_t*
fsm_valid_tt(fsm_trans_t* tt, int size, int max_state)
{

  if(tt==NULL){
    return NULL;
  }

  for(int i = 0 ; i < (size-1); i++)
  {
   if(tt[i].dest_state == -1 || tt[i].orig_state == -1)
   {
    return NULL;
   } 
   }

  for(int i = 0 ; i < (size-2); i++){
    if(tt[i].dest_state < 0 || tt[i].orig_state >= max_state || tt[i].dest_state >= max_state || tt[i].orig_state < 0){ 
      return NULL; 
    }
  }


  if(!(tt[size-1].dest_state == -1 && tt[size-1].orig_state == -1 && tt[size-1].in == NULL && tt[size-1].out == NULL)){
    return NULL;
  }
  
  return tt;
}