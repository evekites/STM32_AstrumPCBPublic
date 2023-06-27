void IO_EXTENDER_LED_Off(int iMask)
{
    bool highON = true;
    // The M_LEDs are OFF when high, so highON = false
    if (iMask == M_LED_RED || iMask == M_LED_GREEN || iMask == M_LED_BLUE)
        highON = false;
    if (highON)
    {
        I2CRegistervalues[0] = I2CRegistervalues[0] & ~iMask;
    }
    else // For the M_LEDs the logic is reversed, so ON when LOW en OFF when HIGH
    {
        I2CRegistervalues[0] = I2CRegistervalues[0] | iMask;
    }
    ret = HAL_I2C_Master_Transmit(&hi2c1, IO_EXT_WRITE, I2CRegistervalues, 1,
                                  HAL_MAX_DELAY); // Write I2CRegistervalues[0] to IO Extender
    if (ret != HAL_OK)
    {
        printf("I2C error\r\n");
    }
}

void IO_EXTENDER_LED_On(int iMask)
{
    bool highON = true;
    // The M_LEDs are OFF when high, so highON = false
    if (iMask == M_LED_RED || iMask == M_LED_GREEN || iMask == M_LED_BLUE)
        highON = false;
    if (highON)
    {
        I2CRegistervalues[0] = I2CRegistervalues[0] | iMask;
    }
    else // For the M_LEDs the logic is reversed, so ON when LOW en OFF when HIGH
    {
        I2CRegistervalues[0] = I2CRegistervalues[0] & ~iMask;
    }
    ret = HAL_I2C_Master_Transmit(&hi2c1, IO_EXT_WRITE, I2CRegistervalues, 1,
                                  HAL_MAX_DELAY); // Write buf[0] to IO Extender
    if (ret != HAL_OK)
    {
        printf("I2C error\r\n");
    }
}

void IO_EXTENDER_LEDs_On()
{
    IO_EXTENDER_(M_LED_RED);
    IO_EXTENDER_(M_LED_GREEN);
    IO_EXTENDER_(M_LED_BLUE);
    IO_EXTENDER_(LED_BLUE);
    IO_EXTENDER_(GPIO2A);
    IO_EXTENDER_(GPIO2B);
    IO_EXTENDER_(J1100_1);
}

void LEDs_Off()
{
    IO_EXTENDER_LED_Off(M_LED_RED);
    IO_EXTENDER_LED_Off(M_LED_GREEN);
    IO_EXTENDER_LED_Off(M_LED_BLUE);
    IO_EXTENDER_LED_Off(LED_BLUE);
    IO_EXTENDER_LED_Off(GPIO2A);
    IO_EXTENDER_LED_Off(GPIO2B);
    IO_EXTENDER_LED_Off(J1100_1);
}

void LED_Toggle(int iMask)
{
    I2CRegistervalues[0] = I2CRegistervalues[0] ^ iMask;
    ret = HAL_I2C_Master_Transmit(&hi2c1, IO_EXT_WRITE, I2CRegistervalues, 1,
                                  HAL_MAX_DELAY);
    if (ret != HAL_OK)
    {
        printf("I2C error\r\n");
    }
}

IO_EXTENDER_LEDs_Off();

int IO_EXTENDER_LEDs[7] = {M_LED_RED, M_LED_GREEN, M_LED_BLUE, LED_BLUE, GPIO2A,
                           GPIO2B, J1100_1};