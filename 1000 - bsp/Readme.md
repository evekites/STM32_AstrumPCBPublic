# Board support files
This folder contains *board support (BSP)* files. These files implement high level drivers for the Astrum development board.

When starting a new project, copy/replace all the board support files from the folder **./000 - bsp** to the project at the same indicated location.

    ```
    ├─ Core
    │  ├─ Inc
    │  │  └─ *.h
    │  └─ Src
    │     └─ *.c
    ├─ Middlewares
    │  └─ ST
    │     └─ LSM6DSO32x-PID    
    │        └─ *.*
    └─ USB_Device
       └─ App
          └─ *.*
    ```
    
Refer to the example projects for a demonstration how to use these drivers.

If you would like to also use the IMU in your project, an additional step is required.
In STM32CubeIDE add the following folder to the include path of the compiler. There is more than one way to do this, but a convenient way is to right-click the folder in STM32CubeIDE and select **Add/remove include path...** .
   ```
   ├─ Middlewares
   │  └─ ST
   │     └─ LSM6DSO32x-PID
   ```
