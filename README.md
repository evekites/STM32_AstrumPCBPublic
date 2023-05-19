# STM32_AstrumPCBPublic

Repro with \*.ioc files and needed USER CODE sections
This repo is for Software Development students of the Astrum College, Velp, The Netherlands.

Most projects contains a README.md, a CONFIGURATION.md and the USER CODE sections of the main.c source file.

Usage:

- Create a new project and choose the STM32WB55RGV6 from the MCU list.
- Implement the settings as described in the CONFIGURATION.md file
- Insert al the USER CODE sections to their corresponding places in your own main.c fie.

All code is based on the Astrum PCB used fot the Embedded Software lessons for 2nd year students MBO Software Development. This STM32 development PCB was developed for the Astrum College by Gemini Embedded Technology.

## STM32WB55RGV6

| Component             | Chip                 | Datasheet                                                                                      |
| --------------------- | -------------------- | ---------------------------------------------------------------------------------------------- |
| 2 User LED's          |                      |                                                                                                |
| 2 User switches       |                      |                                                                                                |
| Grove GPIO connectors |                      |                                                                                                |
| Grove I2C connector   |                      |                                                                                                |
| Grove USART connector |                      |                                                                                                |
| H-Bridge              | L293DD013TR          | https://octopart.com/datasheet/l293dd013tr-stmicroelectronics-39581684                         |
| IMU 3 axis            | LSM6DSO32TR          | https://octopart.com/datasheet/lsm6dso32tr-stmicroelectronics-108038421                        |
| IO_Extender           | PCF8574T/3,518       | https://octopart.com/datasheet/pcf8574t%2F3%2C518-nxp+semiconductors-10470852                  |
| Lightsensor           | SFH 5711-2/3-Z       | https://octopart.com/datasheet/sfh+5711-2%2F3-z-osram+opto-55557865                            |
| Magnetic Buzzer       | KSSGJ4B20            | https://datasheetspdf.com/pdf/1302247/Kingstate/KSSGJ4B20/1                                    |
| Microphone            | POM-2738P-R          | https://octopart.com/datasheet/pom-2738p-r-pui+audio-19251807                                  |
| OLED Display          | WEO012832GWAP3N00000 | https://www.telerex-europe.com/content/files/pdfs/productPdfs/WS/OLED/WEO012832GWAP3N00000.pdf |
| Potmeter              |                      |                                                                                                |
| Reedswitch            |                      |                                                                                                |
| Rotary encoder        |                      |                                                                                                |
| Serial RGB            | WS2813               |                                                                                                |
| Temperaturesensor     | PCT2075D,118         | https://octopart.com/datasheet/pct2075d%2C118-nxp+semiconductors-27207713                      |
| Touchsensors          | CAP1293-1-SN         | https://octopart.com/datasheet/cap1293-1-sn-microchip-71341885                                 |
