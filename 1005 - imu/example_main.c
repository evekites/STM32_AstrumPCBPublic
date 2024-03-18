/*! ***************************************************************************
 *
 * \brief     Example 005 - Inertial Measurement Unit (IMU)
 * \file      example_main.c
 * \author    Hugo Arends
 * \date      July 2023
 *
 * \copyright 2023 HAN University of Applied Sciences. All Rights Reserved.
 *            \n\n
 *            Permission is hereby granted, free of charge, to any person
 *            obtaining a copy of this software and associated documentation
 *            files (the "Software"), to deal in the Software without
 *            restriction, including without limitation the rights to use,
 *            copy, modify, merge, publish, distribute, sublicense, and/or sell
 *            copies of the Software, and to permit persons to whom the
 *            Software is furnished to do so, subject to the following
 *            conditions:
 *            \n\n
 *            The above copyright notice and this permission notice shall be
 *            included in all copies or substantial portions of the Software.
 *            \n\n
 *            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *            OTHER DEALINGS IN THE SOFTWARE.
 *
 *****************************************************************************/

/* Private includes ----------------------------------------------------------*/
#include <example_main.h>
#include "main.h"
#include <stdbool.h>
#include <string.h>

#include "led_red.h"
#include "lsm6dso32x_reg.h"
#include "ws2813.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static uint8_t rst;
static volatile bool imu_int1_flag = false;
static int16_t data_raw_acceleration[3];
static int16_t data_raw_angular_rate[3];
static float acceleration_mg[3];
static float angular_rate_mdps[3];

/* External variables --------------------------------------------------------*/
extern I2C_HandleTypeDef hi2c1;

/* Private function prototypes -----------------------------------------------*/
static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len);
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len);

/* Private user code ---------------------------------------------------------*/

void example_main(void)
{
    stmdev_ctx_t dev_ctx;

    // Initialize IMU driver interface
    dev_ctx.write_reg = platform_write;
    dev_ctx.read_reg = platform_read;
    dev_ctx.mdelay = HAL_Delay;
    dev_ctx.handle = &hi2c1;

    // All LEDs off
    rgb_t leds[N_RGB_LEDS] = {0};
    ws2813_write(leds);

    int32_t curr = 2;
    int32_t next = curr;
    leds[curr].r = 20;

    // Another write to prevent the first RGB led from blinking
    HAL_Delay(500);
    ws2813_write(leds);

    // Sensor boot time
    //HAL_Delay(20);

    do
    {
        lsm6dso32x_reset_get(&dev_ctx, &rst);
    }while(rst);

    // Restore default configuration
    lsm6dso32x_reset_set(&dev_ctx, PROPERTY_ENABLE);

    // Disable I3C interface
    lsm6dso32x_i3c_disable_set(&dev_ctx, LSM6DSO32X_I3C_DISABLE);

    // Enable Block Data Update
    lsm6dso32x_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);

    // Set Output Data Rate
    lsm6dso32x_xl_data_rate_set(&dev_ctx, LSM6DSO32X_XL_ODR_104Hz);
    lsm6dso32x_gy_data_rate_set(&dev_ctx, LSM6DSO32X_GY_ODR_104Hz);

    // Set full scale
    lsm6dso32x_xl_full_scale_set(&dev_ctx, LSM6DSO32X_4g);
    lsm6dso32x_gy_full_scale_set(&dev_ctx, LSM6DSO32X_2000dps);

    // Enable Tap detection on Z
    lsm6dso32x_tap_detection_on_z_set(&dev_ctx, PROPERTY_ENABLE);

    // Set Tap threshold
    lsm6dso32x_tap_threshold_z_set(&dev_ctx, 0x02);

    // Set single tap mode
    lsm6dso32x_tap_mode_set(&dev_ctx, LSM6DSO32X_ONLY_SINGLE);

    // Interrupt generation on Single tap INT1 pin
    lsm6dso32x_pin_int1_route_t int1_route;
    lsm6dso32x_pin_int1_route_get(&dev_ctx, &int1_route);
    int1_route.single_tap = PROPERTY_ENABLE;
    lsm6dso32x_pin_int1_route_set(&dev_ctx, int1_route);

    uint32_t prev_ticks_ms = 0;
    uint32_t current_ticks_ms = 0;
    const uint32_t interval_ms = 200;

    while(1)
    {
        // --------------------------------------------------------------------

        // IMU INT1 pint interrupt?
        if(imu_int1_flag == true)
        {
            imu_int1_flag = false;

            led_red_toggle();
        }

        // --------------------------------------------------------------------

        uint8_t reg;

        // Read output only if new xl value is available
        lsm6dso32x_xl_flag_data_ready_get(&dev_ctx, &reg);

        if(reg)
        {
            // Read acceleration field data
            memset(data_raw_acceleration, 0x00, 3 * sizeof(int16_t));

            lsm6dso32x_acceleration_raw_get(&dev_ctx, data_raw_acceleration);
            acceleration_mg[0] = lsm6dso32x_from_fs4_to_mg(data_raw_acceleration[0]);
            acceleration_mg[1] = lsm6dso32x_from_fs4_to_mg(data_raw_acceleration[1]);
            acceleration_mg[2] = lsm6dso32x_from_fs4_to_mg(data_raw_acceleration[2]);

            // Select the next RGB LED based on the x acceleration
            if(next == curr)
            {
                next = (acceleration_mg[0] <-200) && (next < 4) ? (next+1) : next;
                next = (acceleration_mg[0] > 200) && (next > 0) ? (next-1) : next;
            }
        }

        // --------------------------------------------------------------------

        // Read output only if new gyro value is available
        lsm6dso32x_gy_flag_data_ready_get(&dev_ctx, &reg);

        if(reg)
        {
            // Read angular rate field data
            memset(data_raw_angular_rate, 0x00, 3 * sizeof(int16_t));

            lsm6dso32x_angular_rate_raw_get(&dev_ctx, data_raw_angular_rate);
            angular_rate_mdps[0] = lsm6dso32x_from_fs2000_to_mdps(data_raw_angular_rate[0]);
            angular_rate_mdps[1] = lsm6dso32x_from_fs2000_to_mdps(data_raw_angular_rate[1]);
            angular_rate_mdps[2] = lsm6dso32x_from_fs2000_to_mdps(data_raw_angular_rate[2]);
        }

        // --------------------------------------------------------------------

        // Get system ticks
        current_ticks_ms = HAL_GetTick();

        // Interval passed?
        if(current_ticks_ms >= (prev_ticks_ms + interval_ms))
        {
            prev_ticks_ms = current_ticks_ms;

            // Update LEDs required?
            if(next != curr)
            {
                leds[curr].r = 0;
                leds[next].r = 20;
                curr = next;
                ws2813_write(leds);
            }
        }

    }
}

/*
 * @brief  Write generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this examples is used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to write
 * @param  bufp      pointer to data to write in register reg
 * @param  len       number of consecutive register to write
 *
 */
static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len)
{
    HAL_I2C_Mem_Write(handle, LSM6DSO32X_I2C_ADD_H, reg,
                      I2C_MEMADD_SIZE_8BIT, (uint8_t*) bufp, len, 1000);
    return 0;
}

/*
 * @brief  Read generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this examples is used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to read
 * @param  bufp      pointer to buffer that store the data read
 * @param  len       number of consecutive register to read
 *
 */
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len)
{
    HAL_I2C_Mem_Read(handle, LSM6DSO32X_I2C_ADD_H, reg,
                     I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);
    return 0;
}

// Callback function for the IMU int1
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == IMU_INT1_Pin)
    {
        imu_int1_flag = true;
    }
}
