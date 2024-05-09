#include <lcom/lcf.h>
#include <stdint.h>

int kb_count = 0;

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  if (lsb == NULL) {
    return 1;
  }
  *lsb = val;
  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  if (msb == NULL) {
    return 1;
  }
  *msb = val >> 8;
  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {
  if (value == NULL) {
    return 1;
  }
  uint32_t v = 0;
  if (sys_inb(port, &v)) {
    return 1;
  };
  *value = v;
  #ifdef LAB3 
    kb_count++;
  #endif
  return 0;
}
