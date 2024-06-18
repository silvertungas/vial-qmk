#include QMK_KEYBOARD_H

bool process_global_quick_tap(uint16_t keycode, keyrecord_t *record) {
  static uint16_t global_quick_tap_timer = 0;
  if (keycode < QK_MOD_TAP || keycode > QK_MOD_TAP_MAX) {
    global_quick_tap_timer = timer_read();
    return true;
  }
  if (timer_elapsed(global_quick_tap_timer) > TAPPING_TERM) {
    return true;
  }
  if (record->event.pressed) {
    keycode = keycode & 0xFF;
    global_quick_tap_timer = timer_read();
    tap_code(keycode);
    return false;
  }
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_global_quick_tap(keycode, record)) {
        return false;
    }
    return true;
}

