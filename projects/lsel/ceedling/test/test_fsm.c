
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
 * FSM_NEW
 * 
 *  nt_1. Permite especificar una máquina de estados como un valor de
 *       estado actual y un array de transiciones, terminado con una
 *       transición inválida fija.
 * 
 *  nt_2. Una transición tiene el formato:
 *       orig_state - int - estado de origen
 *       in - int (*func)(fsm_t*) - función de comprobación o guarda
 *       dst_state - int - estado de destino
 *       out - void (*func)(fsm_t*) - función de actualización
 * 
 *  nt_3  Ofrece una función tipo constructor que reserva la memoria
 *       dinámicamente e inicializa la máquina de estados.
 * 
 *  nt_4  Si hay datos erróneos no debe reservar la memoria
 * 
 *  nt_5  Los argumentos son:
 *       La tabla de transiciones (array terminado en la inválida)
 *       Número de transiciones (la última es la inválida)
 *       Estado máximo
 *       Devuelve dirección de la memoria que contiene lo necesario para
 *       poder utilizarla
 * 
 * FSM_INI
 * 
 *  nt_4  Ofrece una función tipo inicialización que inicializa una
 *       estructura reservada en memoria de forma estática,externamente.
 * 
 *  nt_5 Los argumentos son:
 *     - La dirección de memoria para la instancia de la máquina de estados
 *     - La tabla de transiciones (array terminado en la inválida)
 *     - Número de transiciones (la última es la inválida)
 *     - Estado máximo
 * 
 *  nt_6 Devuelve dirección de la memoria que contiene lo necesario para poder utilizarla
 *        FSM FIRE
 * 
 *  nt_7 Hay una función para realizar la comprobación de la transición
 * 
 *  nt_8 El estado inicial es el estado de origen de la primera transición
 * 
 *  nt_9 Solo se comprueban las funciones de guarda de las transiciones con estado de origen igual al de la máquina
 *      de estados
 */

 /**
 * Especificaciones que se pueden traducir a tests
 * FMS_NEW
 * 
 *  t_1  La transición inválida final es {-1, NULL, -1, NULL}
 * 
 *  t_2  Cualquier otra transición debe tener un estado válido de
 *       entrada y de salida
 * 
 *  t_3  Las funciones de guarda y actualización pueden ser NULL
 * 
 *  t_4   Puede haber varias máquinas de estados simultáneamente sin que
 *       afecte una a otra si no tienen conexión externa
 * 
 *  t_5  Si falla en la reserva, devuelve NULL
 * 
 * FSM_INIT
 * 
 *  t_6  Si falla o hay datos erróneos, devuelve false
 *        La comprobación de errores consiste en:
 * 
 *  t_7  La memoria pasada no es NULL (para la estática)
 * 
 *  t_8  La tabla de transiciones no es NULL
 * 
 *  t_9  Todas las transiciones son válidas salvo la última
 * 
 *  t_10 La última transición es la inválida
 *  t_11 Todos los estados son naturales e inferiores al estado máximo (no iguales)
 * 
 * FSM_FIRE
 * 
 *  t_12 Si para una transición a comprobar tiene una función de guarda NULL, se cumple siempre.
 * 
 *  t_13 Si para una transición a comprobar tiene una función de guarda, se ejecuta la función y si devuelve 
 *       distinto de 0, se cumple.
 * 
 *  t_14 Si se cumple, se cambia el estado actual al de destino, no se comprueban 
 *      más transiciones y se ejecuta la función de actualización, si es distinto de NULL y devuelve 1.
 * 
 *  t_15 Si ninguna transición tiene un estado de origen coincidente con el estado actual, la función de
 *       comprobación de transiciones devuelve -1. 
 *  t_16 Si hay transiciones pero no se cumplen las condiciones,devuelve 0.
 */




/**
 * @brief t_1 La última transición es la inválida -fsm_new
 */
 
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

/** 
 * @brief t_2  Cualquier otra transición debe tener un estado válido de entrada y de salida -fsm_new
 */
 
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



/** 
 * @brief t_3  Las funciones de guarda y actualización pueden ser NULL -fsm_new
 */
 
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

/**
* @brief t_4 Puede haber varias máquinas de estados simultáneamente sin que afecte una a otra si no tienen conexión externa
*/

