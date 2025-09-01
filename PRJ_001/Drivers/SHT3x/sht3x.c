#include "sht3x.h"

#include <assert.h>

/**
 * Registers addresses.
 */


typedef enum
{
	SHT3X_COMMAND_MEASURE_HIGHREP_STRETCH = 0x2c06,
	SHT3X_COMMAND_CLEAR_STATUS = 0x3041,
	SHT3X_COMMAND_SOFT_RESET = 0x30A2,
	SHT3X_COMMAND_HEATER_ENABLE = 0x306d,
	SHT3X_COMMAND_HEATER_DISABLE = 0x3066,
	SHT3X_COMMAND_READ_STATUS = 0xf32d,
	SHT3X_COMMAND_FETCH_DATA = 0xe000,
	SHT3X_COMMAND_MEASURE_HIGHREP_10HZ = 0x2737,
	SHT3X_COMMAND_MEASURE_LOWREP_10HZ = 0x272a
} sht3x_command_t;

static void i2c_master_send_impl(I2C_Handle_t *I2C_Handle,
								uint16_t addr,
								uint8_t *pTxbuffer,
								uint32_t len){
	I2C_MasterSend_Multi_Data(I2C_Handle, addr, pTxbuffer, len);
}
static void i2c_master_read_impl(I2C_Handle_t *I2C_Handle,
								uint8_t Address,
								uint8_t *buffer,
								uint8_t size){
	I2C_MasterRead_Data(I2C_Handle, Address, buffer, size);
}

static void i2c_read_mem_impl(I2C_Handle_t *I2C_Handle,
                               uint16_t DevAddr,
                               uint16_t MemAddr,
                               uint8_t MemAddrSize,
                               uint8_t *pData,
                               uint16_t Size){
	I2C_MasterRead_Mem(I2C_Handle, DevAddr, MemAddr, MemAddrSize, pData, Size);
}


static void msdelay_impl(unsigned ms)  { delay_ms(ms); }

sht3x_bus_ops_t ops = {
	.i2c_master_send = i2c_master_send_impl,
	.i2c_master_read = i2c_master_read_impl,
	.i2c_read_mem = i2c_read_mem_impl,
	.ms_delay = msdelay_impl,
};

void sht3x_init(sht3x_handle_t *sht, const sht3x_bus_ops_t *ops, uint16_t addr){
	int ret;
	sht->ops = *ops;
	sht->device_address = addr;
	ret = sht3x_check_init(sht);
	if(!ret){
//		pr_info
	}
}

static uint8_t calculate_crc(const uint8_t *data, size_t length){
	uint8_t crc = 0xff;
	for (size_t i = 0; i < length; i++) {
		crc ^= data[i];
		for (size_t j = 0; j < 8; j++) {
			if ((crc & 0x80u) != 0) {
				crc = (uint8_t)((uint8_t)(crc << 1u) ^ 0x31u);
			} else {
				crc <<= 1u;
			}
		}
	}
	return crc;
}

bool sht3x_send_command(sht3x_handle_t *sht, sht3x_command_t command){
	uint8_t command_buffer[2] = {(command & 0xff00u) >> 8u, command & 0xffu};
	sht->ops.i2c_master_send(
							sht->hi2c1,
							sht->device_address,
							command_buffer,
							sizeof(command_buffer));
	return true;
}

static uint16_t uint8_to_uint16(uint8_t msb, uint8_t lsb){
	return (uint16_t)((uint16_t)msb << 8u) | lsb;
}

bool sht3x_check_init(sht3x_handle_t *sht){

//	assert(sht->i2c_handle->Init.NoStretchMode == I2C_NOSTRETCH_DISABLE);
	// TODO: Assert i2c frequency is not too high

	uint8_t status_reg_and_checksum[3];
	sht->ops.i2c_read_mem(sht->hi2c1,
						0x44 << 1,
						SHT3X_COMMAND_READ_STATUS,
						2,
						status_reg_and_checksum,
						3);


	uint8_t calculated_crc = calculate_crc(status_reg_and_checksum, 2);

//	if (calculated_crc != status_reg_and_checksum[2]) {
//		return false;
//	}

	return true;
}

bool sht3x_read_temperature_and_humidity(sht3x_handle_t *sht, int *temperature, int *humidity){
	sht3x_send_command(sht, SHT3X_COMMAND_MEASURE_HIGHREP_STRETCH);

	sht->ops.ms_delay(1);

	uint8_t buffer[6];

	sht->ops.i2c_master_read(
							sht->hi2c1,
							sht->device_address,
							buffer,
							sizeof(buffer));

	uint8_t temperature_crc = calculate_crc(buffer, 2);
	uint8_t humidity_crc = calculate_crc(buffer + 3, 2);
	if (temperature_crc != buffer[2] || humidity_crc != buffer[5]) {
		return false;
	}

	uint16_t temperature_raw = uint8_to_uint16(buffer[0], buffer[1]);
	uint16_t humidity_raw = uint8_to_uint16(buffer[3], buffer[4]);

	*temperature = -45 + 175 * temperature_raw / 65535;
	*humidity = 100 * humidity_raw / 65535;

	return true;
}

bool sht3x_set_header_enable(sht3x_handle_t *handle, bool enable){
	if (enable) {
		return sht3x_send_command(handle, SHT3X_COMMAND_HEATER_ENABLE);
	} else {
		return sht3x_send_command(handle, SHT3X_COMMAND_HEATER_DISABLE);
	}
}

int st30_init(sht3x_handle_t *handle){
    int temperature, humidity;
    int ret;
//    ssize_t len;

    sht3x_init(handle, &ops,handle->device_address);
    ret = sht3x_read_temperature_and_humidity(handle, &temperature, &humidity);
    if(ret < 0){
//        pr_info("sht: initial read failed (%d)\n", ret);
//        return scnprintf(buf, PAGE_SIZE, "error: read failed\n");
    }
//    pr_info("Initial temperature: %.2dC, humidity: %.2d%%RH\n\r", temperature, humidity);

    // Enable heater for two seconds.
    ret = sht3x_set_header_enable(handle, true); /* giả định API */
    if (ret < 0)
//        pr_info("sht: enable heater failed (%d)\n", ret);
	handle->ops.ms_delay(2000);
    sht3x_set_header_enable(handle, false);

    // Read temperature and humidity again.
    ret = sht3x_read_temperature_and_humidity(handle, &temperature, &humidity);
    if (ret < 0) {
//        pr_info("sht: second read failed (%d)\n", ret);
//        return scnprintf(buf, PAGE_SIZE, "error: read failed\n");
    }
//    pr_info("After heating temperature: %.2dC, humidity: %.2d%%RH\n\r", temperature, humidity);

//    len = scnprintf(buf, PAGE_SIZE, "Humidity = %.2d, Temp = %.2d\n", humidity, temperature);
//    return len;
    return 0;
}
