#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "nuttx_i2c.h"

uint32_t high_level_width=0; 
uint32_t high_level_width_old=0;
bool high_level_update = false;

uint8_t value[4] = { 12, 16, 20, 24};
uint32_t tick= 0;
uint32_t state= 0;

#define EAGAIN  1
#define EIO  2
float difference_press_pa_raw_data = 0;
int collect(uint8_t *val, uint8_t len, float *diff_press_pa_raw_data)
{
	int	ret = -EIO;

	/* read from the sensor */
	//uint8_t val[4] = {0, 0, 0, 0};

	if (len != 4) {
		return ret;
	}

	// perf_begin(_sample_perf);

	// ret = transfer(nullptr, 0, &val[0], 4);

	// if (ret < 0) {
	// 	perf_count(_comms_errors);
	// 	perf_end(_sample_perf);
	// 	return ret;
	// }

	uint8_t status = (val[0] & 0xC0) >> 6;

	// switch (status) {
	// case 0:
	// 	// Normal Operation. Good Data Packet
	// 	break;

	// case 1:
	// 	// Reserved
	// 	//return -EAGAIN;

	// case 2:
	// 	// Stale Data. Data has been fetched since last measurement cycle.
	// 	//return -EAGAIN;

	// case 3:
	// 	// Fault Detected
	// 	//return -EAGAIN;
	// }

	int16_t dp_raw = 0, dT_raw = 0;
	dp_raw = (val[0] << 8) + val[1];
	/* mask the used bits */
	dp_raw = 0x3FFF & dp_raw;
	dT_raw = (val[2] << 8) + val[3];
	dT_raw = (0xFFE0 & dT_raw) >> 5;
	float temperature = ((200.0f * dT_raw) / 2047) - 50;

	// Calculate differential pressure. As its centered around 8000
	// and can go positive or negative
	const float P_min = -1.0f;
	const float P_max = 1.0f;
	const float PSI_to_Pa = 6894.757f;
	/*
	  this equation is an inversion of the equation in the
	  pressure transfer function figure on page 4 of the datasheet

	  We negate the result so that positive differential pressures
	  are generated when the bottom port is used as the static
	  port on the pitot and top port is used as the dynamic port
	 */
	float diff_press_PSI = -((dp_raw - 0.1f * 16383) * (P_max - P_min) / (0.8f * 16383) + P_min);
	float diff_press_pa_raw = diff_press_PSI * PSI_to_Pa;

	*diff_press_pa_raw_data = diff_press_pa_raw;

	printf("diff_press_pa_raw: %f\r\n", diff_press_pa_raw);

	// // correct for 5V rail voltage if possible
	// voltage_correction(diff_press_pa_raw, temperature);

	// // the raw value still should be compensated for the known offset
	// diff_press_pa_raw -= _diff_pres_offset;

	// /*
	//   With the above calculation the MS4525 sensor will produce a
	//   positive number when the top port is used as a dynamic port
	//   and bottom port is used as the static port
	//  */

	// struct differential_pressure_s report;

	//  track maximum differential pressure measured (so we can work out top speed). 
	// if (diff_press_pa_raw > _max_differential_pressure_pa) {
	// 	_max_differential_pressure_pa = diff_press_pa_raw;
	// }

	// report.timestamp = hrt_absolute_time();
	// report.error_count = perf_event_count(_comms_errors);
	// report.temperature = temperature;
	// report.differential_pressure_filtered_pa =  _filter.apply(diff_press_pa_raw);

	// report.differential_pressure_raw_pa = diff_press_pa_raw;
	// report.max_differential_pressure_pa = _max_differential_pressure_pa;


	return ret;
}

int main(int argc, char argv[])
{    
    printf("start\r\n");
    //probe();

    uint8_t val[4] = {0x1F, 0xBE, 0x61, 0x23};
	collect(val, sizeof(val), &difference_press_pa_raw_data);

	return 0;
}


