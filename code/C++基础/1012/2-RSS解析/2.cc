#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <fstream>
#include "tinyxml2.h"
#include "tinyxml2.cpp"
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::regex;
using std::ofstream;
using namespace tinyxml2;

struct RssItem
{
    string title;
    string link;
    string description;
    string content;
};

class RssReader
{
public:
    RssReader();
    void parseRss();//解析
    void dump(const string & filename);//输出
private:
    vector<RssItem> _rss;
    XMLDocument doc;
};
RssReader::RssReader()
{
    doc.LoadFile("coolshell.xml");
}
void RssReader::parseRss()
{
    XMLElement *itemElement = doc.FirstChildElement("rss")->FirstChildElement("channel")->FirstChildElement("item");
    while(itemElement){
        XMLElement *titleElement = itemElement->FirstChildElement("title");
        XMLText* textNode = titleElement->FirstChild()->ToText();
        const char *title = textNode->Value();
        /* cout << title << endl; */

        XMLElement *linkElement = itemElement->FirstChildElement("link");
        textNode = linkElement->FirstChild()->ToText();
        const char *link = textNode->Value();
        /* cout << link << endl; */

        XMLElement *descriptionElement = itemElement->FirstChildElement("description");
        textNode = descriptionElement->FirstChild()->ToText();
        const char *description = textNode->Value();
        regex tagRegex("<[^>]+>");
        string descriptionRes = regex_replace(description, tagRegex, "");
        /* cout << descriptionRes << endl; */

        XMLElement *contentElement = itemElement->FirstChildElement("content:encoded");
        textNode = contentElement->FirstChild()->ToText();
        const char *content = textNode->Value();
        string contentRes = regex_replace(content, tagRegex, "");
        /* cout << contentRes << endl; */

        RssItem item;
        item.title = title;
        item.link = link;
        item.description = descriptionRes;
        item.content = contentRes;

        _rss.push_back(item);
        itemElement = itemElement->NextSiblingElement();
    }
}
void RssReader::dump(const string & filename)
{
    ofstream ofs(filename);
    int count = 1;
    for(size_t i = 0; i < _rss.size(); ++i){
        ofs << "<doc>" << endl;
        ofs << "    <docid>" << count++ << "</docid>" << endl;
        ofs << "    <title>" << _rss[i].title << "</title>" << endl;
        ofs << "    <link>"  << _rss[i].link << "</link>" << endl;
        ofs << "    <description>" << _rss[i].description << "</description>" << endl;
        ofs << "    <content>" << _rss[i].content << "</content>" << endl;
        ofs << "</doc>" << endl;
    }
    ofs << endl;
    ofs.close();
}
int main()
{
    RssReader r;
    r.parseRss();
    r.dump("pagelib.txt");
    return 0;
}


