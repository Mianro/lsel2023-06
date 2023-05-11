
#include "unity.h"

#include "fsm.h"
#include "mock_test_fsm.h"
#include <stdlib.h>

void setUp(void)
{
}

void tearDown(void)
{
}


/**
 * Especificaciones que no se traducen a tests
 * 
 * nt_1. Permite especificar una máquina de estados como un valor de
 *       estado actual y un array de transiciones, terminado con una
 *       transición inválida fija.
 * nt_2. Una transición tiene el formato:
 *       orig_state - int - estado de origen
 *       in - int (*func)(fsm_t*) - función de comprobación o guarda
 *       dst_state - int - estado de destino
 *       out - void (*func)(fsm_t*) - función de actualización
 * nt_2  Ofrece una función tipo constructor que reserva la memoria
 *       dinámicamente e inicializa la máquina de estados.
 * nt_3  Los argumentos son:
 *       La tabla de transiciones (array terminado en la inválida)
 *       Número de transiciones (la última es la inválida)
 *       Estado máximo
 *       Devuelve dirección de la memoria que contiene lo necesario para
 *       poder utilizarla
 * 
 * nt_4  Ofrece una función tipo inicialización que inicializa una
 *       estructura reservada en memoria de forma estática,externamente.

- Los argumentos son:
- La dirección de memoria para la instancia de la máquina de estados
- La tabla de transiciones (array terminado en la inválida)
- Número de transiciones (la última es la inválida)
- Estado máximo
- Devuelve dirección de la memoria que contiene lo necesario para
  poder utilizarla
  Todos los estados son naturales e inferiores al estado máximo (no iguales)



FSM FIRE
- Hay una función para realizar la comprobación de la
transición
- El estado inicial es el estado de origen de la primera
transición
- Solo se comprueban las funciones de guarda de las
transiciones con estado de origen igual al de la máquina
de estados
- Si para una transición a comprobar tiene una función de
guarda NULL, se cumple siempre.
 -Si falla en la reserva, devuelve NULL
 *
 *
 * 
 * 
 * 
 * Especificaciones que se pueden traducir a tests
 * 
 ** t_1  La transición inválida final es {-1, NULL, -1, NULL}
 ** t_2  Cualquier otra transición debe tener un estado válido de
 *       entrada y de salida
 ** t_3  Las funciones de guarda y actualización pueden ser NULL
 * t_4  Puede haber varias máquinas de estados simultáneamente sin que
 *      afecte una a otra si no tienen conexión externa
 ** t_5  Si hay datos erróneos no debe reservar la memoria

 ** t_6  Si falla o hay datos erróneos, devuelve false
 ** t_7  Si para una transición a comprobar tiene una función de
 *       guarda, se ejecuta la función y si devuelve distinto de 0, se cumple.
 *       Si se cumple, se cambia el estado actual al de destino, no se comprueban 
 *       más transiciones y se ejecuta la función de actualización, si es distinto de NULL y devuelve 1.
 ** t_8  Si ninguna transición tiene un estado de origen coincidente con el estado actual, la función de
          comprobación de transiciones devuelve -1.
 * t_9   Si hay transiciones pero no se cumplen las condiciones,devuelve 0
 * La comprobación de errores consiste en:
 * La memoria pasada no es NULL (para la estática)
 ** t_12 La tabla de transiciones no es NULL
 ** t_13 Todas las transiciones son válidas salvo la última
 ** t_14 La última transición es la inválida
 

 */


/**
 *t_12 La tabla de transiciones no es NULL
*/
void test_fsm_new_nullWhenNullTransition(void)
{
    fsm_t *f = (fsm_t*)1;

    f = fsm_new(NULL,0,-1);

    TEST_ASSERT_EQUAL (NULL, f);
}

/**
 *t_13 Todas las transiciones son válidas salvo la última
*/
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
        {0, check_func, 1, do_nothing},
        {-1, NULL, -1, NULL}
    };

    check_func_ExpectAnyArgsAndReturn(1);
    do_nothing_ExpectAnyArgs();
    

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
        {0, check_func, 1, do_nothing},
        {-1, NULL, -1, NULL}
    };

    check_func_ExpectAnyArgsAndReturn(1);
    do_nothing_ExpectAnyArgs();

    fsm_t *f = (fsm_t*)1;

    int size = sizeof(tt)/sizeof(tt[0]);

    f = fsm_new(tt, size, 1);
    
    fsm_fire(f);

    TEST_ASSERT_NOT_NULL (f);
    TEST_ASSERT_EQUAL (1, f->current_state);

    fsm_destroy(f);
}



// t_1  La transición inválida final es {-1, NULL, -1, NULL}
void test_fsm_validTransitionTable(void)
{
    fsm_trans_t tt[] = {
        {0, check_func, 1, do_nothing},
        {-1, NULL, -1, NULL},
        {-1, NULL, -1, NULL},
    };

    fsm_t *f = (fsm_t*)1;

    int size = sizeof(tt)/sizeof(tt[0]);

    f = fsm_new(tt, size, -1);

    TEST_ASSERT_EQUAL (NULL, f);

    fsm_destroy(f);
}

