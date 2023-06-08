#include "snake_input.h"

#include "stm32f4xx.h"

#include "stm32f4xx_hal_conf.h"

#include "stm32f4xx_hal.h"

#include "lsm303dlhc.h"
#include "lsm303agr.h"

#define BUTTON_PORT	GPIOA
#define BUTTON_PIN	0

static void EXTILine0_Config(void);

typedef enum
{
  ACCELERO_OK = 0,
  ACCELERO_ERROR = 1,
  ACCELERO_TIMEOUT = 2
}ACCELERO_StatusTypeDef;


/* Accelerometer functions */
uint8_t BSP_ACCELERO_Init(void);
void    BSP_ACCELERO_Reset(void);
void    BSP_ACCELERO_Click_ITConfig(void);
void    BSP_ACCELERO_GetXYZ(int16_t *pDataXYZ);

static int button_flag;
static int button_heading;
static int16_t acceleroData[3]; // Array to store XYZ acceleration values


int
snake_input_init(snake_game_t* p_game)
{

  BSP_ACCELERO_Init(); 

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
  BSP_ACCELERO_GetXYZ(acceleroData);
  int data_x = 0;
  data_x = acceleroData[0];

  if (data_x > 30000){
    button_flag =1; 
  } 
  
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

static ACCELERO_DrvTypeDef *AccelerometerDrv;
/**
  * @}
  */

/** @defgroup STM32F411E_DISCOVERY_ACCELEROMETER_Private_FunctionPrototypes STM32F411E DISCOVERY ACCELEROMETER Private FunctionPrototypes
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32F411E_DISCOVERY_ACCELEROMETER_Private_Functions STM32F411E DISCOVERY ACCELEROMETER Private Functions
  * @{
  */

/**
  * @brief  Set accelerometer Initialization.
  * @retval ACCELERO_OK if no problem during initialization
  */
uint8_t BSP_ACCELERO_Init(void)
{
  uint8_t ret = ACCELERO_ERROR;
  uint16_t ctrl = 0x0000;
  ACCELERO_InitTypeDef         Accelero_InitStructure;
  ACCELERO_FilterConfigTypeDef Accelero_FilterStructure = {0,0,0,0};

  if(Lsm303dlhcDrv.ReadID() == I_AM_LMS303DLHC)
  {
    /* Initialize the accelerometer driver structure */
    AccelerometerDrv = &Lsm303dlhcDrv;

    /* MEMS configuration ----------------------------------------------------*/
    /* Fill the accelerometer structure */
    Accelero_InitStructure.Power_Mode         = LSM303DLHC_NORMAL_MODE;
    Accelero_InitStructure.AccOutput_DataRate = LSM303DLHC_ODR_50_HZ;
    Accelero_InitStructure.Axes_Enable        = LSM303DLHC_AXES_ENABLE;
    Accelero_InitStructure.AccFull_Scale      = LSM303DLHC_FULLSCALE_2G;
    Accelero_InitStructure.BlockData_Update   = LSM303DLHC_BlockUpdate_Continous;
    Accelero_InitStructure.Endianness         = LSM303DLHC_BLE_LSB;
    Accelero_InitStructure.High_Resolution    = LSM303DLHC_HR_ENABLE;

    /* Configure MEMS: data rate, power mode, full scale and axes */
    ctrl |= (Accelero_InitStructure.Power_Mode | Accelero_InitStructure.AccOutput_DataRate | \
             Accelero_InitStructure.Axes_Enable);

    ctrl |= ((Accelero_InitStructure.BlockData_Update | Accelero_InitStructure.Endianness | \
              Accelero_InitStructure.AccFull_Scale    | Accelero_InitStructure.High_Resolution) << 8);

    /* Configure the accelerometer main parameters */
    AccelerometerDrv->Init(ctrl);

    /* Fill the accelerometer LPF structure */
    Accelero_FilterStructure.HighPassFilter_Mode_Selection   = LSM303DLHC_HPM_NORMAL_MODE;
    Accelero_FilterStructure.HighPassFilter_CutOff_Frequency = LSM303DLHC_HPFCF_16;
    Accelero_FilterStructure.HighPassFilter_AOI1             = LSM303DLHC_HPF_AOI1_DISABLE;
    Accelero_FilterStructure.HighPassFilter_AOI2             = LSM303DLHC_HPF_AOI2_DISABLE;

    /* Configure MEMS: mode, cutoff frquency, Filter status, Click, AOI1 and AOI2 */
    ctrl = (uint8_t) (Accelero_FilterStructure.HighPassFilter_Mode_Selection   |\
                      Accelero_FilterStructure.HighPassFilter_CutOff_Frequency |\
                      Accelero_FilterStructure.HighPassFilter_AOI1             |\
                      Accelero_FilterStructure.HighPassFilter_AOI2);

    /* Configure the accelerometer LPF main parameters */
    AccelerometerDrv->FilterConfig(ctrl);

    ret = ACCELERO_OK;
  }
  else if(Lsm303agrDrv.ReadID() == I_AM_LSM303AGR)
  {
    /* Initialize the accelerometer driver structure */
    AccelerometerDrv = &Lsm303agrDrv;

    /* MEMS configuration ----------------------------------------------------*/
    /* Fill the accelerometer structure */
    Accelero_InitStructure.Power_Mode         = LSM303AGR_NORMAL_MODE;
    Accelero_InitStructure.AccOutput_DataRate = LSM303AGR_ODR_50_HZ;
    Accelero_InitStructure.Axes_Enable        = LSM303AGR_AXES_ENABLE;
    Accelero_InitStructure.AccFull_Scale      = LSM303AGR_FULLSCALE_2G;
    Accelero_InitStructure.BlockData_Update   = LSM303AGR_BlockUpdate_Continous;
    Accelero_InitStructure.Endianness         = LSM303AGR_BLE_LSB;
    Accelero_InitStructure.High_Resolution    = LSM303AGR_HR_ENABLE;

    /* Configure MEMS: data rate, power mode, full scale and axes */
    ctrl |= (Accelero_InitStructure.Power_Mode | Accelero_InitStructure.AccOutput_DataRate | \
             Accelero_InitStructure.Axes_Enable);

    ctrl |= ((Accelero_InitStructure.BlockData_Update | Accelero_InitStructure.Endianness | \
              Accelero_InitStructure.AccFull_Scale    | Accelero_InitStructure.High_Resolution) << 8);

    /* Configure the accelerometer main parameters */
    AccelerometerDrv->Init(ctrl);

    /* Fill the accelerometer LPF structure */
    Accelero_FilterStructure.HighPassFilter_Mode_Selection   = LSM303AGR_HPM_NORMAL_MODE;
    Accelero_FilterStructure.HighPassFilter_CutOff_Frequency = LSM303AGR_HPFCF_16;
    Accelero_FilterStructure.HighPassFilter_AOI1             = LSM303AGR_HPF_AOI1_DISABLE;
    Accelero_FilterStructure.HighPassFilter_AOI2             = LSM303AGR_HPF_AOI2_DISABLE;

    /* Configure MEMS: mode, cutoff frquency, Filter status, Click, AOI1 and AOI2 */
    ctrl = (uint8_t) (Accelero_FilterStructure.HighPassFilter_Mode_Selection   |\
                      Accelero_FilterStructure.HighPassFilter_CutOff_Frequency |\
                      Accelero_FilterStructure.HighPassFilter_AOI1             |\
                      Accelero_FilterStructure.HighPassFilter_AOI2);

    /* Configure the accelerometer LPF main parameters */
    AccelerometerDrv->FilterConfig(ctrl);

    ret = ACCELERO_OK;
  }

  return ret;
}

/**
  * @brief  Reboot memory content of Accelerometer.
  */
void BSP_ACCELERO_Reset(void)
{
  if(AccelerometerDrv->Reset != NULL)
  {
    AccelerometerDrv->Reset();
  }
}

/**
  * @brief  Configure accelerometer click IT.
  */
void BSP_ACCELERO_Click_ITConfig(void)
{
  if(AccelerometerDrv->ConfigIT!= NULL)
  {
    AccelerometerDrv->ConfigIT();
  }
}

/**
  * @brief  Get XYZ axes acceleration.
  * @param  pDataXYZ: Pointer to 3 angular acceleration axes.
  *                   pDataXYZ[0] = X axis, pDataXYZ[1] = Y axis, pDataXYZ[2] = Z axis
  */
void BSP_ACCELERO_GetXYZ(int16_t *pDataXYZ)
{
  int16_t SwitchXY = 0;

  if(AccelerometerDrv->GetXYZ!= NULL)
  {
    AccelerometerDrv->GetXYZ(pDataXYZ);

    /* Switch X and Y Axes in case of LSM303DLHC MEMS */
    if(AccelerometerDrv == &Lsm303dlhcDrv)
    {
      SwitchXY  = pDataXYZ[0];
      pDataXYZ[0] = pDataXYZ[1];

      /* Invert Y Axis to be conpliant with LIS3DSH */
      pDataXYZ[1] = -SwitchXY;
    }
  }
}