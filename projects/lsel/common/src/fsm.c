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
{       // Validacion de F y TT
        if (f == NULL || tt==NULL) {
          return false;
        }
        // Validacion de las tablas de transicion
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
  int valid_state = 0; 
  int guard_function = 0; 

  for (t=f->tt; t->orig_state >= 0; ++t) {

    if(t->in!= NULL){
    guard_function = t->in(f);
    }else{
    guard_function = 1;
    }

    if ((f->current_state == t->orig_state) && guard_function) {
      f->current_state = t->dest_state;
      if (t->out)
      t->out(f);
      return 1; 
      break;
    }
    
    if(f->current_state != t->orig_state){
      valid_state = -1; 
    }else{
      valid_state = 0; 
      break; 
    }
  }

  if(valid_state == -1){
    return -1; 
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
 // Funcion retorna NULL si algun estado no es natural o mayor al maximo estado
  for(int i = 0 ; i < (size-2); i++){
    if(tt[i].dest_state < 0 || tt[i].orig_state >= max_state || tt[i].dest_state >= max_state || tt[i].orig_state < 0){ 
      return NULL; 
    }
  }

// Funcion retorna NULL si el ultimo estado no tiene el formato adecuado
  if(!(tt[size-1].dest_state == -1 && tt[size-1].orig_state == -1 && tt[size-1].in == NULL && tt[size-1].out == NULL)){
    return NULL;
  }
  
  return tt;
}