/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
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
/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */
CanDataFrameInit can_frame_template;
CAN_FilterTypeDef can_filter_template;

uint32_t can_tx_mailbox;
/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;

/* CAN1 init function */
void MX_CAN1_Init()
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */
  if (CAN_SPEED_MODE == CAN_HIGH_SPEED_MODE) 
  {
    hcan1.Init.Prescaler = CAN_HIGH_SPEED_PRESCALER;
  } else if(CAN_SPEED_MODE == CAN_LOW_SPEED_MODE)
  {
    hcan1.Init.Prescaler = CAN_LOW_SPEED_PRESCALER;
  } else 
  {
    Error_Handler();
  }
  hcan1.Init.Mode = CAN_MODE;
  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  // hcan1.Init.Prescaler = 16;
  // hcan1.Init.Mode = CAN_MODE_LOOPBACK;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_13TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/**
 * @brief: Initialize CAN network
 *
 **/
void CanInit() {
	if (HAL_CAN_Start(&hcan1) != HAL_OK) {
		Error_Handler();
	}

	if (HAL_CAN_ActivateNotification(&hcan1,
	CAN_IT_RX_FIFO0_MSG_PENDING | CAN_IT_TX_MAILBOX_EMPTY) != HAL_OK) {
		Error_Handler();
	}
}
/**
 * @brief: configure can data frames hardware filter
 * @param can_filter_bank: Specific filter bank from 0-13
 *
 **/
void CanConfigFilter(uint8_t can_filter_bank){
	can_filter_template.FilterBank = can_filter_bank;
	can_filter_template.FilterMode = CAN_FILTERMODE_IDMASK;
	can_filter_template.FilterScale = CAN_FILTERSCALE_32BIT;
	can_filter_template.FilterIdHigh = 0x0000;
	can_filter_template.FilterIdLow = 0x0000;
	can_filter_template.FilterMaskIdHigh = 0x0000;
	can_filter_template.FilterMaskIdLow = 0x0000;
	can_filter_template.FilterFIFOAssignment = CAN_RX_FIFO0;
	can_filter_template.FilterActivation = ENABLE;
	can_filter_template.SlaveStartFilterBank = 14;

	if (HAL_CAN_ConfigFilter(&hcan1, &can_filter_template) != HAL_OK) {
		Error_Handler();
	}

}
/**
 * @brief: clearing frame of TX data
 *
 **/
void CanClearTxDataFrame() {
	can_frame_template.tx_header.StdId = 0x00;
	can_frame_template.tx_header.RTR = CAN_RTR_DATA;
	can_frame_template.tx_header.IDE = CAN_ID_STD;
	can_frame_template.tx_header.DLC = 0;
	can_frame_template.tx_header.TransmitGlobalTime = DISABLE;
	can_frame_template.tx_data[0] = 0x0;
	can_frame_template.tx_data[1] = 0x0;
	can_frame_template.tx_data[2] = 0x0;
	can_frame_template.tx_data[3] = 0x0;
	can_frame_template.tx_data[4] = 0x0;
	can_frame_template.tx_data[5] = 0x0;
	can_frame_template.tx_data[6] = 0x0;
	can_frame_template.tx_data[7] = 0x0;
}


void CanClearRxDataFrame() {
	can_frame_template.rx_header.StdId = 0x00;
	can_frame_template.rx_header.ExtId = 0x00;
	can_frame_template.rx_header.RTR = CAN_RTR_DATA;
	can_frame_template.rx_header.IDE = CAN_ID_STD;
	can_frame_template.rx_header.DLC = 0;
	can_frame_template.rx_data[0] = 0x0;
	can_frame_template.rx_data[1] = 0x0;
	can_frame_template.rx_data[2] = 0x0;
	can_frame_template.rx_data[3] = 0x0;
	can_frame_template.rx_data[4] = 0x0;
	can_frame_template.rx_data[5] = 0x0;
	can_frame_template.rx_data[6] = 0x0;
	can_frame_template.rx_data[7] = 0x0;
}

int CanSendExtendedIdMessage(uint32_t FrameId, uint8_t DLC,
		uint8_t byte0, uint8_t byte1, uint8_t byte2, uint8_t byte3,
		uint8_t byte4, uint8_t byte5, uint8_t byte6, uint8_t byte7){
  can_frame_template.tx_header.ExtId = FrameId;
	can_frame_template.tx_header.RTR = CAN_RTR_DATA;
	can_frame_template.tx_header.IDE = CAN_ID_EXT;
	can_frame_template.tx_header.DLC = DLC;
	can_frame_template.tx_header.TransmitGlobalTime = DISABLE;
	can_frame_template.tx_data[0] = byte0;
	can_frame_template.tx_data[1] = byte1;
	can_frame_template.tx_data[2] = byte2;
	can_frame_template.tx_data[3] = byte3;
	can_frame_template.tx_data[4] = byte4;
	can_frame_template.tx_data[5] = byte5;
	can_frame_template.tx_data[6] = byte6;
	can_frame_template.tx_data[7] = byte7;
  if (HAL_CAN_AddTxMessage(&hcan1,
	          &can_frame_template.tx_header, can_frame_template.tx_data,
	          &can_tx_mailbox) != HAL_OK) {
	  Error_Handler();
    CanClearTxDataFrame();
    return RESULT_FAILED;
	}

	while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) != 3) {
	}
  CanClearTxDataFrame();
  return RESULT_SUCCESS;
}

int CanSendStandardIdMessage(uint32_t FrameId, uint8_t DLC,
		uint8_t byte0, uint8_t byte1, uint8_t byte2, uint8_t byte3,
		uint8_t byte4, uint8_t byte5, uint8_t byte6, uint8_t byte7){
  can_frame_template.tx_header.ExtId = FrameId;
	can_frame_template.tx_header.RTR = CAN_RTR_DATA;
	can_frame_template.tx_header.IDE = CAN_ID_STD;
	can_frame_template.tx_header.DLC = DLC;
	can_frame_template.tx_header.TransmitGlobalTime = DISABLE;
	can_frame_template.tx_data[0] = byte0;
	can_frame_template.tx_data[1] = byte1;
	can_frame_template.tx_data[2] = byte2;
	can_frame_template.tx_data[3] = byte3;
	can_frame_template.tx_data[4] = byte4;
	can_frame_template.tx_data[5] = byte5;
	can_frame_template.tx_data[6] = byte6;
	can_frame_template.tx_data[7] = byte7;
  if (HAL_CAN_AddTxMessage(&hcan1,
	          &can_frame_template.tx_header, can_frame_template.tx_data,
	          &can_tx_mailbox) != HAL_OK) {
	  Error_Handler();
    CanClearTxDataFrame();
    return RESULT_FAILED;
	}

	while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) != 3) {}
  CanClearTxDataFrame();
  return RESULT_SUCCESS;
}
/**
 * @brief: store received data from chosen network
 *
 **/
int CanReceiveData(CanDataFrameInit* dataFrame) {
	if (HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &dataFrame->rx_header,
			dataFrame->rx_data) != HAL_OK) {
		/* Reception Error */
		Error_Handler();
    CanClearRxDataFrame();
    return RESULT_FAILED;
	}
  return RESULT_SUCCESS;
}

/* USER CODE END 1 */
