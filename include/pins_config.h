#ifndef PINS_CONFIG_H
#define PINS_CONFIG_H

// ============================================
// OLED SH1106 硬件接口定义
// ============================================

// SPI总线引脚配置
#define OLED_SCK   6      // GPIO6  - SPI时钟(Clock)
#define OLED_SDA   7      // GPIO7  - SPI主输出(MOSI/Data)
#define OLED_CS    5      // GPIO5  - 片选(Chip Select)
#define OLED_DC    1      // GPIO1  - 数据/命令选择(Data/Command)
#define OLED_RES   0      // GPIO0  - 复位(Reset)

// ============================================
// 屏幕参数
// ============================================

#define OLED_WIDTH  128   // 屏幕宽度(像素)
#define OLED_HEIGHT 64    // 屏幕高度(像素)

// ============================================
// 调试串口配置
// ============================================

#define SERIAL_BAUD 115200  // 波特率

// ============================================
// 测试参数
// ============================================

#define TEST_STAGE_DURATION_MS 2000  // 每个测试阶段持续时间(毫秒)

#endif // PINS_CONFIG_H
