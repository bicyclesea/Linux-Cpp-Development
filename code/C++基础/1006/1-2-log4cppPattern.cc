#include <iostream>
/* #include <fstream> */
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/PatternLayout.hh>
using std::cout;
using std::endl;
/* using std::ofstream; */
using namespace log4cpp;

void test0()
{
    /* ofstream ofs("1-2-ofs.log", std::ios::app); */

    //1. 设置日志布局
    PatternLayout *ptn1 = new PatternLayout();
    ptn1->setConversionPattern("%d %c [%p] %m%n");

    PatternLayout *ptn2 = new PatternLayout();
    ptn2->setConversionPattern("%d %c [%p] %m%n");

    PatternLayout *ptn3 = new PatternLayout();
    ptn3->setConversionPattern("%d %c [%p] %m%n");

    //2. 创建目的地
    //输出到终端
    OstreamAppender *pos = new OstreamAppender("console", &cout);
    pos->setLayout(ptn1);

    //再创建一个目的地
    //输出到文件（方式1）
    FileAppender *pos2 = new FileAppender("file", "1-2-File.log");
    //目的地和布局要一对一绑定
    pos2->setLayout(ptn2);

    //输出到文件（方式2）
    /* OstreamAppender *pos3 = new OstreamAppender("default", &ofs); */
    /* pos3->setLayout(ptn3); */

    //再创建目的地——回卷文件
    RollingFileAppender *pos3 = new RollingFileAppender("rolling",
                                                        "1-2-rolling.log",
                                                        5 * 1024,
                                                        9);
    pos3->setLayout(ptn3);

    //3. 创建日志记录器
    Category &salesDepart = Category::getInstance("sale");
    //设置优先级
    salesDepart.setPriority(Priority::ERROR);
    //设置目的地
    salesDepart.addAppender(pos);
    salesDepart.addAppender(pos2);
    salesDepart.addAppender(pos3);

    int count = 100;
    while(count-- > 0){
        salesDepart.emerg("this is an emerg msg");
        salesDepart.fatal("this is a fatal msg");
        salesDepart.alert("this is a alert msg");
        salesDepart.crit("this is a crit msg");
        salesDepart.error("this is an error msg");
        salesDepart.warn("this is a warn msg");
        salesDepart.notice("this is a notice msg");
        salesDepart.info("this is a info msg");
        salesDepart.debug("this is a debug msg");
    }

    //回收资源
    Category::shutdown();

    /* ofs.close(); */
}

int main()
{
    test0();
    return 0;
}

