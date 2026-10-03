#pragma once

/*
 * board_pins.h —— 本工程板级引脚事实的【唯一来源】
 *
 * 规则：
 * 1. 所有引脚号只允许定义在本文件；业务代码一律引用宏，禁止裸写数字。
 * 2. 每个常量注释来源：原理图网络名 / 厂家例程宏 / flash_id 实测 / 万用表。
 * 3. 未经显式评审不得修改本文件；换板型新增宏分支，不做全局替换。
 * 4. 未确认的事实写 -1（表示 NC / 未用）或 [unknown] 注释并在 board.md 登记，
 *    禁止凭印象填值。
 *
 * 板型：{{BOARD_VENDOR_MODEL}}
 * 芯片：{{CHIP_MODULE}}
 * 来源：{{SCHEMATIC_OR_DATASHEET_LINK}}
 */

#include <cstdint>

namespace board {

/* ============ 板型选择 ============ */
#if defined({{BOARD_MACRO}})

/* ============ 调试 / 下载 ============ */
// USB: 原生 USB（GPIO19/20）或 USB-UART 桥 {{FILL_USB_PATH}}
constexpr std::uint8_t kUart0TxPin = 43;  // 来源: 芯片默认 U0TXD / 原理图
constexpr std::uint8_t kUart0RxPin = 44;  // 来源: 芯片默认 U0RXD / 原理图

/* ============ 用户输入 ============ */
// 按键按下时接通到 GND，板载外部上拉（以原理图为准）
constexpr std::uint8_t kBootKeyPin = 0;   // 来源: strapping/BOOT 键

/* 示例：普通按键（如与实际不符请在 board.md 标注）
constexpr std::uint8_t kKey1Pin = {{GPIO}};  // 来源: 原理图网络名 KEY1
*/

/* 示例：旋转编码器
constexpr std::uint8_t kEncoderPinA = {{GPIO}};  // 来源: 原理图 ENC_A
constexpr std::uint8_t kEncoderPinB = {{GPIO}};  // 来源: 原理图 ENC_B
constexpr std::uint8_t kEncoderPressPin = {{GPIO}};
*/

/* ============ 指示输出 ============ */
// 板载灯类型: 普通 LED（高/低有效）或 WS2812 {{FILL_LED_TYPE}}
constexpr std::int8_t kStatusLedPin = -1;      // -1 = 尚未确认 [unknown]
constexpr bool kStatusLedActiveHigh = true;    // 来源: {{FILL_SOURCE}}

// 若为 WS2812：
// constexpr std::uint8_t kWs2812Pin  = {{GPIO}};  // 来源: {{FILL_SOURCE}}
// constexpr std::uint8_t kLedCount   = {{N}};

/* ============ 电源控制（危险区：时序见 board.md） ============ */
// 共用电源使能；上电默认态、使能电平、保持时间必须与硬件档案一致
constexpr std::int8_t kPeripheralPowerEnablePin = -1;  // [unknown] 时保持 -1
constexpr bool kPeripheralPowerActiveHigh = true;

/* ============ I2C 总线 ============ */
constexpr std::int8_t kI2cSclPin = -1;  // [unknown]
constexpr std::int8_t kI2cSdaPin = -1;  // [unknown]
// 从机地址上机扫描确认后登记到 board.md，不在此臆造

/* ============ SPI 总线 ============ */
constexpr std::int8_t kSpiClkPin  = -1;  // [unknown]
constexpr std::int8_t kSpiMosiPin = -1;
constexpr std::int8_t kSpiMisoPin = -1;

/* ============ 音频 I2S（如有） ============ */
constexpr std::int8_t kI2sBclkPin   = -1;  // [unknown]
constexpr std::int8_t kI2sWsPin     = -1;
constexpr std::int8_t kI2sDinPin    = -1;  // MIC
constexpr std::int8_t kI2sDoutPin   = -1;  // SPK
constexpr std::int8_t kAmpEnablePin = -1;  // 功放使能/静音，上电默认态需防噪

/* ============ ADC / 模拟 ============ */
constexpr std::int8_t kBatteryAdcPin = -1;  // 优先 ADC1(GPIO1-10)，[unknown]

/* ============ 保留禁止清单（提醒，不可在业务中使用） ============ */
// ESP32-S3: GPIO22-25 不存在；GPIO26-32 接内部 Flash；
// GPIO33-37 在 Octal PSRAM 模组被占用；GPIO0/3/45/46 为 strapping；
// GPIO19/20 原生 USB；GPIO43/44 默认日志串口。

#else
#error "请先定义板型宏 {{BOARD_MACRO}}，并在 board_pins.h 中补齐本板事实"
#endif

}  // namespace board
