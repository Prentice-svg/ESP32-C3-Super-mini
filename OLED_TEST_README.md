# ESP32-C3 OLED SH1106 测试程序

## 程序说明

这是一个针对ESP32-C3 Super Mini与11.3寸OLED屏幕(SH1106, SPI接口)的硬件验证测试程序。

**功能**: 循环显示5个测试阶段，验证OLED屏幕的正常工作。

**库使用**: U8g2库 (v2.33.0+)

## 硬件接线

| OLED引脚 | 功能 | ESP32-C3 GPIO | 说明 |
|---------|------|---------------|------|
| GND | 地线 | GND | 电源地 |
| VCC | 电源 | 3V3 | 3.3V电源 |
| SCK | SPI时钟 | GPIO6 | 硬件SPI SCLK |
| SDA | SPI数据 | GPIO7 | 硬件SPI MOSI |
| RES | 复位 | GPIO0 | 复位信号 |
| DC | 数据/命令 | GPIO1 | 数据/命令选择 |
| CS | 片选 | GPIO5 | SPI片选 |

**接线提示**:
- 确保VCC和GND连接正确(反向接线会损坏芯片)
- 所有信号线使用3.3V逻辑(不要接5V)
- 可选：在VCC和GND之间添加0.1µF去耦电容

## 测试内容

程序循环显示5个测试阶段，每个阶段持续2秒：

### 阶段1: 欢迎屏幕
- 显示标题文字 "OLED Test"
- 显示副标题 "ESP32-C3"
- 显示屏幕边框

**目的**: 验证屏幕基本显示能力和文字显示功能

### 阶段2: 基本图形
- 绘制水平线
- 绘制竖直线
- 绘制填充矩形
- 绘制空心矩形

**目的**: 验证直线和矩形绘制功能

### 阶段3: 圆形绘制
- 绘制空心圆(半径10)
- 绘制空心圆(半径8)
- 绘制填充圆(半径6)

**目的**: 验证圆形绘制功能

### 阶段4: 文字显示
- 显示大号字体文本 "Text Test"
- 显示小号字体文本 "Font: 8pt"
- 显示屏幕边框

**目的**: 验证不同字体大小的显示

### 阶段5: 综合测试
- 显示循环计数(实时更新)
- 绘制水平分割线
- 绘制圆形
- 绘制多个矩形

**目的**: 验证动态内容刷新和多个图形元素的组合显示

## 编译和上传

### 编译项目
```bash
python3 -m platformio run
# 或简化为
pio run
```

输出文件: `.pio/build/adafruit_qtpy_esp32c3/firmware.bin`

### 上传到设备
```bash
python3 -m platformio run -t upload
# 或
pio run -t upload
```

### 串口监视(调试输出)
```bash
python3 -m platformio device monitor --baud 115200
# 或
pio device monitor --baud 115200
```

## 串口输出示例

```
========================================
    ESP32-C3 OLED SH1106 测试程序
========================================
[初始化] 串口初始化完成，波特率: 115200
[OLED] OLED屏幕初始化完成
[初始化] Setup函数执行完成，开始测试循环
========================================
[第1阶段] 欢迎屏幕 - OLED Test
[第1阶段] 欢迎屏幕 - OLED Test
[时间] 2 秒 - 切换到新阶段
[第2阶段] 基本图形 - 直线和矩形
[第2阶段] 基本图形 - 直线和矩形
[时间] 4 秒 - 切换到新阶段
[第3阶段] 圆形测试 - 空心圆和填充圆
...
```

## 故障排查

### 屏幕不显示任何内容

**可能原因**:
1. GPIO接线错误
2. 电源接线反向
3. U8g2库未正确安装

**解决方法**:
- 检查pins_config.h中的GPIO定义是否与实际接线一致
- 检查VCC和GND极性
- 运行 `python3 -m platformio lib install "olikraus/U8g2"` 重新安装库

### 屏幕显示乱码或花屏

**可能原因**:
- SPI通信速率过高
- 接线不稳定或接触不良
- 供电不足

