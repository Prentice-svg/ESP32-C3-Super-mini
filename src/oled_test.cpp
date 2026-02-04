#include <Arduino.h>
#include "pins_config.h"
#include "oled_test.h"

// ============================================
// OLED驱动对象实例化
// ============================================

// U8g2软件SPI驱动初始化
// 改用软件SPI以确保GPIO正确配置
// 软件SPI虽然速度略慢，但更可靠，128x64屏幕完全足够
//
// 构造函数参数:
//   U8G2_R0       - 旋转角度(0度)
//   OLED_SCK      - SPI时钟 GPIO6
//   OLED_SDA      - SPI MOSI GPIO7
//   OLED_CS       - 片选 GPIO5
//   OLED_DC       - 数据/命令 GPIO1
//   OLED_RES      - 复位 GPIO0
U8G2_SH1106_128X64_NONAME_F_4W_SW_SPI u8g2(
    U8G2_R0,           // 旋转角度(0度)
    OLED_SCK,          // SPI时钟 GPIO6
    OLED_SDA,          // SPI MOSI GPIO7
    OLED_CS,           // 片选 GPIO5
    OLED_DC,           // 数据/命令 GPIO1
    OLED_RES           // 复位 GPIO0
);

// ============================================
// 初始化函数实现
// ============================================

/**
 * 初始化OLED屏幕
 */
void initOLED() {
    // 延迟确保屏幕电源稳定
    delay(100);

    Serial.println("[OLED] 启动U8g2驱动...");

    // 启动U8g2驱动
    // 这会自动执行SPI初始化、GPIO配置、屏幕复位和初始化
    u8g2.begin();

    Serial.println("[OLED] U8g2驱动启动成功");

    // 延迟给屏幕时间完成内部初始化
    delay(100);

    // 设置默认字体(8点宽度的sans-serif字体)
    u8g2.setFont(u8g2_font_ncenB08_tr);

    // 设置字体模式为透明(0=不透明, 1=透明背景)
    u8g2.setFontMode(1);

    // 启用显示
    u8g2.setDisplayRotation(U8G2_R0);  // 0度旋转

    // 设置对比度(可选，范围0-255)
    u8g2.setContrast(128);

    // 清屏显示
    u8g2.clearBuffer();
    u8g2.sendBuffer();

    Serial.println("[OLED] OLED屏幕初始化完成");
    Serial.println("[OLED] 屏幕应该显示黑屏");
}

/**
 * 初始化串口调试输出
 */
void initSerial() {
    // 启动串口，波特率115200
    Serial.begin(SERIAL_BAUD);

    // 等待串口就绪
    delay(500);

    // 打印启动信息
    Serial.println("");
    Serial.println("========================================");
    Serial.println("    ESP32-C3 OLED SH1106 测试程序");
    Serial.println("========================================");
    Serial.println("[初始化] 串口初始化完成，波特率: 115200");
}

// ============================================
// 测试用例实现 - 5个显示阶段
// ============================================

/**
 * 测试阶段1: 欢迎屏幕
 * 显示简单的欢迎信息和屏幕边框
 */
void testWelcomeScreen() {
    // 清空显示缓冲区
    u8g2.clearBuffer();

    // 设置较大的字体显示主标题
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.drawStr(20, 30, "OLED Test");

    // 切换回小字体显示副标题
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(25, 50, "ESP32-C3");

    // 绘制屏幕边框
    drawBorder();

    // 发送缓冲区内容到屏幕显示
    u8g2.sendBuffer();

    // 串口输出调试信息
    Serial.println("[第1阶段] 欢迎屏幕 - OLED Test");
}

/**
 * 测试阶段2: 基本图形测试
 * 测试绘制线条和矩形功能
 */
void testBasicShapes() {
    u8g2.clearBuffer();

    // 显示标题
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(5, 10, "Lines & Boxes");

    // 绘制水平线 (从点(10,20)到点(60,20))
    u8g2.drawLine(10, 20, 60, 20);

    // 绘制竖直线 (从点(80,20)到点(80,50))
    u8g2.drawLine(80, 20, 80, 50);

    // 绘制填充矩形 (x=20, y=30, 宽=30, 高=20)
    u8g2.drawBox(20, 30, 30, 20);

    // 绘制空心矩形 (x=70, y=30, 宽=50, 高=30)
    u8g2.drawFrame(70, 30, 50, 30);

    // 绘制屏幕边框
    drawBorder();

    // 发送到屏幕
    u8g2.sendBuffer();

    Serial.println("[第2阶段] 基本图形 - 直线和矩形");
}

