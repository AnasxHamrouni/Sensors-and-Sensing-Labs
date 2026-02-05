#include "main.h"

/* ===== Global variables (visible in debugger) ===== */

/* Raw encoder count (incremental) */
volatile int encoder_pos = 0;

/* Previous quadrature state */
volatile uint8_t prev_state = 0;

/* ===== Calibration variables ===== */

/* Measured pulses per revolution (from experiment)
 * Example: 3 revolutions -> encoder_pos = 96
 * => 96 / 3 = 32 pulses per revolution
 */
volatile int pulses_per_revolution = 80;

/* Calibrated angular position (radians) */
volatile float angle_rad = 0.0f;

/* Optional: angular position in degrees */
volatile float angle_deg = 0.0f;

int main(void)
{
  HAL_Init();

  /* ===== Enable GPIO clocks ===== */
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN |
                 RCC_AHB1ENR_GPIOBEN;

  /* ===== GPIO configuration ===== */

  /* PA4 -> Encoder CLK (input, pull-up) */
  GPIOA->MODER &= ~(3U << (4 * 2));
  GPIOA->PUPDR &= ~(3U << (4 * 2));
  GPIOA->PUPDR |=  (1U << (4 * 2));

  /* PB4 -> Encoder DT (input, pull-up) */
  GPIOB->MODER &= ~(3U << (4 * 2));
  GPIOB->PUPDR &= ~(3U << (4 * 2));
  GPIOB->PUPDR |=  (1U << (4 * 2));

  /* ===== Initial encoder state ===== */
  uint8_t clk = (GPIOA->IDR >> 4) & 1U;
  uint8_t dt  = (GPIOB->IDR >> 4) & 1U;
  prev_state = (clk << 1) | dt;

  while (1)
  {
    /* Read encoder signals */
    clk = (GPIOA->IDR >> 4) & 1U;
    dt  = (GPIOB->IDR >> 4) & 1U;

    uint8_t curr_state = (clk << 1) | dt;

    /* ===== Quadrature decoding ===== */
    switch ((prev_state << 2) | curr_state)
    {
      /* Clockwise rotation */
      case 0b0001:
      case 0b0111:
      case 0b1110:
      case 0b1000:
        encoder_pos++;
        break;

      /* Counter-clockwise rotation */
      case 0b0010:
      case 0b0100:
      case 0b1101:
      case 0b1011:
        encoder_pos--;
        break;

      /* Invalid transition (bounce) */
      default:
        break;
    }

    prev_state = curr_state;

    /* ===== Calibration computation ===== */

    /* Angular position in radians */
    angle_rad = (2.0f * 3.1415926f * encoder_pos)
                / pulses_per_revolution;

    /* Angular position in degrees */
    angle_deg = (360.0f * encoder_pos)
                / pulses_per_revolution;

    /* Small delay to limit polling rate */
    HAL_Delay(1);

  }
}
