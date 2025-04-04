# UDP通信应用

## 项目简介

UDP通信应用是一个基于Qt框架开发的网络通信工具，采用模块化结构设计，实现了用户认证、本地/远程UDP通信等功能。该应用程序允许用户通过UDP协议进行数据传输和接收，支持本地模式和远程模式，并确保两种模式不能同时运行。

## 主要功能

- **用户认证系统**：安全的登录界面，验证用户身份
- **模式选择**：支持本地UDP通信和远程UDP通信两种模式
- **本地通信**：在本地计算机上不同端口之间进行UDP数据交换
- **远程通信**：与Python编写的远程UDP服务器进行通信
- **实时消息显示**：显示发送和接收的消息，包含时间戳和发送者信息
- **模式互斥**：确保本地和远程模式不能同时运行
- **完整日志记录**：记录系统运行状态和用户操作

## 项目结构

项目采用模块化结构设计，包含以下模块：

```
UDPCommunicator/
├── Core/                   # 核心功能模块
│   ├── Authentication.h/cpp  # 用户认证逻辑
│   └── AppManager.h/cpp      # 应用状态管理
├── UI/                     # 用户界面模块
│   ├── LoginWindow.h/cpp     # 登录界面
│   ├── ModeSelectionWindow.h/cpp  # 模式选择界面
│   └── CommunicationWindow.h/cpp  # 通信界面
├── Network/                # 网络通信模块
│   └── UDPManager.h/cpp      # UDP通信管理
├── Utils/                  # 实用工具模块
│   └── Logger.h/cpp          # 日志记录工具
├── Resources/              # 资源文件目录
└── Python/                 # Python UDP服务器
    └── udp_server.py         # 远程模式UDP服务器
```

## 开发环境

- Qt Creator 6.0+
- Qt 6.2+
- C++11
- Python 3.8+
- PyCharm (Python开发环境)

## 安装与运行

### Qt应用程序

1. 使用Qt Creator打开项目文件夹中的`UDPCommunicator.pro`
2. 配置项目构建设置
3. 点击"构建"按钮编译项目
4. 点击"运行"按钮启动应用程序

### Python UDP服务器

1. 使用PyCharm打开`Python/udp_server.py`
2. 确保安装了所需的Python库
3. 运行脚本启动UDP服务器

## 使用说明

1. **登录系统**
   - 启动应用程序后，输入用户名和密码登录
   - 默认用户：用户名`admin`，密码`password`

2. **选择通信模式**
   - 登录成功后，选择通信模式（本地或远程）
   - 本地模式：在本地计算机上不同端口之间通信
   - 远程模式：与Python UDP服务器通信

3. **通信操作**
   - 在输入框中输入要发送的消息
   - 点击"发送"按钮发送消息
   - 收到的消息会显示在消息记录区域
   - 点击"返回"按钮回到模式选择界面

## 技术特点

- 基于QUdpSocket实现UDP通信
- 采用信号-槽机制实现界面与逻辑的解耦
- 单例模式实现应用状态管理
- 完整的错误处理和日志记录
- 模块化架构，易于扩展和维护

## 注意事项

- 远程模式需要先启动Python UDP服务器
- 本地模式和远程模式不能同时运行
- 应用程序会在`application.log`文件中记录运行日志

## 协议

本项目仅用于学习和教育目的，基于MIT许可证开源。