void test_fsm_FMS_NEW_INDEPENDENT_FSM(void)
{
    fsm_trans_t tt1[] = {
        {0, check_func, 1, do_nothing},
        {0, check_func, 2, do_nothing},
        {-1, NULL, -1, NULL},
    };

    fsm_trans_t tt2[] = {
        {0, check_func, 1, do_nothing},
        {0, check_func, 2, do_nothing},
        {-1, NULL, -1, NULL},
    };

    check_func_ExpectAnyArgsAndReturn(1);
    do_nothing_ExpectAnyArgs(); 

    fsm_t *f1 = (fsm_t*)1;
    fsm_t *f2 = (fsm_t*)1;

    int size1 = sizeof(tt1)/sizeof(tt1[0]);
    int size2 = sizeof(tt2)/sizeof(tt2[0]);

    f1 = fsm_new(tt1, size1, 3);
    f2 = fsm_new(tt2, size2, 3);

    fsm_fire(f1); 

    TEST_ASSERT_EQUAL(1,f1->current_state);
    TEST_ASSERT_EQUAL(0,f2->current_state);

    fsm_destroy(f1);
    fsm_destroy(f2); 
}

/**
 * @brief t_5 Si falla en la reserva, devuelve NULL -fsm_new
 */
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

/** 
 * @brief t_6  Si falla o hay datos erróneos, devuelve false -fsm_init
 */
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


/**
 * @brief t_7 La memoria pasada no es NULL (para la estática) -fsm_init
 */
void test_fsm__INIT_F_NOT_NULL(void)
{   fsm_trans_t tt[] = {
        {0, check_func, 1, do_nothing},
        {-1, NULL, -1, NULL},
    };

    int size = sizeof(tt)/sizeof(tt[0]);

    TEST_ASSERT_EQUAL (NULL, fsm_init(NULL,tt,size,1));

}

/**
 * @brief t_8 La tabla de transiciones no es NULL -fsm_init
 */

void test_fsm_INIT_TT_NOT_NULL(void)
{   fsm_trans_t tt[] = {
        {0, check_func, 1, do_nothing},
        {1, check_func, 2, do_nothing},
        {-1, NULL, -1, NULL},
    };

    fsm_t *f = (fsm_t*)1;

    int size = sizeof(tt)/sizeof(tt[0]);

    TEST_ASSERT_EQUAL (NULL, fsm_init(f,NULL,size,1));

}

/**
 * @brief t_9 Todas las transiciones son válidas salvo la última -fsm_init
 */

void test_fsm_INIT_TT_IS_VALID_NULL(void)
{   fsm_trans_t tt[] = {
        {0, check_func, 1, do_nothing},
        {-1, check_func, 2, do_nothing},
        {-1, NULL, -1, NULL},
    };

    fsm_t* f = (fsm_t*) malloc (sizeof (fsm_t));

    int size = sizeof(tt)/sizeof(tt[0]);

    TEST_ASSERT_EQUAL (false, fsm_init(f,tt,size,2));

}

/**
 * @brief t_10 La última transición es la inválida -fsm_init
 */

void test_fsm_INIT_LAST_TT_IS_INVALID(void)
{   fsm_trans_t tt[] = {
        {0, check_func, 1, do_nothing},
        {1, check_func, 2, do_nothing},
        {-1, NULL, -1, NULL},
    };

    fsm_t* f = (fsm_t*) malloc (sizeof (fsm_t));

    int size = sizeof(tt)/sizeof(tt[0]);

    TEST_ASSERT_EQUAL (true, fsm_init(f,tt,size,2));

}

/**
 * @brief t_11 Todos los estados son naturales e inferiores al estado máximo (no iguales) -fsm_init
 */
void test_fsm_INIT_VALID_STATES(void)
{   fsm_trans_t tt[] = {
        {0, check_func, 1, do_nothing},
        {1, check_func, 2, do_nothing},
        {-1, NULL, -1, NULL},
    };

    fsm_t* f = (fsm_t*) malloc (sizeof (fsm_t));

    int size = sizeof(tt)/sizeof(tt[0]);

    TEST_ASSERT_EQUAL (true, fsm_init(f,tt,size,2));

}



/**
 * @brief t_12 Si para una transición a comprobar tiene una función de guarda NULL, se cumple siempre. -fsm_fire
 */
