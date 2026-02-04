#include <Arduino.h>
#include <SPI.h>
#include "pins_config.h"
#include "oled_test.h"

// ============================================
// ESP32-C3 OLED SH1106 测试程序 - 优化版
// ============================================

void setup() {
    // 初始化串口调试输出 (115200 baud)
    initSerial();

    // 延迟确保串口就绪
    delay(500);

    Serial.println("");
    Serial.println("=== 详细初始化过程 ===");

    // 延迟2秒，给OLED屏幕电源稳定时间
    Serial.println("[步骤1] 等待OLED电源稳定...");
    for (int i = 0; i < 20; i++) {
        Serial.print(".");
        delay(100);
    }
    Serial.println(" 完成 (2秒)");

    // 初始化OLED屏幕
    Serial.println("[步骤2] 初始化OLED屏幕...");
    initOLED();

    // 打印初始化完成信息
    Serial.println("");
    Serial.println("=== 初始化完成 ===");
    Serial.println("[状态] 以下内容应该显示在屏幕上:");
    Serial.println("  - 第1阶段: 欢迎屏幕 (2秒)");
    Serial.println("  - 第2阶段: 线条和矩形 (2秒)");
    Serial.println("  - 第3阶段: 圆形 (2秒)");
    Serial.println("  - 第4阶段: 文字 (2秒)");
    Serial.println("  - 第5阶段: 综合测试循环计数 (2秒)");
    Serial.println("  - 然后循环重复...");
    Serial.println("");
    Serial.println("[监测] 串口输出应该每2秒显示一次阶段切换");
    Serial.println("========================================");
}

void loop() {
    // 获取当前应该显示的测试阶段 (0-4)
    int stage = getCurrentTestStage();

    // 根据阶段号执行对应的测试函数
    switch (stage) {
        // 阶段0: 欢迎屏幕
        case 0:
            testWelcomeScreen();
            break;

        // 阶段1: 基本图形(线、矩形)
        case 1:
            testBasicShapes();
            break;

        // 阶段2: 圆形绘制
        case 2:
            testCircles();
            break;

        // 阶段3: 文字显示
        case 3:
            testText();
            break;

        // 阶段4: 综合显示(动态计数+多个图形)
        case 4:
            testCombined();
            break;

        // 默认情况(不应该发生)
        default:
            break;
    }

    // 延迟50毫秒，避免过度刷新屏幕
    // 这样总的刷新频率约为20Hz
    delay(50);
}