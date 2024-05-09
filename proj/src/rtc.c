#include "rtc.h"
#include <lcom/lcf.h>

static uint8_t original_data;

int hook_id = 8;
int rtc_subscribe_int(uint8_t *bit_no) {
  hook_id = RTC_IRQ;
  *bit_no = (uint8_t) hook_id;
  if (sys_irqsetpolicy(RTC_IRQ, IRQ_REENABLE, &hook_id) != OK) {
    return 1;
  }
  return 0;
}

int rtc_unsubscribe_int() {
  if (sys_irqrmpolicy(&hook_id) != OK) {
    return 1;
  }
  return 0;
}


int rtc_init() {
  uint8_t data;
  if (rtc_read_register(RTC_REGISTER_B, &data)) {
    return 1;
  }
  original_data = data;
  if (rtc_set_register(RTC_REGISTER_B, data | RTC_UF | RTC_AF)) {
    return 1;
  }
  return 0;
}

int rtc_read_register(uint8_t address, uint8_t *data) {
  if (sys_outb(RTC_ADDR_REG, address)) {
    return 1;
  }
  if (util_sys_inb(RTC_DATA_REG, data)) {
    return 1;
  }
  return 0;
}

int rtc_set_register(uint8_t address, uint8_t data) {
  if (sys_outb(RTC_ADDR_REG, address)) {
    return 1;
  }
  if (sys_outb(RTC_DATA_REG, data)) {
    return 1;
  }
  return 0;
}

int rtc_read_date(char *string) {
  uint8_t data;
  uint8_t day, month, year;
  do {
    rtc_read_register(RTC_REGISTER_A, &data);
  } while (data & BIT(7));
  if (rtc_read_register(RTC_DAY_OF_MONTH_ADDRESS, &day)) {
    return 1;
  }
  if (rtc_read_register(RTC_MONTH_ADDRESS, &month)) {
    return 1;
  }
  if (rtc_read_register(RTC_YEAR_ADDRESS, &year)) {
    return 1;
  }
  sprintf(string, "%02x-%02x-%02x", day, month, year);
  return 0;
}

int rtc_read_time(char *string) {
  uint8_t data;
  uint8_t hour, minute, second;
  do {
    rtc_read_register(RTC_REGISTER_A, &data);
  } while (data & BIT(7));
  if (rtc_read_register(RTC_SECONDS_ADDRESS, &second)) {
    return 1;
  }
  if (rtc_read_register(RTC_MINUTES_ADDRESS, &minute)) {
    return 1;
  }
  if (rtc_read_register(RTC_HOURS_ADDRESS, &hour)) {
    return 1;
  }
  sprintf(string, "%02x:%02x:%02x", hour, minute, second);
  return 0;
}

int rtc_clean() {
  if (rtc_set_register(RTC_REGISTER_B, original_data)) {
    return 1;
  }
  return 0;
}