void test_fsm_FIRE_IN_NULL(void)
{   fsm_trans_t tt[] = {
        {0, NULL, 1, do_nothing},
        {1, check_func, 2, do_nothing},
        {-1, NULL, -1, NULL},
    };

    do_nothing_ExpectAnyArgs();
    
    fsm_t *f = (fsm_t*)1;

    int size = sizeof(tt)/sizeof(tt[0]);

    f = fsm_new(tt, size, 2); 

    fsm_fire(f);

    TEST_ASSERT_EQUAL (1,f->current_state );

    fsm_destroy(f);

}


/**
 * @brief t_13 Si para una transición a comprobar tiene una función de guarda, se ejecuta la función y si devuelve 
 *        distinto de 0, se cumple. -fsm_fire
 */

void test_fsm_FIRE_IN_VALID(void)
{   fsm_trans_t tt[] = {
        {0, check_func, 1, do_nothing},
        {1, check_func, 2, do_nothing},
        {-1, NULL, -1, NULL},
    };

    check_func_ExpectAnyArgsAndReturn(1);
    do_nothing_ExpectAnyArgs();
    
    fsm_t *f = (fsm_t*)1;

    int size = sizeof(tt)/sizeof(tt[0]);

    f = fsm_new(tt, size, 2); 

    fsm_fire(f);

    TEST_ASSERT_EQUAL (1,f->current_state );

    fsm_destroy(f);
}

/**
 * t_14 Si se cumple, se cambia el estado actual al de destino, no se comprueban 
 *      más transiciones y se ejecuta la función de actualización, si es distinto de NULL y devuelve 1.
 */
void test_fsm_FIRE_VALID_T(void)
{   fsm_trans_t tt[] = {
        {0, check_func, 1, do_nothing},
        {1, check_func, 2, do_nothing},
        {-1, NULL, -1, NULL},
    };

    check_func_ExpectAnyArgsAndReturn(1);
    do_nothing_ExpectAnyArgs();
    
    fsm_t *f = (fsm_t*)1;

    int size = sizeof(tt)/sizeof(tt[0]);

    f = fsm_new(tt, size, 2); 

    TEST_ASSERT_EQUAL(1, fsm_fire(f));

    TEST_ASSERT_EQUAL (1,f->current_state );

    fsm_destroy(f);

}

/**
 *  t_15 Si ninguna transición tiene un estado de origen coincidente con el estado actual, la función de
 * comprobación de transiciones devuelve -1. -fsm_fire
 */
void test_fsm_ORIG_STATE_NOT_EQUAL_CURRENT_STATE(void)
{
    fsm_trans_t tt[] = {
        {0, check_func, 1, do_nothing},
        {1, check_func, 2, do_nothing},
        {-1, NULL, -1, NULL},
    };

    check_func_ExpectAnyArgsAndReturn(0);
    check_func_ExpectAnyArgsAndReturn(0);

    fsm_t *f = (fsm_t*)1;

    int size = sizeof(tt)/sizeof(tt[0]);

    f = fsm_new(tt, size, 2);

    f->current_state = 3; 

    TEST_ASSERT_EQUAL (-1, fsm_fire(f));

    fsm_destroy(f);
}

/**
 * @brief t_16 Si hay transiciones pero no se cumplen las condiciones,devuelve 0 -fsm_fire
 */
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





/**
 * \cond
 *t_ La tabla de transiciones no es NULL -fsm_new

void test_fsm_new_nullWhenNullTransition(void)
{
    fsm_t *f = (fsm_t*)1;

    f = fsm_new(NULL,0,-1);

    TEST_ASSERT_EQUAL (NULL, f);
}
 *
 *
 *t_
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

    f = fsm_new(tt, size, 2);

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

// fsm_fire
void test_fsm_INPUT_FUNC_VALID_T(void)
{
    fsm_trans_t tt[] = {
        {0, check_func, 1, do_nothing},
        {1, check_func, 2, do_nothing},
        {-1, NULL, -1, NULL},
    };

    check_func_ExpectAnyArgsAndReturn(1);
    do_nothing_ExpectAnyArgs();
    
    fsm_t *f = (fsm_t*)1;

    int size = sizeof(tt)/sizeof(tt[0]);

    f = fsm_new(tt, size, 2);

    TEST_ASSERT_EQUAL (1, fsm_fire(f));

    fsm_destroy(f);
}


// t_ -fsm_new
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
* \endcond
*/

