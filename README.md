# Setup Solution Without Timer (GPIO Encoder Mode)

## MX Configuration (Board Datasheet: https://os.mbed.com/platforms/ST-Nucleo-F767ZI/)

*(Generate code from MX once setup is done)*

### Pinout & Configuration Tab → Categories

#### System Core

-   **RCC**
    -   Set **High Speed Clock (HSE)** to: `Crystal/Ceramic Resonator`
    -   Set **Low Speed Clock (LSE)** to: `Crystal/Ceramic Resonator`
-   **SYS**
    -   Set **Debug** to: `Trace Asynchronous SW`

------------------------------------------------------------------------

### Pinout View

Configure encoder pins as GPIO inputs:

-   **PB4** → Set as: `GPIO_Input`\
    *(Encoder Channel B)*

-   **PA4** → Set as: `GPIO_Input`\
    *(Encoder Channel A)*

------------------------------------------------------------------------

## IDE Configuration

*(Configure Live Expressions to monitor encoder position and angle)*

### Live Expressions Setup

1.  Open the **Live Expressions** window in STM32CubeIDE
2.  Click **Add new expression**
3.  Add the following variables one by one:
```
    encoder_pos
    angle_rad
    angle_deg
```
These variables allow you to monitor:

-   Incremental encoder position
-   Angular position in radians
-   Angular position in degrees

------------------------------------------------------------------------

## Expected Result

When rotating the encoder:

-   `encoder_pos` increases or decreases incrementally (PPR(Pulses_Per_Revolution=80) -> 4 pulses per tick) 
-   `angle_rad` updates continuously in radians
-   `angle_deg` updates continuously in degrees

This confirms correct encoder reading using GPIO polling mode.
