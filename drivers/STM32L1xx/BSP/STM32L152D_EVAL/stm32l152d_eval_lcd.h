/**
  ******************************************************************************
  * @file    stm32l152d_eval_lcd.h
  * @author  MCD Application Team
  * @brief   This file contains the common defines and functions prototypes for
  *          the stm32l152d_eval_lcd.c driver.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */ 

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32L152D_EVAL
  * @{
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L152D_EVAL_LCD_H
#define __STM32L152D_EVAL_LCD_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32l152d_eval.h" 
#include "../Components/hx8347d/hx8347d.h"
#include "../Components/spfd5408/spfd5408.h"
#include "../Components/ili9320/ili9320.h"
#include "../Components/ili9325/ili9325.h"
#include "../../../Utilities/Fonts/fonts.h"

/** @addtogroup STM32L152D_EVAL_LCD
  * @{
  */ 


/** @defgroup STM32L152D_EVAL_LCD_Exported_Types Exported Types
  * @{
  */
typedef struct 
{ 
  uint32_t TextColor;
  uint32_t BackColor;
  sFONT    *pFont; 

}LCD_DrawPropTypeDef;
/**
  * @}
  */ 

/** @defgroup STM32L152D_EVAL_LCD_Exported_Constants Exported Constants
  * @{
  */
/** 
  * @brief  LCD status structure definition  
  */     
#define LCD_OK         0x00
#define LCD_ERROR      0x01
#define LCD_TIMEOUT    0x02
    
typedef struct 
{
  int16_t X;
  int16_t Y;

}Point, * pPoint; 

/** 
  * @brief  Line mode structures definition
  */ 
typedef enum
{
  CENTER_MODE             = 0x01,    /*!< Center mode */
  RIGHT_MODE              = 0x02,    /*!< Right mode  */
  LEFT_MODE               = 0x03     /*!< Left mode   */

}Line_ModeTypdef;

/** 
  * @brief  LCD color  
  */ 
#define LCD_COLOR_BLUE          (uint16_t)0x001F
#define LCD_COLOR_GREEN         (uint16_t)0x07E0
#define LCD_COLOR_RED           (uint16_t)0xF800
#define LCD_COLOR_CYAN          (uint16_t)0x07FF
#define LCD_COLOR_MAGENTA       (uint16_t)0xF81F
#define LCD_COLOR_YELLOW        (uint16_t)0xFFE0
#define LCD_COLOR_LIGHTBLUE     (uint16_t)0x841F
#define LCD_COLOR_LIGHTGREEN    (uint16_t)0x87F0
#define LCD_COLOR_LIGHTRED      (uint16_t)0xFC10
#define LCD_COLOR_LIGHTCYAN     (uint16_t)0x87FF
#define LCD_COLOR_LIGHTMAGENTA  (uint16_t)0xFC1F
#define LCD_COLOR_LIGHTYELLOW   (uint16_t)0xFFF0
#define LCD_COLOR_DARKBLUE      (uint16_t)0x0010
#define LCD_COLOR_DARKGREEN     (uint16_t)0x0400
#define LCD_COLOR_DARKRED       (uint16_t)0x8000
#define LCD_COLOR_DARKCYAN      (uint16_t)0x0410
#define LCD_COLOR_DARKMAGENTA   (uint16_t)0x8010
#define LCD_COLOR_DARKYELLOW    (uint16_t)0x8400
#define LCD_COLOR_WHITE         (uint16_t)0xFFFF
#define LCD_COLOR_LIGHTGRAY     (uint16_t)0xD69A
#define LCD_COLOR_GRAY          (uint16_t)0x8410
#define LCD_COLOR_DARKGRAY      (uint16_t)0x4208
#define LCD_COLOR_BLACK         (uint16_t)0x0000
#define LCD_COLOR_BROWN         (uint16_t)0xA145
#define LCD_COLOR_ORANGE        (uint16_t)0xFD20

/** 
  * @brief LCD default font 
  */ 
#define LCD_DEFAULT_FONT         Font24

/**
  * @}
  */

/** @addtogroup STM32L152D_EVAL_LCD_Exported_Functions
  * @{
  */

uint8_t  BSP_LCD_Init(void);
uint32_t BSP_LCD_GetXSize(void);
uint32_t BSP_LCD_GetYSize(void);
 
uint16_t BSP_LCD_GetTextColor(void);
uint16_t BSP_LCD_GetBackColor(void);
void     BSP_LCD_SetTextColor(__IO uint16_t Color);
void     BSP_LCD_SetBackColor(__IO uint16_t Color);
void     BSP_LCD_SetFont(sFONT *fonts);
sFONT    *BSP_LCD_GetFont(void);

void     BSP_LCD_Clear(uint16_t Color);
void     BSP_LCD_ClearStringLine(uint16_t Line);
void     BSP_LCD_DisplayStringAtLine(uint16_t Line, uint8_t *ptr);
void     BSP_LCD_DisplayStringAt(uint16_t Xpos, uint16_t Ypos, uint8_t *Text, Line_ModeTypdef Mode);
void     BSP_LCD_DisplayChar(uint16_t Xpos, uint16_t Ypos, uint8_t Ascii);

uint16_t BSP_LCD_ReadPixel(uint16_t Xpos, uint16_t Ypos);
void     BSP_LCD_DrawPixel(uint16_t Xpos, uint16_t Ypos, uint16_t RGB_Code);
void     BSP_LCD_DrawHLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length);
void     BSP_LCD_DrawVLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length);
void     BSP_LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void     BSP_LCD_DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void     BSP_LCD_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);
void     BSP_LCD_DrawPolygon(pPoint Points, uint16_t PointCount);
void     BSP_LCD_FillTriangle(uint16_t X1, uint16_t X2, uint16_t X3, uint16_t Y1, uint16_t Y2, uint16_t Y3);
void     BSP_LCD_FillPolygon(pPoint Points, uint16_t PointCount);
void     BSP_LCD_DrawEllipse(int Xpos, int Ypos, int XRadius, int YRadius);
void     BSP_LCD_DrawBitmap(uint16_t Xpos, uint16_t Ypos, uint8_t *pbmp);
void     BSP_LCD_DrawRGBImage(uint16_t Xpos, uint16_t Ypos, uint16_t Xsize, uint16_t Ysize, uint8_t *pbmp);
void     BSP_LCD_FillRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void     BSP_LCD_FillCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);
void     BSP_LCD_FillEllipse(int Xpos, int Ypos, int XRadius, int YRadius);

void     BSP_LCD_DisplayOff(void);
void     BSP_LCD_DisplayOn(void);

/**
  * @}
  */

/**
  * @}
  */ 

#ifdef __cplusplus
}
#endif

#endif /* __STM32L152D_EVAL_LCD_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
