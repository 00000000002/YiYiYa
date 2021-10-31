#include "gpio.h"

UART_HandleTypeDef huart1;

void uart_init() {
  __HAL_RCC_USART1_CLK_ENABLE();
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK) {
    kprintf("error uart init\n");
  }
}

// USART_HandleTypeDef husart1;
// void usart_init() {
//   __HAL_RCC_USART1_CLK_ENABLE();

//   GPIO_InitTypeDef GPIO_InitStruct;

//   GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
//   GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//   GPIO_InitStruct.Pull = GPIO_NOPULL;
//   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//   GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
//   HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

//   husart1.Instance = USART1;
//   husart1.Init.BaudRate = 115200;
//   husart1.Init.WordLength = USART_WORDLENGTH_8B;
//   husart1.Init.StopBits = USART_STOPBITS_1;
//   husart1.Init.Parity = USART_PARITY_NONE;
//   husart1.Init.Mode = USART_MODE_TX_RX;
//   husart1.Init.CLKPolarity = USART_POLARITY_LOW;
//   husart1.Init.CLKPhase = USART_PHASE_1EDGE;
//   husart1.Init.CLKLastBit = USART_LASTBIT_DISABLE;
//   if (HAL_USART_Init(&husart1) != HAL_OK) {
//     kprintf("error uart init\n");
//   }
// }

void uart_send(unsigned int c) { HAL_UART_Transmit(&huart1, &c, 1, 1000); }

void system_init_clock() {
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  /** Configure the main internal regulator output voltage
   */
  __HAL_RCC_PWR_CLK_ENABLE();

  // __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType =
      RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 15;
  RCC_OscInitStruct.PLL.PLLN = 144;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 5;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    kprintf("errro\n");
    return;
  }
  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
    kprintf("errro\n");
    return;
  }
}

void gpio_init() {
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
}

void system_init() {
// enable fpu
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
  SCB->CPACR |= (3 << 20) | (3 << 22);
#endif

  /* Reset of all peripherals, Initializes the Flash interface and the Systick.
   */
  // HAL_Init();
  HAL_MspInit();

  /* Configure the system clock */
  system_init_clock();

  /* Initialize all configured peripherals */
  gpio_init();
  uart_init();
}

void timer_init(int hz) { kprintf("timer init\n"); }
void timer_end() {}

#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC

void test_led() {
  GPIO_InitTypeDef GPIO_InitStruct;

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

  while (1) {
    static uint8_t pwmset;
    static uint16_t time;
    static uint8_t timeflag;
    static uint8_t timecount;

    if (timeflag == 0) {
      time++;
      if (time >= 800) timeflag = 1;
    } else {
      time--;
      if (time == 0) timeflag = 0;
    }

    pwmset = time / 80;

    if (timecount > 20)
      timecount = 0;
    else
      timecount++;

    if (timecount >= pwmset)
      HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
    else
      HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
    for (int i = 0; i < 100000; i++) {
    }
  }
}

void platform_init() {
  // init system
  system_init();

  // init uart
  uart_init();

  // test_led();
  for (;;) {
    uart_send('d');
  }
}