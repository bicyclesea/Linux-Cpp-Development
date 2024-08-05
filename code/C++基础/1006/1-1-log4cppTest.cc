#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"
using namespace log4cpp;

int main(int argc, char** argv) {
    //基类指针指向派生类对象
    /* Appender *appender1 = new OstreamAppender("console", &std::cout); */
    //目的地
    OstreamAppender *appender1 = new OstreamAppender("console", &std::cout);
    //设置布局为basicLayout
	appender1->setLayout(new BasicLayout());

    //还设置了一个目的地保存到文件program.log
	FileAppender *appender2 = new FileAppender("default", "program.log");
	appender2->setLayout(new BasicLayout());

    //通过getRoot创建了根Category对象
    //并在代码中定义了引用root来表示
	Category& root = Category::getRoot();
    //通过日志记录器去设置日志系统的优先级
    //作为过滤日志的门槛
	root.setPriority(Priority::WARN);
    //通过日志记录器添加目的地
	root.addAppender(appender1);//appender1代表输出到终端

    //引用名sub1是代码中用来表示这个创建的子Category的名字
    //传入的参数sub1代表的日志信息中需要保存的日志记录器名字
    //也就是这条日志到底是来源于哪个模块
	Category& sub1 = Category::getInstance(std::string("sub1"));
    //子Category对象会继承父Category对象设置的优先级和目的地
    /* sub1.setPriority(Priority::WARN); */
	/* sub1.addAppender(appender2); */
    sub1.setAppender(appender2);
    sub1.setAdditivity(false);

	// use of functions for logging messages
	root.error("root error");
	root.info("root info");
	sub1.error("sub1 error");
	sub1.warn("sub1 warn");

	// printf-style for logging variables
	root.warn("%d + %d == %s ?", 1, 1, "two");

	// use of streams for logging messages
	root << log4cpp::Priority::ERROR << "Streamed root error";
	root << log4cpp::Priority::INFO << "Streamed root info";
	sub1 << log4cpp::Priority::ERROR << "Streamed sub1 error";
	sub1 << log4cpp::Priority::WARN << "Streamed sub1 warn";

	// or this way:
	root.errorStream() << "Another streamed error";

	return 0;
}

