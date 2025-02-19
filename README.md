# Saver3RB 桌面应用开发框架文档

## 目录
1. [框架概述](#框架概述)
2. [架构设计](#架构设计)
3. [核心模块说明](#核心模块说明)
   - [流处理模块](#流处理模块)
   - [网络通信模块](#网络通信模块)
   - [硬件信息模块](#硬件信息模块)
   - [窗口管理模块](#窗口管理模块)
   - [工具类模块](#工具类模块)
4. [开发指南](#开发指南)
5. [API 参考](#api-参考)
6. [扩展开发](#扩展开发)
7. [最佳实践](#最佳实践)
8. [已知问题与改进方向](#已知问题与改进方向)

---

## 框架概述
Saver3RB 是一个基于 C++ 的跨平台桌面应用开发框架，集成网络通信、硬件监控、资源管理和可视化界面功能。核心特性包括：

- 🖥️ 混合式架构：结合 Web 前端（HTML/JS）与原生 C++ 后端
- 📡 内置高性能网络服务器（TCP/HTTP 双协议支持）
- 📊 实时硬件监控（CPU/内存/GPU/磁盘）
- 🎨 现代化窗口效果（毛玻璃/透明背景/无边框）
- ⚙️ 模块化设计，支持快速功能扩展

---

## 架构设计
```plaintext
+---------------------+
|    Web 前端层       |
| (HTML/CSS/JavaScript) |
+----------+----------+
           |
+----------v----------+    +-------------------+
|   Native Bridge     <---->  C++ 核心逻辑层   |
+----------+----------+    +---------+---------+
           |                         |
+----------v----------+    +---------v---------+
|  窗口管理系统        |    | 网络通信系统       |
| (透明/毛玻璃效果)    |    | (TCP/HTTP Server)  |
+----------+----------+    +---------+---------+
           |                         |
+----------v----------+    +---------v---------+
| 硬件监控系统         |    | 资源管理系统       |
| (CPU/内存/GPU/磁盘)  |    | (文件/流处理)      |
+---------------------+    +-------------------+


核心模块说明
流处理模块
文件： stream.h
功能： 统一管理图片、视频、脚本等资源文件

``cpp
// 资源元数据结构
struct PrjectURL {
    std::string Name;  // 资源名称
    std::string URL;   // 存储路径
    std::string Type;  // 文件类型
    std::string Tag;   // 标签信息
};

// 全局资源向量
std::vector<PrjectURL> PIIEG;  // 图片
std::vector<PrjectURL> VIDEO;  // 视频
std::vector<PrjectURL> JavaSc; // JavaScript

// 序列化到文件
void OutFilePrject(std::vector<PrjectURL> File, std::string outfile);

// 从文件反序列化
void ReadFilePrject(std::vector<PrjectURL>* File, std::string outfile);

``

硬件信息模块
文件： InTypeSendSQL.h (ComeputerInfo 命名空间)
功能： 实时获取系统硬件数据

``cpp
// CPU 监控
class CPUinfor {
public:
    double getCpuUsage();       // 获取使用率
    double GettoCPUmhz();       // 获取当前频率
    std::wstring GetCPUName();  // 获取处理器型号
};

// 内存监控
class RamInfor {
public:
    double GetMemoryUsage();    // 内存使用率
    double GetMemoryMax();      // 总内存容量
};

// 系统硬件综合信息
class HardwareInfo {
public:
    struct GPUInfo { /*...*/ };
    struct DiskInfo { /*...*/ };
    
    std::vector<GPUInfo> GetGPUInfo();
    std::vector<DiskInfo> GetDiskInfo();
};
``

工具类模块
文件： InTypeSendSQL.h (EXTF 命名空间)
功能： 提供通用开发工具

``cpp

// 高性能计时器
class TimeData {
public:
    static void MkTimerMS(int* a, int ms); // 毫秒级计时
    static void MkTimerS(int* a, int s);   // 秒级计时
};

// 键盘监听
class Extm {
public:
    static void OpenThreadGetKey(char* c); // 启动按键监听线程
};

``

开发指南
环境要求
编译器：MSVC 2019+ / GCC 9.3+

依赖库：Win32 API, WebView2, PDH, WMI

推荐 IDE：Visual Studio 2022

项目配置

``cpp

// 窗口参数
int WHHight = GetSystemMetrics(SM_CYSCREEN); 
int WHWither = GetSystemMetrics(SM_CXSCREEN);
std::wstring RNAME = L"Saver3RB"; // 窗口标题

// 网络参数
int por = 11451; // 服务端口

``

API 参考
核心函数
函数签名	功能描述
IdWebOpen::OpenWeb()	启动内嵌浏览器窗口
IntelNet::InteS::MkIntNet()	初始化网络服务
ComeputerInfo::CPUinfor::getCpuUsage()	获取 CPU 使用率

扩展开发
添加新业务逻辑
在 OPEN.h 的 openWeb 函数中扩展处理逻辑：

``cpp
void openWeb(IntelNet::InteS& server, SOCKET clientSocket, 
           std::vector<std::string>Data, std::vector<std::string>Name) {
    
    // 示例：处理登录请求
    if(InquireName(Name, "login")) {
        std::string response = "<h1>Welcome " + Data[0] + "</h1>";
        std::string http = IntelNet::CreaPost("text/html", response, response.size());
        server.Send((char*)http.c_str(), http.size());
    }
}
``

最佳实践
硬件监控实现

``cpp
// 在 main.cpp 中启动监控线程
std::thread TimeGetCpuU([](){
    while(CpuUsergeButton) {
        CpuUserge = CPU.getCpuUsage();
        // 推送到前端
        std::string data = "CPU:" + std::to_string(CpuUserge);
        BroadcastToClients(data); 
    }
});
``

已知问题与改进方向
当前限制
窗口系统仅支持 Windows 平台

网络模块缺少 HTTPS 支持

硬件监控采样频率固定为 1Hz

规划特性
跨平台支持（Linux/macOS）

集成 SQLite 数据库

增加 GPU 温度监控

支持 WebSocket 通信
