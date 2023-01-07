/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    can.h
 * @brief   This file contains all the function prototypes for
 *          the can.c file
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CAN_H__
#define __CAN_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

  /* USER CODE BEGIN Includes */
  /**
   * CAN PINS ARE MAPPED AS FOLLOWS:
   * PA11 - RX PIN[D10]
   * PA12 - TX PIN[D2]
   **/
  /* USER CODE END Includes */

  extern CAN_HandleTypeDef hcan1;

/* USER CODE BEGIN Private defines */
#define CAN_HIGH_SPEED_MODE 1
#define CAN_LOW_SPEED_MODE 2
/**
 * @brief: CAN_SPEED_MODE
 * @param 1 : Can mode is set to HIGH SPEED
 * @param 2 : Can mode is set to LOW SPEED
 **/
#define CAN_SPEED_MODE CAN_HIGH_SPEED_MODE

#define CAN_MODE CAN_MODE_NORMAL

#define CAN_HIGH_SPEED_PRESCALER 8
#define CAN_LOW_SPEED_PRESCALER 16

#define RESULT_FAILED 0
#define RESULT_SUCCESS 1

/* Specified id for extended frame type */
#define SPECIFIED_EXTENDED_ID 0x18065

/* Specified id for standard frame type */
#define SPECIFIED_STANDARD_ID 0x300

  /* USER CODE END Private defines */

  void MX_CAN1_Init();

  /* USER CODE BEGIN Prototypes */
  typedef struct CanDataFrameInit
  {
    uint8_t tx_data[8];
    CAN_TxHeaderTypeDef tx_header;
    CAN_RxHeaderTypeDef rx_header;
    uint8_t rx_data[8];
  } CanDataFrameInit;

  void CanInit();
  void CanConfigFilter(uint8_t can_filter_bank);

  int CanSendExtendedIdMessage(uint32_t FrameId, uint8_t DLC,
                               uint8_t byte0, uint8_t byte1, uint8_t byte2, uint8_t byte3,
                               uint8_t byte4, uint8_t byte5, uint8_t byte6, uint8_t byte7);

  int CanSendStandardIdMessage(uint32_t FrameId, uint8_t DLC,
                               uint8_t byte0, uint8_t byte1, uint8_t byte2, uint8_t byte3,
                               uint8_t byte4, uint8_t byte5, uint8_t byte6, uint8_t byte7);

  int CanReceiveData(CanDataFrameInit *);
  void CanClearRxDataFrame(CanDataFrameInit *);
  void ValidateStandardFrame(CanDataFrameInit *frame);
  void ValidateExtendedFrame(CanDataFrameInit *frame);
  /* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __CAN_H__ */
