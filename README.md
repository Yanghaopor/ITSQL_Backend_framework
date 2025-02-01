# ITSQL_Backend_framework
-这是一个用来搭建网站与应用的框架，且可进行自定义<br>
-现在是个简单的搭建教程<br>
-1.下载此框架，框架包含3个文件与一个文件夹:<br>
-(1)main.cpp 这个文件包含框架基础框架，所有逻辑检测与工作写到这里面<br>
-(2)InTypeSendSQL.h 这个文件是整个框架的基础，实现函数与类在这里面<br>
-(3)stream.h 这个文件是存储类文件用来写入导入修改文件<br>
-(4)Saver 这个文件夹是存储基础网站，js，图片，视频文件的<br>
<br>
-1.用VS2022 - VS2017 创建一个空项目<br>
-2.将所有框架文件复制到你的项目文件<br>
-3.将main.cpp放入你的源文件中<br>
-4.将InTypeSendSQL.h和stream.h 放入你的头文件中<br>
-至此框架搭建完毕<br>
<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>InTypeSendSQL.h 开发文档</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            line-height: 1.6;
            margin: 20px;
        }
        h1, h2, h3 {
            color: #333;
        }
        code {
            background-color: #f4f4f4;
            padding: 2px 5px;
            border-radius: 3px;
            font-family: monospace;
        }
        pre {
            background-color: #f4f4f4;
            padding: 10px;
            border-radius: 5px;
            overflow-x: auto;
        }
        .section {
            margin-bottom: 30px;
        }
    </style>
</head>
<body>

<h1>InTypeSendSQL.h 开发文档</h1>

<div class="section">
    <h2>1. 概述</h2>
    <p>该文件定义了一个名为 <code>ICSQL::Var</code> 的类，用于处理多种数据类型和进制转换。此外，文件还包含了一些额外的功能，如网络设置、计时器、键盘监听、窗口管理等。</p>
</div>

<div class="section">
    <h2>2. 主要类与功能</h2>
    <h3>2.1 ICSQL::Var 类</h3>
    <p><code>ICSQL::Var</code> 类用于存储和操作多种数据类型，包括整数、浮点数、布尔值、字符串等。它还提供了进制转换、排序等功能。</p>
    <pre><code>
namespace ICSQL {
    class Var {
    private:
        std::stack&lt;std::string&gt; T_DEX; // 进制存储栈
        std::stack&lt;int&gt; T_DEXC; // 进制存储栈

    public:
        // 类型定义
        int Int;
        double Double;
        bool Bool;
        std::wstring Wstring;
        std::string String;
        char Char;

        // 指针类型
        int* Int_f;
        double* Double_f;
        bool* Bool_f;
        std::wstring* Wstring_f;
        std::string* String_f;
        char* Char_f;

        // 方法
        void Fpont_Self(); // 指针类型指向自己
        void InitVar(); // 初始化变量
        void D_bug(); // 调试输出
        void Turn_binary(int tobe, std::string* Mube); // 二进制转换
        int BinToDEX(std::string Bin, int Leng); // 二进制转十进制
        void Automatic_sorting(double A[], bool Be, int Nme); // 自动排序
        std::string DexTOoct(int Dex); // 十进制转八进制
        int OoctToDex(std::string Bin, int Leng); // 八进制转十进制
        void DexToHex(int DEX, std::string* HEX); // 十进制转十六进制
        int HexToDex(std::string Hex, int Len); // 十六进制转十进制
    };
}
    </code></pre>

    <h3>2.2 EXTF::Extm 类</h3>
    <p><code>EXTF::Extm</code> 类提供了键盘监听和多线程支持。</p>
    <pre><code>
namespace EXTF {
    class Extm {
    private:
        static bool GetKeyBool; // 控制监听键盘
        static bool GetUndGetKey; // 控制线程段性监听

        static void ThreadGetKey(char* c); // 线程获取输入监听
        static void ThreadUndGetKey(char* c); // 线程段性监听

    public:
        static void OpenThreadUndGetKey(char* c); // 运行多线程段性监听
        static void OpenThreadGetKey(char* c); // 运行多线程监听
        static void OffGetKey(); // 关闭线程监听
        static void OpenGetKey(); // 开启多线程监听
        static void OffUndGetKey(); // 关闭段性线程监听
        static void OpenUndGetKey(); // 开启段性线程监听
    };
}
    </code></pre>

    <h3>2.3 EXTF::TimeData 类</h3>
    <p><code>EXTF::TimeData</code> 类提供了计时器功能，支持秒和毫秒级别的计时。</p>
    <pre><code>
namespace EXTF {
    class TimeData {
    private:
        static void TimerS(int* a, int s); // 秒计时器
        static void TimermS(int* a, int ms); // 毫秒计时器
        static bool TimerS_Butten; // 秒计时器开关
        static bool TimerMS_Butten; // 毫秒计时器开关

