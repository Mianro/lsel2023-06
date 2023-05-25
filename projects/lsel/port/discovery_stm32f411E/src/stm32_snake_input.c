#include "snake_input.h"

#include "stm32f4xx.h"

#include "stm32f4xx_hal.h"

#define BUTTON_PORT	GPIOA
#define BUTTON_PIN	0


static int button_flag;
static int button_heading;

int
snake_input_init(snake_game_t* p_game)
{

#define MODER_MASK (0x03 << BUTTON_PIN * 2) /* Cada pin ocupa 2 bits */
#define PUPDR_MASK (0x03 << BUTTON_PIN * 2)  /* Cada pin ocupa 2 bits */
#define AFR_MASK (0x0F << ((BUTTON_PIN%8) * 4))  /* Cada pin ocupa 4 bits */
#define EXTICR_MASK (0x0F << ((BUTTON_PIN%4) * 4))  /* Cada pin ocupa 4 bits */

#define MODER_AS_INPUT (0x00 << BUTTON_PIN * 2)       /* Cada pin ocupa 2 bits */
#define PUPDR_AS_NOPUPD (0x00 << BUTTON_PIN * 2) /* Cada pin ocupa 2 bits */
#define AFR_AS_GPIO (0x00 << ((BUTTON_PIN%8) * 4))  /* Cada pin ocupa 4 bits */
#define EXTICR_AS_BUTTON (0x02 << ((BUTTON_PIN%4) * 4))  /* Cada pin ocupa 4 bits */

#define IDR_MASK (0x01 << 13) /* Cada pin ocupa 1 bit */


  button_flag = 0;
  button_heading = UP;

  BUTTON_PORT->MODER &= MODER_MASK;
  BUTTON_PORT->MODER |= MODER_AS_INPUT;

  BUTTON_PORT->PUPDR &= PUPDR_MASK;
  BUTTON_PORT->PUPDR |= PUPDR_AS_NOPUPD;
  
  BUTTON_PORT->AFR[BUTTON_PIN/8] &= AFR_MASK;
  BUTTON_PORT->AFR[BUTTON_PIN/8] |= AFR_AS_GPIO;

  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
  SYSCFG->EXTICR[BUTTON_PIN/4] = (SYSCFG->EXTICR[BUTTON_PIN/4]&EXTICR_MASK) | EXTICR_AS_BUTTON;

  EXTI->FTSR |=   1 << BUTTON_PIN;
  EXTI->RTSR &= ~(1 << BUTTON_PIN);
  EXTI->EMR  &= ~(1 << BUTTON_PIN);
  EXTI->IMR  |=   1 << BUTTON_PIN;
  EXTI->PR   |=   1 << BUTTON_PIN;

  NVIC_SetPriority(EXTI0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
  NVIC_EnableIRQ(EXTI0_IRQn);

  return 1;
}

void
snake_input_set_flag ()
{
  button_flag = 1;
}

void
EXTI0_IRQHandler(void)
{
  if (EXTI->PR & (1 << BUTTON_PIN)) {
    EXTI->PR |= 1 << BUTTON_PIN;
    snake_input_set_flag();
  }
}

void
snake_input_update_new_heading (snake_game_t* p_game)
{
    p_game->new_heading = p_game->snake.heading;
    /* Global variable button_heading indicates last heading value of button */
    /* Change: every USER button pressed, change button_heading COUNTERCLOCKWISE: */
    /* From LEFT to DOWN */
    /* From DOWN to RIGHT */
    /* From RIGHT to UP */
    /* From UP to LEFT */
  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)){
    button_flag = 1; 
  }

  if (button_flag) {
      /* TODO */
      if (button_heading == LEFT) {
         button_heading = UP; 
         p_game->new_heading = UP;
      } else if (button_heading == DOWN) {
        button_heading = RIGHT;
        p_game->new_heading = RIGHT;
      } else if (button_heading == RIGHT) {
        button_heading = DOWN;
        p_game->new_heading = DOWN;
      } else if (button_heading == UP) {
        button_heading = LEFT;
        p_game->new_heading = LEFT;
      }
    }
}

void
snake_input_close(snake_game_t* p_game)
{
  EXTI->IMR &= (1 << BUTTON_PIN);
  button_flag = 0;
}