/**
 * 测试阶段3: 圆形绘制测试
 * 测试绘制空心圆和填充圆
 */
void testCircles() {
    u8g2.clearBuffer();

    // 显示标题
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(35, 10, "Circles");

    // 绘制空心圆1 (圆心x=30, y=38, 半径=10)
    u8g2.drawCircle(30, 38, 10);

    // 绘制空心圆2 (圆心x=65, y=38, 半径=8)
    u8g2.drawCircle(65, 38, 8);

    // 绘制填充圆 (圆心x=100, y=38, 半径=6)
    u8g2.drawDisc(100, 38, 6);

    // 绘制屏幕边框
    drawBorder();

    // 发送到屏幕
    u8g2.sendBuffer();

    Serial.println("[第3阶段] 圆形测试 - 空心圆和填充圆");
}

/**
 * 测试阶段4: 文字显示测试
 * 演示不同大小的文字显示
 */
void testText() {
    u8g2.clearBuffer();

    // 显示大号标题
    u8g2.setFont(u8g2_font_ncenB12_tr);
    u8g2.drawStr(15, 25, "Text Test");

    // 显示小号副标题
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(10, 45, "Font: 8pt");

    // 绘制屏幕边框
    drawBorder();

    // 发送到屏幕
    u8g2.sendBuffer();

    Serial.println("[第4阶段] 文字显示 - 多种字体大小");
}

/**
 * 测试阶段5: 综合显示测试
 * 组合显示循环计数+多个图形元素
 * 验证屏幕能否流畅显示动态内容
 */
void testCombined() {
    // 静态变量用于记录循环次数
    static unsigned long testCounter = 0;

    u8g2.clearBuffer();

    // 显示循环计数标题
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(5, 12, "Cycle:");

    // 将循环计数转换为字符串显示
    char buffer[20];
    sprintf(buffer, "%lu", testCounter++);
    u8g2.drawStr(60, 12, buffer);

    // 绘制水平分割线
    u8g2.drawLine(10, 30, 118, 30);

    // 绘制圆形
    u8g2.drawCircle(64, 45, 12);

    // 绘制填充矩形
    u8g2.drawBox(20, 50, 25, 10);

    // 绘制空心矩形
    u8g2.drawFrame(85, 50, 25, 10);

    // 绘制屏幕边框
    drawBorder();

    // 发送到屏幕
    u8g2.sendBuffer();

    // 串口输出，包含当前循环计数
    Serial.print("[第5阶段] 综合显示 [循环次数: ");
    Serial.print(testCounter);
    Serial.println("]");
}

// ============================================
// 工具函数实现
// ============================================

/**
 * 获取当前测试阶段
 * 根据运行时间自动切换不同的测试阶段
 * 每个阶段持续TEST_STAGE_DURATION_MS毫秒(默认2秒)
 * 5个阶段循环显示
 *
 * @return 当前阶段号 (0-4)
 */
int getCurrentTestStage() {
    // 静态变量记录上次阶段切换的时间
    static unsigned long lastStageTime = 0;

    // 静态变量记录当前阶段号
    static int currentStage = 0;

    // 获取当前运行时间(毫秒)
    unsigned long currentTime = millis();

    // 检查是否需要切换到下一个阶段
    if (currentTime - lastStageTime >= TEST_STAGE_DURATION_MS) {
        // 更新时间戳
        lastStageTime = currentTime;

        // 切换到下一个阶段，循环显示(0->1->2->3->4->0...)
        currentStage = (currentStage + 1) % 5;

        // 串口打印阶段切换信息
        Serial.print("[时间] ");
        Serial.print(currentTime / 1000);
        Serial.println(" 秒 - 切换到新阶段");
    }

    return currentStage;
}

/**
 * 绘制屏幕边框
 * 在整个显示缓冲区周围绘制一个矩形边框
 * 用于美化和区分显示区域
 */
void drawBorder() {
    // drawFrame参数说明:
    //   x=0, y=0 - 起始坐标(左上角)
    //   width=OLED_WIDTH(128) - 宽度
    //   height=OLED_HEIGHT(64) - 高度
    u8g2.drawFrame(0, 0, OLED_WIDTH, OLED_HEIGHT);
}