**解决方法**:
- 检查所有接线连接是否牢固
- 确保ESP32-C3和OLED共享同一个GND
- 尝试添加电容到电源(0.1µF和10µF并联)

### 串口无输出

**可能原因**:
- 波特率不匹配
- COM端口选择错误
- USB驱动问题

**解决方法**:
- 检查波特率设置为115200
- 尝试 `pio device list` 查看可用端口
- 重新连接USB,让设备重新枚举

### 编译错误

**可能原因**:
- U8g2库版本不兼容
- 包含文件路径错误

**解决方法**:
- 清理构建: `python3 -m platformio run -t clean`
- 重新编译: `python3 -m platformio run`

## 代码结构

```
ESP32-C3-Super-mini/
├── platformio.ini          # 项目配置,包含U8g2库依赖
├── src/
│   ├── main.cpp           # 主程序入口
│   └── oled_test.cpp      # OLED测试功能实现(5个测试用例)
├── include/
│   ├── pins_config.h      # GPIO引脚配置和常量定义
│   └── oled_test.h        # 测试函数接口声明
└── OLED_TEST_README.md    # 本文档
```

### 关键文件说明

**pins_config.h**:
- 集中管理所有GPIO引脚映射
- 定义屏幕参数(分辨率、测试时间等)
- 修改GPIO接线时只需改这个文件

**oled_test.h**:
- 定义所有测试函数的接口
- 包含详细的函数文档

**oled_test.cpp**:
- 实现5个测试阶段的具体逻辑
- 实现初始化和工具函数
- 所有代码都有中文注释

**main.cpp**:
- setup()函数：初始化串口和OLED
- loop()函数：循环执行5个测试阶段

## 自定义和扩展

### 修改阶段显示时间

编辑 `include/pins_config.h`:
```cpp
#define TEST_STAGE_DURATION_MS 2000  // 改为所需毫秒数
```

### 修改GPIO引脚

编辑 `include/pins_config.h`:
```cpp
#define OLED_SCK   6      // 改为你的SCK GPIO
#define OLED_SDA   7      // 改为你的SDA GPIO
// ... 修改其他引脚
```

### 添加新的测试阶段

1. 在 `include/oled_test.h` 中声明新函数
2. 在 `src/oled_test.cpp` 中实现函数
3. 在 `src/main.cpp` 的 switch 语句中添加新的 case

### 显示自定义内容

在测试函数中使用U8g2 API:
```cpp
u8g2.clearBuffer();           // 清空缓冲区
u8g2.setFont(...);            // 设置字体
u8g2.drawStr(x, y, "text");  // 绘制文字
u8g2.drawLine(x1, y1, x2, y2); // 绘制线条
u8g2.drawBox(x, y, w, h);    // 绘制填充矩形
u8g2.drawFrame(x, y, w, h);  // 绘制空心矩形
u8g2.drawCircle(x, y, r);    // 绘制空心圆
u8g2.drawDisc(x, y, r);      // 绘制填充圆
u8g2.sendBuffer();            // 发送到屏幕显示
```

U8g2完整API文档: https://github.com/olikraus/u8g2/wiki/u8g2reference

## 常见问题

**Q: 可以用其他OLED驱动IC(如SSD1306)吗?**
A: 可以。修改oled_test.cpp中的驱动器类定义，改为 `U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI` 即可。

**Q: 如何添加中文显示?**
A: U8g2支持中文字库，但需要额外配置。参考: https://github.com/olikraus/u8g2/wiki/fntlistall

**Q: 屏幕支持的分辨率是多少?**
A: 128×64像素。

**Q: 可以显示图片吗?**
A: 可以。U8g2支持XBM格式位图。

**Q: 程序占用多少flash/RAM?**
A: Flash约265KB(占总容量的20.2%), RAM约15KB(占总容量的4.7%)。

## 许可证和作者

程序使用U8g2库(开源BSD许可)

修改和使用此程序无限制。

---

**最后更新**: 2026年2月
**基于**: PlatformIO + Arduino框架 + U8g2库
