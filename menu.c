/******************************************************************************
 * Function Name : menu_base_int
 * Description   : Interrupt based menu handling function
 ******************************************************************************/
void menu_base_int(void)
{
	char ch;                      // Variable to store keypad key

	if(flag == 1)                // Check whether interrupt occurred
	{
		flag = 0;                // Clear interrupt flag

		Write_CMD_LCD(0x01);     // Clear LCD display

		Write_CMD_LCD(0x80);     // Move cursor to line1

		Write_str_LCD("1.Irrigation Time");
		// Display first menu option

		Write_CMD_LCD(0xC0);     // Move cursor to line2

		Write_str_LCD("3.Temp & Humidity");
		// Display second menu option

		Write_CMD_LCD(0xD4);     // Move cursor to line4

		Write_str_LCD("Select Option:");
		// Ask user to select option

		ch = keyScan();          // Read keypad input

		switch(ch)               // Check selected option
		{
			case '1': 
				SetIrrigationTiming();
				// Configure irrigation timing
				break;

			case '3': 
				Set_Temp_Humidity();
				// Configure temperature and humidity thresholds
				break;

			default:
				Write_CMD_LCD(0x01);
				// Clear LCD

				Write_str_LCD("Invalid Option");
				// Display invalid option message

				delay_ms(1000);
				// Wait for 1 second
		}
	}
}

/******************************************************************************
 * Function Name : compare_temp_hum
 * Description   : Compare sensor values and control irrigation motor
 ******************************************************************************/
void compare_temp_hum(void)
{
	int delay_time;               // Variable for motor ON duration

	if((flag1==1) && (flag2==1))
	// Check whether all settings configured
	{
		delay_time=0;             // Initialize delay time

		if ((IOPIN0 >> 21) & 1)
		// Check soil moisture sensor
		// 1 = Dry soil
		{
			int cnt=0;            // Counter variable

			if ((temperature >= T_t1) && (humidity <= H_t1))
			// High temperature and low humidity condition
				delay_time = I_t1;

			else if ((temperature >= T_t2) && (humidity >= H_t2))
			// Moderate condition
				delay_time = I_t2;

			else if ((temperature <= T_t3) && (humidity <= H_t3))
			// Low temperature and low humidity condition
				delay_time = I_t3;

			if (delay_time > 0)
			// Check whether motor should turn ON
			{
				Write_CMD_LCD(0x01);
				// Clear LCD

				Write_str_LCD("MOTOR TURN ON");
				// Display motor status

				IOSET0 = 1 << 20;
				// Turn motor ON using relay

				esp01_sendToThingspeak3(1);
				// Send motor ON status to ThingSpeak

				while(1)
				{
					cnt++;         
					// Increment counter every second

					delay_s(1);
					// Wait for 1 second

					if((cnt==(delay_time*60)) || ((IOPIN0 >> 21) & 1)==0)
					// Stop motor after set duration
					// OR if soil becomes wet
					{
						break;
					}
				}

				IOCLR0 = 1 << 20;
				// Turn motor OFF

				Write_CMD_LCD(0x01);
				// Clear LCD

				esp01_sendToThingspeak3(0);
				// Send motor OFF status to ThingSpeak
			}
		}
	}
}