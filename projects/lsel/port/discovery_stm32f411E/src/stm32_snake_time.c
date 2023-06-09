#include "snake_time.h"

#include "stm32f4xx.h"

//#include "stm32f4xx_hal_conf.h"

#define NVIC_PRIORITY_GROUP_0	((uint32_t)0x00000007)	/*!< 0 bits for pre-emption priority, 4 for sub-priority*/
#define NVIC_PRIORITY_GROUP_4	((uint32_t)0x00000003)	/*!< 4 bits for pre-emption priority, 0 for sub-priority*/

#define POWER_REGULATOR_VOLTAGE_SCALE3 	0x01
#define RCC_HSI_CALIBRATION_DEFAULT	0x10U
#define TICK_FREQ_1KHZ			1U


#define HSI_VALUE ((uint32_t)16000000) /*!< Value of the Internal oscillator in Hz */

/* GLOBAL VARIABLES */
static uint32_t msTicks = 0; /*!< Variable to store millisecond ticks */

/* These variables are declared extern in CMSIS (system_stm32f4xx.h) */
uint32_t SystemCoreClock = HSI_VALUE;                                               /*!< Frequency of the System clock */
const uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9}; /*!< Prescaler values for AHB bus */
const uint8_t APBPrescTable[8] = {0, 0, 0, 0, 1, 2, 3, 4};                          /*!< Prescaler values for APB bus */

//------------------------------------------------------
// SYSTEM CONFIGURATION
//------------------------------------------------------
/**
 * @brief  Setup the microcontroller system
 *         Initialize the FPU setting, vector table location and External memory
 *         configuration.
 *
 * @note   This function is called at startup by CMSIS in startup_stm32f446xx.s.
 */
void SystemInit(void)
{
/* FPU settings ------------------------------------------------------------*/
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
  SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2)); /* set CP10 and CP11 Full Access */
#endif

#if defined(DATA_IN_ExtSRAM) || defined(DATA_IN_ExtSDRAM)
  SystemInit_ExtMemCtl();
#endif /* DATA_IN_ExtSRAM || DATA_IN_ExtSDRAM */

  /* Configure the Vector Table location -------------------------------------*/
#if defined(USER_VECT_TAB_ADDRESS)
  SCB->VTOR = VECT_TAB_BASE_ADDRESS | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM */
#endif                                                 /* USER_VECT_TAB_ADDRESS */
}

/**
 * @brief System Clock Configuration
 *
 * @attention This function should NOT be accesible from the outside to avoid configuration problems.
 * @note This function starts a system timer that generates a SysTick every 1 ms.
 * @retval None
 */
static void system_clock_config(void)
{
  /** Configure the main internal regulator output voltage */
  /* Power controller (PWR) */
  /* Control the main internal voltage regulator output voltage to achieve a trade-off between performance and power consumption when the device does not operate at the maximum frequency */
  PWR->CR &= ~PWR_CR_VOS; // Clean and set value
  PWR->CR |= (PWR_CR_VOS & (POWER_REGULATOR_VOLTAGE_SCALE3 << PWR_CR_VOS_Pos));

  /* Initializes the RCC Oscillators. */
  /* Adjusts the Internal High Speed oscillator (HSI) calibration value.*/
  RCC->CR &= ~RCC_CR_HSITRIM; // Clean and set value
  RCC->CR |= (RCC_CR_HSITRIM & (RCC_HSI_CALIBRATION_DEFAULT << RCC_CR_HSITRIM_Pos));

  /* RCC Clock Config */
  /* Initializes the CPU, AHB and APB buses clocks */
  /* To correctly read data from FLASH memory, the number of wait states (LATENCY)
      must be correctly programmed according to the frequency of the CPU clock
      (HCLK) and the supply voltage of the device. */

  /* Increasing the number of wait states because of higher CPU frequency */
  FLASH->ACR = FLASH_ACR_LATENCY_2WS; /* Program the new number of wait states to the LATENCY bits in the FLASH_ACR register */

  /* Change in clock source is performed in 16 clock cycles after writing to CFGR */
  RCC->CFGR &= ~RCC_CFGR_SW; // Clean and set value
  RCC->CFGR |= (RCC_CFGR_SW & (RCC_CFGR_SW_HSI << RCC_CFGR_SW_Pos));

  /* Update the SystemCoreClock global variable */
  SystemCoreClock = HSI_VALUE >> AHBPrescTable[(RCC->CFGR & RCC_CFGR_HPRE) >> RCC_CFGR_HPRE_Pos];

  /* Configure the source of time base considering new system clocks settings */
  SysTick_Config(SystemCoreClock / (1000U / TICK_FREQ_1KHZ)); /* Set Systick to 1 ms */
}

int _stm32_init()
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  /* Configure Flash prefetch, Instruction cache, Data cache */
  /* Instruction cache enable */
  FLASH->ACR |= FLASH_ACR_ICEN;

  /* Data cache enable */
  FLASH->ACR |= FLASH_ACR_DCEN;

  /* Prefetch cache enable */
  FLASH->ACR |= FLASH_ACR_PRFTEN;

  /* Set Interrupt Group Priority */
  NVIC_SetPriorityGrouping(NVIC_PRIORITY_GROUP_4);

  /* Use systick as time base source and configure 1ms tick (default clock after Reset is HSI) */
  /* Configure the SysTick IRQ priority. It must be the highest (lower number: 0)*/
  NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0U, 0U)); /* Tick interrupt priority */

  /* Init the low level hardware */
  /* Reset and clock control (RCC) */
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; /* Syscfg clock enabling */

  /* Peripheral clock enable register */
  RCC->APB1ENR |= RCC_APB1ENR_PWREN; /* PWREN: Power interface clock enable */

  /* Configure the system clock */
  system_clock_config();

  return 0;
}

//------------------------------------------------------
// INTERRUPT SERVICE ROUTINES
//------------------------------------------------------
/**
 * @brief This function handles the System tick timer that increments the system millisecond counter (global variable).
 *
 * > ✅ 1. **Increment the System tick counter `msTicks` in 1 count.** \n
 * > &nbsp;&nbsp;&nbsp;&nbsp;💡 `msTicks` is a global `static` variable declared in @link port_system.c @endlink. \n
 *
 */
void SysTick_Handler(void)
{
  /* TODO Update global tick variable */
  msTicks++;
}
	
	
int 
snake_time_init (snake_game_t* p_game) 
{
  _stm32_init();
  return 1;
}

uint32_t
snake_time_get_ms()
{
  return msTicks;
}

void 
snake_time_delay_until_ms(uint32_t *p_t, uint32_t ms)
{
  /* TODO Wait until the difference between current time and t is greater or equal than ms */
  uint32_t pt = *p_t;
  uint32_t snake_time = snake_time_get_ms();
  uint32_t total_delay = pt + ms;

    while (snake_time < total_delay)
  {
    snake_time = snake_time_get_ms();
  }

  /* Update next tick */
  *p_t += ms;
}

void 
snake_time_close () 
{
}

void 
snake_time_delay_ms (uint32_t ms) 
{
  /* TODO Implement with snake_time_delay_until */
  uint32_t current_ms = snake_time_get_ms();
  uint32_t target_ms = 0;
  target_ms = ms;

  snake_time_delay_until_ms(&current_ms, target_ms);
}