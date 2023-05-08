#include <stdlib.h>
#include <stdbool.h>
#include "fsm.h"

fsm_t*
fsm_new (fsm_trans_t* tt, int size, int max_state)
{
  
// Cualquier otra transición debe tener un estado válido de entrada y de salida  
  tt = fsm_valid_tt(tt,size);

  if (tt==NULL) 
  {
  return NULL;   
  }else if(tt->dest_state == -1 && tt->orig_state == -1 && tt->in == NULL && tt->out==NULL) 
    {
    return NULL; 
// Si hay datos erróneos no debe reservar la memoria
    }else if(!(tt[size-1].dest_state == -1 && tt[size-1].orig_state == -1 && tt[size-1].in == NULL && tt[size-1].out==NULL)){
        return NULL;
      }  
        else 
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

        if (!fsm_valid_tt(tt,size)){
          return false;
        }


//Si hay datos erroneos no se debe de reservar memoria
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

void
fsm_fire (fsm_t* f)
{
  fsm_trans_t* t;

  for (t = f->tt; t->orig_state >= 0; ++t) {
    if ((f->current_state == t->orig_state) && t->in(f)) {
      f->current_state = t->dest_state;
      if (t->out)
        t->out(f);
      break;
    }
  }
}

fsm_trans_t*
fsm_valid_tt(fsm_trans_t* tt, int size)
{

  for(int i = 0 ; i < (size-1); i++)
  {

   if(tt[i].dest_state == -1 || tt[i].orig_state == -1)
   {
      return NULL;
   }
  }

  if(!(tt[size-1].dest_state == -1 && tt[size-1].orig_state == -1 && tt[size-1].in == NULL && tt[size-1].out==NULL)){
    return NULL;
  }
  
  return tt;
}