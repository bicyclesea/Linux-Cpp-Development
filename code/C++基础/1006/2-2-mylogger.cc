#include <iostream>
#include <cstring>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/Category.hh>
using std::cout;
using std::endl;
using namespace log4cpp;

class Mylogger
{
public:
    static Mylogger *getInstance()
    {
        if(_pInstance == nullptr){
            _pInstance = new Mylogger();
        }
        return _pInstance;
    }
    void warn(const char *msg)
    {
        root.warn(msg);
    }
    void error(const char *msg)
    {
        root.error(msg);
    }
    void debug(const char *msg)
    {
        root.debug(msg);
    }
    void info(const char *msg)
    {
        root.info(msg);
    }
    void fatal(const char *msg)
    {
        root.fatal(msg);
    }
    void crit(const char *msg)
    {
        root.crit(msg);
    }
    static void destroy()
    {
        if(_pInstance){
            delete _pInstance;
            _pInstance = nullptr;
        }
    }
private:
    Mylogger()
    {
        //创建目的地
        OstreamAppender *pos = new OstreamAppender("console", &cout);

        //设置优先级
        root.setPriority(Priority::ERROR);
        //设置目的地
        root.addAppender(pos);
    }
    ~Mylogger()
    {
        //回收资源
        Category::shutdown();
    }
    Mylogger(Mylogger &rhs) = delete;
    Mylogger &operator=(const Mylogger &rhs) = delete;
private:
    //创建日志记录器
    Category &root = Category::getRoot();
    //定义一个指针保存第一次创建的对象
    static Mylogger *_pInstance;
};
Mylogger *Mylogger::_pInstance = nullptr;

void test0()
{
    //第一步，完成单例模式的写法
    Mylogger *log = Mylogger::getInstance();

    log->info("The log is info message");
    log->error("The log is error message");
    log->fatal("The log is fatal message");
    log->crit("The log is crit message");
    log->destroy();
}

class LogInfo
{
public:
    LogInfo(const char *msg)
    {
        //创建目的地
        OstreamAppender *pos = new OstreamAppender("console", &cout);

        //设置优先级
        root.setPriority(Priority::ERROR);
        //设置目的地
        root.addAppender(pos);
        // use of functions for logging messages
        info(msg);
    }
    void info(const char *msg)
    {
        root.info(msg);
    }
    LogInfo(LogInfo &rhs) = delete;
    LogInfo &operator=(const LogInfo &rhs) = delete;
    ~LogInfo()
    {
        //回收资源
        Category::shutdown();
    }
private:
    //创建日志记录器
    Category &root = Category::getRoot();
};

class LogError
{
public:
    LogError(const char *msg)
    {
        //创建目的地
        OstreamAppender *pos = new OstreamAppender("console", &cout);

        //设置优先级
        root.setPriority(Priority::ERROR);
        //设置目的地
        root.addAppender(pos);
        // use of functions for logging messages
        error(msg);
    }
    void error(const char *msg)
    {
        root.error(msg);
    }
    LogError(LogError &rhs) = delete;
    LogError &operator=(const LogError &rhs) = delete;
    ~LogError()
    {
        //回收资源
        Category::shutdown();
    }
private:
    //创建日志记录器
    Category &root = Category::getRoot();
};

class LogWarn
{
public:
    LogWarn(const char *msg)
    {
        //创建目的地
        OstreamAppender *pos = new OstreamAppender("console", &cout);

        //设置优先级
        root.setPriority(Priority::ERROR);
        //设置目的地
        root.addAppender(pos);
        // use of functions for logging messages
        warn(msg);
    }
    void warn(const char *msg)
    {
        root.warn(msg);
    }
    LogWarn(LogWarn &rhs) = delete;
    LogWarn &operator=(const LogWarn &rhs) = delete;
    ~LogWarn()
    {
        //回收资源
        Category::shutdown();
    }
private:
    //创建日志记录器
    Category &root = Category::getRoot();
};

class LogDebug
{
public:
    LogDebug(const char *msg)
    {
        //创建目的地
        OstreamAppender *pos = new OstreamAppender("console", &cout);

        //设置优先级
        root.setPriority(Priority::ERROR);
        //设置目的地
        root.addAppender(pos);
        // use of functions for logging messages
        debug(msg);
    }
    void debug(const char *msg)
    {
        root.debug(msg);
    }
    LogDebug(LogDebug &rhs) = delete;
    LogDebug &operator=(const LogDebug &rhs) = delete;
    ~LogDebug()
    {
        //回收资源
        Category::shutdown();
    }
private:
    //创建日志记录器
    Category &root = Category::getRoot();
};

void test1() 
{
    printf("hello,world\n");
    //第二步，像使用printf一样
    //只要求能输出纯字符串信息即可，不需要做到格式化输出
    LogInfo("The log is info message");
    LogError("The log is error message");
    LogWarn("The log is warn message");
    LogDebug("The log is debug message");
}
int main()
{
    test1();
    return 0;
}


