# ESP32-C3 OLED SH1106 测试程序

[![GitHub License](https://img.shields.io/github/license/Prentice-svg/ESP32-C3-Super-mini)](LICENSE)
[![GitHub Stars](https://img.shields.io/github/stars/Prentice-svg/ESP32-C3-Super-mini)](https://github.com/Prentice-svg/ESP32-C3-Super-mini)

一个完整的ESP32-C3 Super Mini与11.3寸OLED屏幕(SH1106, SPI接口)的硬件验证测试程序。

## 🎯 项目概述

本项目使用**U8g2图形库**驱动SH1106 OLED屏幕，通过**软件SPI**实现可靠的硬件通信。程序循环显示5个测试阶段，全面验证屏幕的各项功能。

**特点**：
- ✅ 硬件已验证工作正常
- ✅ 所有代码包含详细的中文注释
- ✅ 模块化设计，易于扩展
- ✅ 完整的文档和示例

## 📋 硬件规格

| 参数 | 规格 |
|------|------|
| **微控制器** | Adafruit QT Py ESP32-C3 |
| **CPU** | 160 MHz RISC-V |
| **内存** | 320KB RAM, 4MB Flash |
| **OLED屏幕** | 11.3寸 SH1106, 128×64像素 |
| **通信方式** | SPI (软件模拟) |
| **电源** | 3.3V |

## 🔌 接线方案

### GPIO映射表

| OLED引脚 | 功能 | ESP32-C3 GPIO |
|---------|------|---------------|
| GND | 地线 | GND |
| VCC | 电源(3.3V) | 3V3 |
| SCK | SPI时钟 | GPIO6 |
| SDA | SPI数据(MOSI) | GPIO7 |
| CS | 片选 | GPIO5 |
| DC | 数据/命令选择 | GPIO1 |
| RES | 复位 | GPIO0 |

### 物理接线示意

```
ESP32-C3 Super Mini
┌─────────────────┐
│ 3V3 ── VCC      │
│ GND ── GND      │
│ G6  ── SCK      │  SH1106 OLED
│ G7  ── SDA      │  ┌──────────┐
│ G5  ── CS       │  │ 128×64px │
│ G1  ── DC       │  └──────────┘
│ G0  ── RES      │
└─────────────────┘
```

## 🚀 快速开始

### 前置要求

- Python 3.7+
- PlatformIO CLI
- USB转TTL串口线(可选，用于调试输出)

### 安装PlatformIO

```bash
pip install platformio
```

### 编译项目

```bash
pio run
```

### 上传到设备

```bash
pio run -t upload --upload-port /dev/cu.usbmodem1401
# 或在Linux/Windows上：
# pio run -t upload --upload-port COM3
```

### 查看串口输出

```bash
pio device monitor --baud 115200
```

## 📺 测试内容

程序循环显示5个测试阶段，每个阶段持续2秒：

### 阶段1: 欢迎屏幕
显示简单的文字和屏幕边框
- 标题: "OLED Test"
- 副标题: "ESP32-C3"
- 屏幕边框装饰

**目的**: 验证基本文字显示功能

### 阶段2: 基本图形
绘制线条和矩形
- 水平线
- 竖直线
- 填充矩形
- 空心矩形

**目的**: 验证直线和矩形绘制功能

### 阶段3: 圆形测试
绘制不同大小的圆形
- 空心圆(半径10)
- 空心圆(半径8)
- 填充圆(半径6)

**目的**: 验证圆形绘制功能

### 阶段4: 文字显示
演示不同大小的文字
- 大号字体 "Text Test"
- 小号字体 "Font: 8pt"

**目的**: 验证多种字体支持

### 阶段5: 综合测试
组合显示动态内容
- 实时循环计数
- 多个图形元素
- 验证刷新性能

**目的**: 验证动态内容显示和图形组合

## 📁 项目结构

```
ESP32-C3-Super-mini/
├── src/
│   ├── main.cpp              # 主程序入口
│   └── oled_test.cpp         # OLED测试功能实现
├── include/
│   ├── oled_test.h           # 测试函数接口声明
│   └── pins_config.h         # GPIO引脚配置
├── platformio.ini            # PlatformIO项目配置
├── CLAUDE.md                 # Claude Code开发指南
├── OLED_TEST_README.md       # 详细技术文档
├── README.md                 # 本文件
└── .gitignore               # Git忽略配置
```

## 📝 代码说明

### pins_config.h - GPIO配置

集中管理所有GPIO引脚映射：

```cpp
#define OLED_SCK   6      // GPIO6  - SPI时钟
#define OLED_SDA   7      // GPIO7  - SPI数据
#define OLED_CS    5      // GPIO5  - 片选
#define OLED_DC    1      // GPIO1  - 数据/命令
#define OLED_RES   0      // GPIO0  - 复位
```

### oled_test.cpp - 测试实现

实现5个独立的测试函数：
- `testWelcomeScreen()` - 欢迎屏幕
- `testBasicShapes()` - 基本图形
- `testCircles()` - 圆形
- `testText()` - 文字
- `testCombined()` - 综合测试

### main.cpp - 主程序

```cpp
void setup() {
    // 初始化串口和OLED
    initSerial();
    delay(2000);  // 等待OLED电源稳定
    initOLED();
}

void loop() {
    // 根据时间切换测试阶段
    int stage = getCurrentTestStage();
    // 执行对应测试函数...
}
```

## 🔧 自定义与扩展

### 修改GPIO引脚

编辑 `include/pins_config.h`：

```cpp
#define OLED_SCK   6      // 改为你的SCK GPIO
#define OLED_SDA   7      // 改为你的SDA GPIO
// ... 修改其他引脚
```

### 修改阶段显示时间

编辑 `include/pins_config.h`：

```cpp
#define TEST_STAGE_DURATION_MS 2000  // 改为所需毫秒数
```

### 添加新的测试阶段

1. 在 `include/oled_test.h` 中声明函数
2. 在 `src/oled_test.cpp` 中实现函数
3. 在 `src/main.cpp` 的 switch 语句中添加新的 case

## 🎨 使用U8g2绘制

### 常用API

```cpp
u8g2.clearBuffer();              // 清空缓冲区
u8g2.sendBuffer();               // 发送到屏幕
u8g2.setFont(...);               // 设置字体
u8g2.drawStr(x, y, "text");     // 绘制文字
u8g2.drawLine(x1, y1, x2, y2);  // 绘制线条
u8g2.drawBox(x, y, w, h);       // 绘制填充矩形
u8g2.drawFrame(x, y, w, h);     // 绘制空心矩形
u8g2.drawCircle(x, y, r);       // 绘制空心圆
u8g2.drawDisc(x, y, r);         // 绘制填充圆
```

详见: [U8g2文档](https://github.com/olikraus/u8g2/wiki/u8g2reference)

## 📊 性能指标

| 指标 | 数值 |
|------|------|
| Flash占用 | 263 KB (20.1%) |
| RAM占用 | 15 KB (4.7%) |
| 屏幕刷新率 | ~20 Hz |
| SPI模式 | 软件模拟 |
| 显示分辨率 | 128×64像素 |

## 🐛 故障排查

### 屏幕不显示任何内容

**检查项**:
1. ✓ VCC和GND极性是否正确
2. ✓ 所有接线是否插接牢固
3. ✓ GPIO引脚定义是否与实际接线一致
4. ✓ ESP32-C3是否正常工作（尝试其他程序）

**解决方案**:
- 检查 `include/pins_config.h` 中的GPIO定义
- 确保3.3V电源稳定
- 尝试重新上传固件

### 屏幕显示乱码

**可能原因**:
- 接线不稳定
- 供电不足
- SPI通信时序问题

**解决方案**:
- 检查所有接线连接
- 添加电容到电源(0.1µF和10µF并联)
- 确保ESP32-C3和OLED共享同一个GND

### 串口无输出

**可能原因**:
- 波特率设置错误
- USB驱动问题
- 串口端口选择错误

**解决方案**:
- 确认波特率为115200
- 检查USB连接和驱动
- 运行 `pio device list` 查看可用端口

## 📚 相关资源

- [U8g2项目](https://github.com/olikraus/u8g2) - 图形库文档
- [ESP32-C3数据手册](https://www.espressif.com/sites/default/files/documentation/esp32-c3_datasheet_cn.pdf) - 微控制器规格
- [SH1106控制器](https://www.solomon-systech.com/zh_CN/product/sh1106/) - OLED驱动IC
- [PlatformIO文档](https://docs.platformio.org/) - 构建和上传工具

## 💡 下一步建议

- [ ] 添加按钮交互控制
- [ ] 集成传感器数据显示
- [ ] 实现WiFi连接
- [ ] 添加蓝牙功能
- [ ] 创建OTA固件更新
- [ ] 开发完整的UI框架

## 📄 许可证

MIT License - 详见 [LICENSE](LICENSE) 文件

## 🤝 贡献

欢迎提交Issue和Pull Request！

## 👤 作者

- **Claude Code** - AI编程助手
- **Prentice-svg** - 项目所有者

## 📞 联系方式

GitHub: [@Prentice-svg](https://github.com/Prentice-svg)

---

**更新时间**: 2026年2月

**项目状态**: ✅ 完成并验证