    public:
        static void MkTimerS(int* a, int s); // 创建以秒计时的计时器
        static void MkTimerMS(int* a, int ms); // 创建以毫秒计时的计时器
        static void DeletTimr_s(); // 关闭秒计时器
        static void DeletTimr_Ms(); // 关闭毫秒计时器
        static void OpenTimr_s(); // 开启秒计时器
        static void OpenTimr_Ms(); // 开启毫秒计时器

        // 获取当前时间
        int GetNowYear();
        int GetNowMonth();
        int GetNowDayOfWeek();
        int GetNowDay();
        int GetNowHour();
        int GetNowMinute();
        int GetNowSecond();
        int GetNowMilliseconds();
    };
}
    </code></pre>

    <h3>2.4 IntelNet::InteS 类</h3>
    <p><code>IntelNet::InteS</code> 类用于网络设置和通信，支持TCP和UDP协议。</p>
    <pre><code>
namespace IntelNet {
    class InteS {
    private:
        WSADATA Wser; // 网络安全类
        SOCKET sock; // 网络套接字
        sockaddr_in AddSock; // 链接套接字

        struct OnlineSet {
            int port; // 端口设置
            bool agreement; // 网络协议 true为TCP，false为UDP
            std::string IPCL; // IP地址存储
            int Namber = NULL; // 接收人数
        };

    public:
        void OpenIntOP(); // 打开网络权限
        char EMA1024[1024] = { 0 }; // 1024标准接收字符
        char EMA2048[2048] = { 0 }; // 2048标准接收字符
        char EMA4096[4096] = { 0 }; // 4096标准接收字符
        OnlineSet OSset; // 网络参数
        SOCKET reception; // 接收套接字

        void MkIntNet(); // 创建网络
        void FluRecSock(); // 刷新套接字
        void Recv(char c[], int Len); // 接收数据
        void Send(char c[], int Len); // 发送数据
        SOCKET GetScok(); // 获取套接字
    };
}
    </code></pre>

    <h3>2.5 ComeputerInfo::CPUinfor 类</h3>
    <p><code>ComeputerInfo::CPUinfor</code> 类用于获取CPU的相关信息，包括使用率、频率和名称。</p>
    <pre><code>
namespace ComeputerInfo {
    class CPUinfor {
    private:
        __int64 Filetime2Int64(const FILETIME& ftime);
        __int64 CompareFileTime2(const FILETIME& preTime, const FILETIME& nowTime);

    public:
        double getCpuUsage(); // 获取CPU使用率
        double GettoCPUmhz(); // 获取CPU当前频率
        std::wstring GetCPUNameFromRegistry(); // 获取CPU名称
    };
}
    </code></pre>
</div>

<div class="section">
    <h2>3. 其他功能</h2>
    <h3>3.1 网页打开功能</h3>
    <p><code>IdWebOpen::OpenWeb</code> 函数用于打开指定URL的网页。</p>
    <pre><code>
namespace IdWebOpen {
    void OpenWeb(std::wstring URL, int width = 800, int height = 600, int posX = 0, int posY = 0);
}
    </code></pre>

    <h3>3.2 窗口管理功能</h3>
    <p><code>CreaWindowts</code> 命名空间提供了窗口管理功能，包括设置窗口透明度、毛玻璃效果等。</p>
    <pre><code>
namespace CreaWindowts {
    void WebNotSize(HWND& windG); // 设置窗口不可拉伸
    void SetWebAlpha(HWND& windG, int Alpha); // 设置窗口背景透明度
    BOOL EnableBlurBehindWindow(HWND hwnd); // 启用毛玻璃效果
}
    </code></pre>
</div>

<div class="section">
    <h2>4. 使用示例</h2>
    <p>以下是一个简单的使用示例，展示了如何使用 <code>ICSQL::Var</code> 类进行进制转换：</p>
    <pre><code>
#include "InTypeSendSQL.h"

int main() {
    ICSQL::Var var;
    std::string binaryResult;
    var.Turn_binary(10, &binaryResult);
    std::cout << "Binary of 10: " << binaryResult << std::endl;

    int decimalResult = var.BinToDEX("1010", 4);
    std::cout << "Decimal of 1010: " << decimalResult << std::endl;

    return 0;
}
    </code></pre>
</div>

<div class="section">
    <h2>5. 注意事项</h2>
    <ul>
        <li>在使用网络功能时，确保已正确配置网络权限。</li>
        <li>多线程操作时，注意线程安全问题。</li>
        <li>进制转换功能仅支持整数，不支持小数。</li>
    </ul>
</div>

<div class="section">
    <h2>6. 联系方式</h2>
    <p>如有任何问题，请联系开发团队：</p>
    <p>Email: <a href="mailto:dev@example.com">dev@example.com</a></p>
</div>

</body>
</html>
