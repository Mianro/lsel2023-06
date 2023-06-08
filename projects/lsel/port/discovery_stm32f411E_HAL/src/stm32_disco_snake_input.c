#include "snake_input.h"

#include "stm32f4xx.h"

#include "stm32f4xx_hal_conf.h"

#include "stm32f4xx_hal.h"

#define BUTTON_PORT	GPIOA
#define BUTTON_PIN	0

static void EXTILine0_Config(void);



static int button_flag;
static int button_heading;

int
snake_input_init(snake_game_t* p_game)
{


  button_flag = 0;
  button_heading = UP;

  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;

  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* Configure EXTI Line0 (connected to PA0 pin) in interrupt mode */
  EXTILine0_Config();
 

  return 1;
}


void
snake_input_set_flag ()
{
  button_flag = 1;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == 1)
  {
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

  if (button_flag) {
      /* TODO */
      if (button_heading == LEFT) {
         button_heading = DOWN; 
         p_game->new_heading = DOWN;
      } else if (button_heading == DOWN) {
        button_heading = RIGHT;
        p_game->new_heading = RIGHT;
      } else if (button_heading == RIGHT) {
        button_heading = UP;
        p_game->new_heading = UP;
      } else if (button_heading == UP) {
        button_heading = LEFT;
        p_game->new_heading = LEFT;
      }
    button_flag = 0;
    }
}

void
snake_input_close(snake_game_t* p_game)
{
  button_flag = 0;
}

void EXTILine0_Config(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;

  /* Enable GPIOA clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  
  /* Configure PA0 pin as input floating */
  GPIO_InitStructure.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStructure.Pull = GPIO_NOPULL;
  GPIO_InitStructure.Pin = GPIO_PIN_0;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Enable and set EXTI Line0 Interrupt to the lowest priority */
  HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}