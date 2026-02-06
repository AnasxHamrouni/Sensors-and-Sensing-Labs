# STM32 Encoder Interface Using Timer (TIM3) and USART3

This project configures an incremental rotary encoder using **hardware
timer encoder mode (TIM3)** and transmits encoder position data via
**USART3** to a serial console. This method provides accurate position
tracking and real‑time monitoring without relying on software polling.

------------------------------------------------------------------------

# Hardware Configuration (STM32CubeMX) (Board Datasheet: https://os.mbed.com/platforms/ST-Nucleo-F767ZI/)

Generate code after completing the following configuration.

## System Core Configuration

### RCC (Reset and Clock Control)

Set external clock sources:

-   **High Speed Clock (HSE):** Crystal/Ceramic Resonator\
-   **Low Speed Clock (LSE):** Crystal/Ceramic Resonator

### SYS (System)

-   Set **Debug** to:\
    `Trace Asynchronous SW`

------------------------------------------------------------------------

### GPIO Configuration (USART3 Pins)

Navigate to:

**System Core → GPIO → Configuration → USART3 Pins**

Configure the following:

  Pin   Function    Pull Configuration
  ----- ----------- -----------------------------
  PD8   USART3_TX   No pull-up and no pull-down
  PD9   USART3_RX   Pull-up

------------------------------------------------------------------------

## Timer Configuration

Navigate to:

**Timers → TIM3**

Set:

-   **Combined Channels:** Encoder Mode

This enables hardware quadrature decoding.

------------------------------------------------------------------------

## Connectivity Configuration

Navigate to:

**Connectivity → USART3**

Set:

-   Mode: `Asynchronous`

Then go to:

**NVIC Settings:**

-   Enable:\
    `USART3 Global Interrupt`

------------------------------------------------------------------------

## Pinout Configuration

Assign the following pins:

### Encoder Pins (TIM3)

  Pin   Function   Description
  ----- ---------- -------------------
  PB4   TIM3_CH1   Encoder Channel A
  PB5   TIM3_CH2   Encoder Channel B

------------------------------------------------------------------------

### USART3 Pins

  Pin   Function    Description
  ----- ----------- -----------------
  PD8   USART3_TX   Serial transmit
  PD9   USART3_RX   Serial receive

------------------------------------------------------------------------

# IDE Configuration (STM32CubeIDE)

## Serial Console Setup

To monitor encoder output:

### Step 1: Open Console

-   Go to:\
    `Console tab → Open Console → Command Shell Console`

------------------------------------------------------------------------

### Step 2: Configure Connection

Set:

-   Connection Type: `Serial Port`
-   Click: `New`

------------------------------------------------------------------------

### Step 3: Select Serial Port

-   Select your board USB port from:

    `Serial port`

------------------------------------------------------------------------

### Step 4: Name the Connection

-   Enter any name in:

    `Connection name`

Example:

    STM32 USART3 Monitor

Click:

    Finish

------------------------------------------------------------------------

# Expected Result

When rotating the encoder:

-   Timer counter (TIM3-\>CNT) updates automatically
-   Encoder position is transmitted via USART3
-   Serial console displays real‑time encoder values

------------------------------------------------------------------------

# Advantages of Timer Encoder Mode

Compared to GPIO polling:

-   Higher accuracy
-   No missed pulses
-   Hardware‑level decoding
-   Lower CPU usage
-   Professional and industry‑standard method

------------------------------------------------------------------------

# Typical Data Flow

Encoder → TIM3 Encoder Mode → Counter Register → USART3 → Serial Console

------------------------------------------------------------------------

# Requirements

Hardware:

-   STM32 board (e.g., STM32F7 series)
-   Incremental rotary encoder
-   USB cable

Software:

-   STM32CubeMX
-   STM32CubeIDE

------------------------------------------------------------------------

# Notes

Ensure:

-   Correct COM port selected
-   Proper baud rate configured in code and console
-   Encoder connected correctly to TIM3 pins

------------------------------------------------------------------------

# Author

STM32 Encoder Interface using Timer and USART3
