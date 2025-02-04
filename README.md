# C++框架开发文档

## 文件结构说明

### 1. InTypeSendSQL.h
#### 核心功能模块
```cpp
namespace ICSQL {
    class Var { // 多类型变量容器及进制转换工具
        // 成员变量: 支持int/double/string等基础类型及指针
        // 核心方法:
        - Fpont_Self()        // 指针自绑定
        - Turn_binary()       // 十进制转二进制
        - BinToDEX()          // 二进制转十进制
        - Automatic_sorting() // 数组自动排序
        - DexToHex()          // 十进制转十六进制
    };
}

namespace EXTF {
    class Extm { // 键盘监听模块
        // 核心方法:
        - OpenThreadGetKey()  // 启动异步键盘监听
        - ThreadGetKey()      // 键盘输入捕获线程
    };

    class TimeData { // 计时器系统
        // 核心方法:
        - MkTimerS()          // 创建秒级计时器
        - MkTimerMS()         // 创建毫秒级计时器
        - GetNow***()系列     // 获取系统时间组件
    };
}

namespace IntelNet {
    class InteS { // 网络通信核心
        // 成员变量:
        - EMA4096等接收缓冲区
        - OnlineSet 网络参数配置结构体
        
        // 核心方法:
        - MkIntNet()          // 创建网络服务端
        - Recv()/Send()       // 数据收发接口
        - CreaPost()系列      // HTTP协议构造工具
        - GetNAME()/GetData() // HTTP参数解析
    };
}

namespace ComeputerInfo {
    class RamInfor { // 内存信息模块
        // 核心方法:
        - GetMemoryUsage()    // 内存使用率
        - GetMemoryModuleInfo() // 内存硬件信息
    };

    class CPUinfor { // CPU监控模块
        // 核心方法:
        - getCpuUsage()       // CPU使用率
        - GettoCPUmhz()       // 实时频率监测
    };

    class HardwareInfo { // 硬件综合信息
        // 核心数据结构:
        - GPUInfo/DiskInfo/SystemInfo
        
        // 核心方法:
        - GetGPUInfo()        // 显卡信息获取
        - GetDiskInfo()       // 硬盘信息扫描
        - GetSystemInfo()     // 系统信息整合
    };
}

namespace CreaWindowts {
    class AsyncWindow { // 异步窗口管理
        // 核心方法:
        - Start()             // 启动窗口线程
        - WindowProc()        // 窗口消息处理
    };
    
    // 实用函数:
    - WebNotSize()           // 窗口尺寸锁定
    - SetWebAlpha()          // 透明度控制
    - EnableBlurBehindWindow() // 毛玻璃效果
}
```
<br><h2>main.cpp文件</h2>
```cpp
// 全局状态:
- g_bRunning                // 程序运行标志
- CpuUserge/CpuMhz          // CPU监控变量

// 核心函数:
- main()                    // 主入口
  ├─ 资源初始化
  ├─ 启动监控线程
  ├─ 创建浏览器窗口
  └─ 启动网络服务

- OpenNet()                 // 网络服务初始化
  ├─ 窗口属性设置
  ├─ 创建TCP服务端
  └─ 客户端连接管理

- HandleClient()            // 客户端请求处理
  ├─ 数据接收解析
  └─ 调用业务逻辑
```
<br><h2>OPEN.h文件</h2>
```cpp
// 系统参数:
- WHHight/WHWither          // 屏幕分辨率

// 硬件监控实例:
- CPU/RAM/HAR               // 各硬件模块实例

// 业务函数声明:
- openWeb()                 // 网页业务处理入口
```

<br><h2>stream.h文件</h2>
```cpp
// 数据结构:
struct PrjectURL {          // 资源描述结构体
    string Name/URL/Type/Tag
}

// 资源向量:
- PIIEG/VIDEO/JavaSc        // 分类资源存储

// 文件操作:
- OutFilePrject()           // 资源序列化存储
- ReadFilePrject()          // 资源反序列化加载
```


<br><h2>功能流程图</h2>
```cpp
程序启动
├─ 初始化硬件监控线程
├─ 加载本地资源文件
├─ 创建浏览器窗口
└─ 启动网络服务
   ├─ 监听客户端连接
   └─ 异步处理请求
       ├─ 解析HTTP参数
       └─ 执行对应硬件操作

接口实例
// 获取CPU信息
double usage = CPU.getCpuUsage();
wstring name = CPU.GetCPUNameFromRegistry();

// 创建网络服务
IntelNet::InteS server;
server.OSset.port = 8080;
server.MkIntNet();

// 资源文件操作
ReadFilePrject(&PIIEG, "resources.txt");

注意事项
网络模块需先调用OpenIntOP()初始化Winsock

硬件信息获取需要管理员权限

窗口模块依赖WebView2运行时环境

资源文件按四行一组格式存储(Name/URL/Type/Tag)

```