//t_14 La última transición es la inválida
void test_fsm_validLastTransition(void)
{
    fsm_trans_t tt[] = {
        {0, check_func, 1, do_nothing},
        {0, check_func, 2, do_nothing},
        {-1, NULL, -1, do_nothing},
    };


    fsm_t *f = (fsm_t*)1;

    int size = sizeof(tt)/sizeof(tt[0]);

    f = fsm_new(tt, size, 2);

    TEST_ASSERT_EQUAL (NULL, f);

    fsm_destroy(f);
}


// t_2  Cualquier otra transición debe tener un estado válido de entrada y de salida
void test_fsm_valid_state(void)
{
    fsm_trans_t tt[] = {
        {0, check_func, 1, do_nothing},
        {0, check_func, 3, do_nothing},
        {0, check_func, 3, do_nothing},
        {-1, NULL, -1, do_nothing},
    };


    fsm_t *f = (fsm_t*)1;

    int size = sizeof(tt)/sizeof(tt[0]);

    f = fsm_new(tt, size, 3);

    TEST_ASSERT_EQUAL (NULL, f);

    fsm_destroy(f);
}

// t_3  Las funciones de guarda y actualización pueden ser NULL
void test_fsm_NULL_argument_valid_InOut(void)
{
    fsm_trans_t tt[] = {
        {0, check_func, 1, do_nothing},
        {0, NULL, 2, NULL},
        {-1, NULL, -1, NULL},
    };


    fsm_t *f = (fsm_t*)1;

    int size = sizeof(tt)/sizeof(tt[0]);

    f = fsm_new(tt, size, 2);

    TEST_ASSERT_NOT_NULL (f);

    fsm_destroy(f);
}

// t_5 Si hay datos erróneos no debe reservar la memoria
void test_fsm_NULL_IF_WRONG_DATA(void)
{
    fsm_trans_t tt[] = {
        {-1, check_func, 1, do_nothing},
        {0, check_func, 2, do_nothing},
        {-1, NULL, -1, NULL},
    };


    fsm_t *f = (fsm_t*)1;

    int size = sizeof(tt)/sizeof(tt[0]);

    f = fsm_new(tt, size, 2);

    TEST_ASSERT_EQUAL (NULL, f);

    fsm_destroy(f);
}

// t_6  Si falla o hay datos erróneos, devuelve false
void test_fsm_NULL_IFWRONGDATA_INIT(void)
{
    fsm_trans_t tt[] = {
        {-1, check_func, 1, do_nothing},
        {0, check_func, 2, do_nothing},
        {-1, NULL, -1, NULL},
    };

    fsm_t* f = (fsm_t*) malloc (sizeof (fsm_t));

    int size = sizeof(tt)/sizeof(tt[0]);

    //f = fsm_new(tt, size, 2);

    TEST_ASSERT_EQUAL (false, fsm_init(f,tt,size,2));

    fsm_destroy(f);
}

void test_fsm_INPUT_FUNC_VALID_T(void)
{
    fsm_trans_t tt[] = {
        {0, check_func, 1, do_nothing},
        {1, check_func, 2, do_nothing},
        {-1, NULL, -1, NULL},
    };

    check_func_ExpectAnyArgsAndReturn(1);
    
    fsm_t *f = (fsm_t*)1;

    int size = sizeof(tt)/sizeof(tt[0]);

    f = fsm_new(tt, size, 2);

    TEST_ASSERT_EQUAL (1, fsm_fire(f));

    fsm_destroy(f);
}

// t_8 Si ninguna transición tiene un estado de origen coincidente con el estado actual, la función de
// comprobación de transiciones devuelve -1.
void test_fsm_ORIG_STATE_NOT_EQUAL_CURRENT_STATE(void)
{
    fsm_trans_t tt[] = {
        {0, check_func, 1, do_nothing},
        {1, check_func, 2, do_nothing},
        {-1, NULL, -1, NULL},
    };

    
    fsm_t *f = (fsm_t*)1;

    int size = sizeof(tt)/sizeof(tt[0]);

    f = fsm_new(tt, size, 2);

    f->current_state = 3; 

    TEST_ASSERT_EQUAL (-1, fsm_fire(f));

    fsm_destroy(f);
}


// t_9 Si hay transiciones pero no se cumplen las condiciones,devuelve 0
void test_fsm_VALID_T_NO_INPUT_FUNC(void)
{
    fsm_trans_t tt[] = {
        {0, check_func, 1, do_nothing},
        {1, check_func, 2, do_nothing},
        {-1, NULL, -1, NULL},
    };

    check_func_ExpectAnyArgsAndReturn(0);
        
    fsm_t *f = (fsm_t*)1;

    int size = sizeof(tt)/sizeof(tt[0]);

    f = fsm_new(tt, size, 2);

    TEST_ASSERT_EQUAL (0, fsm_fire(f));

    fsm_destroy(f);
}