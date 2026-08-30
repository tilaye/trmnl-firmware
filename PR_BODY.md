# reTerminal E1001: wake on all three buttons and report which one in Update-Source

## What

The reTerminal E1001 has three buttons — green (GPIO3), right white (GPIO4),
left white (GPIO5) — but the firmware arms only the green one as a wake
source (ext0), so the white buttons do nothing. This PR:

- switches the S3 sleep arming for this board from ext0 to **ext1 over all
  three pins** (`ESP_EXT1_WAKEUP_ANY_LOW`), with the internal RTC pull-ups
  held through deep sleep;
- reads `esp_sleep_get_ext1_wakeup_status()` on wake and reports the source
  in the existing `Update-Source` header: the green button keeps the stock
  `button` string; the whites send `button_a` / `button_b`;
- skips the press-classification loop for white-button wakes (it reads only
  `PIN_INTERRUPT` and would idle through the double-click window).

Everything is guarded by `MULTI_BUTTON_WAKEUP`, currently defined only for
`BOARD_SEEED_RETERMINAL_E1001`. The E1002 shares the same button wiring and
could likely enable it too; left off pending hardware testing.

## Why

This lets any server — TRMNL cloud or BYOS — give the side buttons meaning
(previous screen, jump to a specific plugin, device info, …) with zero
protocol changes. Fully backward compatible: the green button reports the
exact stock string, and servers that ignore unknown `Update-Source` values
see no difference.

## Hardware notes (tested on a physical E1001)

- The white buttons have **no external pull-ups** (Seeed's own ESPHome docs
  configure them `INPUT_PULLUP`). Arming ext1 without `rtc_gpio_pullup_en`
  makes unpulled pins float low in deep sleep and fire phantom wakes — we
  observed a ~15 s wake/poll/sleep loop on hardware before holding the RTC
  pull-ups. The patch enables them explicitly for all three pins.
- Button behavior was hardware-verified on a v1.8.0-based build, because the
  E1001 display does not draw on current releases (#502 / #563). This port
  to `main` compiles cleanly for env `seeed_reTerminal_E1001` but could not
  be display-tested on `main` for that reason.
