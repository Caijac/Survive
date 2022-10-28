/**
    Survive——A console sandbox game based on C plus plus
    Copyright (C) 2022  Enderite
    Distrubuted under GPL 3.0 License

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
/* Copyright(c) 2021 Xinrui Zhang,JiaCheng Pan and all contributors
All right Reserved
    
    Distributed under GPL license
    See copy at https://opensource.org/licenses/GPL-3.0
*/
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <locale>
#include <clocale>
#include <cwchar>
#include <typeinfo>
#include <algorithm>
#include <climits>
#include <sstream>
#include <queue>
#include <set>
#include <map>
#include <iomanip>
#include <unistd.h>
#include <termios.h>
#include <cstdio>
#include <cstring>
#include <random>
const bool Enderite_died = true;
namespace stdcolor_256{
    const std::string red    = "\033[48;5;1m";//红色
    const std::string yellow = "\033[48;5;3m";//黄色
    const std::string green  = "\033[48;5;2m";//绿色
    const std::string blue   = "\033[48;5;4m";//蓝色
    const std::string cyan   = "\033[48;5;5m";//青色
    const std::string purple = "\033[48;5;6m";//紫色
    const std::string white  = "\033[48;5;255m";//白色
    const std::string gray   = "\033[48;5;8m";//灰色
    const std::string black  = "\033[48;5;0m";//黑色
    const std::string darkgray = "\033[48;5;235m";//暗灰色
    const std::string light_red    = "\033[48;5;9m";//亮红色
    const std::string light_yellow = "\033[48;5;11m";//亮黄色
    const std::string light_green  = "\033[48;5;10m";//亮绿色
    const std::string light_blue   = "\033[48;5;12m";//亮蓝色
    const std::string light_cyan   = "\033[48;5;13m";//亮青色
    const std::string light_purple = "\033[48;5;14m";//亮紫色
    const std::string light_white  = "\033[48;5;15m";//亮白色
    const std::string dark_black  = "\033[48;5;16m";//纯黑色
    inline std::string to256color(int incolor){
        return "\033[48;5;"+std::to_string(std::abs(incolor%256))+"m";
    }//数字直接转换至256色字符串
    const std::string code_background = stdcolor_256::darkgray;//代码背景色
};//标准256背景色

namespace stdcolor_RGB{
    const std::string pure_red =    "\033[48;2;255;0;0m";//      颜色#FF0000
    const std::string pure_green =  "\033[48;2;0;255;0m";//      颜色#00FF00
    const std::string pure_blue  =  "\033[48;2;0;0;255m";//      颜色#0000FF
    const std::string pure_black =  "\033[48;2;0;0;0m";//        颜色#000000
    const std::string pure_white =  "\0333[48;2;255;255;255m";// 颜色#FFFFFF
    const std::string pure_yellow = "\033[48;2;255;255;0m";//    颜色#FFFF00
    const std::string pure_violet = "\033[48;2;255;0;255m";//    颜色#FF00FF
    const std::string pure_cyan   = "\033[48;2;0;255;255m";//    颜色#00FFFF
    inline std::string torgbcolor(unsigned char inred,
                                   unsigned char ingreen,
                                   unsigned char inblue){
        return "\033[48;2;" + std::to_string(inred) + ";" +
                               std::to_string(ingreen) + ";" +
                               std::to_string(inblue) + "m";
    }//数字直接转换至RGB字符串
};//RGB标准颜色库

namespace stdtext{
    const std::string text_white = "\033[38;5;255m";//文字纯白
    const std::string text_red = "\033[38;5;9m";//文字红色
    const std::string text_orange = "\033[38;5;208m";//文字橙色
    const std::string text_yellow = "\033[33m";//文字黄色
    const std::string text_green = "\033[32m";//文字绿色
    const std::string text_blue = "\033[34m";//文字蓝色
    const std::string text_cyan = "\033[38;2;0;255;255m";//文字靛色
    const std::string text_violet = "\033[38;2;255;0;255m";//文字紫色
    const std::string text_dark = "\033[38;5;232m";//文字纯黑
    const std::string text_darkgray = "\033[38;5;234m";
    const std::string text_gray = "\033[38;5;242m";//文字灰色
    const std::string text_darkblue = "\033[38;5;27m";//文字深蓝
    const std::string text_lightblue = "\033[38;5;39m";//文字亮蓝
    const std::string text_lightgreen = "\033[38;5;10m";//文字亮绿
    const std::string text_lightyellow = "\033[38;2;255;255;0m";
    const std::string italic = "\033[003m";//文字斜体
    const std::string text_underline = "\033[004m";//文字下划线
    
};//文字格式标准库

namespace CUIL_std{
    using namespace stdcolor_256;
    using namespace stdcolor_RGB;
    using namespace stdtext;
    #ifndef EXTERNED_UNISTDH
        extern "C" unsigned int sleep (unsigned int __seconds);
        extern "C" int usleep (__useconds_t __useconds);
        #define EXTERNED_UNISTDH
    #endif
    #define _EN_UK_DEFAULT_WARNING "Warning,error occured because of wrong parameter or incorrect use."//默认反馈信息——英语
    #define _ZH_CN_DEFAULT_WARNING "警告：错误的参数或不正当使用导致了一个错误"//默认反馈信息——中文
    #ifdef __linux
	    #define CLEARSCREEN_CMDCOMMMAND "\033c\033[1;1H"
	#endif
    int WCHAR_T_INIT(){
        try{
            std::locale lc("zh_CN.UTF-8");
    	    std::locale::global(lc);
    	    return 1;
        }catch(...){
            return 0;
        }
    }
    const int SUPPORT_WCHAR_T = WCHAR_T_INIT();//常量——系统是否支持中文宽字符（unicode字符集）
    
	//清除屏幕的system指令
    const std::string VOID_PARAMETER = "NONE";//默认空参数
    const std::string _DEFAULT_LANGUAGE = "zh-CN";//默认语言
    const std::string _NOW_DEFAULT_WARNING = _ZH_CN_DEFAULT_WARNING;//现在的默认警告（可随时更改）
    const std::string _CLEAREFFECT_STR = "\033[m";//清除效果
    const std::string CUIL_VERSIONINFO = "CUIL v0.0.9";//CUIL的版本
    
    //CUIL基础结构
    
    //衍生功能库
    
    enum RGB{
        RED,
        GREEN,
        BLUE,
    };
    const std::string warning_color_type[] = {stdcolor_256::yellow,stdcolor_256::light_red,stdcolor_256::red};
    //0级警告：黄，1级警告：亮红，2级（最高）警告：暗红
    //基础类
    struct warning{
        int warn_type;
        std::string content;
    };
    std::queue<warning> warning_queue;//警告队列
    inline int warn_if(bool statement,const std::string& show,int type_warning = 1);//警告
    class format{
        protected:
            bool formatlock;//格式锁
        private:
            std::string text_color;//文字颜色 
            std::string background_color;//背景颜色
            bool useitalic;//是否启用斜体
        public:
            void settextcolor(const std::string& input){
                if(!warn_if(formatlock,"此类的格式锁已启用，无法通过set进行修改"))
                    text_color = input;
            }
            void setbgcolor(const std::string& input){
                if(!warn_if(formatlock,"此类的格式锁已启用，无法通过set进行修改"))
                    background_color = input;
            }
            void setitalic(bool input){
                if(!warn_if(formatlock,"此类的格式锁已启用，无法通过set进行修改"))
                    useitalic = input;
            }
            void lock(){
                formatlock=true;    
            }
            void unlock(){
                formatlock=false;
            }
            void clear(){
                formatlock = false;
                useitalic=false;
                text_color="";
                background_color="";
            }//清除效果
            format(bool a,bool b,const std::string& c,const std::string& d){
                formatlock = a;
                useitalic = b;
                text_color = c;
                background_color = d;
            }
            format(){}
            ~format(){}
        friend void print(const std::string& content,const format& formatin,bool step,double char_per_sec,bool end);
        friend void printcode(const std::string code,const std::string lang);
        friend std::ostream& operator<<(std::ostream& wis,const format& c);
    }publicformat = {false,false,"",""},
    default_printformat = {false,false,"",""},
    default_codeformat = {false,false,"",code_background};
    format printformat = default_printformat;
    format codeformat = default_codeformat;    
    std::ostream& operator<<(std::ostream& wis,const format& c){
        std::string s = c.text_color + c.background_color + (c.useitalic?italic:"");
        wis << s;
        return wis;
    
    }
    class element{
        public:
            std::string content;//模板化内容
            format buildin_format;//内置格式
        public:
            void show() const{ std::cout << buildin_format << content; /* 内容 */ }
            element(){
                content = "";
                buildin_format = default_printformat;
            }//默认构造
            explicit element(const std::string& input,const format& formatin = printformat){
                content = input;
                buildin_format = formatin;
            }//输入元素内容
            explicit element(const long long input,const format& formatin = printformat){
                content = std::to_string(input);
                buildin_format = formatin;
            }//对整型数据的重载
            explicit element(const char input,const format& formatin = printformat){
                content += input;
                buildin_format = formatin;
            }//对宽字符数据的重载
            explicit element(const long double input,const format& formatin = printformat){
                content = std::to_string(input);
                buildin_format = formatin;
            }
    }voidelement{"",default_printformat};//元素类
    
    int count_showlen(const element& input){
        int count_t = input.content.length();
        for(auto&& i:input.content){
            if(int(i) > 127)
                count_t++;
        }
        return count_t;
    }
    std::string strcpy(const std::string& cpystr,int cpynum);
    class label_line{
        public:
            element left;//左元素
            element mid;//中元素
            element right;//右元素
            int line_len;//当前对齐长度
        public:
            int minshowlen() const{
                int show_len_left = count_showlen(left),
                    show_len_mid  = count_showlen(mid),
                    show_len_right = count_showlen(right);
                int line_len = show_len_left + show_len_mid + show_len_right + 2;
                return line_len;
            }
            void editleft(const element& in){
                left = in;
            }
            void editright(const element& in){
                right = in;
            }
            void editmid(const element& in){
                mid = in;
            }
            void show(int line_len_min = 20){
                int now_len = minshowlen();
                if(now_len > line_len_min){
                    left.show();
                    std::cout << " ";
                    mid.show();
                    std::cout << " ";
                    right.show();
                    line_len = now_len;
                }//拓展长度
                else{
                    int space_left = (line_len_min - now_len + 2)/2,
                        space_right = line_len_min - now_len + 2 - space_left;
                    left.show();
                    std::cout << strcpy(" ",space_left);
                    mid.show();
                    std::cout << strcpy(" ",space_right);
                    right.show();
                    line_len = line_len_min;
                }
            }//展示标签行
            label_line(){
                left = element();
                mid = element();
                right = element();
            }
            explicit label_line(const element& l,const element& m = voidelement,const element& r = voidelement){
                left = l;
                mid = m;
                right = r;
                
            }
    };//标签行类
    class label{
        public:
            std::vector<label_line>content;
        public:
            void add_line(const label_line& in){
                content.push_back(in);
            }
            void delete_line(){
                content.pop_back();
            }
            void show(int show_len = 20){
                int max_len = -1;
                for(auto&&i:content){
                    int tmp_len = i.minshowlen();
                    max_len = tmp_len>max_len?tmp_len:max_len;
                }//检索最大长度
                show_len = max_len>=show_len?max_len:show_len;//如果最大长度超过定义，则换为最大长度
                std::cout << "┌"<<strcpy("─",show_len-1)<<"┐"<<std::endl;
                for(auto&&i:content){
                    std::cout << "│";
                    i.show(show_len);
                    std::cout << "│"<<std::endl;
                }
                std::cout << "└"<<strcpy("─",show_len-1)<<"┘"<<std::endl;
            }
    };//标签总类
    double half_precision(double a){
        return fabs(a - floor(a))<fabs(ceil(a)-a)?floor(a):ceil(a);
    }
    template<class T>class matrix{
        private:
            std::vector<std::vector<T>>content;
        public:
            void edit(int x,int y,const T& v){
                if(warn_if(!(0<=x&&x<content[0].size()&&0<=y&&y<content.size()),"尝试访问不存在的矩阵元素["+std::to_string(x)+","+std::to_string(y)+"]"))
                    return ;
                else
                    content[y][x]=v;
            }
            T get(int x,int y)const{
                if(0<=x&&x<content[0].size()&&0<=y&&y<content.size())
                    return content[y][x];
                return T();
            }
            matrix<T>(int h,int w){
                std::vector<std::vector<T> >tmp(h,std::vector<T>(w,T()));
                content = tmp;
            }
            matrix<T>(const std::vector<std::vector<T>>& inmatrix = {{}}){
                for(auto&&i:inmatrix){
                    content.emplace_back();
                    for(auto&&j:i)
                        content[content.size() - 1].push_back(j);
                }
            }
            int geth()const{
                return content.size();
            }
            int getw()const{
                return content[0].size();
            }
            void seth(int newh,const T& set_as = T()){
                if(newh<content.size()){
                    while(content.size()>newh&&(!content.empty()))
                        content.pop_back();
                }else{
                    std::vector<T>tmp;
                    while(tmp.size()<content[0].size())
                        tmp.push_back(set_as);
                    while(content.size()<newh)
                        content.push_back(tmp);
                }
            }
            void setw(int neww,const T& set_as = T()){
                if(neww<content[0].size()){
                    for(auto&&i:content){
                        while(i.size()>neww)
                            i.pop_back();
                    }
                }else{
                    for(auto&&i:content){
                        while(i.size()<neww)
                            i.push_back(set_as);
                    }
                }
            }
            void recover(const T& input){
                for(int i = 0;i<content.size();++i){
                    for(int j = 0;j<content[i].size();++j)
                        content[i][j] = input;
                }
            }
            void cover(int sx,int sy,int ex,int ey,const T& input){
                if(0<=sx&&sx<content[0].size()){
                    if(0<=sy&&sy<content.size()){
                        
                    }else
                        sy = sy<0?0:content.size()-1;
                        warn_if(true,"开始的y坐标超出范围，已自动调整",0);    
                }//开始坐标在范围内
                else{
                    sx = sx<0?0:content[0].size()-1;
                    warn_if(true,"开始的x坐标超出范围，已自动调整",0);
                }
                if(0<=ex&&ex<content[0].size()){
                    if(0<=ey&&ey<content.size()){
                        
                    }else
                        ey = ey<0?0:content.size()-1;
                        warn_if(true,"结束的y坐标超出范围，已自动调整",0);    
                }//开始坐标在范围内
                else{
                    ex = ex<0?0:content[0].size()-1;
                    warn_if(true,"结束的x坐标超出范围，已自动调整",0);
                }
                int tmp = sx;
                sx = std::min(tmp,ex);
                ex = std::max(tmp,ex);
                tmp=sy;
                sy = std::min(tmp,ey);
                ey = std::max(tmp,ey);
                for(int i = sx;i<=ex;++i){
                    for(int j = sy;j<=ey;++j)
                        content[j][i] = input;
                }
            }
            void matrixcover(const matrix<T>& inmat,int x,int y){
                for(int i = (x < 0?0:x);i < ((x + inmat.getw()) < getw()?(x + inmat.getw()):getw());++i){
                    for(int j = (y < 0?0:y);j < ((y + inmat.geth()) < geth()?(y + inmat.geth()):geth());++j)
                        edit(i,j,inmat.get(i - x,j - y));
                }
            }
            void print()const{
                for(int i = 0;i<content.size();++i){
                    for(int j = 0;j<content[i].size();++j)
                        std::cout << content[i][j]<<",";
                    std::cout << std::endl;
                }
            }
            void line(int sx,int sy,int ex,int ey,const T& input){
                long double k = (sx!=ex)?(ey-sy-0.0)/(ex-sx-0.0):(1e+308);
                long double b = sy - sx*k;
                if(sx>ex){
                    for(long double i = ex;i<=sx;i+=0.1){
                        long double nx = i,ny = k*i+b;
                        if(0<=nx&&nx<=content[0].size()&&0<=ny&&ny<=content.size())
                            content[half_precision(ny)][half_precision(nx)] = input;
                    }
                }else if(sx<ex){
                    for(long double i = sx;i<=ex;i+=0.1){
                        long double nx = i,ny = k*i+b;
                        if(0<=nx&&nx<=content[0].size()&&0<=ny&&ny<=content.size())
                            content[half_precision(ny)][half_precision(nx)] = input;
                    }
                }else{
                    int nsy = std::min(sy,ey),ney = std::max(sy,ey);
                    for(int i = nsy;i<=ney;++i){
                        if((0<=i&i<=content.size()&&0<=sx&&sx<=content[0].size()))
                            content[i][sx] = input;
                    }
                }
            }
            void circle(int x,int y,int r,const T& input){
                for(int i = x-r;i<=x+r;++i){
                    for(int j = y-r;j<=y+r;++j){
                        if(0<=i&i<=content[0].size()&&0<=j&&j<=content.size()){
                            if((i-x)*(i-x)+(j-y)*(j-y)<r*r)
                                content[j][i] = input;
                        }
                    }
                }
            }
    };
    const std::vector<std::string> img_type = {"rgb","256","grey"};
    bool intype(const std::string& typein){
        for(auto && i : img_type){
            if(typein == i)
                return true;
        }
        return false;
    }
    inline int chartohex(char inchar){
        return isdigit(inchar)?inchar - '0':(isalpha(inchar)?(toupper(inchar) > 'F'?0:toupper(inchar) - '7'):0);
    }
    class pixel{
        public:
            unsigned char red;//红
            unsigned char green;//绿
            unsigned char blue;//蓝
            unsigned char alpha;//透明度
        public:
            std::string make_show_RGB()const{
                return "\033[48;2;"+std::to_string(red)+";"+
                                     std::to_string(green)+";"+
                                     std::to_string(blue)+"m";
            }
            std::string make_show_RGB_text()const{
                return "\033[38;2;"+std::to_string(red)+";"+
                                     std::to_string(green)+";"+
                                     std::to_string(blue)+"m";
            }
            pixel(int r = 255,int g = 255,int b = 255,int a = 255){
                red = r;
                green = g;
                blue = b;
                alpha = a;
            }
            unsigned char getred() const{ return red; };
            unsigned char getgreen() const{ return green; };
            unsigned char getblue() const{ return blue; };
            unsigned char getalpha() const{ return alpha; };
            pixel(const std::string& rgb){
                if(rgb[0] == '#' && rgb.length() == 7){
                    red =   chartohex(rgb[1]) * 16 + chartohex(rgb[2]);
                    green = chartohex(rgb[3]) * 16 + chartohex(rgb[4]);
                    blue =  chartohex(rgb[5]) * 16 + chartohex(rgb[6]);
                }else if(rgb.length() == 6){
                    red =   chartohex(rgb[0]) * 16 + chartohex(rgb[1]);
                    green = chartohex(rgb[2]) * 16 + chartohex(rgb[3]);
                    blue =  chartohex(rgb[4]) * 16 + chartohex(rgb[5]);
                }else{
                    warn_if(true,"不合法的RGB值表示: " + rgb);
                    red = 255;
                    green = 255;
                    blue = 255;
                }
            }
            bool not_equal(const pixel& pix)const{
                return pix.red != red || pix.green != green || pix.blue != blue;
            }
            bool operator==(const pixel& pix2)const{
                return red == pix2.red && green == pix2.green && blue == pix2.blue;
            }
            bool operator!=(const pixel& pix2)const{
                return !(*this == pix2);
            }
            pixel reverse_color(){
                return pixel(255 - red,255 - green,255 - blue);   
            }
            void show(const pixel& last = pixel(0,0,0),bool at_front = false)const{
                if(last != *this || at_front)
                    std::cout << make_show_RGB();
                std::cout << "  ";
            }
            friend inline std::string torgbcolor(const pixel& inpixel);
            friend std::ostream& operator<<(std::ostream& wis,const pixel& c);
    }
    pixel_red(255,0,0),//纯红像素
    pixel_green(0,255,0),//纯绿像素
    pixel_blue(0,0,255),//纯蓝像素
    pixel_white(255,255,255),//纯白像素
    pixel_cyan(0,255,255),//纯靛像素
    pixel_violet(255,0,255),//纯紫像素
    pixel_yellow(255,255,0),//纯黄像素
    pixel_black(0,0,0);//纯黑像素
    class pixel_hsv{
        private:
            float hue;
            float saturation;
            float value;
        public:
            pixel_hsv(float h = 0.0,float s = 1.0,float v = 1.0){
                hue = h;
                saturation = s;
                value = v;
            }
            pixel_hsv(const pixel& inpix){
                int red = inpix.getred(),green = inpix.getgreen(),blue = inpix.getblue();
                int Pmax = std::max(red,std::max(green,blue)),Pmin=std::min(red,std::min(green,blue));
                if(Pmax == Pmin)
                    hue = 0.0;
                else if(red == Pmax)
                    hue = (green - blue)*1.0 /(Pmax - Pmin);
                else if(green == Pmax)
                    hue = 2.0 + (blue - red)*1.0/(Pmax - Pmin);
                else if(blue == Pmax)
                    hue = 4.0 + (red - green)*1.0/(Pmax - Pmin);
                else
                    hue = 0.0;
                hue *= 60.0;
                while(hue < 0.0)
                    hue+=360.0;
                while(hue >= 360.0)
                    hue-=360.0;
                value = Pmax*1.0/255;
                saturation = (Pmax - Pmin) * 1.0 / Pmax;
            }
            pixel torgbpix() const{
                int h = 2 * (floor(hue)/2);
                double c = value * saturation,
                       x = c * (1 - std::fabs(hue-h - 1.0)),
                       m = value - c;
                int int_hue = (int(hue/60))%6;
                double R,G,B;
                switch(int_hue){
                    case 0:R = c,G = x,B = 0.0;break;
                    case 1:R = x,G = c,B = 0.0;break;
                    case 2:R = 0.0,G = c,B = x;break;   
                    case 3:R = 0.0,G = x,B = c;break;   
                    case 4:R = x,G = 0.0,B = c;break;   
                    case 5:R = c,G = 0.0,B = x;break;   
                }
                return pixel(int((R+m)*255),int((G+m)*255),int((B+m)*255));
            }
            pixel_hsv reverse_color() const{
                return pixel_hsv(360.0 - hue,1.0 - saturation,1.0 - value);
            }
            std::string make_show_RGB() const{
                return torgbpix().make_show_RGB();
            }
            bool operator==(const pixel_hsv& pix2)const{
                return hue == pix2.hue && saturation == pix2.saturation && value == pix2.value;
            }
            bool operator!=(const pixel_hsv& pix2)const{
                return !(*this == pix2);
            }
            void show(const pixel_hsv& last,bool at_front = false)const{
                if(last != *this || at_front)
                    std::cout << make_show_RGB();
                std::cout << "  ";
            }
    };
   
    inline std::string torgbcolor(const pixel& inpixel){
        return "\033[48;2;"+std::to_string(inpixel.red)+";"+
                             std::to_string(inpixel.green)+";"+
                             std::to_string(inpixel.blue)+"m";
    }//数字直接转换至RGB字符串
    inline std::string torgbcolor(const pixel_hsv& inpixel){
        return torgbcolor(inpixel.torgbpix());
    }
    std::ostream& operator<<(std::ostream& wis,const pixel& c){
        std::string s = "["+std::to_string(c.red)+","+std::to_string(c.green)+","+std::to_string(c.blue)+"]";
        wis<<s;
        return wis;
    }
    class grey{
        public:unsigned char vgrey;
        public:
            std::string make_show_RGB() const{
                return "\033[48;2;"+std::to_string(vgrey)+";"+
                                     std::to_string(vgrey)+";"+
                                     std::to_string(vgrey)+"m";
            }
            std::string make_show_RGB_text() const{
                return "\033[38;2;"+std::to_string(vgrey)+";"+
                                     std::to_string(vgrey)+";"+
                                     std::to_string(vgrey)+"m";
            }
            void edit(unsigned char a){
                vgrey = a;
            }
            grey(unsigned char a = 255){
                vgrey = a;
            }
            grey(const pixel& pix,double vRed = 0.30,double vGreen = 0.59,double vBlue = 0.11){
                vgrey = pix.red * vRed + pix.green * vGreen + pix.blue * vBlue;
            }
            bool not_equal(const grey& ing)const{
                return ing.vgrey != vgrey;
            }
            grey reverse_color()const{
                return grey(255 - vgrey);
            }
            unsigned char getgrey()const{
                return vgrey;
            }
            bool operator==(const grey& pix2)const{
                return vgrey == pix2.vgrey;
            }
            bool operator!=(const grey& pix2)const{
                return !(*this == pix2);
            }
            void show(const grey& last,bool at_front = false)const{
                if(last != *this || at_front)
                    std::cout << make_show_RGB();
                std::cout << "  ";
            }
            friend inline std::string torgbcolor(const grey& ingrey);
            friend std::ostream& operator<<(std::ostream& wis,const grey& c);
    }grey_white(255),grey_black(0);
    inline std::string torgbcolor(const grey& ingrey){
        return "\033[48;2;"+std::to_string(ingrey.vgrey)+";"+
                             std::to_string(ingrey.vgrey)+";"+
                             std::to_string(ingrey.vgrey)+"m";
    }//数字直接转换至RGB字符串
    std::ostream& operator<<(std::ostream& wis,const grey& c){
        std::string s = "["+std::to_string(c.vgrey)+"]";
        wis<<s;
        return wis;
    }
    template<class T>
    class basic_image{
        public:
            int height;//图像高
            int width;//图像宽
            matrix<T>pmap;//像素矩阵
            double speed;//速度
        public:
            basic_image(const int h = 16,const int w = 16){
                height = h;
                width = w;
                pmap = matrix<T>(h,w);
                speed = 100;
            }
            basic_image(const matrix<T>& mapin){
                height = mapin.geth();
                width = mapin.getw();
                pmap = mapin;
                speed = 100;
            }
            void setspeed(double a){
                speed = a;
            }
            void show(bool with_border = false,bool has_margin = true)const{
                if(with_border){
                    std::cout << "\r┏━";
                    for(int x = 0;x < 2 * pmap.getw();++x)
                        std::cout << "━";
                    std::cout << "┓" << std::endl;
                }
                for(int i = 0;i<pmap.geth();++i){
                    if(with_border)
                        std::cout << "\r┃ ";
                    for(int j = 0;j<pmap.getw();++j){
                        pmap.get(j,i).show(pmap.get(j - 1,i),j == 0);
                        usleep(500000/speed);
                    }
                    std::cout << _CLEAREFFECT_STR;
                    if(with_border)
                        std::cout << "┃";
                    std::cout << std::endl;
                }
                if(with_border){
                    std::cout << "\r┗━";
                    for(int x = 0;x < 2 * pmap.getw();++x)
                        std::cout << "━";
                    std::cout << "┛" << std::endl;
                }
                std::cout << _CLEAREFFECT_STR;
            }
            void recover(const T& input){
                pmap.recover(input);
            }
            void cover(int sx,int sy,int ex,int ey,const T& input){
                pmap.cover(sx,sy,ex,ey,input);
            }
            void edit(int x,int y,const T& input){
                pmap.edit(x,y,input);
            }
            void line(int sx,int sy,int ex,int ey,const T& input){
                pmap.line(sx,sy,ex,ey,input);
            }
            void circle(int x,int y,int r,const T& input){
                pmap.circle(x,y,r,input);
            }
            void seth(int newh,const T& set_as = pixel_white){
                if(warn_if(newh<0,"设置的图像高无法小于0",1))
                    return ;
                else
                    pmap.seth(newh,set_as);
                height = newh;
            }
            void setw(int neww,const T& set_as = pixel_white){
                if(warn_if(neww<0,"设置的图像宽无法小于0",1))
                    return ;
                else
                    pmap.setw(neww,set_as);
                width = neww;
            }
            std::string to_str()const{
                std::string output;
                pixel tmp;
                for(int i = 0;i<pmap.geth();++i){
                    T last = pixel(255,255,255);
                    for(int j = 0;j<pmap.getw();++j){
                        tmp = pmap.get(j,i);
                        if(last != tmp || j == 0){
                            output += tmp.make_show_RGB();
                            last = tmp;
                        }
                        output += "  ";
                    }
                    output+=_CLEAREFFECT_STR+"\n";
                }
                return output;
            }
            T get(int x,int y)const{
                return pmap.get(x,y);
            }
            basic_image intercept(int x1,int y1,int x2,int y2)const{
                basic_image out(std::max(x1,x2) - std::min(x1,x2),std::max(y1,y2) - std::min(y1,y2));
                int sx = std::min(x1,x2),sy = std::min(y1,y2);
                for(int i = 0;i < out.height;++i){
                    for(int j = 0;j < out.width;++j)
                        out.edit(j,i,get(sx + j,sy + i));
                }
                return out;
            }
            basic_image rotate_clockwise()const{
                basic_image out(width,height);
                for(int x = 0;x < width;++x){
                    for(int y = 0;y < height;++y){
                        out.edit(int(height - y - 0.5),int(x + 0.5),get(x,y));
                    }
                }
                return out;
            }//顺时针旋转
            basic_image rotate_anticlockwise()const{
                basic_image out(width,height);
                for(int x = 0;x < width;++x){
                    for(int y = 0;y < height;++y)
                        out.edit(int(y + 0.5),int(width - x - 0.5),get(x,y));
                }
                return out;
            }//逆时针旋转
            basic_image overturn_x()const{
                basic_image out(height,width);
                for(int x = 0;x < width;++x){
                    for(int y = 0;y < height;++y)
                        out.edit(x,floor(height - y - 0.5),get(x,y));
                }
                return out;
            }//绕x轴旋转
            basic_image overturn_y()const{
                basic_image out(height,width);
                for(int x = 0;x < width;++x){
                    for(int y = 0;y < height;++y)
                        out.edit(floor(width - x - 0.5),y,get(x,y));
                }
                return out;
            }//绕y轴旋转
            basic_image reverse_color()const{
                basic_image out(height,width);
                for(int x = 0;x < width;++x){
                    for(int y = 0;y < height;++y)
                        out.edit(x,y,get(x,y).reverse_color());
                }
                return out;
            }
            void imgcover(const basic_image<T>& img,int x,int y,const T& avoid_color){
                for(int i = (x < 0?0:x);i < ((x + img.width) < width?(x + img.width):width);++i){
                    for(int j = (y < 0?0:y);j < ((y + img.height) < height?(y + img.height):height);++j){
                        if(avoid_color != img.get(i - x,j - y))
                            edit(i,j,img.get(i - x,j - y));
                    }
                }
            }
            friend std::wostream& operator<<(std::wostream& wis,const basic_image& c);
    };
    template<class T>
    std::wostream& operator<<(std::wostream& wis,const basic_image<T>& c){
        wis<<c.to_str();
        return wis;
    }
    typedef basic_image<pixel>             image;
    typedef basic_image<char>         image_char;
    typedef basic_image<grey>         image_grey;
    typedef basic_image<pixel_hsv>     image_hsv;
    class hyperpixel{
        private:
            pixel m1;
            pixel m2;
            pixel m3;
            pixel m4;
        public:
            hyperpixel(const pixel& a = pixel(),const pixel& b = pixel(),
                       const pixel& c = pixel(),const pixel& d = pixel()){
                m1 = a;
                m2 = b;
                m3 = c;
                m4 = d;
            }
            void show(const hyperpixel& last = hyperpixel(),bool at_front = false){
                if(last.m2.not_equal(m1) || at_front)
                    std::cout << m1.make_show_RGB();
                if((last.m4.not_equal(m3) && m1 != m3) || at_front){
                    std::cout << m3.make_show_RGB_text();
                    std::cout << "▄";
                }else
                    std::cout << " ";
                if(m1.not_equal(m2) || at_front)
                    std::cout <<  m2.make_show_RGB();
                if((m3.not_equal(m4) && m2 != m4) || at_front){
                    std::cout << m4.make_show_RGB_text();
                    std::cout << "▄";
                }else
                    std::cout << " ";
            }
    };
    const std::vector<std::string> map_dotmatrix = {
    "\u2800","\u2801","\u2802","\u2803","\u2804","\u2805","\u2806","\u2807","\u2808","\u2809","\u280A","\u280B","\u280C","\u280D","\u280E","\u280F",
    "\u2810","\u2811","\u2812","\u2813","\u2814","\u2815","\u2816","\u2817","\u2818","\u2819","\u281A","\u281B","\u281C","\u281D","\u281E","\u281F",
    "\u2820","\u2821","\u2822","\u2823","\u2824","\u2825","\u2826","\u2827","\u2828","\u2829","\u282A","\u282B","\u282C","\u282D","\u282E","\u282F",
    "\u2830","\u2831","\u2832","\u2833","\u2834","\u2835","\u2836","\u2837","\u2838","\u2839","\u283A","\u283B","\u283C","\u283D","\u283E","\u283F",
    "\u2840","\u2841","\u2842","\u2843","\u2844","\u2845","\u2846","\u2847","\u2848","\u2849","\u284A","\u284B","\u284C","\u284D","\u284E","\u284F",
    "\u2850","\u2851","\u2852","\u2853","\u2854","\u2855","\u2856","\u2857","\u2858","\u2859","\u285A","\u285B","\u285C","\u285D","\u285E","\u285F",
    "\u2860","\u2861","\u2862","\u2863","\u2864","\u2865","\u2866","\u2867","\u2868","\u2869","\u286A","\u286B","\u286C","\u286D","\u286E","\u286F",
    "\u2870","\u2871","\u2872","\u2873","\u2874","\u2875","\u2876","\u2877","\u2878","\u2879","\u287A","\u287B","\u287C","\u287D","\u287E","\u287F",
    "\u2880","\u2881","\u2882","\u2883","\u2884","\u2885","\u2886","\u2887","\u2888","\u2889","\u288A","\u288B","\u288C","\u288D","\u288E","\u288F",
    "\u2890","\u2891","\u2892","\u2893","\u2894","\u2895","\u2896","\u2897","\u2898","\u2899","\u289A","\u289B","\u289C","\u289D","\u289E","\u289F",
    "\u28A0","\u28A1","\u28A2","\u28A3","\u28A4","\u28A5","\u28A6","\u28A7","\u28A8","\u28A9","\u28AA","\u28AB","\u28AC","\u28AD","\u28AE","\u28AF",
    "\u28B0","\u28B1","\u28B2","\u28B3","\u28B4","\u28B5","\u28B6","\u28B7","\u28B8","\u28B9","\u28BA","\u28BB","\u28BC","\u28BD","\u28BE","\u28BF",
    "\u28C0","\u28C1","\u28C2","\u28C3","\u28C4","\u28C5","\u28C6","\u28C7","\u28C8","\u28C9","\u28CA","\u28CB","\u28CC","\u28CD","\u28CE","\u28CF",
    "\u28D0","\u28D1","\u28D2","\u28D3","\u28D4","\u28D5","\u28D6","\u28D7","\u28D8","\u28D9","\u28DA","\u28DB","\u28DC","\u28DD","\u28DE","\u28DF",
    "\u28E0","\u28E1","\u28E2","\u28E3","\u28E4","\u28E5","\u28E6","\u28E7","\u28E8","\u28E9","\u28EA","\u28EB","\u28EC","\u28ED","\u28EE","\u28EF",
    "\u28F0","\u28F1","\u28F2","\u28F3","\u28F4","\u28F5","\u28F6","\u28F7","\u28F8","\u28F9","\u28FA","\u28FB","\u28FC","\u28FD","\u28FE","\u28FF",
    };
    pixel t256[256] = {
        pixel("#000000"),pixel("#800000"),pixel("#008000"),pixel("#808000"),pixel("#000080"),pixel("#800080"),pixel("#008080"),pixel("#c0c0c0"),
        pixel("#808080"),pixel("#ff0000"),pixel("#ffff00"),pixel("#00ff00"),pixel("#0000ff"),pixel("#ff00ff"),pixel("#00ffff"),pixel("#ffffff"),
        pixel("#000000"),pixel("#00005f"),pixel("#000087"),pixel("#0000af"),pixel("#0000d7"),pixel("#0000ff"),pixel("#005f00"),pixel("#005f5f"),
        pixel("#005f87"),pixel("#005faf"),pixel("#005fd7"),pixel("#005fff"),pixel("#008700"),pixel("#00875f"),pixel("#008787"),pixel("#0087af"),
        pixel("#0087d7"),pixel("#0087ff"),pixel("#00af00"),pixel("#00af5f"),pixel("#00af87"),pixel("#00afaf"),pixel("#00afd7"),pixel("#00afff"),
        pixel("#00d700"),pixel("#00d75f"),pixel("#00d787"),pixel("#00d7af"),pixel("#00d7d7"),pixel("#00d7ff"),pixel("#00ff00"),pixel("#00ff5f"),
        pixel("#00ff87"),pixel("#00ffaf"),pixel("#00ffd7"),pixel("#00ffff"),pixel("#5f0000"),pixel("#5f005f"),pixel("#5f0087"),pixel("#5f00af"),
        pixel("#5f00d7"),pixel("#5f00ff"),pixel("#5f5f00"),pixel("#5f5f5f"),pixel("#5f5f87"),pixel("#5f5faf"),pixel("#5f5fd7"),pixel("#5f5fff"),
        pixel("#5f8700"),pixel("#5f875f"),pixel("#5f8787"),pixel("#5f87af"),pixel("#5f87d7"),pixel("#5f87ff"),pixel("#5faf00"),pixel("#5faf5f"),
        pixel("#5faf87"),pixel("#5fafaf"),pixel("#5fafd7"),pixel("#5fafff"),pixel("#5fd700"),pixel("#5fd75f"),pixel("#5fd787"),pixel("#5fd7af"),
        pixel("#5fd7d7"),pixel("#5fd7ff"),pixel("#5fff00"),pixel("#5fff5f"),pixel("#5fff87"),pixel("#5fffaf"),pixel("#5fffd7"),pixel("#5fffff"),
        pixel("#870000"),pixel("#87005f"),pixel("#870087"),pixel("#8700af"),pixel("#8700d7"),pixel("#8700ff"),pixel("#875f00"),pixel("#875f5f"),
        pixel("#875f87"),pixel("#875faf"),pixel("#875fd7"),pixel("#875fff"),pixel("#878700"),pixel("#87875f"),pixel("#878787"),pixel("#8787af"),
        pixel("#8787d7"),pixel("#8787ff"),pixel("#87af00"),pixel("#87af5f"),pixel("#87af87"),pixel("#87afaf"),pixel("#87afd7"),pixel("#87afff"),
        pixel("#87d700"),pixel("#87d75f"),pixel("#87d787"),pixel("#87d7af"),pixel("#87d7d7"),pixel("#87d7ff"),pixel("#87ff00"),pixel("#87ff5f"),
        pixel("#87ff87"),pixel("#87ffaf"),pixel("#87ffd7"),pixel("#87ffff"),pixel("#af0000"),pixel("#af005f"),pixel("#af0087"),pixel("#af00af"),
        pixel("#af00d7"),pixel("#af00ff"),pixel("#af5f00"),pixel("#af5f5f"),pixel("#af5f87"),pixel("#af5faf"),pixel("#af5fd7"),pixel("#af5fff"),
        pixel("#af8700"),pixel("#af875f"),pixel("#af8787"),pixel("#af87af"),pixel("#af87d7"),pixel("#af87ff"),pixel("#afaf00"),pixel("#afaf5f"),
        pixel("#afaf87"),pixel("#afafaf"),pixel("#afafd7"),pixel("#afafff"),pixel("#afd700"),pixel("#afd75f"),pixel("#afd787"),pixel("#afd7af"),
        pixel("#afd7d7"),pixel("#afd7ff"),pixel("#afff00"),pixel("#afff5f"),pixel("#afff87"),pixel("#afffaf"),pixel("#afffd7"),pixel("#afffff"),
        pixel("#d70000"),pixel("#d7005f"),pixel("#d70087"),pixel("#d700af"),pixel("#d700d7"),pixel("#d700ff"),pixel("#d75f00"),pixel("#d75f5f"),
        pixel("#d75f87"),pixel("#d75faf"),pixel("#d75fd7"),pixel("#d75fff"),pixel("#d78700"),pixel("#d7875f"),pixel("#d78787"),pixel("#d787af"),
        pixel("#d787d7"),pixel("#d787ff"),pixel("#d7af00"),pixel("#d7af5f"),pixel("#d7af87"),pixel("#d7afaf"),pixel("#d7afd7"),pixel("#d7afff"),
        pixel("#d7d700"),pixel("#d7d75f"),pixel("#d7d787"),pixel("#d7d7af"),pixel("#d7d7d7"),pixel("#d7d7ff"),pixel("#d7ff00"),pixel("#d7ff5f"),
        pixel("#d7ff87"),pixel("#d7ffaf"),pixel("#d7ffd7"),pixel("#d7ffff"),pixel("#ff0000"),pixel("#ff005f"),pixel("#ff0087"),pixel("#ff00af"),
        pixel("#ff00d7"),pixel("#ff00ff"),pixel("#ff5f00"),pixel("#ff5f5f"),pixel("#ff5f87"),pixel("#ff5faf"),pixel("#ff5fd7"),pixel("#ff5fff"),
        pixel("#ff8700"),pixel("#ff875f"),pixel("#ff8787"),pixel("#ff87af"),pixel("#ff87d7"),pixel("#ff87ff"),pixel("#ffaf00"),pixel("#ffaf5f"),
        pixel("#ffaf87"),pixel("#ffafaf"),pixel("#ffafd7"),pixel("#ffafff"),pixel("#ffd700"),pixel("#ffd75f"),pixel("#ffd787"),pixel("#ffd7af"),
        pixel("#ffd7d7"),pixel("#ffd7ff"),pixel("#ffff00"),pixel("#ffff5f"),pixel("#ffff87"),pixel("#ffffaf"),pixel("#ffffd7"),pixel("#ffffff"),
        pixel("#080808"),pixel("#121212"),pixel("#1c1c1c"),pixel("#262626"),pixel("#303030"),pixel("#3a3a3a"),pixel("#444444"),pixel("#4e4e4e"),
        pixel("#585858"),pixel("#626262"),pixel("#6c6c6c"),pixel("#767676"),pixel("#808080"),pixel("#8a8a8a"),pixel("#949494"),pixel("#9e9e9e"),
        pixel("#a8a8a8"),pixel("#b2b2b2"),pixel("#bcbcbc"),pixel("#c6c6c6"),pixel("#d0d0d0"),pixel("#dadada"),pixel("#e4e4e4"),pixel("#eeeeee"),
    };
    enum GREY_MODE{
    GREY,    
    BINARY,
    C256,
    };
    class hyper_greypixel{
        public:
            bool pix[4][2];
            grey grey_info;
            GREY_MODE mode;
        public:
            bool operator==(const hyper_greypixel& op2)const{
                return op2.grey_info == grey_info;
            }
            bool operator!=(const hyper_greypixel& op2)const{
                return !(op2 == *this);
            }
            hyper_greypixel(const std::vector<grey>& grey_list = {8,grey()},
                            const grey& sgrey = grey(0),
                            GREY_MODE inmode = GREY){
                if(warn_if(grey_list.size() != 8,"为hyper_greypixel复制的列表项数不符合要求"))
                    return ;
                int sum = 0;
                for(int i = 0;i < 8;++i){
                    sum += grey_list[i].vgrey;
                    pix[i/2][i%2] = (inmode == C256?(grey(t256[sgrey.vgrey]).vgrey > 16):(grey_list[i].vgrey > 128));
                }
                if(sgrey == grey(0))
                    grey_info = grey(sum/8);
                else
                    grey_info = sgrey;
                mode = inmode;
            }
            void show(const hyper_greypixel& last,bool at_front = false)const{
                bool tmp[8] = {pix[0][0],pix[1][0],pix[2][0],pix[0][1],pix[1][1],pix[2][1],pix[3][0],pix[3][1]};
                int res = tmp[0] + tmp[1] * 2 + tmp[2] * 4 + tmp[3] * 8 +
                          tmp[4] * 16 + tmp[5] * 32 + tmp[6] * 64 + tmp[7] * 128;
                if(grey_info.vgrey < 240 || (last.grey_info != grey_info) || at_front){
                    switch(mode){
                        case BINARY:break;
                        case GREY:std::cout << grey_info.make_show_RGB_text();break;
                        case C256:std::cout << t256[grey_info.vgrey].make_show_RGB_text();break;
                        default:std::cout << grey_info.make_show_RGB_text();break;
                    }
                }
                std::cout << map_dotmatrix[res];
            }
    };
    typedef basic_image<hyperpixel> hyper_image;
    hyper_image tohyperimg(const image& img){
        hyper_image outimg(img.height / 2 + img.height%2,img.width / 2 + img.width%2);
        for(int y = 0;y < outimg.height;++y){
            for(int x= 0;x < outimg.width;++x)
                outimg.edit(x,y,hyperpixel(img.get(x * 2,y * 2),img.get(x * 2 + 1,y * 2),img.get(x * 2,y * 2 + 1),img.get(x * 2 + 1,y * 2 + 1)));
        }
        return outimg;
    }
    typedef basic_image<hyper_greypixel> hyper_greyimage;
    pixel search_256pix(const pixel& inpix){
        long long distance = LONG_LONG_MAX;
        int ret = 0;
        for(int i = 0;i < 256;i++){
            long long t1 = (inpix.getred() - t256[i].getred()),
                   t2 = (inpix.getgreen() - t256[i].getgreen()),
                   t3 = (inpix.getblue() - t256[i].getblue()),
                   d = t1*t1 + t2*t2 + t3*t3;
            if(d < distance){
                distance = d;
                ret = i;
            }
        }
        return t256[ret];
    }
    int search_256pix_id(const pixel& inpix){
        long long distance = LONG_LONG_MAX;
        int ret = 0;
        for(int i = 0;i < 256;i++){
            long long t1 = (inpix.getred() - t256[i].getred()),
                   t2 = (inpix.getgreen() - t256[i].getgreen()),
                   t3 = (inpix.getblue() - t256[i].getblue()),
                   d = t1*t1 + t2*t2 + t3*t3;
            if(d < distance){
                distance = d;
                ret = i;
            }
        }
        return ret;
    }
    image reset256(const image& img){
        image tmpimg(img.height,img.width);
        for(int i = 0;i < img.height;++i){
            for(int j = 0;j < img.width;++j)
                tmpimg.edit(j,i,search_256pix(img.get(j,i)));
        }
        return tmpimg;
    }
    hyper_greyimage tohypergreyimg(const image_grey& img,GREY_MODE grey_mode = GREY,bool AUTO = true,const image& c256_img = image()){
        hyper_greyimage outimg(img.height / 4 + (img.height%4 > 0),img.width / 2 + img.width%2);
        for(int y = 0;y < outimg.height;++y){
            for(int x= 0;x < outimg.width;++x){
                outimg.edit(x,y,hyper_greypixel({
                    img.get(x * 2,y * 4)    ,img.get(x * 2 + 1,y * 4),
                    img.get(x * 2,y * 4 + 1),img.get(x * 2 + 1,y * 4 + 1),
                    img.get(x * 2,y * 4 + 2),img.get(x * 2 + 1,y * 4 + 2),
                    img.get(x * 2,y * 4 + 3),img.get(x * 2 + 1,y * 4 + 3)},
                    AUTO?0:search_256pix_id(c256_img.get(x,y)),grey_mode)
                );
            }
        }
        return outimg;
    }
    class pixel_text{
        public:
            pixel pix;
            std::string text;
        public:
            std::string make_show_RGB()const{
                return "\033[48;2;"+std::to_string(pix.red)+";"+
                                     std::to_string(pix.green)+";"+
                                     std::to_string(pix.blue)+"m";
            }
            std::string make_show_RGB_text()const{
                return "\033[38;2;"+std::to_string(pix.red)+";"+
                                     std::to_string(pix.green)+";"+
                                     std::to_string(pix.blue)+"m";
            }
            pixel_text(const pixel& inpix = pixel_white,const std::string& instr = "  "){
                pix = inpix;
                text = instr;
            }
            bool not_equal(const pixel_text& pix2)const{
                return pix != pix2.pix;
            }
            bool operator==(const pixel_text& pix2)const{
                return pix == pix2.pix;
            }
            bool operator!=(const pixel_text& pix2)const{
                return !(pix == pix2.pix);
            }
            void show(const pixel_text& last = pixel_text({0,0,0},""),bool at_front = false)const{
                if(last != *this || at_front)
                    std::cout << make_show_RGB();
                std::cout << text;
            }
    };
    typedef basic_image<pixel_text>   image_text;

    image_grey getPassage(const image& img,const RGB passage){
        image_grey out(img.height,img.width);
        for(int x = 0;x < img.width;++x){
            for(int y = 0;y < img.height;++y){
                switch(passage){
                    case   RED:    out.edit(x,y,grey(img.get(x,y).getred()));break;
                    case GREEN:  out.edit(x,y,grey(img.get(x,y).getgreen()));break;
                    case  BLUE:   out.edit(x,y,grey(img.get(x,y).getblue()));break;
                }
            }
        }
        return out;
    }
    image_grey ImgtoGrey(const image& img,double vRed = 0.30,double vGreen = 0.59,double vBlue = 0.11){
        image_grey out(img.height,img.width);
        for(int x = 0;x < img.width;++x){
            for(int y = 0;y < img.height;++y){
                pixel tmp = img.get(x,y);
                out.edit(x,y,grey(vRed * tmp.getred() + vGreen * tmp.getgreen() + vBlue * tmp.getblue()));
            }
        }
        return out;
    }
    image GreytoImg(const image_grey& img){
        image out(img.height,img.width);
        for(int x = 0;x < img.width;++x){
            for(int y = 0;y < img.height;++y){
                grey tmp = img.get(x,y);
                out.edit(x,y,pixel(tmp.getgrey(),tmp.getgrey(),tmp.getgrey()));
            }
        }
        return out;
    }
    image combinePassage(const image_grey& img_R,const image_grey& img_G,const image_grey& img_B){
        image out(std::min(img_R.height,std::min(img_G.height,img_B.height)),
                  std::min(img_R.width,std::min(img_G.width,img_B.width)));        
        for(int x = 0;x < out.width;++x){
            for(int y = 0;y < out.height;++y)
                out.edit(x,y,pixel(img_R.get(x,y).getgrey(),img_G.get(x,y).getgrey(),img_B.get(x,y).getgrey()));
        }
        return out;
    }
    image averageNoise(const image& img,unsigned char differ = 16){
        const int dx[8] = {-1,0,1,-1,1,-1,0,1},dy[8] = {-1,-1,-1,0,0,1,1,1};
        image out(img.height,img.width);
        for(int x = 0;x < img.width;++x){
            for(int y = 0;y < img.height;++y){
                pixel pix = img.get(x,y);
                int dR = 0,dG = 0,dB = 0;
                for(int i = 0;i < 8;++i){
                    pixel tmp = img.get(x + dx[i],y + dy[i]);
                    dR += tmp.getred();
                    dG += tmp.getgreen();
                    dB += tmp.getblue();
                }
                if(abs(dR + dG + dB - 8 * (pix.getred() + pix.getgreen() + pix.getblue())) >= 3 * differ)
                    out.edit(x,y,pixel(dR / 8,dG / 8,dB / 8));
                else
                    out.edit(x,y,pix);
            }
        }
        return out;
    }
    
    class windows{
        private:
            int height;
            int width;
            
    };
    int doclear(){
        try{
            std::cout << CLEARSCREEN_CMDCOMMMAND;
            return 1;
        }catch(...){
            return 0;
        }//或许永远不会发生？
    }//调用系统cmd清屏
    
    char getch(){  
        char Input;
        struct termios a;
        struct termios b;
        int ret;
        tcgetattr(STDIN_FILENO,&a);
        memcpy(&b,&a,sizeof(b));
        b.c_lflag &= ~(ICANON);
        b.c_cc[VMIN] = 1;
        b.c_cc[VTIME] = 0;
        ret=tcsetattr(STDIN_FILENO,TCSANOW,&b);
        fflush(stdout);
        ret = read(STDIN_FILENO,&Input,1);
        tcsetattr(STDIN_FILENO,TCSANOW,&a);
        return Input;
    }  
    char datain(bool end = true){
        char tmp_c = getch();
        if(end)
            std::cout << std::endl << "\r";
        return tmp_c;
    }//获取单个字符
    
    int digitin(){
        char tmpin = datain(true);
        return isdigit(tmpin)?(tmpin-'0'):1;
    }
    const std::vector<std::string> key_word = {
    "alignas","alignof","and","and_eq","asm","__asm__",
    "auto","bitand","bitor","bool","break","_Bool",
    "case","catch","char","char16_t","char32_t","class",
    "const","compl","const_cast","constexpr","decltype","default",
    "delete","do","double","dynamic_cast","else","enum",
    "explicit","export","extern","false","FALSE","float",
    "for","friend","global","goto","if","include",
    "inline","int","iostream","iterator","_Imaginary",
    "long","mutable","new","namespace","noexcept","not",
    "not_eq","NULL","nullptr","operator","or","or_eq",
    "private","protected","public","_Pragma","register","reinterpret_cast",
    "restrict","return","short","signed","size","sizeof",
    "static","static_cast","struct","switch","template",
    "this","thread_local","throw","true","TRUE","try",
    "typedef","typeid","typename","union","unsigned","using",
    "virtual","void","volatile","wchar_t","while","xor",
    "xor_eq",
    "std","string","wstring","vector","map","list","multimap","set","multiset",
    };//关键词
    const std::vector<std::string> key_word_color = {
    text_lightblue,text_lightblue,text_gray,text_gray,text_lightblue,text_lightblue,
    text_lightblue,text_gray,text_gray,text_lightblue,text_lightblue,text_lightblue,
    text_lightblue,text_lightblue,text_lightblue,text_lightblue,text_lightblue,text_lightblue,
    text_lightblue,text_gray,text_lightblue,text_lightblue,text_lightblue,text_lightblue,
    text_lightblue,text_lightblue,text_lightblue,text_gray,text_lightblue,text_lightblue,
    text_lightblue,text_lightblue,text_lightblue,text_cyan,text_cyan,text_lightblue,
    text_lightblue,text_lightblue,text_lightblue,text_lightblue,text_lightblue,text_lightblue,
    text_lightblue,text_lightblue,text_lightblue,text_lightblue,text_lightblue,
    text_lightblue,text_lightblue,text_lightblue,text_gray,text_lightblue,text_gray,
    text_gray,text_cyan,text_cyan,text_lightblue,text_gray,text_gray,
    text_lightblue,text_lightblue,text_lightblue,text_lightblue,text_lightblue,text_gray,
    text_lightblue,text_lightblue,text_lightblue,text_lightblue,text_lightblue,text_gray,
    text_lightblue,text_gray,text_lightblue,text_lightblue,text_lightblue,
    text_green,text_lightblue,text_lightblue,text_cyan,text_cyan,text_lightblue,
    text_lightblue,text_gray,text_lightblue,text_lightblue,text_lightblue,text_lightblue,
    text_lightblue,text_lightblue,text_lightblue,text_lightblue,text_lightblue,text_gray,
    text_gray,
    text_violet,text_cyan,text_cyan,text_cyan,text_cyan,text_cyan,text_cyan,text_cyan,text_cyan,
    };//关键字标色
    const std::vector<char> key_char = {
    '!','%','^','&','-','=','+','|','<','>','/','~',':','(',')','[',']','{','}',',',        
    };
    const std::vector<std::string> key_macro = {
    "#include","#define","#if","#else","#endif","#ifdef","#ifndef","#pragma","#elif"
    };
    const std::vector<std::string> key_char_color = {
    text_orange,text_orange,text_orange,text_orange,text_orange,text_orange,text_orange,text_orange,text_orange,text_orange,text_orange,text_orange,text_violet,text_orange,text_orange,text_orange,text_orange,text_orange,text_orange,text_orange,
    };
    
    inline int find_keyword(const std::string& input){
        for(int i = 0;i< key_word.size();++i){
            if(input == key_word[i])
                return i;
        }
        return -1;
    }
    inline int find_macro(const std::string& input){
        for(int i = 0;i< key_word.size();++i){
            if(input == key_macro[i])
                return i;
        }
        return -1;
    }
    inline int find_keychar(char input){
        for(int i = 0;i<key_char.size();++i){
            if(input == key_char[i])
                return i;
        }
        return -1;
    }
    inline bool isnoncoloredchar(char input){
        return (isalpha(input)||isdigit(input)||input=='_'||input=='#'||input=='\"'||input=='\'');
    }
    bool issimulatechar(char front,char input){
        return ( (isalpha(front)&&isalpha(input))||
                 (isalpha(front)&&isdigit(input))||
                 (isdigit(front)&&isalpha(input))||
                 (isdigit(front)&&isdigit(input))||
                 (front=='_'&&(isdigit(input)||isalpha(input)||input=='_'))||
                 (input=='_'&&(isdigit(front)||isalpha(front)||front=='_'))||
                 (front=='#'&&(isdigit(input)||isalpha(input)||input=='#'))||
                 (input=='#'&&(isdigit(front)||isalpha(front)||front=='#'))||
                 (find_keychar(front)!=-1 && find_keychar(input)!=-1 && !(front != '/' && input == '/'))||
                 (front==input&&front!='\"'&&front!='\''&&input!='\"'&&input!='\'')
        );
    }
    std::vector<std::string> sep_bykeychar(const std::string& input){
        std::vector<std::string> out;
        for(int a = 0;a<input.length();a++){
            std::string put_newstr;
            put_newstr+=input[a];
            a++;
            while(issimulatechar(input[a-1],input[a])&&input[a-1]!='\n'&&a<input.length())
                put_newstr+=input[a++];
            a--;
            out.push_back(put_newstr);
        }
        return out;
    }
    bool contain_onlydigit(const std::string& input){
        for(auto&&i:input){
            if(!isdigit(i))
                return false;
        }
        return true;
    }
    bool is_hex_num(const std::string& input){
        if(input.size()<=1)
            return false;
        if(input[0]=='0'&&(input[1]=='x'||input[1]=='X')){
            for(int i = 2;i<input.length();++i){
                if(!isdigit(input[i]))
                    return false;
            }    
            return true;
        }else
            return false;
    }
    bool is_long_num(const std::string& input){
        if(input.size()<=1)
            return false;
        if(input[input.size()-1]=='l'||input[input.size()-1]=='L'){
            for(int i = 0;i<input.size()-1;++i){
                if(!isdigit(input[i]))
                    return false;
            }    
            return true;
        }else
            return false;
    }
    bool is_longhex_num(const std::string& input){
        if(input.size()<=1)
            return false;
        if(input[input.size()-1]=='l'||input[input.size()-1]=='L'){
            if(input[0]=='0'&&(input[1]=='x'||input[1]=='X')){
                for(int i = 2;i<input.length()-1;++i){
                    if(!isdigit(input[i]))
                        return false;
                }    
                return true;
            }else
                return false;
        }else
            return false;
    }
    bool is_float_num(const std::string& input){
        if(input.size()<=1)
            return false;
        if(input[input.size()-1]=='f'||input[input.size()-1]=='F'){
            for(int i = 0;i<input.size()-1;++i){
                if(!isdigit(input[i]))
                    return false;
            }    
            return true;
        }else
            return false;
    }
    
    inline int warn_if(bool statement,const std::string& show,int type_warning){
        if(statement){
            if(show != VOID_PARAMETER)//非空串
                CUIL_std::warning_queue.push({type_warning,show+CUIL_std::_CLEAREFFECT_STR});
            else
                CUIL_std::warning_queue.push({type_warning,_NOW_DEFAULT_WARNING+CUIL_std::_CLEAREFFECT_STR});
        }
        return statement;
    }//如果表达式为真，进行警告
    
    std::vector<std::string> split(const std::string& input,char sep = ','){
        std::vector<std::string>input_units;
        for(long long spliti=0;spliti<input.length();++spliti){
            if(input[spliti]!=sep){
                input_units.push_back("");
                while(input[spliti]!=sep&&spliti<input.length())
                    input_units[input_units.size()-1]+=input[spliti++];
            }
        }
        return input_units;
    }//分割字符串
    
    std::string wstrcpy(const std::string& cpystr,int cpynum){
        std::string out_wstrcpy;
        for(int i = 1;i<cpynum;++i)
            out_wstrcpy+=cpystr;
        return out_wstrcpy;
    }//复写字符串
    
    std::string wstrcpy(char cpystr,int cpynum){
        std::string out_wstrcpy;
        for(int i = 1;i<=cpynum;++i)
            out_wstrcpy+=cpystr;
        return out_wstrcpy;
    }//对char的重载
    void clear_warning(){
        while(!warning_queue.empty())
            CUIL_std::warning_queue.pop();
        return ;
    }//清除警告
    void updwarning(){
        while(!CUIL_std::warning_queue.empty()){
            std::cout  << "|"<<warning_color_type[CUIL_std::warning_queue.front().warn_type]<<"  "<<_CLEAREFFECT_STR<<"|"
                        <<CUIL_std::warning_queue.front().content<<"\n";
            CUIL_std::warning_queue.pop();
        }
        std::cout<<std::endl;
    }//清空并输出警告队列
    void PAUSE(){
        char tmp;
        std::cout<<"按任意键继续>>>";
        tmp = datain(true);
    }
    std::string make_shapebool(bool input){
        return input?("是|"+green+"  "+_CLEAREFFECT_STR):("否|"+red+"  "+_CLEAREFFECT_STR);
    }
    std::string formin(const std::string& show = "输入：",int line_len = 10){
        std::cout << show;
        std::string line = wstrcpy("_",line_len);
        std::string back = wstrcpy("\b",line_len);
        std::cout << line<<back;
        std::string input;
        getline(std::cin,input);
        return input;
    }
    
    //复合组件原型
    template<class T>int uniselect(const std::vector<T>choice_list,std::string title="",char last_sign='w',char next_sign='s',char end_sign='y',int choice_first=1);//一元选择器
    template<class T>std::vector<int> multiselect(const std::vector<T> choice_list,std::string title="",char last_sign='w',char next_sign='s',char choice_sign='y',char cancel_sign='c',char end_sign='z',int choice_first=1);
    void dot_linerary_load(double wait_time,int width = 10,int height = 1,bool has_boarder = true,bool has_progress = true,char show_char = 'O',char blank_char = ' ');//点型加载
    void shape_linerary_load(double wait_time,int width = 10,int height = 1,bool has_border = true,bool has_progress = true,std::string format_pass = _CLEAREFFECT_STR,std::string format_border = _CLEAREFFECT_STR,char pass_char = '#',char show_char = '#',char blank_char = ' ');//线性加载 
    void ring_linerary_load();//环形加载动效
    void print(const std::string& content,const format& formatin = printformat,bool step = true,double char_per_sec = 4.0,bool end = true);//打印
    void printcode(const std::string code,const std::string lang = "cpp");
    //复合组件实现

    
    
    template<class T>
    int uniselect(const std::vector<T> choice_list,std::string title,char last_sign,char next_sign,char end_sign,int choice_first){
        std::set<char>sign_list = {last_sign,next_sign,end_sign};
        if(warn_if(sign_list.size()<3,"uniselect组件不得有相同的操作字符"))
            return 0;
        char tmp_listchoice=' ';
        int choice_now = choice_first;
        while(tmp_listchoice!=end_sign){
            doclear();
            if(title.length()<30)
                std::cout <<title<<std::endl;
            else
                print(title,printformat,true,500.0);
            std::cout<<"选择："<<std::endl;
            for(int choice_i = 1;choice_i<=choice_list.size();++choice_i)
                std::cout<<(choice_now==choice_i?">  "+text_lightgreen:"   ")<<choice_i<<"." << choice_list.at(choice_i-1) << _CLEAREFFECT_STR<< std::endl;
            std::cout<<"（"<<last_sign<<","<<next_sign<<"上下切换选项,"<<end_sign<<"确定）"<<std::endl;
            std::cout<<">>>";
            tmp_listchoice=datain(true);
            if(tmp_listchoice==last_sign)
                choice_now=(choice_now>1?choice_now-1:choice_list.size());
            if(tmp_listchoice==next_sign)
                choice_now=(choice_now<choice_list.size()?choice_now+1:1);
        }
        return choice_now;
    }
    template<class T>
    std::vector<int> multiselect(const std::vector<T> choice_list,std::string title,char last_sign,char next_sign,char choice_sign,char cancel_sign,char end_sign,int choice_first){
        std::set<char>sign_list = {last_sign,next_sign,end_sign,choice_sign,cancel_sign};
        if(warn_if(sign_list.size()<5,"multiselect组件不得有相同的操作字符"))
            return {0};
        char tmp_listchoice=' ';
        int choice_now = choice_first;
        std::set<int> select_list;
        std::vector<int> ret_list;
        while(tmp_listchoice!=end_sign){
            doclear();
            if(title.length()<30)
                std::cout <<title<<std::endl;
            else
                print(title,printformat,true,500.0);
            std::cout<<"选择："<<std::endl;
            for(int choice_i = 1;choice_i<=choice_list.size();++choice_i)
                std::cout<<(choice_now==choice_i?"> ":"  ")<<((select_list.find(choice_i)!=select_list.end())?"O "+text_lightgreen:"  ")<<choice_i<<"." << choice_list.at(choice_i-1) << _CLEAREFFECT_STR << std::endl;
            std::cout<<"（"<<last_sign<<","<<next_sign<<"上下切换选项,"<<choice_sign<<"选择,"<<cancel_sign<<"取消,"<<end_sign<<"结束）"<<std::endl<<">>>";
            tmp_listchoice=datain(true);
            if(tmp_listchoice==last_sign)
                choice_now=(choice_now>1?choice_now-1:choice_list.size());
            if(tmp_listchoice==next_sign)
                choice_now=(choice_now<choice_list.size()?choice_now+1:1);
            if(tmp_listchoice==choice_sign)
                select_list.insert(choice_now);
            if(tmp_listchoice==cancel_sign){
                if(select_list.find(choice_now) != select_list.end())
                    select_list.erase(select_list.find(choice_now));
            }
        }
        for(auto&&i:select_list)
            ret_list.push_back(i);
        return ret_list;
    }
    template<class T>
    int uniselect_extend(const std::vector<T> choice_list,std::string title,char last_sign,char next_sign,char end_sign,int choice_first){
        std::set<char>sign_list = {last_sign,next_sign,end_sign};
        if(warn_if(sign_list.size()<3,"uniselect组件不得有相同的操作字符"))
            return 0;
        char tmp_listchoice=' ';
        int choice_now = choice_first;
        while(tmp_listchoice!=end_sign){
            doclear();
            if(title.length()<30)
                std::cout <<title<<std::endl;
            else
                print(title,printformat,true,500.0);
            std::cout<<"选择："<<std::endl;
            for(int choice_i = 1;choice_i<=choice_list.size();++choice_i)
                std::cout<<(choice_now==choice_i?">  "+text_lightgreen:"   ")<<choice_i<<"." << choice_list.at(choice_i-1) << _CLEAREFFECT_STR<< std::endl;
            std::cout<<"（"<<last_sign<<","<<next_sign<<"上下切换选项,"<<end_sign<<"确定）"<<std::endl;
            std::cout<<">>>";
            tmp_listchoice=datain(true);
            if(tmp_listchoice==last_sign)
                choice_now=(choice_now>1?choice_now-1:choice_list.size());
            if(tmp_listchoice==next_sign)
                choice_now=(choice_now<choice_list.size()?choice_now+1:1);
        }
        return choice_now;
    }
    void dot_linerary_load(double wait_time,int width,int height,bool has_border,bool has_progress,char show_char,char blank_char){
        if(warn_if(wait_time<0.0,"dot_linerary_load组件参数错误：时间参数不得小于0",1))
            return ;
        if(warn_if(width<0,"dot_linerary_load组件参数错误：长度参数不得小于0",1))
            return ;
        if(warn_if(height<0,"dot_linerary_load组件参数错误：高度参数不得小于0",1))
            return ;
        doclear();
        std::string up_border_str = "┌" + wstrcpy("─",width+1) + "┐\n",
                     down_border_str = "└" + wstrcpy("─",width+1) + "┘\n";
        for(int i = 1;i<=width;++i){
            doclear();
            if(height == 1){
                std::cout << (has_border?"[":"");
                for(int j = 0;j<width;++j){
                    if(j==i-1)
                        std::cout << show_char;
                    else
                        std::cout << blank_char;
                }
                std::cout << (has_border?"]":"") << _CLEAREFFECT_STR;
                if(has_progress)
                    std::cout << int(100*i/width) <<"%"<<_CLEAREFFECT_STR;//文字颜色自行添加
                std::cout << std::endl;
            }
            else{
                std::string mid_content_str = (has_border?"│":"") + wstrcpy(blank_char,i-1) + show_char + wstrcpy(blank_char,width-i) + (has_border?"│":""); 
                if(has_border)
                    std::cout << up_border_str;
                for(int k = 0;k<height;k++){
                    std::cout << mid_content_str;
                    if(k==(height+1)/2){
                        if(has_progress)
                        std::cout << int(100*i/width) <<"%"<<_CLEAREFFECT_STR;//文字颜色自行添加
                    }
                    std::cout << "\n"; 
                }
                if(has_border)
                    std::cout << down_border_str;
            }
            usleep(int(wait_time*1000000)/width);
        }//线性加载动效
    }
    void shape_linerary_load(double wait_time,int width,int height,bool has_border,bool has_progress,std::string format_pass,std::string format_border,char pass_char,char show_char,char blank_char){
        if(warn_if(wait_time<0.0,"shape_linerary_load组件参数错误：时间参数不得小于0",1))
            return ;
        if(warn_if(width<0,"shape_linerary_load组件参数错误：长度参数不得小于0",1))
            return ;
        if(warn_if(height<0,"shape_linerary_load组件参数错误：高度参数不得小于0",1))
            return ;
        std::string up_border_str = format_border + "┌" + wstrcpy("─",width+1) + "┐\n"+_CLEAREFFECT_STR,
                     down_border_str = format_border + "└" + wstrcpy("─",width+1) + "┘\n"+_CLEAREFFECT_STR;
        for(int i = 1;i<=width;++i){
            doclear();
            if(height == 1){
                std::cout << format_border << (has_border?"[":"") << _CLEAREFFECT_STR;
                std::cout << format_pass;
                for(int j = 0;j<width;++j){
                    if(j<i-1)
                        std::cout << pass_char;
                    else if(j==i-1)
                        std::cout <<show_char<<_CLEAREFFECT_STR;
                    else
                        std::cout << blank_char;
                }
                std::cout << format_border << (has_border?"]":"") << _CLEAREFFECT_STR;
                if(has_progress)
                    std::cout << int(100*i/width) <<"%"<<_CLEAREFFECT_STR;//文字颜色自行添加
                std::cout << std::endl;
            }
            else{
                std::string mid_content_str = format_border + (has_border?"│":"") + _CLEAREFFECT_STR + format_pass + wstrcpy(pass_char,i-1) + show_char + _CLEAREFFECT_STR + wstrcpy(blank_char,width-i) + _CLEAREFFECT_STR + format_border + (has_border?"│":"")+_CLEAREFFECT_STR; 
                if(has_border)
                    std::cout << up_border_str;
                for(int k = 0;k<height;k++){
                    std::cout << mid_content_str;
                    if(k==(height+1)/2){
                        if(has_progress)
                        std::cout << int(100*i/width) <<"%"<<_CLEAREFFECT_STR;//文字颜色自行添加
                    }
                    std::cout << "\n"; 
                }
                if(has_border)
                    std::cout << down_border_str;
            }
            usleep(int(wait_time*1000000)/width);
        }//图形化加载动效
    }
    void print(const std::string& content,const format& formatin,bool step,double char_per_sec,bool end){
        if(warn_if(char_per_sec<0.0,"print组件参数错误：速度参数不得小于0",1))
            return ;
        std::cout << formatin.text_color<<
                      formatin.background_color<<
                      (formatin.useitalic?italic:"");
        if(!step || char_per_sec == 0.0)
            std::cout<<content;//无延迟，直接输出
        else{
            for(auto&&i:content){
                std::cout<<i;
                if(isascii(i))
                    usleep(1000000.0/(3 * char_per_sec));
                else
                    usleep(1000000.0/(9* char_per_sec));
            }
            
        }
        std::cout<<_CLEAREFFECT_STR;
        if(end)
            std::cout << std::endl;
        
    }
    template<typename T>
    void printvec(std::vector<T>input){
        std::cout<<"{"<<std::endl;
        for(auto&&i:input)
            std::cout<<"["<<i<<"]"<<std::endl;
        std::cout<<"}"<<std::endl;
    }
    void printcode(const std::string code,const std::string lang){
        std::cout << codeformat.background_color << (codeformat.useitalic?italic:"");
        std::string out_print;
        std::string code_t;
        int code_start = 0;
        out_print+=codeformat.background_color;
        while(code[code_start]==' '&&code_start<code.length())
            out_print+=code[code_start++];
        for(int i = code_start;i<code.length();++i)
            code_t+=code[i];
        std::vector<std::string>first_word = sep_bykeychar(code_t);
        printvec(first_word);
        sleep(1);
        for(int i = 0;i<first_word.size();++i){
            out_print+=codeformat.background_color;
            std::string j = first_word[i];
            if(contain_onlydigit(j)||is_hex_num(j)||is_long_num(j)||is_longhex_num(j)||is_float_num(j)){
                out_print+=(text_lightblue+j+_CLEAREFFECT_STR);
                continue;
                //对于16进制数字，长整型数字与浮点数字的判定
            }else{
                if(j==";"){
                    out_print+=codeformat.background_color+text_white+j;
                    continue;
                }
                if(j=="/" && first_word[i + 1] == "*"){
                    out_print+=codeformat.background_color+text_green + "/*";
                    i+=2;
                    while(i + 1 < first_word.size() && !(first_word[i] == "*" && first_word[i+1] == "/"))
                        out_print+=first_word[i++];
                    //注释一律标绿
                    ++i;
                    out_print+="*/"+_CLEAREFFECT_STR;
                    continue;
                }//行间注释
                if(j=="\""){
                    out_print+=text_lightgreen+codeformat.background_color+j;
                    ++i;
                    while(first_word[i]!="\""&&i<first_word.size()){
                        if(first_word[i]=="\\"){
                            out_print+=text_lightblue+codeformat.background_color;
                            out_print+=first_word[i]+first_word[i+1];//转义字符本身
                            out_print+=_CLEAREFFECT_STR+codeformat.background_color;
                            i+=2;//跳过两个字符
                            continue;
                        }//转义字符判定
                        out_print+=first_word.at(i++);
                    }
                    out_print+=text_lightgreen+first_word[i]+_CLEAREFFECT_STR+codeformat.background_color;
                    continue;
                }//字符串判定
                if(j=="\'"){
                    out_print+=text_lightgreen+codeformat.background_color+j;
                    if(i+2<first_word.size() && first_word[i+2]=="\'")
                        out_print+=first_word[i+1]+"\'";
                    out_print+=_CLEAREFFECT_STR+codeformat.background_color;
                    i+=2;
                    continue;
                }//字符判定
                if(first_word[i]=="\\"){
                    out_print+=text_lightblue+codeformat.background_color;
                    out_print+=first_word[i]+first_word[i+1];//转义字符本身
                    out_print+=_CLEAREFFECT_STR+codeformat.background_color;
                    i+=2;//跳过两个字符
                    continue;
                }//转义字符判定
                int id_keyword = find_keyword(j),id_macro = find_macro(j);
                if(id_keyword!=-1)
                    out_print+=(key_word_color[id_keyword]+j+_CLEAREFFECT_STR);
                //关键字    
                else if(j=="//"){
                    out_print+=codeformat.background_color+text_green;
                    for(;i<first_word.size();++i){
                        if(first_word[i] == "\n")
                            break;
                        out_print+=first_word[i];
                    }
                    //注释一律标绿
                    out_print+="\n"+_CLEAREFFECT_STR;
                    continue;
                }else if(id_macro!=-1){
                    //非关键字，但为宏类型关键词
                    out_print+=(text_lightblue+j+" "+codeformat.background_color);
                    for(int k = i+1;k<first_word.size();k++)
                        out_print+=text_red+first_word[k];
                    //宏关键词一律标红
                    out_print+=_CLEAREFFECT_STR;
                    break;
                }else if(find_keychar(j[0]) != -1)
                    out_print+=key_char_color[find_keychar(j[0])]+j;
                //关键字符
                else
                    out_print+=text_white+j;
                //用户自定义标识符或未知，默认为白色
            }//关键字，宏定义等其他情况
            
        }
        print(out_print+_CLEAREFFECT_STR,printformat,true,1000.0);
    }
};
using namespace CUIL_std;
    

namespace survive{
    const std::string REQUIRE_CUIL_VERSION = "CUIL v0.0.9";//需要的CUIL版本
    const std::string GameVersion = "Survive 1.5.2";//游戏版本

    // @note 这部分定义所有的方块id
    enum basic_block_id{
        id_block_empty = -1,//非游戏内方块，占位用
        id_block_air,//空气                  0
        id_block_stone,//石头                1
        id_block_cobblestone,//圆石          2
        id_block_grass,//草方块              3
        id_block_dirt,//泥土                 4
        id_block_barrier,//屏障              5
        id_block_water,//水                  6
        id_block_lava,//岩浆                 7
        id_block_bedrock,//基岩              8
        id_block_wood,//树木                 9
        id_block_furnace,//熔炉              10
        id_block_crafting_table,//工作台     11
        id_block_sand,//沙子                 12
        id_block_leaf,//树叶                 13
        id_block_unknown_block,//未知方块    14
        id_block_coal_ore,//煤矿石           15
        id_block_short_grass,//矮草丛        16
        id_block_rose,//玫瑰                 17
        id_block_snow,//雪块                 18
        id_block_ice,//冰块                  19
        id_block_magma_block,//岩浆方块      20
        id_block_granite,//花岗岩            21
        id_block_limestone,//石灰岩          22
        id_block_wood_plank,//木板           23
    };
    // @note 这部分定义所有的生物群系
    enum basic_biome_id{
        id_biome_plain,//平原                            0
        id_biome_dessert,//沙漠                          1
        id_biome_mountain,//山脉                         2
        id_biome_extreme_mountain,//极限山脉             3
        id_biome_ocean,//海洋                            4
        id_biome_lava_sea,//岩浆海                       5
        id_biome_forest,//森林                           6
        id_biome_jungle,//丛林                           7
        id_biome_volcano,//火山                          8
        id_biome_extreme_plain,//极平原                  9
        id_biome_snow_plain,//雪原                       10
        id_biome_extreme_peak,//极限山峰                 11
        id_biome_extreme_deepocean,//极限深海            12
        id_biome_extreme_snow_plain,//极地雪原           13
        id_biome_beach,//海滩                            14
        id_biome_mountain_edge,//山地边缘                15
        id_biome_lavaland,//岩浆陆                       16
        id_biome_continent_shelf,//大陆架                17
        id_biome_plateau,//高原                          18
        id_biome_tectogene,//海沟                        19
        id_biome_tropical_plain,//热带草原               20
        id_biome_extreme_heatpeak,//赤极                 21
        id_biome_infinite_abysm,//无尽渊                 22
        id_biome_polar_ocean,//极洋                      23
        id_biome_lush_plateau,//繁茂高原                 24
        id_biome_lush_plain,//繁花平原                   25
        id_biome_hill,//丘陵                             26
        id_biome_fractured_cliff,//破碎峭壁              27
        id_biome_forest_edge,//森林边界                  28
        id_biome_steepice_plain,//峭冰平原               29
        id_biome_fallen_valley,//陨落谷                  30
        id_biome_swamp,//沼泽                            31
        id_biome_lush_jungle,//繁茂雨林                  32
    };
    // @note 这部分定义所有的方块tag
    enum basic_tag_id{
        tag_unbreakable,//规定方块不可破坏
        tag_interaction,//规定方块可以进行交互
        tag_plant,//规定方块可以在上方生成植物
        tag_ore_replaceable,//规定方块可以被替换为矿石
        tag_through,//规定方块可以穿过
        tag_gravity,//规定方块受重力影响
        tag_oxygen,//规定处于方块中会消耗氧气值
        tag_fluid,//规定方块是流体
        tag_replaceable,//规定方块可以被直接替换为别的方块
    };
    enum basic_item_tag_id{
        tag_item_meltable,//规定物品可熔炼
        tag_item_food,//规定物品为食物
        tag_item_invalid,//规定物品在生存模式下非法
        tag_item_fuel,//规定物品可做燃料
    };
    // @note 这部分定义所有的世界生成模式
    enum basic_worldtype_id{
        id_worldtype_normal, //正常世界
        id_worldtype_flat,   //超平坦世界
        id_worldtype_void,   //虚空世界
        id_worldtype_error,  //错乱世界
        id_worldtype_arrakis,//沙丘世界
        id_worldtype_ocean,  //海洋世界
        id_worldtype_froze,  //冰雪世界
    };
    // @note 这部分定义所有的游戏模式
    enum gamemode_basic{
        gamemode_survival,//生存模式
        gamemode_creative,//创造模式
    };
    // @note 这部分定义所有物品的id
    // 物品详细信息见items_list定义
    enum basic_item_id{
        id_item_void,//空物品                           0
        id_item_stone,//石头                            1
        id_item_cobblestone,//圆石                      2
        id_item_grass,//草方块                          3
        id_item_dirt,//泥土                             4
        id_item_bedrock,//基岩                          5
        id_item_barrier,//屏障                          6
        id_item_wood,//木头                             7
        id_item_leaf,//树叶                             8
        id_item_furnace,//熔炉                          9
        id_item_crafting_table,//工作台                10
        id_item_sand,//沙子                            11
        id_item_coal_ore,//煤矿石                      12
        id_item_rose,//玫瑰花                          13
        id_item_short_grass,//矮草丛                   14
        id_item_snow_block,//雪块                      15
        id_item_ice,//冰                               16
        id_item_magma_block,//岩浆方块                 17
        id_item_granite,//花岗岩                       18
        id_item_limestone,//石灰岩                     19
        id_item_stick,//木棍                           20
        id_item_wood_plank,//木板                      21
        id_item_raw_pork,//生猪肉                      22
        id_item_cooked_pork,//熟猪肉                   23
        id_item_raw_mutton,//生羊肉                    24
        id_item_cooked_mutton,//熟羊肉                 25
        id_item_raw_beef,//生牛肉                      26
        id_item_cooked_beef,//熟牛肉                   27
        id_item_leather,//皮革                         28
    };
    typedef basic_item_id item_t;
    // @note 这部分定义标准时间的ID，按时间段划分
    // 详细分区见getGameTimeID函数
    enum TIME{
        SUNRISE,  //日出
        DAY,      //白日
        NOON,     //正午
        AFTERNOON,//下午
        SUNSET,   //日落
        NIGHT,    //夜晚
        MIDNIGHT, //午夜
    };
    // @note 这部分定义所有的行为树返回结果，存在特殊值
    enum BEHAVIOR_STATUS{
        FAILURE =  0,//失败
        SUCCESS = +1,//成功
        FINAL   = -1,//清除
        MOVE    = -2,//转移
    };
    // @note 这部分定义所有的实体id
    enum basic_entity_id{
        entity_void,//空实体
        entity_player,//玩家
        entity_wanderer,//荡迹人
        entity_pig,//猪
        entity_cow,//牛
        entity_sheep,//羊
    };
    // @note 对玩家权限的定义
    enum PERMISSION{
        VISITOR,//访客
        OPERATOR,//操作员
        TRUSTABLE,//完全信任
    };
    enum INTERFACE{
        INTERFACE_MAINSCREEN,
        INTERFACE_BACKPACK,
        INTERFACE_CRAFTING_TABLE,
        INTERFACE_FURNACE
    };
    struct gameruninfo;//游戏运行信息（实例为gameinfo）
    class __convert;//标准转换类（实例为convert）
    struct block;//方块信息类
    struct item;//物品类
    struct item_info;//物品信息类
    struct biome;//生物群系信息类
    struct Worldset;//世界设置类（实例为worldset）
    class noise;//噪声类
    template<class T> class basic_position;//基础坐标(position == basic_position<long long,long long>)
    template<class T> class basic_range;//基础区间类
    struct gamerule_info;//游戏规则设置（实例为gamerule）
    class container;//容器类
    class basic_ui;//基础UI
    class ui_crafting_table;//工作台UI
    struct playerinfo;//玩家信息（实例为player）
    struct info_pack;//信息包
    class exception;//异常类
    struct block_operation;//方块操作类
    struct std_position_cmp;//标准坐标比较
    class world;//世界类
    class chunk;//区块类
    struct hitbox;//碰撞箱
    class basic_ai;//基础行为AI
    class entity;//基础实体
    struct predicator_block_through;//方块谓词：检查through标签
    struct predicator_block_fluid;//方块谓词：检查fluid标签
    struct predicator_block_breakable;//方块谓词：检查unbreakable标签
    struct predicator_block_air;//方块谓词：检查id ?= air
    const long long max_data = 9223372036854775807;//设定的游戏地图数据最大值
    const long long chunkWidth = 16;//区块宽度
    //折中值，对地图单元化存储很友好
    const long long positive_crash_line = max_data - (chunkWidth << 1);//正崩坏线  9223372036854775775 
    //具体计算方式为max_data - 2 * chunkWidth，系数2来自玩家视野距离（最大为2个区块）
    const long long worldMaxinumHeight = 512;// 世界高度限制
    //256不能容纳部分极高大的山峦群系，故设置为512
    
    const long double default_sample_terrain = 0.0009765625;
    //地形取样频率：每一坐标单位取样1024次(2^-10)
    //从大尺度上看一个基础的噪声地形至少需要横跨上百方块的变化才能是合格的大型地图地形，故将此频率设置的较高
    //如果想缩小整个地形的变化尺度，可以以2^-N的方式重新设置该值。
    const long double default_sample_biome = 0.0009765625;
    //群系取样频率：每一坐标单位取样1024次(2^-10)
    //同上，群系的变化程度也应该与地形匹配。
    const long double default_sample_terrain_granite = 0.00390625;
    //地形-地质-花岗岩：每一坐标单位取样256次(2^-8)
    const long double default_sample_terrain_limestone = 0.00390625;
    //地形-地质-石灰岩：每一坐标单位取样256次(2^-8)
    const long double default_sample_terrain_dirt = 0.00390625;
    //地质方块的生成需要形成小而密集的簇状分布，故将此值设置的较大
    const long double default_sample_cave = 0.001953125;
    //洞穴取样频率：每一坐标单位取样512次（2^-9）
    //相较于地形，洞穴的变化程度要略高于山峦，故设置为地形取样频率*2
    
    
    /*@defination_commarg_1
        ——命令系统部分——
        命令执行函数：command_<命令标识符>
        函数执行成功返回1，失败返回0
        任何参数都与下方command_arg_num与command_arg_type类型保持一致
        一些代号：
        0/i —— integer
        1/b —— boolean value
        2/s —— string
        3/c —— character
    */
    const std::string command_argname[] = {"integer","boolean","string","character","float"};
    // @note 所有的命令标识符
    struct commands_info{
        std::string identifier;
        int arg_num;
        std::string arg_type;
        PERMISSION permission;
    };
    std::vector<commands_info> command_list = {
        {"w",                  0,          "n",       VISITOR},
        {"a",                  0,          "n",       VISITOR},
        {"s",                  0,          "n",       VISITOR},
        {"d",                  0,          "n",       VISITOR},
        {"/move",              1,          "3",       VISITOR},
        {"/set",               3,          "302",     VISITOR},
        {"/break",             2,          "30",      VISITOR},
        {"/fill",              5,          "22222",  OPERATOR},
        {"/tp",                2,          "22",     OPERATOR},
        {"/clone",             6,          "222222", OPERATOR},
        {"/gamemode",          1,          "2",       VISITOR},
        {"/help",              0,          "n",       VISITOR},
        {"e",                  0,          "n",       VISITOR},
        {"/gamerule",         -1,          "n",      OPERATOR},
        {"/testblock",         2,          "22",     OPERATOR},
        {"/kill",              0,          "n",      OPERATOR},
        {"/eat",               0,          "n",      OPERATOR},
        {"/setblock",          3,          "222",    OPERATOR},
        {"/seed",              0,          "n",       VISITOR},
        {"/biome",             0,          "n",       VISITOR},
        {"/say",              -1,          "n",       VISITOR},
        {"/give",              2,          "20",     OPERATOR},
        {"/throw",             1,          "0",       VISITOR},
        {"/savefile",          1,          "2",       VISITOR},
        {"/time",              2,          "22",     OPERATOR},
        {"/info",              0,          "n",       VISITOR},
        {"1",                  0,          "n",       VISITOR},
        {"2",                  0,          "n",       VISITOR},
        {"3",                  0,          "n",       VISITOR},
        {"4",                  0,          "n",       VISITOR},
        {"5",                  0,          "n",       VISITOR},
        {"6",                  0,          "n",       VISITOR},
        {"7",                  0,          "n",       VISITOR},
        {"8",                  0,          "n",       VISITOR},
        {"9",                  0,          "n",       VISITOR},
        {"r",                  0,          "n",       VISITOR},
        {"f",                  0,          "n",       VISITOR},
        {"/exc",               2,          "00",      VISITOR},
        {"/cload",             1,          "0",     TRUSTABLE},
        {"/creload",           1,          "0",     TRUSTABLE},
        {"/cclear",            1,          "0",     TRUSTABLE},
        {"/ccopy",             2,          "00",    TRUSTABLE},
        {"/permission",        1,          "2",       VISITOR},
        {"/copyright",         0,          "n",       VISITOR},
        {"/debug",             0,          "n",       VISITOR},
        {"/spawn",             3,          "222",    OPERATOR},
        {"/damage",            3,          "220",    OPERATOR},
        {"/dokill",            2,          "22",     OPERATOR},
        {"/chunkinfo",         1,          "0",       VISITOR},
        {"/exit",              0,          "n",       VISITOR},
        {"/w",                 0,          "n",       VISITOR},
        {"/a",                 0,          "n",       VISITOR},
        {"/s",                 0,          "n",       VISITOR},
        {"/d",                 0,          "n",       VISITOR},
        {"/crash",             0,          "n",     TRUSTABLE},
        {"/put",               3,          "000",     VISITOR},
        {"/remove",            2,          "00",      VISITOR},
        {"/get",               1,          "0",       VISITOR},
        {"/clear",             0,          "n",      OPERATOR},
    };
    // @note 所有的游戏规则定义
    std::vector<std::string> gamerule_identifier = {
             "player_name",       "world_name",    "vision_mode",
               "auto_jump",         "no_enter",  "respawn_point",
               "reverse_y",        "knowledge",  "auto_savefile",
        "longest_timeleap",  "command_replace",  "maxinum_debug",
    };
    // @note 游戏规则的参数类型定义
    // 各个数字的意义见@defination_commarg_1
    std::vector<std::string> gamerule_argtype = {
        "2","2","2",
        "1","1","00",
        "1","1","1",
        "0","1","0",
    };
    // @note 游戏规则的参数数量定义
    std::vector<long long> gamerule_argnum = {
        1,1,1,
        1,1,2,
        1,1,1,
        1,1,1,
    };
    
    const std::vector<std::string> permission_identifier = {"VISITOR","OPERATOR","TRUSTABLE"};
    //各级权限的显示字符串
    const std::vector<std::string> available_versions = {"Survive 1.5.0.8","Survive 1.5.0.9","Survive pre1.5.1","Survive 1.5.1","Survive 1.5.2"};
    //游戏支持解析的存档版本
    const std::vector<std::string> vision_mode_identifier = {"normal","large","wide","super_large"};
    //对显示模式的字符串定义
    const std::vector<std::string> size_unit = {"B","Kb","Mb","Gb","Tb"};//大小单位
    //用于在存档中显示其大小
    const long long time_total = 7;
    //标明时间段的总数
    const std::vector<std::string> gametime_show = {"sunrise","day","noon","afternoon","sunset","night","midnight"};
    //各个时间段的标准名称
    const std::vector<std::string> gametime_intershow = {"日出","白日","正午","下午","日落","夜晚","午夜"};
    //各个时间段的显示名称
    const short sunrise_color[] = {27,33,39,172,166,142,178,190,228,45,51};
    //日出时的天空颜色设置（256色下的索引）
    const short day_color = 51;
    //白日时的天空颜色设置（256色下的索引）
    const short noon_color = 14;
    //正午时的天空颜色设置（256色下的索引）
    const short afternoon_color = 81;
    //下午时的天空颜色设置（256色下的索引）
    const short sunset_color[] = {147,141,135,130,214,208,202,196,88};
    //日落时的天空颜色设置（256色下的索引）
    const short night_color[] = {21,20,18,17};
    //夜晚时的天空颜色设置（256色下的索引）
    const short midnight_color[] = {16,17,18,19,20,21};
    //午夜时的天空颜色设置（256色下的索引）
    const std::string gamemode_name[] = {"生存模式","创造模式"};
    //对游戏模式的显示字符串定义
    // @note 这是一个映射表，根据方块id获得其对应的物品id
    std::vector<item_t> block_itemid = {
        id_item_void,
        id_item_stone,
        id_item_cobblestone,
        id_item_grass,
        id_item_dirt,
        id_item_barrier,
        id_item_void,
        id_item_void,
        id_item_bedrock,
        id_item_wood,
        id_item_furnace,
        id_item_crafting_table,
        id_item_sand,
        id_item_leaf,
        id_item_void,
        id_item_coal_ore,
        id_item_short_grass,
        id_item_rose,
        id_item_snow_block,
        id_item_ice,
        id_item_magma_block,
        id_item_granite,
        id_item_limestone,
        id_item_stick,
        id_item_wood_plank,
    };
    
    pixel now_sky_color = pixel(127,255,255);
    //一个全局变量，表示游戏目前的天空颜色
    //基于CUIL，请勿删除此依赖项
    
    const std::string worldspawntype_name[] = {"Normal","Flat","Void","eRr0|^","Arrakis","Ocean","Froze"};
    //对世界生成模式的标准名称
    
    long long game_starttime;
    //一个全局变量，表示游戏开始运行时的时间戳
    
    
    
    struct info_pack;
    std::queue<info_pack>info_list;// 消息队列
    
    
    struct gameruninfo{
        long long game_time;// 游戏时间
        std::string filename;// 存档名称
        long long file_savetime;// 存档保存时间
        std::string file;// 存档
        INTERFACE active_screen;// 活跃屏幕
        gameruninfo(){
            game_time = 0;
            filename = "file";
            file_savetime = time(0);
            file = "";
            active_screen = INTERFACE_MAINSCREEN;
        }
    }gameinfo;
    //对游戏基础信息的包装
    
    // @note 标准类型转换类，单例模式
    class __convert{
        public:
            template<class T>std::string to_string(const T& __input) const;
            // 如果convert不能转换某个类型，尝试调用标准库实现
            std::string to_string(long double __input,int precision = 3) const;
            // 将浮点数转换为指定精度的字符串
            long long to_int(char __input) const;
            // 将字符转换为数字
            long long to_int(const std::string& __input) const;
            // 将字符串转换为数字
            long double to_float(const std::string& input) const;
            // 将字符串转换为浮点数
            std::string to_string(char __input) const;
            // 将字符转换为字符串
    }convert;
    
    
    // @note 这个便于今后对方块存储模式的修改
    typedef basic_block_id block_t;

    
    struct block{
        std::string name;// 名称
        std::string universal_name;// 在命令中的名称
        pixel_text color;// 颜色
        std::set<basic_tag_id>tag_list;// tag列表
        bool transparent;// 是否透明
        bool hastag(basic_tag_id tag)const;// 是否拥有id为tag的标签，是返回1，否返回0
    };
    // @note 这些是所有方块的信息
    std::vector<block> block_list = {
        {"空气",                "air",pixel_text(now_sky_color,"  "),  {tag_through,tag_replaceable},       true},
        {"石头",              "stone",pixel_text({192,192,192},"  "),  {tag_ore_replaceable},              false},
        {"圆石",        "cobblestone",pixel_text({128,128,128},"  "),  {},                                 false},
        {"草方块",            "grass",pixel_text({118,254,  0},"  "),  {tag_plant},                        false},
        {"泥土",               "dirt",pixel_text({ 96,  0,  0},"  "),  {tag_plant},                        false},
        {"屏障",            "barrier",pixel_text({147,112,219},"  "),  {tag_unbreakable},                  false},
        {"水",                "water",pixel_text({  0,128,255},"  "),  {tag_through,tag_fluid,tag_oxygen,tag_replaceable}, false},
        {"岩浆",               "lava",pixel_text({255, 96,  0},"  "),  {tag_through,tag_fluid,tag_oxygen,tag_replaceable}, false},
        {"基岩",            "bedrock",pixel_text({ 32, 32, 32},"  "),  {tag_unbreakable},                  false},
        {"木头",               "wood",pixel_text({128,128, 16},pixel("#8B4513").make_show_RGB_text() + "▒▒"),  {},                                 false},
        {"熔炉",            "furnace",pixel_text({192,192,160},"  "),  {tag_interaction},                  false},
        {"工作台",   "crafting_table",pixel_text({192,160, 64},"  "),  {tag_interaction},                  false},
        {"沙子",               "sand",pixel_text({240,240,128},"  "),  {tag_gravity},                      false},
        {"树叶",               "leaf",pixel_text({ 64,192, 32},"  "),  {tag_through},                      false},
        {"未知方块",  "unknown_block",pixel_text( pixel_black ,"  "),  {tag_unbreakable},                  false},
        {"煤矿石",         "coal_ore",pixel_text({128,128, 96},"  "),  {},                                 false},
        {"矮草丛",      "short_grass",pixel_text(now_sky_color,text_green + "ω "),{tag_through,tag_replaceable},            true},
        {"玫瑰",               "rose",pixel_text(now_sky_color,text_red + "✿ "),{tag_through,tag_replaceable},             true},
        {"雪",                 "snow",pixel_text({250,250,250},"  "),  {},                                 false},
        {"冰",                  "ice",pixel_text({192,255,255},"  "),  {},                                 false},
        {"岩浆方块",    "magma_block",pixel_text({128, 96, 96},"  "),  {},                                 false},
        {"花岗岩",          "granite",pixel_text({224,176,160},"  "),  {},                                 false},
        {"石灰岩",        "limestone",pixel_text({224,224,224},"  "),  {},                                 false},
        {"木板",         "wood_plank",pixel_text({240,224,128},"  "),  {},                                 false},
    };
    std::map<basic_block_id,INTERFACE> map_block_interface = {
        {id_block_crafting_table,INTERFACE_CRAFTING_TABLE},
        {id_block_furnace,INTERFACE_BACKPACK},
    };
    std::vector<std::pair<pixel_text,basic_biome_id> > water_color = {
        {pixel_text({  0,128,255},"  "), id_biome_plain},
        {pixel_text({  0,128,255},"  "), id_biome_swamp},
        
    };//水在各个群系下的颜色
    
    enum ITEM_USE_TYPE{
        BLOCK,
        TOOL,
        FOOD,
        OTHER,
    };
    struct item_info{
        std::string name;// 标准名称
        std::string universal_name;// 通用名称
        unsigned long long maxinum_stack;// 最大堆叠数量
        bool has_damage;// 是否有耐久度
        volatile unsigned long long max_damage;// 耐久最大值（无则为最大）
        bool can_place;// 是否能被放置
        int damage_type;// 挖掘等级
        block_t relate_block;// 对应的方块
        ITEM_USE_TYPE use_type;// 使用类型
        int health_damage;// 伤害
        int burn_times;// 可熔炼物品数
        std::set<basic_item_tag_id> tag_list;
        bool hastag(basic_item_tag_id tag){
            return tag_list.count(tag);
        }
    };
    std::vector<item_info> items_list = {
        {"空物品",    "void", LONG_LONG_MAX,  false,  LONG_LONG_MAX, false,  0,  id_block_air,             BLOCK,  1,  0,  {}},
        {"石头",      "stone",           64,  false,  LONG_LONG_MAX,  true,  0,  id_block_stone,           BLOCK,  1,  0,  {tag_item_meltable}},
        {"圆石",      "cobblestone",     64,  false,  LONG_LONG_MAX,  true,  0,  id_block_cobblestone,     BLOCK,  1,  0,  {tag_item_meltable}},
        {"草方块",    "grass",           64,  false,  LONG_LONG_MAX,  true,  0,  id_block_grass,           BLOCK,  1,  0,  {}},
        {"泥土",      "dirt",            64,  false,  LONG_LONG_MAX,  true,  0,  id_block_dirt,            BLOCK,  1,  0,  {}},
        {"基岩",      "bedrock",         64,  false,  LONG_LONG_MAX,  true,  0,  id_block_bedrock,         BLOCK,  1,  0,  {tag_item_invalid}},
        {"屏障",      "barrier",         64,  false,  LONG_LONG_MAX,  true,  0,  id_block_barrier,         BLOCK,  1,  0,  {tag_item_invalid}},
        {"木头",      "wood",            64,  false,  LONG_LONG_MAX,  true,  0,  id_block_wood,            BLOCK,  1,  8,  {tag_item_fuel,tag_item_meltable}},
        {"树叶",      "leaf",            64,  false,  LONG_LONG_MAX,  true,  0,  id_block_leaf,            BLOCK,  1,  0,  {}},
        {"熔炉",      "furnace",         64,  false,  LONG_LONG_MAX,  true,  0,  id_block_furnace,         BLOCK,  1,  0,  {}},
        {"工作台",    "crafting_table",  64,  false,  LONG_LONG_MAX,  true,  0,  id_block_crafting_table,  BLOCK,  1,  8,  {}},
        {"沙子",      "sand",            64,  false,  LONG_LONG_MAX,  true,  0,  id_block_sand,            BLOCK,  1,  0,  {tag_item_meltable}},
        {"煤矿石",    "coal_ore",        64,  false,  LONG_LONG_MAX,  true,  0,  id_block_coal_ore,        BLOCK,  1,  0,  {tag_item_meltable}},
        {"玫瑰",      "rose",            64,  false,  LONG_LONG_MAX,  true,  0,  id_block_rose,            BLOCK,  1,  0,  {}},
        {"矮草丛",    "short_grass",     64,  false,  LONG_LONG_MAX,  true,  0,  id_block_short_grass,     BLOCK,  1,  0,  {}},
        {"雪块",      "snow",            64,  false,  LONG_LONG_MAX,  true,  0,  id_block_snow,            BLOCK,  1,  0,  {}},
        {"冰块",      "ice",             64,  false,  LONG_LONG_MAX,  true,  0,  id_block_ice,             BLOCK,  1,  0,  {}},
        {"岩浆方块",  "magma_block",     64,  false,  LONG_LONG_MAX,  true,  0,  id_block_magma_block,     BLOCK,  1,  0,  {}},
        {"花岗岩",    "granite",         64,  false,  LONG_LONG_MAX,  true,  0,  id_block_granite,         BLOCK,  1,  0,  {tag_item_meltable}},
        {"石灰岩",    "limestone",       64,  false,  LONG_LONG_MAX,  true,  0,  id_block_limestone,       BLOCK,  1,  0,  {tag_item_meltable}},
        {"木棍",      "stick",           64,  false,  LONG_LONG_MAX, false,  0,  id_block_empty,           OTHER,  1,  1,  {tag_item_fuel}},
        {"木板",      "wood_plank",      64,  false,  LONG_LONG_MAX,  true,  0,  id_block_wood_plank,      BLOCK,  1,  2,  {tag_item_fuel}},
        {"生猪肉",    "raw_pork",        64,  false,  LONG_LONG_MAX,  false, 0,  id_block_empty,           FOOD,   1,  0,  {tag_item_food}},
        {"熟猪肉",    "cooked_pork",     64,  false,  LONG_LONG_MAX,  false, 0,  id_block_empty,           FOOD,   1,  0,  {tag_item_food}},
        {"生羊肉",    "raw_mutton",      64,  false,  LONG_LONG_MAX,  false, 0,  id_block_empty,           FOOD,   1,  0,  {tag_item_food}},
        {"熟羊肉",    "cooked_mutton",   64,  false,  LONG_LONG_MAX,  false, 0,  id_block_empty,           FOOD,   1,  0,  {tag_item_food}},
        {"生牛肉",    "raw_beef",        64,  false,  LONG_LONG_MAX,  false, 0,  id_block_empty,           FOOD,   1,  0,  {tag_item_food}},
        {"熟牛肉",    "cooked_beef",     64,  false,  LONG_LONG_MAX,  false, 0,  id_block_empty,           FOOD,   1,  0,  {tag_item_food}},
        {"皮革",      "leather",         64,  false,  LONG_LONG_MAX,  false, 0,  id_block_empty,           OTHER,  1,  0,  {}},
    };
    struct item{
        item_t type;// 物品id
        long long total;// 该组物品总数
        long long damage;// 耐久度
        std::string tag_name;// 特殊标识名（默认无）
        item(item_t Atype = id_item_void,long long Atotal = 0,long long Adamage = -1,const std::string& Atag_name = ""){
            type = Atype;
            total = Atotal;
            damage = Adamage == -1?items_list[type].max_damage:Adamage;
            tag_name = Atag_name;
        }
        std::string to_string() const;
        std::string to_stdstr() const;
        void combine(item& combine_item);
        item total_change(long long change) const;
    };
    std::string item::to_string() const{
        return items_list[type].name + " * " + convert.to_string(total);
    }
    std::string item::to_stdstr() const{
        return convert.to_string(int(type)) + "*" + convert.to_string(total);
    }
    void item::combine(item& combine_item){
        if(type == combine_item.type && type != id_item_void){
            long long actual_putnum = std::min(combine_item.total + total,(long long)items_list[type].maxinum_stack) - combine_item.total;
            combine_item.total += actual_putnum;
            total -= actual_putnum;
        }
        else if(combine_item.type != type){
            item tmp(type,total,damage,tag_name);
            *this = combine_item;
            combine_item = tmp;
            
        }
        else;
    }//合并物品，修改自身及combine_item的内容，不产生返回值
    item item::total_change(long long change) const{
        return item(type,change,damage,tag_name);
    }
    struct inventory_plate{
        CUIL_std::matrix<item_t> plate;// 合成面板
        public:
            inventory_plate(){
                plate = CUIL_std::matrix<item_t>(3,3);        
            }
            inventory_plate(const CUIL_std::matrix<item_t>& inmat){
                plate = inmat;
            }
            bool check(const inventory_plate& inplate,bool strict_aligned = true) const{
                inventory_plate tmp;
                if(!strict_aligned){
                    int sx = 3,sy = 3,ex = -1,ey = -1;
                    for(int x = 0;x < 3;++x){
                        for(int y = 0;y < 3;++y){
                            if(inplate.plate.get(x,y) != id_item_void){
                                sx = std::min(sx,x);
                                sy = std::min(sy,y);
                                ex = std::max(ex,x);
                                ey = std::max(ey,y);
                            }
                        }
                    }
                    for(int x = sx;x < 3;++x){
                        for(int y = sy;y < 3;++y)
                            tmp.plate.edit(x - sx,y - sy,inplate.plate.get(x,y));
                    }
                }//全部置于左上角对齐
                for(int x = 0;x < 3;++x){
                    for(int y = 0;y < 3;++y){
                        if(plate.get(x,y) != tmp.plate.get(x,y))
                            return false;
                    }
                }
                return true;
            }
            bool operator==(const inventory_plate& inplate) const{
                return check(inplate,true);
            }
    };
    struct inventory_info{
        inventory_plate item_plate;// 物品的矩阵排列
        item inventory_result;// 合成产物
        bool strict_aligned;// 是否需要严格对齐
        public:
            inventory_info(const inventory_plate& Aitem_plate,const item& Ainventory_result,bool Astrict_aligned){
                item_plate = Aitem_plate;
                inventory_result = Ainventory_result;
                strict_aligned = Astrict_aligned;
            }
    };
    const std::vector<inventory_info> inventory_list = 
    {
        inventory_info(
            inventory_plate(
                CUIL_std::matrix<item_t>(
                    {
                        {id_item_wood_plank,id_item_wood_plank,id_item_void},
                        {id_item_wood_plank,id_item_wood_plank,id_item_void},
                        {      id_item_void,      id_item_void,id_item_void},
                    }
                )
            ),//工作台-合成面板物品排列
            item(id_item_crafting_table,1),//返回物品-工作台
            false//不需要严格对齐
        ),// 合成信息：工作台
        //以下合成信息内容同上
        inventory_info(
            inventory_plate(
                CUIL_std::matrix<item_t>(
                    {
                        {id_item_wood_plank,id_item_void,id_item_void},
                        {id_item_wood_plank,id_item_void,id_item_void},
                        {      id_item_void,id_item_void,id_item_void},
                    }
                )
            ),
            item(id_item_stick,8),
            false
        ),// 合成信息：木棍
        inventory_info(
            inventory_plate(
                CUIL_std::matrix<item_t>(
                    {
                        {id_item_cobblestone,id_item_cobblestone,id_item_cobblestone},
                        {id_item_cobblestone,       id_item_void,id_item_cobblestone},
                        {id_item_cobblestone,id_item_cobblestone,id_item_cobblestone},
                    }
                )
            ),
            item(id_item_furnace,1),
            true
        ),// 合成信息：熔炉
        inventory_info(
            inventory_plate(
                CUIL_std::matrix<item_t>(
                    {
                        {id_item_wood,id_item_void,id_item_void},
                        {id_item_void,id_item_void,id_item_void},
                        {id_item_void,id_item_void,id_item_void},
                    }
                )
            ),
            item(id_item_wood_plank,4),
            false
        ),// 合成信息：木板
    };
    inline inventory_plate convert_as_plate(const std::vector<item>& item_list){
        inventory_plate tmp;
        for(int i = 0;i < std::min(9,int(item_list.size()));++i)
            tmp.plate.edit(i % 3,i / 3,item_list[i].type);
        return tmp;
    }
    struct biome{
        std::string name;// 名称
        std::string color;// 显示颜色
        double spawn_value;// 生成权重
        double temperature_value;// 温度
        double height_value;// 高度值
        block_t surface_block;// 表层方块
        block_t subsurface_block;// 次表层方块
        short density_plant;// 植被密度
        short density_tree;// 树木密度
        int terrain_scale;//地形缩放
        double continent;//陆地性
        double cliff;//陡峭性
    };
    std::vector<biome> biome_list = {
        {"平原",      "\033[48;5;118m",  1.50,  +00.500,  +00.500,  id_block_grass,        id_block_dirt,         40,     5,    16,    +1.00,    0.00,},
        {"沙漠",      "\033[48;5;220m",  1.00,  +37.500,  +01.000,  id_block_sand,         id_block_sand,         0,      0,    16,    +1.00,    0.00,},
        {"山地",      "\033[48;5;247m",  0.50,  -25.000,  +50.000,  id_block_stone,        id_block_stone,        10,     0,    64,    +1.00,   +0.50,},
        {"极限山地",  "\033[48;5;123m",  0.20,  -65.375,  +60.750,  id_block_stone,        id_block_stone,        0,      0,   128,    +1.00,   +1.00,},
        {"海洋",      "\033[48;5;033m",  1.50,  -10.250,  -40.750,  id_block_sand,         id_block_sand,         0,      0,   -64,     0.00,   +0.25,},
        {"岩浆海",    "\033[48;5;202m",  0.20,  +90.250,  -40.725,  id_block_cobblestone,  id_block_cobblestone,  0,      0,   -64,     1.00,   +0.25,},
        {"森林",      "\033[48;5;040m",  1.00,  +02.500,  +00.500,  id_block_grass,        id_block_dirt,         100,   50,    16,    +1.00,   +0.15,},
        {"丛林",      "\033[48;5;034m",  0.50,  +25.000,  +05.000,  id_block_grass,        id_block_dirt,         100,   70,    16,    +1.00,   +0.20,},
        {"火山",      "\033[48;5;160m",  0.20,  +89.750,  +70.750,  id_block_lava,         id_block_magma_block,  0,      0,    96,    +1.00,   +1.00,},
        {"极平原",    "\033[48;5;015m",  0.00,  +00.000,  +00.000,  id_block_grass,        id_block_dirt,         0,      0,     0,    +1.00,    0.00,},
        {"雪原",      "\033[48;5;195m",  1.00,  -50.500,  +00.500,  id_block_snow,         id_block_dirt,         10,    10,    16,    +1.00,    0.00,},
        {"极限山峰",  "\033[48;5;153m",  0.20,  -90.000,  +99.975,  id_block_ice,          id_block_snow,         0,      0,   256,    +1.00,   +1.00,},
        {"极限深海",  "\033[48;5;021m",  0.20,  -45.500,  -90.375,  id_block_sand,         id_block_sand,         0,      0,  -128,    +0.00,   +1.00,},
        {"极地平原",  "\033[48;5;015m",  0.20,  -90.250,  +05.750,  id_block_ice,          id_block_snow,         5,      0,    16,    +1.00,    0.00,},
        {"沙滩",      "\033[48;5;228m",  0.20,  +10.000,  -00.500,  id_block_sand,         id_block_sand,         0,      0,     2,    +0.50,    0.00,},
        {"山地边缘",  "\033[48;5;112m",  0.50,  +00.000,  +15.250,  id_block_grass,        id_block_dirt,         70,    10,    24,    +1.00,   +0.25,},
        {"岩浆陆",    "\033[48;5;166m",  0.15,  +85.750,  +25.500,  id_block_lava,         id_block_magma_block,  0,      0,    64,    +1.00,   +0.10,},
        {"大陆架",    "\033[48;5;075m",  1.00,  -07.500,  -07.500,  id_block_sand,         id_block_sand,         0,      0,   -24,    +0.25,   +0.05,},
        {"高原",      "\033[48;5;153m",  1.50,  -75.875,  +75.875,  id_block_grass,        id_block_dirt,         20,    10,    96,    +1.00,   +0.05,},
        {"海沟",      "\033[48;5;019m",  0.20,  -30.500,  -85.500,  id_block_sand,         id_block_sand,         0,      0,  -128,    +0.00,   +0.85,},
        {"热带草原",  "\033[48;5;154m",  1.00,  +25.750,  +05.000,  id_block_grass,        id_block_dirt,         80,    10,    16,    +1.00,    0.00,},
        {"赤极",      "\033[48;5;009m",  0.02,  +99.975,  +99.975,  id_block_lava,         id_block_lava,         0,      0,   256,    +1.00,   +1.00,},
        {"无尽渊",    "\033[48;5;017m",  0.02,  -45.750,  -99.975,  id_block_sand,         id_block_sand,         0,      0,  -256,    +0.00,   +1.00,},
        {"极洋",      "\033[48;5;014m",  0.05,  -99.975,  -45.750,  id_block_ice,          id_block_sand,         0,      0,   -64,    +0.00,   +0.25,},
        {"繁茂高原",  "\033[48;5;120m",  0.45,  -72.875,  +75.875,  id_block_grass,        id_block_dirt,         100,   30,    96,    +1.00,   +0.05,},
        {"繁花平原",  "\033[48;5;010m",  0.50,  +03.500,  +00.500,  id_block_grass,        id_block_dirt,         100,    5,    16,    +1.00,    0.00,},
        {"丘陵",      "\033[48;5;112m",  0.25,  +00.500,  +25.000,  id_block_stone,        id_block_stone,        50,     5,    32,    +1.00,    0.20,},
        {"破碎峭壁",  "\033[48;5;242m",  0.75,  -25.000,  +55.750,  id_block_stone,        id_block_stone,        0,      0,    96,    +1.00,   +1.00,},
        {"森林边界",  "\033[48;5;040m",  0.50,  +02.500,  +00.500,  id_block_grass,        id_block_dirt,         50,    25,    16,    +1.00,   +0.05,},
        {"峭冰平原",  "\033[48;5;195m",  0.50,  -90.250,  +07.750,  id_block_snow,         id_block_snow,         0,      0,    24,    +1.00,   +0.85,},
        {"陨落谷",    "\033[48;5;160m",  0.15,  +90.750,  -70.750,  id_block_lava,         id_block_lava,         0,      0,  -128,    +1.00,   +1.00,},
        {"沼泽",      "\033[48;5;058m",  1.00,  +00.500,  +10.500,  id_block_dirt,         id_block_dirt,        75,     50,    -8,    +0.75,   +0.00,},
        {"繁茂雨林",  "\033[48;5;034m",  0.25,  +35.000,  +05.000,  id_block_grass,        id_block_dirt,       125,     95,    16,    +1.00,   +0.20,},
    };//群系模板
    struct Worldset{
        long long seed;//世界生成种子
        long long sea_level;//海平面
        std::string playername;//玩家名称
        std::string worldname;//世界名称
        basic_worldtype_id world_spawn_type;//世界类型（默认无限，正常）
        short world_single_biome;//世界群系（默认不启用）
        long double terrain_scale;//地形缩放
        std::string pre_execute_command;//预处理指令
        Worldset(long long Aseed = 8869311,
                 long long Asea_level = 384,
                 const std::string& Aplayername = "ParseY Pasy",
                 const std::string& Aworldname = "default_world",
                 basic_worldtype_id Aworld_spawn_type = id_worldtype_normal,
                 short Aworld_spawn_biome = -1,
                 long double Aterrain_scale = 1.0);
        void show() const;
    }worldset;
    const long long NOISE_SAMPLEARRAY_LENGTH = 1048576;//这个数字决定生成的不重复地形的长度
    
    class random_list{
        private:
            long long seed;
            unsigned char buildin_list[NOISE_SAMPLEARRAY_LENGTH];
        public:
            random_list(int Listseed = 0){
                seed = Listseed;
                std::mt19937 ran(seed);
                for(int i = 0;i < NOISE_SAMPLEARRAY_LENGTH;++i)
                    buildin_list[i] = (unsigned char)(rand()%256);
            }
            unsigned char operator[](const long long index) const{
                if(index < NOISE_SAMPLEARRAY_LENGTH)
                    return buildin_list[index];
                else
                    return (unsigned char)(std::mt19937(seed + index)() % 256);
            }
    };
    class noise{
        private:
            random_list r;
        public:
            noise(int Aseed);// 通过种子值构建一个伪随机取值列表
            inline double lerp(long double t,long double a,long double b) const;//线性插值
        	inline double grad(long long hash,long double x,long double y,long double z) const;//哈希梯度值
        	inline double fade(long double t) const;//缓动函数
            long double getNoiseValue(long double x,long double y,long double z) const;//获取单点的噪声值
            long double getOctaveNoise(long double x,long double y,long double z,int __octaves = 10,long long seed = 0) const;//获取倍频噪声值
    };
    noise TerrainNoise = noise(0),
          BiomeTemperatureNoise = noise(1),
          TerrainGraniteNoise = noise(2),
          TerrainLimeStoneNoise = noise(3),
          CaveNoise = noise(4),
          TerrainDirtNoise(5);
    template<class T> class basic_position{
        public:
            T x;
            T y;
        public:
            basic_position(T __x = 0,T __y = 0){
                x = __x;
                y = __y;
            }
            std::string to_string() const{
                return "("+convert.to_string(x)+","+convert.to_string(y)+")";
            }// 转换为字符串
            void show() const{
                std::cout << "(" << x << "," << y << ")";
            }// 显示坐标
            void editxy(T __x,T __y){
                x = __x;
                y = __y;
            }// 编辑x,y坐标
            inline basic_position delta(T dx,T dy = 0) const{
                return basic_position(x + dx,y + dy);
            }// 返回在当前坐标上变化后的坐标，x方向变化dx，y方向变化dy
            inline bool operator==(const basic_position<T>& inpos) const{
                return x == inpos.x && y == inpos.y;
            }
            inline bool operator!=(const basic_position<T>& inpos) const{
                return !(x == y);
            }
    };
    typedef basic_position<long long>             position;
    typedef basic_position<long double>           position_float;
    typedef basic_position<unsigned long long>    position_unsigned;
    const position void_position(-1,-1);
    template<class T> class basic_range{
        T vmin;
        T vmax;
        public:
            basic_range(T a,T b){
                vmin = a;
                vmax = b;
                if(a > b)
                    std::swap(vmin,vmax);
            }
            void show() const{
                std::cout << "[" << vmin << "," << vmax<< "]" << std::endl;
            }// 返回区间范围
            T setin(T value) const{
                return value>vmax?vmax:(value<vmin?vmin:value);
            }// 若value是否在区间内则返回自身，否则根据其大小返回左或右边界
            bool inrange(T value) const{
                return value>=vmin&&value<=vmax;
            }// 检查value是否在区间内，是返回1，否返回0
            size_t size() const{
                return vmax - vmin + 1;
            }// 返回区间大小
            friend bool inrange(const basic_range& ran,T value);
    };
    typedef basic_range<long long>                  range;
    typedef basic_range<long double>          range_float;
    typedef basic_range<char>                  range_char;
    typedef basic_range<unsigned long long>    range_uint;
    const range_char lower_alpha('a','z'),upper_alpha('A','Z');
    const range byte_range(0,255);
    struct gamerule_info{
        bool auto_jump = true;// 自动跳跃
        bool show_command_parse = false;// 显示命令解析信息
        bool no_enter = true;// 无回车输入
        bool reverse_y = true;// 反转y轴
        bool knowledge = true;// 知识分享
        bool auto_savefile = true;// 自动保存存档
        bool debug = false;// debug模式
        bool command_replace = true;// 自动替换命令字符
        int gamemode = 0;// 游戏模式
        int vision_mode = 0;// 视野模式
        int longest_timeleap = 320;// 最长跳过时间
        position respawn_point;// 重生点
        long long maxinum_debuginfo;// debug信息数量限制
        gamerule_info(bool Aauto_jump = true,
                      bool Ashow_command_parse = false,
                      bool Ano_enter = true,
                      bool Areverse_y = true,
                      bool Aknowledge = true,
                      bool Aauto_savefile = true,
                      bool Acommand_replace = true,
                      bool Adebug = false,
                      int Agamemode = 0,
                      int Avision_mode = 0,
                      int Alongest_timeleap = 320,
                      long long Amaxinum_debuginfo = 100,
                      position Arespawn_point = {32768,worldset.sea_level}){
            auto_jump = Aauto_jump;
            show_command_parse = Ashow_command_parse;
            no_enter = Ano_enter;
            reverse_y = Areverse_y;
            knowledge = Aknowledge;
            auto_savefile = Aauto_savefile;
            command_replace = Acommand_replace;
            debug = Adebug;
            gamemode = Agamemode;
            vision_mode = Avision_mode;
            longest_timeleap = Alongest_timeleap;
            respawn_point = Arespawn_point;
            maxinum_debuginfo = Amaxinum_debuginfo;
        }
    }gamerule;
    class container{
        private:
            std::vector<item> item_list;// 物品列表
            std::string name;// 界面名称
        public:
            long long max_size;// 物品列表最大长度
        public:
            container(const std::string& Aname = "背包",long long make_size = 36);
            int hasitem(long long item_type) const;// 检查是否包含id为item_type的物品，若有则返回1，否则返回0
            int pushNewItem(item& in_item);// 尝试放入in_item，成功返回1，否则返回0
            int canPushNewItem(const item& in_item) const;// 检查能否继续放入in_item
            void print(int column = 3) const;// 以column列的形式打印界面信息
            item& getitem(long long index);// 通过index访问物品列表
            void mergeitem(long long index,const item& initem);// 修改物品内容
            void exchangeitem(long long index1,long long index2);// 交换两个物品
            void movein_item(item& initem,long long move_total);// 移入物品，但修改原物品信息
            friend int command_put(long long from_index,long long to_index,long long put_num);
            friend void screen_print();
            friend void printfile();
    };
    class basic_ui{
        public:
            std::vector<item> material;// 材料
            item product;// 产物
            long long set_size;// 大小
        public:
            virtual void show()const = 0;// 显示UI信息
            virtual void pushInItem(item& initem,int index) = 0;// 放入物品
    };
    class ui_crafting_table : public basic_ui{
        public:
            ui_crafting_table(){
                material = std::vector<item>(9,item());
                set_size = 9;
            }
            void show() const;// 显示工作台UI
            void pushInItem(item& initem,int index);// 在index处尝试放入initem
            void check_inventory();// 检查与更新合成内容
            void clear();// 返还物品
    }crafting_table_ui;
    void debug(const std::string& info);
    inline void pushNewInfo(const std::string content,const std::string deliverer);
    class ui_simple_crafting_table : public basic_ui{
        public:
            ui_simple_crafting_table(){
                material = std::vector<item>(4,item());
                set_size = 4;
            }
            void show() const;
            void pushInItem(item& initem,int index);
            void check_inventory();// 检查并更新合成内容
            void clear();// 返还物品
    }simple_crafting_table_ui;
    class ui_furnace : public basic_ui{
        public:
            ui_furnace(){
                material = std::vector<item>(3,item());
            }
            void show() const{}// 显示熔炉UI
            void pushInItem(item& initem,int index){
                item* operate_item;
                if(items_list[initem.type].hastag(tag_item_meltable))
                    operate_item = &material[0];
                //可熔炼物品
                else if(items_list[initem.type].hastag(tag_item_fuel))
                    operate_item = &material[1];
                //燃料
                else
                    return ;
                if(operate_item->type == initem.type){
                    long long canput_total = items_list[initem.type].maxinum_stack - operate_item->total;
                    long long actual_put_total = std::min(canput_total,initem.total);
                    operate_item->total += actual_put_total;
                    initem.total -= actual_put_total;
                }
                else{
                    item tmp = initem;
                    initem = *operate_item;
                    *operate_item = initem;
                }
            }
    }furnace_ui;
    struct playerinfo{
        position pos;//位置
        int health;//生命值
        int hunger;//饥饿度
        double oxygen;//氧气值
        world* at_world;//所处世界
        container backpack;//背包
        long long backpack_pointer;//快捷键指针位置
        PERMISSION operate_permission;//操作权限
        position operating_container_pos;//操作容器的坐标
        void update();
        playerinfo(container inter = container()){
            backpack = inter;
        }
    }player({"背包",36});
    struct info_pack{
        std::string content;// 内容
        std::string deliverer;// 发送者
        info_pack(const std::string c,const std::string d = "系统"){
            content = c;
            deliverer = d;
        }
    };
    class exception{
        std::string content;
        public:
            exception(const std::string& Acontent);
            std::string what() const;// 返回content，即报错原因
    };
    struct block_operation{
        block_t block_id;
        block_operation(block_t b_id);
    };
    struct std_position_cmp{
        bool operator()(const position& pos1,const position& pos2) const;// 比较两个坐标大小
    };
    class world{
        public:
            short type;//世界类型
            std::map<position,block_operation,std_position_cmp>merge_list;//世界公共操作序列
        private:
            std::map<long long,chunk>chunk_list;//世界地形数据
        public:
            void pushBlockMerge(const position& inpos,block_t merge_id);// 将一个新的方块操作放入操作序列内
            block_t getblock(const position& inpos) const;// 获得inpos位置所对应的方块，若所属区块未生成则返回id_block_air
            int editblock(const position& inpos,block_t block);// 尝试修改inpos位置的方块为block，若所属区块未生成则放入方块修改列表内
            bool inchunklist(long long id) const;// 检查id号区块是否在世界区块列表内
            void pushchunk(const chunk& inchunk);// 将一个区块放入世界区块列表，若已存在则反馈错误
            std::map<long long,chunk>::iterator getchunkiter(long long id);// 获得id号区块所对应的迭代器
            chunk& getchunk(long long id);// 获得id号区块的引用
            friend position playerborn(world* spawn_world,const position& spawn_pos);
            friend void printfile();
            friend int ui_readfile();
            friend int gamerun();
            friend position spawn_pos_entity(chunk* spawn_chunk,const position& spawn_pos);
    }MainWorld;
    class basic_worldgenerator{
        public:
            long double sample_terrain;// 地形取样密度
            long double sample_biome;// 群系取样密度
            long double sample_cave;// 洞穴取样密度
            long double sample_terrain_granite;// 花岗岩取样密度
            long double sample_terrain_limestone;// 石灰岩取样密度
            long double sample_terrain_dirt;// 泥土取样密度
            long long lava_layer_height;// 岩浆层高度
        public:
            basic_worldgenerator(long double sample_t = default_sample_terrain,
                                 long double sample_b = default_sample_biome,
                                 long double sample_c = default_sample_cave,
                                 long double sample_tg = default_sample_terrain_granite,
                                 long double sample_tl = default_sample_terrain_limestone,
                                 long double sample_td = default_sample_terrain_dirt,
                                 long long Alava_layer_height = 16);
        private:
            struct poss_sort_biome;
            static bool biome_cmp(poss_sort_biome& a,poss_sort_biome& b);
        public:
            long long getNoiseBiome(long double value_h,long double value_t);//单纯以噪声值获取群系
            int getbiome(long long id);//获取群系
            long long getBiomeHeightInterrupt(long double inputy,int biome_type);//获得特定群系下的高度
            long long getheight(long long x);//获取单点的地形高度
            void setRawTerrainX(chunk* inchunk,long long x,long long y = -1);//生成单x坐标下的一级地形
            void setRawTerrain(chunk* inchunk);//生成一级地形
            void setSecondaryTerrain(chunk* inchunk,world* _inworld);//生成二级地形
            void setEntity(chunk*,world*);
            void correctTerrain(chunk* inchunk);//修正地形
            chunk generate_chunk(long long id,int world_type);//总的区块生成方法
            long long find_first_block(chunk* inchunk,long long x,block_t id);//找到x坐标上第一个指定方块
            long long find_first_not_block(chunk* inchunk,long long x,block_t id);//找到x坐标上第一个非指定方块
            long long reverse_find_first_block(chunk* inchunk,long long x,block_t id);//从y轴底部开始找到第一个指定方块
            long long reverse_find_first_not_block(chunk* inchunk,long long x,block_t id);//从y轴底部开始找到第一个非指定方块
            void setTreeBranch(chunk* inchunk,world* _inworld,const position& pos1,const position& pos2,int size_branch,int type);
            void setTree(chunk* inchunk,world* _inworld,const position& inpos,int size_tree,int type);//生成结构：树
            bool rand_bool(long long x);//随机Boolean值
            bool hasblock(chunk* inchunk,block_t id);//检查一个区块中是否有id号方块
            inline long double continent_curve(long double x) const;//海陆曲线
            int init(void){
                return 0;
            }//在地形生成器被创建时，调用此函数
    };
    class MainWorld_worldgenerator : public basic_worldgenerator{
        public:
            MainWorld_worldgenerator(long double sample_t = default_sample_terrain,
                                     long double sample_b = default_sample_biome,
                                     long double sample_c = default_sample_cave,
                                     long double sample_tg = default_sample_terrain_granite,
                                     long double sample_tl = default_sample_terrain_limestone);
    };
    MainWorld_worldgenerator worldgenerator(default_sample_terrain,default_sample_biome,default_sample_cave);
    
    
    struct basic_worldgenerator::poss_sort_biome{
        long double possibility;
        short biome_id;
    };
    class entity{
        public:
            basic_entity_id type;//实体类型
            position pos;//当前位置
            world* at_world;//所处世界
            int health;//生命值
            int oxygen;//氧气值
            bool need_update;//是否需要更新
            std::string name_tag;//名称
        public:
            entity(basic_entity_id Atype = entity_void,
                   const position& Apos = {0,0},
                   world* Aworld = &MainWorld,
                   int Ahealth = -1,
                   int Aoxygen = 20,
                   bool Aneed_update = true,
                   const std::string& Aname_tag = "");//设置实体信息
            BEHAVIOR_STATUS update();//更新实体
            std::string to_string() const{
                return "(" + 
                       convert.to_string(int(type)) + "," + 
                       convert.to_string(pos.x) + "," + 
                       convert.to_string(pos.y) + "," + 
                       convert.to_string(health) + "," + 
                       convert.to_string(oxygen) + "," + 
                       convert.to_string(int(need_update)) + ",-" + 
                       name_tag + ")";
            }
    };
    
    class chunk{
        private:
            long long id;//区块号
            world* related_world;//所属的世界
            block_t block[worldMaxinumHeight * chunkWidth];//地形信息
            std::vector<entity>entity_list;//实体数据
            bool merged;//是否被修改
            bool generated;//是否生成
        public:
            chunk(long long __id,world* __related_world);// 创建一个指定id与所属世界的chunk
            bool operator()(const chunk& op2) const;// 按照id排序
            long long getid() const;// 获取id
            block_t getblock(const position& inpos) const;// 按照position对象获取方块（仅当position在区块范围内）
            block_t getblockindex(long long index) const;// 直接通过下标获取方块
            void editblock(const position& inpos,block_t block_in,bool just_push = false);// 按照position对象修改区块内方块（仅当position在区块范围内）
            void applyBlockMerge();// 按照所在世界的方块操作序列修改自身方块信息
            void print() const;// 绘制整个区块的完整图像（使用标准的方块颜色）
            void copy(const chunk& op2);// 复制一个区块
            void update();// 更新方块信息
            void addentity(const entity& inentity);//新增一个实体
            friend block_t getblock(world* target_world,const position& inpos);//按所给的坐标获取方块（仅在本区块内）
            friend int editblock(world* target_world,const position& inpos,block_t editid);//按照所给的坐标修改方块（仅在本区块内）
            friend void basic_worldgenerator::setRawTerrainX(chunk* inchunk,long long x,long long y);//生成单x坐标的地形
            friend void basic_worldgenerator::setRawTerrain(chunk* inchunk);//生成一级地形
            friend void basic_worldgenerator::setSecondaryTerrain(chunk* inchunk,world* _inworld);//生成二级地形
            friend position spawn_pos_entity(chunk* spawn_chunk,const position& spawn_pos);
            friend void basic_worldgenerator::setEntity(chunk* inchunk,world* _inworld);// 生成实体
            friend void basic_worldgenerator::setTreeBranch(chunk* inchunk,world* _inworld,const position& pos1,const position& pos2,int size_branch,int type);//生成一个树的枝干
            friend void basic_worldgenerator::setTree(chunk* inchunk,world* _inworld,const position& inpos,int size_tree,int type);//生成树
            friend int ui_readfile();
            friend int gamerun();
            friend void screen_print();
            friend int command_damage(const std::string& x,const std::string& y,long long damage);
            friend int command_dokill(const std::string& x,const std::string& y);
            friend int command_chunkinfo(long long id);
            friend std::string getchunkCode(const chunk& input);
            friend chunk basic_worldgenerator::generate_chunk(long long id,int world_type);
            friend int command_use(char ch);
    }debug_chunk(-1,&MainWorld);
    struct _hitbox{
        int start_x;// 起始x坐标
        int start_y;// 起始y坐标
        int end_x;// 终止x坐标
        int end_y;// 终止y坐标
    };
    enum entity_type{
        AMITY,//友好
        HOSTILE,//敌对
        NEUTRAL,//中立
        ORIGINAL,//????
    };
    struct entity_trophy{
        item_t type;
        range num_range;
        short posibility;
    };
    struct entity_info{
        std::string name;//显示名称
        std::string universal_name;//标准名称
        double maxinum_health;//最大生命
        double attack;//攻击伤害
        entity_type type;//实体类型
        _hitbox hitbox;//碰撞箱
        image_text img;//贴图
        std::vector<entity_trophy> trophy_list;//战利品列表
    };
    std::vector<entity_info> entity_list = {
        {"空無",    "void",      1e+308,  1e+308,  ORIGINAL,  {0,0,0,0},  image_text({{{{pixel_black,"  "}}}}),      
            {}
        },//空实体
        {"玩家",    "player",    20.0,    4.0,     AMITY,     {0,0,0,0},  image_text({{{{pixel_white,"! "}}}}),
            {}
        },//玩家
        {"荡迹人",  "wanderer",  20.0,    0.0,     NEUTRAL,   {0,0,0,0},  image_text({{{{pixel_white,"! "}}}}),
            {}
        },//荡迹人
        {"猪",      "pig",       10.0,    0.0,     AMITY,     {0,0,0,0},  image_text({{{{pixel("FFB6C1"),"  "}}}}),
            {{id_item_raw_pork,range(1,3),100}}
        },//猪
        {"牛",      "cow",       10.0,    0.0,     AMITY,     {0,0,0,0},  image_text({{{{pixel("BEBEBE"),"  "}}}}),
            {{id_item_raw_beef,range(1,3),100},{id_item_leather,range(0,2),25}}
        },//牛
        {"羊",      "sheep",     10.0,    0.0,     AMITY,     {0,0,0,0},  image_text({{{{pixel("F8F8F8"),"  "}}}}),
            {{id_item_raw_mutton,range(1,3),100}}    
        },//羊
    };
    
    long long debug_id = 0;
    struct debug_pack{
        long long id;
        std::string info;
        debug_pack(const std::string& Ainfo){
            id = debug_id++;
            info = Ainfo;
        }
    };
    std::queue<debug_pack> debug_list;
    
    void debug(const std::string& info){
        debug_list.push(debug_pack(info));
        while(debug_list.size() > gamerule.maxinum_debuginfo && debug_list.size() > 0)
            debug_list.pop();
    }
    void printdebug(){
        std::cout << "--Start debug--" << std::endl;
        while(debug_list.size() > 0){
            std::cout << "debug(" << debug_list.front().id << " of " << debug_id - 1 << " ): " << debug_list.front().info << std::endl;
            usleep(10000 + debug_list.front().info.length() * 100);
            debug_list.pop();
        }
        std::cout << "--Debug end--" << std::endl;
    }
    inline void pushNewInfo(const std::string content,const std::string deliverer = "系统");// 放入新的信息，默认发送者为系统
    long long showlen(const std::string& instr);// 获取instr显示输出的实际长度
    std::string str_setw(long long len,const std::string& instr);// 将instr按照len字符宽度进行左对齐，超过范围则正常输出
    std::string str_rsetw(long long len,const std::string& instr);// 将instr按照len字符宽度进行右对齐，超过范围则正常输出
    long long hash_str(const std::string& input);// 获取字符串的哈希值
    inline long long getcid(long long x);// 获取x对应的区块号
    long double geometrical_distance(const position_float& a,const position_float& b);// 返回两个浮点坐标的距离
    inline constexpr int isValidBlock(block_t block_id);// 检查block_id是否为合法的方块id，是返回1，否返回0
    inline const int isValidEntity(basic_entity_id entity_id);// 检查entity_id是否为合法的实体id，是返回1，否返回0
    inline int inworld(const position& inpos);// 检查坐标是否在世界范围内，是返回1，否返回0
    void setworldtype(Worldset *inset,const std::string& input);// 设置世界生成类型
    void speedtest();// 性能测试
    inline long long actual_y(long long input);// 返回input对应的实际y坐标
    Worldset ui_worldset();// 世界生成设置的UI，返回一个Worldset类用以保存所设置的世界生成信息
    int update_chunk(world* at_world,long long from_cid,long long to_cid);// 更新from_cid至to_cid间的区块
    int getcommandid(const std::string& input);// 获得input对应命令的id，不存在则返回-1
    block_t blockid(const std::string& inblock);// 获得inblock对应方块的id，不存在则返回-1
    basic_entity_id entityid(const std::string& inentity);// 获得inblock对应方块的id，不存在返回-1
    int itemid(const std::string& initem);// 获得initem对应物品的id，不存在则返回-1
    template<class Predicator> bool predication_block(const world* inworld,const position& pos,Predicator predicate);
    template<class Predicator> bool predication_block(const world* inworld,const position& pos1,const position& pos2,Predicator predicate);
    int command_move(char input);// 命令/move
    int command_set(char direction,long long distance,const std::string& inblock);// 命令/set
    int command_break(char direction,long long distance);// 命令/break
    int command_fill(const std::string& sx,const std::string& sy,
                     const std::string& ex,const std::string& ey,
                     const std::string& use_block);// 命令/fill
    /*
    若为创造模式则可成功执行并返回1，否则返回0
    */
    int command_tp(const std::string& tx,const std::string& ty);// 命令/tp
    /*
    若为创造模式则可成功执行并返回1，否则返回0
    */
    int command_clone(const std::string& sx,const std::string& sy,
                      const std::string& ex,const std::string& ey,
                      const std::string& tx,const std::string& ty);// 命令/clone
    /*
    若为创造模式则：
    复制区域与源区域重叠，返回0
    否则成功执行，返回1，否则返回0
    */
    int command_gamemode(const std::string& inmode);// 命令/gamemode
    /*
    若参数为合法的游戏模式则返回1并修改游戏模式，否则返回0
    */
    int command_backpack();// 命令e
    int getgameruleid(const std::string& input);// 获得游戏规则标识符的id
    int get_vision_mode_id(const std::string& input);// 获得显示模式的id
    int command_gamerule(const std::string& incommand);// 命令/gamerule
    int command_testblock(const std::string& x,const std::string& y);// 命令/testblock
    /*
    若为创造模式则可成功执行并返回1，否则返回0
    */
    int command_eat();// 命令/eat，执行成功返回1
    int command_setblock(const std::string& x,const std::string& y,const std::string& use_block);// 命令/setblock
    /*
    若为创造模式则可成功执行并返回1，否则返回0
    */
    int command_seed();// 命令/seed，执行成功返回1
    int command_biome();// 命令/biome，执行成功返回1
    int command_give(const std::string& item_name,long long total);// 命令/give，执行成功返回1
    int command_throw(long long index);// 命令/throw，执行成功返回1
    int command_exchange(long long index1,long long index2);// 命令/exc，执行成功返回1
    int command_spawn(const std::string& type,const std::string& x,const std::string& y);// 命令/spawn，执行成功返回1
    int command_damage(const std::string& x,const std::string& y,long long damage);// 命令/damage，执行成功返回1，否则返回0
    int command_dokill(const std::string& x,const std::string& y);// 命令/dokill，执行成功返回1
    int command_chunkinfo(long long id);// 命令/chunkinfo，执行成功返回1
    int command_exit();// 命令/exit，执行成功返回1
    std::string numpress_str(std::vector<block_t> input);// 按连续数据压缩数组
    /*
    将一段由空格做分割的数字串压缩
    */
    std::vector<block_t> depress_str(const std::string& input);// 解压数组
    /*
    将经过numpress_str压缩的字符串解压，并放入一个block_t类型的vector中
    */
    std::string getchunkCode(const chunk& input);// 获取区块储存码
    inline std::string bool_tostr(bool input);
    /*
    将input转换为字符串型的布尔字面值(true/false)
    */
    inline bool str_tobool(const std::string& input);
    /*
    若input是true或false，返回其对应的布尔值
    */
    void printfile();
    /*
    打印存档码
    */
    bool available_version(const std::string& inver);
    /*
    检查inver是否属于可使用的存档版本
    */
    std::string getFileSizeUnit(const std::string& filein);
    /*
    对于filein参数，返回其容量信息，自动选择单位
    */
    int ui_readfile();
    /*
    执行成功返回1，否则返回0
    将调出存档解析的UI，显示并修改对应的游戏信息
    */
    int command_savefile(const std::string& name);
    /*
    执行成功返回1
    会将gameinfo.filename（即存档名称）设置为name，接着调用printfile()打印存档码
    */
    int gettimeid(const std::string& intime);
    /*
    若intime是七个标准时间段名称(gametime_show数组内)之一，返回1，否则返回0
    */
    int command_timeset(const std::string& arg1,const std::string& arg2);
    /*
    执行成功返回1，否则返回0
    arg1为/time命令的模式，arg2则是每个模式下属的参数
    */
    int command_info();//全部信息显示
    /*
    执行成功返回1
    用以输出当前游戏的运行信息
    */
    int command_chunkreload(long long id);//重加载区块
    /*
    执行成功返回1
    尝试重新生成一次id号区块
    */
    int command_chunkcopy(long long id1,long long id2);//复制一个区块
    /*
    执行成功返回1
    尝试将id2区块重新赋值为id1区块
    */
    int command_chunkclear(long long id);//清空一个区块
    /*
    执行成功返回1
    将id号区块的所有方块全部变为空气（广义上使用void_block）
    */
    int command_permission(const std::string& permission_in);//修改玩家的权限信息
    /*
    执行成功返回1
    将player.operate_permission参数修改为permission_in所对的权限模式
    */
    int command_copyright();//版权信息
    /*
    永远返回1
    输出版权信息
    */
    void command_parser(const std::string& command);// 解析命令组 
    /*
    自动解析参数command，若其包含多条命令则按顺序执行每一条
    如果命令检查通过，会自动调用其函数
    若gamerule.show_command_parse为true则显示检查流程
    */
    std::string getcommand();// 获得命令
    /*
    返回所输入的命令
    若gamerule.no_enter为true，则输入w,a,s,d,e命令时，直接返回输入的字符
    */
    position playerborn(world* spawn_world,const position& spawn_pos);// 寻找出生点
    /*
    寻找出生点，并同时重置玩家的信息
    返回出生的坐标
    */
    void screen_print();// 打印屏幕界面
    TIME getGameTimeID(long long realtime);// 得到游戏时间的阶段id（时间段）
    /*
    参数realtime代表游戏时间
    返回时间所处的时间段id（0至6）
    */
    pixel update_nowsky_color();// 更新当前的天空颜色
    void update_time(long long t);// 更新时间 参数t代表调用此函数时的时间戳（time(0)）
    void ui_gamemain();// 游戏主界面
    void ui_game_crafting_table();// 工作台界面
    void ui_game_furnace();// 熔炉界面
    void print_gamelogo();// 打印游戏logo
    void show_check_gamerun();// 显示游戏运行信息检查界面
    void game_startui();// 游戏开始的UI界面显示
    void api_addblock(const std::string& name,const std::string& universal_name,
                      char show_char,bool need_char,const std::set<short>& tags,
                      const std::string& color);
    bool str_contain(const std::string& input,char testchar);
    void api_merge_command_identifier(const std::string& identifier,int index);
    
    int gamerun(){
        doclear();
        std::cout << "彩色显示测试：" << std::endl;
        image test256(16,16);
        for(int i = 0;i< 16;++i){
            for(int j = 0;j < 16;++j)
                test256.edit(j,i,t256[i * 16 + j]);
        }
        test256.setspeed(10000);
        test256.show();
        std::cout << "在开始游戏前，请首先检查上面的图片能否正常显示，通常情况下，它应该是16*16的256色标准图片（也即CUIL的8位色彩映射表），如果出现颜色显示不完全等情况，请尝试更换运行环境或重新编译。" << std::endl;
        std::cout << "确认显示正常(0/1) >>> ";
        datain(true);
        doclear();
        game_starttime = time(0);
        game_startui();
        switch(uniselect<std::string>({"加载存档","创建新世界"})){
            case 1:
                if(ui_readfile() != 1)
                    exit(0);
                player.at_world = &MainWorld;
                update_chunk(player.at_world,getcid(player.pos.x) - 16,getcid(player.pos.x) + 16);
                break;
            case 2:
                do{
                    doclear();
                    worldset = ui_worldset();
                    worldset.show();
                    std::cout << "确认设置? (0/1) >>> ";
                }while(datain(true) == '0');
                player.at_world = &MainWorld;
                std::cout << "玩家生成中……" << std::endl;
                playerborn(&MainWorld,gamerule.respawn_point);
                std::cout << "加载玩家周围区块……(共8个)" << std::endl;
                update_chunk(player.at_world,getcid(player.pos.x) - 4,getcid(player.pos.x) + 4);
                break;
        }
        long long last_savetime = 0;
        if(worldset.pre_execute_command != "")
            command_parser(worldset.pre_execute_command);
        gameinfo.active_screen = INTERFACE_MAINSCREEN;
        while(true){
            ui_gamemain();
            long long stime = time(0);
            command_parser(getcommand());
            
            player.update();
            update_chunk(player.at_world,getcid(player.pos.x) - 2,getcid(player.pos.x) + 2);
            update_time(stime);
            now_sky_color = update_nowsky_color();
            
            if(online_xes && stime - game_starttime > 290){
                printfile();
                PAUSE();
                exit(0);
            }
            if(gamerule.auto_savefile && gameinfo.game_time- last_savetime >= 3000){
                std::cout << std::endl << "自动保存存档:" << std::endl;
                printfile();
                PAUSE();
                last_savetime = gameinfo.game_time;
            }
            CUIL_std::updwarning();
        }
        return 0;
    }
    
    inline void pushNewInfo(const std::string content,const std::string deliverer){ info_list.push(info_pack(content,deliverer)); }
    long long showlen(const std::string& instr){
        long long len = 0;
        //std::cout << instr<< std::endl;
        //for(int i = 0;i < instr.length();++i)
            //std::cout << int(instr[i]) << std::endl;
        for(int i = 0;i < instr.length();++i){
            if(int(instr[i]) < 0){
                len+=2;
                i+=2;
            }
            else 
                len++;
        }
        //std::cout << "[" << instr << "] len = " << len << std::endl;
        return len;
    }
    std::string str_setw(long long len,const std::string& instr){
        long long slen = showlen(instr);
        if(slen >= len)
            return instr;
        else
            return (std::string(len-slen,' ')+instr);
    }
    std::string str_rsetw(long long len,const std::string& instr){
        long long slen = showlen(instr);
        if(slen >= len)
            return instr;
        else
            return (instr+std::string(len-slen,' '));
    }
    long long hash_str(const std::string& input){
        unsigned long long p = 2147483647,mod = 1610612741;
        unsigned long long hash[input.length()];
        hash[0] = int(input[0]) % mod;
        for(int i = 1;i<input.length();++i)
            hash[i]=(hash[i-1])*p+int(input[i]) % mod;
        return hash[input.length()-1];
    }
    inline long long getcid(long long x){
        return x / chunkWidth - (x < 0);
    }//获取x坐标对应的区块号
    long double geometrical_distance(const position_float& a,const position_float& b){
        return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
    }
    inline constexpr int isValidBlock(block_t block_id){ return 0 <= block_id && block_id < block_list.size(); }
    inline const int isValidEntity(basic_entity_id entity_id){ return 0 <= entity_id && entity_id < entity_list.size(); }
    template<typename T> std::string __convert::to_string(const T& __input) const{
        return std::to_string(__input);
    }
    std::string __convert::to_string(long double __input,int precision) const{
        std::string __out = to_string(static_cast<long long>(__input)) + ".";
        __input -= floor(__input);
        for(int i = 0;i<precision;++i){
            __input *= 10;
            __out += (int(floor(__input)) % 10 + '0');
        }
        return __out;
    }
    long long __convert::to_int(char __input) const{
        return (isdigit(__input)?(__input - '0'):0);
    }
    long long __convert::to_int(const std::string& __input) const{
        if(__input.length() == 1 && isdigit(__input[0]))
            return __input[0] - '0';
        long long __r = 0;
        for(auto&& i:__input)
            __r = __r * 10 + (isdigit(i)?(i - '0'):0);
        for(auto&& i:__input){
            if(i == '-'){
                __r *= -1;
                return __r;
            }
        }
        return __r;
    }
    long double __convert::to_float(const std::string& input) const{
        int i = 0;
        long long integer_part = 0;
        long double uniform_part = 0.0;
        while(input[i] != '.' && i < input.length()){
            if(isdigit(input[i]))
                integer_part=integer_part * 10 + (input[i] - '0');
            ++i;
        }
        ++i;
        long double scale = 0.1;
        while(i < input.length()){
            if(isdigit(input[i]))
                uniform_part=uniform_part + scale * (input[i] - '0');
            ++i;
            scale *= 0.1;
        }    
        return (integer_part + uniform_part)*(input[0] == '-'?-1:1);
    }
    std::string __convert::to_string(char __input) const{
        return std::string(1,__input);
    }
    
    
    bool block::hastag(basic_tag_id tag) const{
        return tag_list.count(tag);
    }
    struct predicator_block_through{
        bool operator()(const block_t in){
            if(!isValidBlock(in))
                return false;
            return block_list[in].hastag(tag_through);
        }
    }isthrough;
    struct predicator_block_fluid{
        bool operator()(const block_t in)const{
            if(!isValidBlock(in))
                return false;
            return block_list[in].hastag(tag_fluid);
        }
    }isfluid;
    struct predicator_block_breakable{
        bool operator()(const block_t in){
            if(!isValidBlock(in))
                return false;
            return !block_list[in].hastag(tag_unbreakable);
        }
    }isbreakable;
    struct predicator_block_air{
        bool operator()(const block_t& in){
            if(!isValidBlock(in))
                return false;
            return in == id_block_air;
        }
    }isair;
    struct predicator_block_checkblock{
        bool operator()(const block_t& in,const block_t& c){
            if(!isValidBlock(in))
                return false;
            return c == in;
        }
    }isblock;

    noise::noise(int Aseed){
        r = random_list(Aseed);
    }
    inline double noise::lerp(long double t,long double a,long double b) const{
        return a + t * (b - a);
    }//线性插值
    inline double noise::grad(long long hash,long double x,long double y,long double z) const{
    	long long h = hash & 15;                     
    	double u = h < 8 ? x : y,v = h < 4 ? y : h == 12 || h == 14 ? x : z;
        return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
    }//哈希梯度值
    inline double noise::fade(long double t) const{
    	return t * t * t * (t * (t * 6.0 - 15.0) + 10.0);
    }//缓动函数
    long double noise::getNoiseValue(long double x,long double y,long double z) const{
        long long tx = static_cast<long long>(floor(x)) % 131072,
                  ty = static_cast<long long>(floor(y)) % 131072,
                  tz = static_cast<long long>(floor(z)) % 131072;
        x -= floor(x);y -= floor(y);z -= floor(z);
        long double u = fade(x),v = fade(y),w = fade(z);
        long long A = r[tx] + ty,
                  AA = r[A] + tz,
                  AB = r[A + 1] + tz,
                  B = r[tx + 1] + ty,
                  BA = r[B] + tz,
                  BB = r[B + 1] + tz;
        return lerp(w,
                    lerp(v,
                         lerp(u,
                              grad(r[AA], x, y, z),
                              grad(r[BA], x - 1, y, z)
                             ),
                         lerp(u,
                              grad(r[AB], x, y - 1, z),
                              grad(r[BB], x - 1, y - 1, z)
                              )
                        ),
    		        lerp(v,
    		             lerp(u,
    		                  grad(r[AA + 1], x, y, z - 1),
    		                  grad(r[BA + 1], x - 1, y, z - 1)
    		                 ),
    		             lerp(u,
    		                  grad(r[AB + 1], x, y - 1, z - 1),
    		                  grad(r[BB + 1], x - 1, y - 1, z - 1)
    		                 )
    		             )
      		       );
    }//获取噪声值
    long double noise::getOctaveNoise(long double x,long double y,long double z,int __octaves,long long seed) const{
        long double sum = 0.0,res = 0.0,freq = 1.0;
    	for(long long z = 1;z <= __octaves;z++){
            sum = getNoiseValue(x * freq,freq * y,freq * z);
            res += (sum + 0.1) * 16.0 / freq;
            freq *= 2;
        }
        res /= __octaves;
        return res;
    }//获取倍频噪声

    container::container(const std::string& Aname,long long make_size){
        name = Aname;
        item_list = {static_cast<size_t>(make_size),{id_item_void,0}};
    }
    int container::hasitem(long long item_type) const{
        long long return_index = 0;
        for(auto&&i:item_list){
            if(item_type == i.type)
                return return_index;
            return_index++;
        }
        return -1;
    }
    int container::pushNewItem(item& in_item){
        for(long long targetitem_index = 0;targetitem_index<item_list.size();targetitem_index++){
            if(in_item.type == item_list[targetitem_index].type || item_list[targetitem_index].type == id_item_void){
                if(item_list[targetitem_index].type == id_item_void)
                    item_list[targetitem_index].type = in_item.type;
                unsigned long long actual_putnum = 0;
                if(item_list[targetitem_index].total + in_item.total > items_list[item_list[targetitem_index].type].maxinum_stack)
                    actual_putnum = items_list[item_list[targetitem_index].type].maxinum_stack - item_list[targetitem_index].total;
                //超过最大堆叠数量，则部分放入
                else
                    actual_putnum = in_item.total;
                //全部放入
                item_list[targetitem_index].total+=actual_putnum;
                in_item.total-=actual_putnum;
            }
            if(in_item.total <= 0)
                return 1;//放完，成功
        }
        return 0;//未放完，失败
    }
    int container::canPushNewItem(const item& in_item) const{
        item in_item_cpy = in_item;
        long long can_put_total = 0;
        for(long long targetitem_index = 0;targetitem_index<item_list.size();targetitem_index++){
            if(in_item_cpy.type == item_list[targetitem_index].type || item_list[targetitem_index].type == id_item_void){
                unsigned long long actual_putnum = 0;
                if(item_list[targetitem_index].type == id_item_void)
                    actual_putnum = items_list[item_list[targetitem_index].type].maxinum_stack;
                //空物品，则为物品本身的最大堆叠数量
                else if(item_list[targetitem_index].total + in_item_cpy.total > items_list[item_list[targetitem_index].type].maxinum_stack)
                    actual_putnum = items_list[item_list[targetitem_index].type].maxinum_stack - item_list[targetitem_index].total;
                //超过最大堆叠数量，则部分放入
                else
                    actual_putnum = in_item_cpy.total;
                //全部放入
                can_put_total+=actual_putnum;//剩余空间增加
            }
            if(in_item_cpy.total <= can_put_total)
                return 1;
        }
        return 0;//未放完，失败
    }
    void container::print(int column) const{
        std::cout << "#"<<name<<std::endl<<"#物品列表："<<std::endl;
        bool has_item = false;
        long long max_showitem_len = 4;
        std::vector<std::string>item_str;
        for(auto&&i:item_list){
            std::string tmp_itemstr = i.to_string();
            if(max_showitem_len < showlen(tmp_itemstr))
                max_showitem_len = showlen(tmp_itemstr);
            item_str.push_back(tmp_itemstr);
        }
        bool row_hasitem = false;
        for(long long item_index = 0;item_index < item_list.size();item_index++){
            std::cout << str_setw(3,convert.to_string(item_index + 1)) << ": ";
            std::cout << str_rsetw(max_showitem_len + 2,item_list[item_index].type != id_item_void?item_str[item_index]:"")<<" ";
            if(item_index > 0 && (item_index+1) % column == 0)
                std::cout << std::endl;
        }
    }
    item& container::getitem(long long index) { return item_list[index]; }
    void container::mergeitem(long long index,const item& initem){ item_list.at(index) = initem; }
    void ui_crafting_table::show() const{
        std::cout << "#工作台" << std::endl;
        long long maxlen = 0;
        for(int i = 0;i < set_size;++i)
            maxlen = std::max(maxlen,(material[i].type == id_item_void) ? 3 : showlen(material[i].to_string()));
        for(int i = 0;i < set_size;++i){
            if(material[i].type != id_item_void)
                std::cout << " - " << str_setw(maxlen,material[i].to_string());
            else
                std::cout << " - " << str_setw(maxlen," ");
            if((i+1) % 3 == 0)
                std::cout << std::endl << std::endl;
        }
        std::cout << "产物 >>> " << ( product.type != id_item_void ? product.to_string() : "" ) << std::endl;
    }
    
    void ui_crafting_table::check_inventory(){
        product = item();
        inventory_plate tmp = convert_as_plate(material);
        for(auto&& i : inventory_list){
            if(i.item_plate.check(tmp,i.strict_aligned)){
                product = i.inventory_result;
                break;
            }
        }
    }
    void ui_crafting_table::clear(){
        for(auto&& i : material){
            player.backpack.pushNewItem(i);
            i.type = id_item_void;
        }
    }
    void ui_simple_crafting_table::clear(){
        for(auto&& i : material){
            player.backpack.pushNewItem(i);
            i.type = id_item_void;
        }
    }
    void container::exchangeitem(long long index1,long long index2){
        std::swap(item_list[index1 - 1],item_list[index2 - 1]);        
    }
    void container::movein_item(item& initem,long long move_total){
        if(canPushNewItem(initem))
            pushNewItem(initem);
        //优化掉
        else{
            move_total = std::min(initem.total,move_total);
            item tmp(initem.type,move_total);
            pushNewItem(tmp);
            initem.total -= (move_total - tmp.total);
        }
        
    }
    void ui_crafting_table::pushInItem(item& initem,int index){
        if(index > 8)
            index = 8;
        if(initem.total == 0)
            return ;
        while(material.size() < 9)
            material.push_back({id_item_void,0});
        if(material[index].type == initem.type || material[index].type == id_item_void){
            material[index].type = initem.type;
            if(material[index].total == items_list[material[index].type].maxinum_stack)
                return ;
            else{
                material[index].total ++;
                initem.total--;
                return ;
            }
        }
    }
    void ui_simple_crafting_table::show() const{
        std::cout << "#简易工作台" << std::endl;
        long long maxlen = 0;
        for(int i = 0;i < 4;++i)
            maxlen = std::max(maxlen,(material[i].type == id_item_void) ? 3 : showlen(material[i].to_string()));
        for(int i = 0;i < 4;++i){
            if(material[i].type != id_item_void)
                std::cout << " - " << str_setw(maxlen,material[i].to_string());
            else
                std::cout << " - " << str_setw(maxlen," ");
            if( !((i + 1) % 2) )
                std::cout << std::endl;
        }
        std::cout << "产物 >>> " << ( product.type != id_item_void ? product.to_string() : "" ) << std::endl;
    }// 显示简易工作台UI
    void ui_simple_crafting_table::pushInItem(item& initem,int index){
        if(range(0,4).inrange(index)){
            if(material[index].type == initem.type){
                long long canput_total = items_list[initem.type].maxinum_stack - material[index].total;
                long long actual_put_total = std::min(canput_total,initem.total);
                material[index].total += actual_put_total;
                initem.total -= actual_put_total;
            }
            else{
                item tmp = initem;
                initem = material[index];
                material[index] = initem;
            }
            debug("Put item[" + initem.to_string() + "] to simple_crafting_table");
        }
        else{
            pushNewInfo("不合法的下标","系统");
        }
    }// 在index处尝试放入initem
    void ui_simple_crafting_table::check_inventory(){
        product = item();
        inventory_plate tmp;
        tmp.plate.edit(0,0,material[0].type);
        tmp.plate.edit(1,0,material[1].type);
        tmp.plate.edit(0,1,material[2].type);
        tmp.plate.edit(1,1,material[3].type);
        for(auto&& i : inventory_list){
            if(i.item_plate.check(tmp,i.strict_aligned)){
                product = i.inventory_result;
                break;
            }
        }
    }
    exception::exception(const std::string& Acontent){
        content = Acontent;
    }
    std::string exception::what() const{
        return content;
    }
    Worldset::Worldset(long long Aseed,
                        long long Asea_level,
                        const std::string& Aplayername,
                        const std::string& Aworldname,
                        basic_worldtype_id Aworld_spawn_type,
                        short Aworld_spawn_biome,
                        long double Aterrain_scale){
        seed = Aseed;
        sea_level = Asea_level;
        playername = Aplayername;
        worldname = Aworldname;
        world_spawn_type = Aworld_spawn_type;
        world_single_biome = Aworld_spawn_biome;
        terrain_scale = Aterrain_scale;
    }
    void Worldset::show() const{
        std::cout  << worldname << "世界生成设置：" << std::endl;
        std::cout  << ".   她之名: " << playername << std::endl;
        std::cout  << ".   世界种子: " << seed << std::endl
                   << ".   海平面: " << sea_level << std::endl
                   << ".   世界类型: " << worldspawntype_name[world_spawn_type] << std::endl
                   << ".   世界群系设置: " << (world_single_biome == -1?"正常群系设置":("仅生成" + biome_list[world_single_biome].name + "群系")) << std::endl
                   << ".   地形缩放: " << std::fixed << std::setprecision(3) << terrain_scale << "倍" << std::endl;
        std::cout  << ".   地形采样密度: " << std::fixed << std::setprecision(5) << worldgenerator.sample_terrain << "每方块" << std::endl
                   << ".   群系采样密度: " << worldgenerator.sample_biome << "每方块" << std::endl
                   << ".   洞穴采样密度: " << worldgenerator.sample_cave << "每方块" << std::endl;
        std::cout  << ".   预处理指令: [" << pre_execute_command << "]" << std::endl;
    }
    block_operation::block_operation(block_t b_id){
        block_id = b_id;
    }
    bool std_position_cmp::operator()(const position& pos1,const position& pos2) const{
        return pos1.x == pos2.x?pos1.y < pos2.y:pos1.x < pos2.x;
    }
    void world::pushBlockMerge(const position& inpos,block_t merge_id){
        if(merge_list.find(inpos) == merge_list.end())
            merge_list.insert(std::make_pair(inpos,block_operation(merge_id)));
        else if(merge_list.find(inpos)->second.block_id != id_block_bedrock)    
            merge_list.find(inpos)->second.block_id = merge_id;
        else;
    }
    block_t world::getblock(const position& inpos)const{
        auto find_iter = chunk_list.find(getcid(inpos.x));
        if(!inworld(inpos)){
            if(inpos.x < 0 || inpos.x >= positive_crash_line)
                return id_block_barrier;
            else
                return id_block_air;
        }
        if(find_iter != chunk_list.end())
            return find_iter->second.getblock(inpos);
        else
            return id_block_empty;
    }
    int world::editblock(const position& inpos,block_t block){
        auto find_iter = chunk_list.find(getcid(inpos.x));
        if(find_iter != chunk_list.end())
            find_iter->second.editblock(inpos,block);
        else
            return 0;
        return 0;
    }
    bool world::inchunklist(long long id) const{
        return chunk_list.count(id);
    }
    void world::pushchunk(const chunk& inchunk){
        try{
            if(!inchunklist(inchunk.getid()))
                chunk_list.insert(std::pair<long long,chunk>(inchunk.getid(),inchunk));
            else    
                throw exception("在当前世界列表中已经存在"+convert.to_string(inchunk.getid())+"号区块");
        }catch(const exception& exception_out){
            pushNewInfo(exception_out.what(),"DEBUG");
        }
    }
    std::map<long long,chunk>::iterator world::getchunkiter(long long id){
        return chunk_list.count(id)?chunk_list.find(id):chunk_list.end();
    }
    chunk& world::getchunk(long long id){
        auto i = getchunkiter(id);
        return i == chunk_list.end() ? debug_chunk : i->second;
    }
    chunk::chunk(long long __id,world* __related_world){
        id = __id;
        related_world = __related_world;
        for(long long i = 0;i<worldMaxinumHeight * chunkWidth;++i)
            block[i] = id_block_air;
    }
    void chunk::copy(const chunk& op2){
        for(long long i = 0;i<worldMaxinumHeight * chunkWidth;++i)
            block[i] = op2.block[i];
    }
    bool chunk::operator()(const chunk& op2) const{
        return id < op2.id;
    }
    long long chunk::getid() const{
        return id;
    }
    block_t chunk::getblock(const position& inpos) const{
        if(getcid(inpos.x) == id && inworld(inpos))
            return block[inpos.x % chunkWidth + chunkWidth * inpos.y];
        else
            return id_block_air;
    }
    block_t chunk::getblockindex(long long index) const{
        return 0 <= index && index < worldMaxinumHeight * chunkWidth ?block[index]:id_block_air;
    }
    void chunk::editblock(const position& inpos,block_t block_in,bool just_push){
        if(getcid(inpos.x) == id && inworld(inpos) && isValidBlock(block_in)){
            if(generated)
                merged = true;
            block[inpos.x % chunkWidth + chunkWidth * inpos.y] = block_in;
        }
        else{
            if(just_push)
                return ;
            if(getcid(inpos.x) != id && inworld(inpos))
                related_world->pushBlockMerge(inpos,block_in);
        }
    }
    void chunk::print() const{
        image_text show_img(worldMaxinumHeight,chunkWidth);
        for(long long y = 0;y < worldMaxinumHeight;++y){
            for(long long x = id*chunkWidth;x<(id+1)*chunkWidth;++x)
                show_img.edit(x - id*chunkWidth,y,block_list[getblock({x,y})].color);
        }
        show_img.show();
    }
    void chunk::applyBlockMerge(){
        for(long long x = id*chunkWidth;x<chunkWidth*(id+1);++x){
            for(long long y = 0;y<worldMaxinumHeight;++y){
                for(long long i = 0;i<block_list.size();++i){
                    auto iter = related_world->merge_list.find({x,y});
                    if(iter != related_world->merge_list.end()){
                        if(!(iter->second.block_id == id_block_leaf && getblock({iter->first.x,iter->first.y}) == id_block_wood))
                            editblock({iter->first.x,iter->first.y},iter->second.block_id,true);
                        related_world->merge_list.erase(iter);
                    }
                }
            }
        }
    }
    void chunk::update(){
        for(std::vector<entity>::iterator i = entity_list.begin();i < entity_list.end();++i){
            if(std::abs(getcid(player.pos.x) - getcid(i->pos.x)) < chunkWidth * 2){
                BEHAVIOR_STATUS status = i->update();
                if(status < 0){
                    switch(status){
                        case SUCCESS:case FAILURE:break;
                        case FINAL:entity_list.erase(i);break;
                        case MOVE:
                            chunk* op_chunk = &(i->at_world->getchunkiter(getcid(i->pos.x))->second);
                            op_chunk->entity_list.push_back(*i);
                            entity_list.erase(i);
                            i--;
                        break;
                    }
                }
            }
        }
        applyBlockMerge();
    }
    void chunk::addentity(const entity& inentity){ entity_list.push_back(inentity); }
    struct entity_behavior_fall{
        BEHAVIOR_STATUS operator()(entity* inentity)const{
            //std::cout << "Call entity_fall"<<std::endl;
            bool check = predication_block(inentity->at_world,
                                           inentity->pos.delta(entity_list[inentity->type].hitbox.start_x,1),
                                           inentity->pos.delta(entity_list[inentity->type].hitbox.end_x,1),
                                           isthrough);
            if(!check)
                return FAILURE;
            inentity->pos = inentity->pos.delta(0,1);
            return SUCCESS;
        }
    }entity_fall;
    struct entity_behavior_isalive{
        BEHAVIOR_STATUS operator()(entity* inentity)const{
            //std::cout << "Call entity_isalive"<<std::endl;
            if(inentity->oxygen <= 0)
                inentity->health -= 2;
            if(inentity->health <= 0)
                return FINAL;//清除
            //生命值检测
            if(!inworld(inentity->pos) && inentity->pos.y >= 0){
                return FINAL;//行为树进行清除操作
                //只检测除了高度过高（y<0）的情况
            }
            return SUCCESS;
        }
    }entity_isalive;
    struct entity_behavior_move{
        BEHAVIOR_STATUS operator()(entity* inentity)const{
            //std::cout << "Call entity_move"<<std::endl;
            std::random_device rd;
            std::mt19937 ran(rd());
            int delta_x = ran()%3 - 1; 
            long long from_chunk = getcid(inentity->pos.x);
            //std::cout << "Call entity_move_status_1: from_chunk: " << from_chunk << ",delta_x = "<< delta_x<<std::endl;
            //std::cout << "type : " <<inentity->type << std::endl;
            position tpos = inentity->pos.delta(delta_x,0),
                     spos = tpos.delta(entity_list[inentity->type].hitbox.start_x,entity_list[inentity->type].hitbox.start_y),
                     epos = tpos.delta(entity_list[inentity->type].hitbox.end_x,entity_list[inentity->type].hitbox.end_y);
            //std::cout << "start = " << spos.to_string() << ",end = " << epos.to_string() << std::endl;
            //std::cout << "Hitbox check: " << (predication_block(inentity->at_world,spos,epos,isthrough)?"true":"false") << std::endl;
            if(!inworld(spos) || !inworld(epos))
                return FAILURE;
            if(predication_block(inentity->at_world,spos,epos,isthrough)){
                inentity->pos = inentity->pos.delta(delta_x,0);
                if(!inworld(inentity->pos))
                    return FAILURE;
                //std::cout << "Now chunk: " << getcid(inentity->pos.x) << std::endl;
                if(getcid(inentity->pos.x) != from_chunk){
                    if(!inentity->at_world->inchunklist(getcid(inentity->pos.x)))
                        return FAILURE;
                    else{
                        //std::cout << "Call entity_move_status_3b"<<std::endl;
                        //pushNewInfo("pos at" + inentity->pos.to_string());
                        return MOVE;
                    }
                }
                return SUCCESS;
            }
            tpos = tpos.delta(0,-1);
            spos = tpos.delta(entity_list[inentity->type].hitbox.start_x,entity_list[inentity->type].hitbox.start_y),
            epos = tpos.delta(entity_list[inentity->type].hitbox.end_x,entity_list[inentity->type].hitbox.end_y);
            if(predication_block(inentity->at_world,spos,epos,isthrough)){
                inentity->pos = inentity->pos.delta(delta_x,-1);
                if(!inworld(inentity->pos))
                    return FAILURE;
                if(getcid(inentity->pos.x) != from_chunk){
                    //std::cout << "Now chunk: " << getcid(inentity->pos.x) << std::endl;
                    if(!inentity->at_world->inchunklist(getcid(inentity->pos.x)))
                        return FAILURE;
                    else{
                        //std::cout << "Call entity_move_status_3b"<<std::endl;
                        pushNewInfo("pos at" + inentity->pos.to_string());
                        return MOVE;
                    }
                }
                return SUCCESS;
            }
            return FAILURE;
        }
    }entity_move;
    struct entity_behavior_float{
        BEHAVIOR_STATUS operator()(entity* inentity){
            position from_pos = inentity->pos;
            block_t at_block = inentity->at_world->getblock(from_pos);
            if(block_list[at_block].hastag(tag_fluid)){
                if(block_list[at_block].hastag(tag_oxygen))
                    inentity->oxygen = inentity->oxygen > 0 ? inentity->oxygen - 2 : 0;
                //if(block_list[inentity->at_world->getblock(from_pos.delta(0,-1))].hastag(tag_oxygen))
                inentity->pos = inentity->pos.delta(0,-1);
                return SUCCESS;
            }
            else{
                if(inentity->oxygen < 20)
                    inentity->oxygen = (inentity->oxygen / 2 + 1) * 2;
                return FAILURE;
            }
            
        }
    }entity_float;
    BEHAVIOR_STATUS basic_behavior_tree(entity* inentity){
        position from_pos = inentity->pos;
        if(entity_isalive(inentity) == FINAL)
            return FINAL;
        else{
            BEHAVIOR_STATUS ret_status = SUCCESS;
            entity_fall(inentity);
            if(entity_float(inentity) == FAILURE)
                ret_status = entity_move(inentity);
            return ret_status;
        }
        return SUCCESS;
    }//基础行为树
    entity::entity(basic_entity_id Atype,
                   const position& Apos,
                   world* Aworld,
                   int Ahealth,
                   int Aoxygen,
                   bool Aneed_update,
                   const std::string& Aname_tag){
        type = Atype;
        pos = Apos;
        at_world = Aworld;
        if(Ahealth == -1)
            health = entity_list[type].maxinum_health;
        else
            health = Ahealth;
        oxygen = Aoxygen;
        need_update = Aneed_update;
        name_tag = Aname_tag;
    }
    BEHAVIOR_STATUS entity::update(){
        return basic_behavior_tree(this);
    }
    position playerborn(world*,const position&);
    void playerinfo::update(){
        debug("game_updateinfo: update player");
        if(gamerule.gamemode!=gamemode_creative){
            if(!block_list[at_world->getblock(pos)].hastag(tag_oxygen))
                oxygen = oxygen + 2 <= 20?oxygen + 2:oxygen;
            if(block_list[at_world->getblock(pos)].hastag(tag_oxygen) && oxygen > 0)
                oxygen -= 2;
            if(oxygen == 0){
                health -= 2;
                if(health <= 0){
                    pushNewInfo(worldset.playername+"溺水了");
                    debug("game_updateinfo: respawn player");
                    player.pos = playerborn(at_world,gamerule.respawn_point);
                }
            }
            if(at_world->getblock(pos) == id_block_lava){
                health -= 4;
                if(health <= 0){
                    pushNewInfo(worldset.playername+"化为了灰烬");
                    debug("game_updateinfo: respawn player");
                    player.pos = playerborn(at_world,gamerule.respawn_point);
                }
            }
        }
        if(gameinfo.active_screen == INTERFACE_BACKPACK)
            player.operating_container_pos = void_position;
    }
    basic_worldgenerator::basic_worldgenerator(long double sample_t,long double sample_b,long double sample_c,long double sample_tg,long double sample_tl,long double sample_td,long long Alava_layer_height){
        sample_terrain = sample_t;
        sample_biome = sample_b;
        sample_cave = sample_c;
        sample_terrain_granite = sample_tg;
        sample_terrain_limestone = sample_tl;
        sample_terrain_dirt = sample_td;
        lava_layer_height = 16;
        init();
    }
    MainWorld_worldgenerator::MainWorld_worldgenerator(long double sample_t,long double sample_b,long double sample_c,long double sample_tg,long double sample_tl){
        sample_terrain = sample_t;
        sample_biome = sample_b;
        sample_cave = sample_c;
        sample_terrain_granite = sample_tg;
        sample_terrain_limestone = sample_tl;
    }
    bool basic_worldgenerator::biome_cmp(poss_sort_biome& a,poss_sort_biome& b){
        return a.possibility < b.possibility;
    }
    bool basic_worldgenerator::rand_bool(long long x){
        long long res = 0;
        for(int i = 0;i<100;++i)
            res = (46364081 * res + x) % 2147483648;
        return res >= 1073741824;
    }
    inline long double basic_worldgenerator::continent_curve(long double x) const{
        return std::pow(std::abs((x * ( x * x * (3 * x * x - 10) + 15) ) / 8.0),1.75);
    }
    int basic_worldgenerator::getbiome(long long id){
        if(worldset.world_single_biome!=-1)
            return worldset.world_single_biome;
        long double terrain_value = continent_curve((worldset.terrain_scale*TerrainNoise.getOctaveNoise(id*chunkWidth*sample_terrain,1.0,1.0,16,worldset.seed)-0.1))*100.0,
                    temeperature_value = (BiomeTemperatureNoise.getOctaveNoise(id*sample_biome,1.0,1.0,10,worldset.seed)-0.2)*100.0;
        std::mt19937 gen(worldset.seed);
        switch(worldset.world_spawn_type){
            case id_worldtype_normal:/* 正常世界 */
                return getNoiseBiome(terrain_value,temeperature_value);
            case id_worldtype_flat:/* 超平坦世界 */
                return id_biome_extreme_plain;
            case id_worldtype_error:/* 混乱世界 */
                return gen()%biome_list.size();
            case id_worldtype_ocean:/* 海世界 */
                return getNoiseBiome(fmax(terrain_value-100.0,-100.0),temeperature_value);
            case id_worldtype_arrakis:/* 沙丘世界 */
                return id_biome_dessert;
            case id_worldtype_froze:/* 冰世界 */
                return getNoiseBiome(terrain_value,fmax(temeperature_value-100.0,100.0));
            case id_worldtype_void:
                return id_biome_plain;
        }
        return id_biome_plain;
    }
    long long basic_worldgenerator::getNoiseBiome(long double value_h,long double value_t){
        std::vector<double> getDiffer_Biome;
        std::vector<poss_sort_biome> biome_matchlist = {{0,0}};
        for(long long gnbi = 0;gnbi<biome_list.size();gnbi++){
            getDiffer_Biome.push_back(0.0);
            biome_matchlist.push_back({0,0});
            long double biome_distance = (geometrical_distance({value_h,value_t},{biome_list[gnbi].height_value,biome_list[gnbi].temperature_value})+0.01);
            if((biome_list[gnbi].height_value>0.0&&value_h<0.0) || (biome_list[gnbi].height_value<0.0&&value_h>0.0))
                biome_matchlist[gnbi].possibility = 0;
            else
                biome_matchlist[gnbi].possibility = biome_list[gnbi].spawn_value*(gnbi == id_biome_extreme_plain?0:100000.0 / (biome_distance * biome_distance));
            biome_matchlist[gnbi].biome_id = gnbi;
        }
        std::sort(biome_matchlist.begin(),biome_matchlist.end(),biome_cmp);
        long long retbiome = biome_matchlist[biome_matchlist.size()-1].biome_id;
        return retbiome;
        /*
        for(long long ret_biomeID = biome_total-1;ret_biomeID>=0;ret_biomeID--){
            srand(ret_biomeID + (long long)(worldset.seed*8869311+(long long)(value_h*8869311+value_t*8869311)-(x_input * 16000)));
            if(rand()%200000 < biome_matchlist[ret_biomeID].possibility)
                return biome_matchlist[ret_biomeID].biome_id;//如果小于随机值则返回对应的群系，群系的生成将概率越来越大
        }
        */
    }
    
    long long basic_worldgenerator::getBiomeHeightInterrupt(long double inputy,int biome_type){
        if(worldset.world_spawn_type == id_worldtype_error)
            return rand()%512;
        inputy*=worldset.terrain_scale;
        inputy = std::fabs(inputy);
        if(0 <= biome_type && biome_type < biome_list.size())
            return worldset.sea_level - inputy * biome_list[biome_type].terrain_scale;
        else
            return worldset.sea_level;
    }
    long long basic_worldgenerator::getheight(long long x){
        return getBiomeHeightInterrupt(worldset.terrain_scale*TerrainNoise.getOctaveNoise(x*sample_terrain,1.0,1.0,10,worldset.seed),getbiome(getcid(x)));
    }
    long long basic_worldgenerator::find_first_block(chunk* inchunk,long long x,block_t id){
        for(long long y = 0;y < worldMaxinumHeight;++y){
            if(inchunk->getblock({x,y}) == id)
                return y;
        }
        return -1;
    }
    long long basic_worldgenerator::find_first_not_block(chunk* inchunk,long long x,block_t id){
        for(long long y = 0;y < worldMaxinumHeight;++y){
            if(inchunk->getblock({x,y}) != id)
                return y;
        }
        return -1;
    }
    long long basic_worldgenerator::reverse_find_first_block(chunk* inchunk,long long x,block_t id){
        for(long long y = worldMaxinumHeight - 1;y >= 0;--y){
            if(inchunk->getblock({x,y}) == id)
                return y;
        }
        return -1;
    }
    long long basic_worldgenerator::reverse_find_first_not_block(chunk* inchunk,long long x,block_t id){
        for(long long y = worldMaxinumHeight - 1;y >= 0;--y){
            if(inchunk->getblock({x,y}) != id)
                return y;
        }
        return -1;
    }
    bool basic_worldgenerator::hasblock(chunk* inchunk,block_t id){
        for(long long y = 0;y<worldMaxinumHeight;++y){
            for(long long x = id*chunkWidth;x<(id+1)*chunkWidth;++x){
                if(inchunk->getblock({x,y}) == id)
                    return true;
            }
        }
        return false;
    }
    void basic_worldgenerator::setTreeBranch(chunk* inchunk,world* _inworld,const position& pos1,const position& pos2,int size_branch,int type){
        long long midx_tree = pos2.x,midy_tree = pos2.y;
        long double k = (pos1.x!=pos2.x)?(pos1.y-pos2.y-0.0)/(pos1.x-pos2.x-0.0):(1e+308),b = pos1.y - pos1.x*k;
        long double nx,ny;
        long long nsy,ney;
        switch(type){
            case 0:
                if(pos1.x>pos2.x){
                    for(long double i = pos2.x;i<=pos1.x;i+=0.1){
                        nx = i,ny = k*i+b;
                        if(inworld({(long long)nx,(long long)ny})){
                            if(block_list[inchunk->getblock({(long long)nx,(long long)ny})].hastag(tag_through))
                                inchunk->editblock({(long long)nx,(long long)ny},id_block_wood);
                        }
                    }
                }else if(pos1.x<pos2.x){
                    for(long double i = pos1.x;i<=pos2.x;i+=0.1){
                        nx = i,ny = k*i+b;
                        if(inworld({(long long)nx,(long long)ny})){
                            if(block_list[inchunk->getblock({(long long)nx,(long long)ny})].hastag(tag_through))
                                inchunk->editblock({(long long)nx,(long long)ny},id_block_wood);
                        }
                    }
                }else{
                    nsy = std::min(pos1.y,pos2.y),ney = std::max(pos1.y,pos2.y);
                    for(long long i = nsy;i<=ney;++i){
                        if(inworld({pos1.x,(long long)i})){
                            if(block_list[inchunk->getblock({pos1.x,i})].hastag(tag_through))
                                inchunk->editblock({pos1.x,(long long)i},id_block_wood);
                        }
                    }
                }
                for(long long tx = pos2.x - size_branch;tx<= pos2.x + size_branch;tx++){
                    for(long long ty = midy_tree + size_branch / 1.3;ty>= midy_tree - size_branch - size_branch / 1.5;ty--){
                        if((tx - pos2.x)*(tx - pos2.x) + (ty - midy_tree)*(ty - midy_tree) <= size_branch * size_branch * 1.5625){
                            if(inchunk->getblock({tx,ty}) != id_block_wood && inworld({tx,ty})){
                                if(tx >= (inchunk->id * chunkWidth) || tx < (inchunk->id+1)*chunkWidth){
                                    if(block_list[inchunk->getblock({tx,ty})].hastag(tag_through))
                                        inchunk->editblock({tx,ty},id_block_leaf);
                                }
                            }
                        }
                    }
                }   
            break;
        }
    }
    void basic_worldgenerator::setTree(chunk* inchunk,world* _inworld,const position& inpos,int size_tree,int type){
        std::mt19937 g(worldset.seed+inpos.x+inpos.y);
        long long size_branch = size_tree + (g()%size_tree / 3)+1;
        for(long long x = (inpos.x-1);x<=(inpos.x+1);++x){
            for(long long y = inpos.y-size_branch;y<inpos.y;++y){
                if(!block_list[inchunk->getblock({x,y})].hastag(tag_through))
                    return ;
            }
        }
        setTreeBranch(inchunk,_inworld,inpos,{inpos.x,inpos.y-size_branch},size_tree,type);
        inchunk->editblock(inpos,id_block_dirt);//基础的泥土
        //层0主干
        if(type == 0){
            long long tmp = rand()%2+1;
            if(size_tree > 3)
                setTreeBranch(inchunk,_inworld,{inpos.x,inpos.y-1-size_branch+tmp},{inpos.x+rand()%5-2,inpos.y-1-size_branch+tmp-(rand()%2)},size_tree/2 + 1,type);
            //层1主枝
            if(size_tree > 5){
                srand(worldset.seed+inpos.x+inpos.y+1);
                setTreeBranch(inchunk,_inworld,{inpos.x,inpos.y-1-size_branch},{inpos.x+rand()%5-2,inpos.y-1-size_branch-(rand()%2)},size_tree/2+1,type);
                
            }//层1副枝
        }
    }
    const long double cave_x_buffer = 1.0;
    const long double cave_y_buffer = 2.125;
    void basic_worldgenerator::setRawTerrainX(chunk* inchunk,long long x,long long y){
        long long id = inchunk->id;//简写.jpg
        debug("game_worldgenerate: Process of creating chunk(id = " + convert.to_string(inchunk->id) + "): start setting raw terrain at x = " + convert.to_string(x));
        int chunk_biome = basic_worldgenerator::getbiome(id);//区块群系
        long long incursion_depth = 2 + (TerrainNoise.getOctaveNoise(worldset.seed * (x * sample_terrain)+ 0.001,worldset.seed * 0.001,worldset.seed * 0.001) + 1.23894);
        //表层方块厚度
        long long terrain_height = (y == -1?basic_worldgenerator::getheight(x):y);
        if(terrain_height >= worldMaxinumHeight - 2)
            terrain_height = worldMaxinumHeight - 2;
        for(long long y = 0;y < worldMaxinumHeight;++y){
            block_t block_generate = id_block_air;
            long double value = CaveNoise.getOctaveNoise(x * worldgenerator.sample_cave * cave_x_buffer,y * worldgenerator.sample_cave * cave_y_buffer,0.0,10);
                if(y >= terrain_height - (chunk_biome == id_biome_volcano?16.0 / 4 * incursion_depth:0)){
                    block_generate = block_t(worldset.world_spawn_type == id_worldtype_error?rand()%block_list.size():id_block_stone);
                    if(y-terrain_height <= incursion_depth){
                        if(y>worldset.sea_level && y == terrain_height)
                            block_generate = id_block_sand;
                        else if(y == terrain_height)//第一层为表层方块
                            block_generate = biome_list[chunk_biome].surface_block;
                        else//否则为近表层方块
                            block_generate= biome_list[chunk_biome].subsurface_block;
                        if(value >= -0.053125 * y / worldMaxinumHeight && value <= 0.053125 * y / worldMaxinumHeight){
                            if(!block_list[inchunk->getblock({x,y})].hastag(tag_unbreakable))
                                block_generate = id_block_air;
                            if(y > worldMaxinumHeight - lava_layer_height)
                                block_generate = id_block_lava;
                        }
                    }else{
                        int bedrock_incursion_p = 100 + 20 * (y - worldMaxinumHeight + 1);
                        srand(worldset.seed + x + y + 19283713 * x * y * worldset.seed + x * y);
                        if(rand()%100 <= bedrock_incursion_p)//基岩侵入
                            block_generate = id_block_bedrock;
                        else{
                            bool change_flag = false;
                            if((1 - 1.5 * (worldMaxinumHeight - y) / worldMaxinumHeight) * TerrainGraniteNoise.getOctaveNoise(x * sample_terrain_granite * 10.0,y * sample_terrain_granite * 10.0,worldset.seed * 0.01) > 0.75){
                                block_generate = id_block_granite;
                                change_flag = true;
                            }
                            if((1 - 0.5 * (worldMaxinumHeight - y) / worldMaxinumHeight) * TerrainLimeStoneNoise.getOctaveNoise(x * sample_terrain_limestone * 10.0,y * sample_terrain_limestone * 10.0,worldset.seed * 0.01) < -0.5){
                                block_generate = id_block_limestone;
                                change_flag = true;
                            }
                            if((1 - 0.5 * (worldMaxinumHeight - y) / worldMaxinumHeight) * TerrainDirtNoise.getOctaveNoise(x * sample_terrain_dirt * 10.0,y * sample_terrain_limestone * 10.0,worldset.seed * 0.01) < -0.625){
                                block_generate = id_block_dirt;
                                change_flag = true;
                            }
                            if(!change_flag)
                                block_generate = block_t(worldset.world_spawn_type == id_worldtype_error?rand()%block_list.size():id_block_stone);//石头
                        }
                    }//基岩的过渡
                    if(y == worldMaxinumHeight - 1)
                        block_generate = id_block_bedrock;//底层强制替换
                }//海平面下
                else if(y >= worldset.sea_level){
                    if(chunk_biome == id_biome_lava_sea || chunk_biome == id_biome_volcano || chunk_biome == id_biome_lavaland)
                        block_generate = id_block_lava;
                    //岩浆海，火山，石原覆盖岩浆
                    else if(biome_list[chunk_biome].temperature_value <= 30.0 && biome_list[chunk_biome].temperature_value >= -40.0)
                        block_generate = id_block_water;
                    //温度值小于0.3，大于-0.4的群系覆盖水
                    else if(biome_list[chunk_biome].temperature_value < -40.0){
                        if(y < worldset.sea_level + incursion_depth * ((-40.0 - biome_list[chunk_biome].temperature_value) + 10.0) * 0.1)//如果温度过低，逐渐增厚冰层
                            block_generate = id_block_ice;
                        else//否则仍为水
                            block_generate = id_block_water;
                    }
                    //温度小于-0.4的群系表面覆冰
                    else
                        block_generate = id_block_air;
                }//大于生成高度但小于海平面
                else//否则为空气
                    block_generate = id_block_air;
                
                inchunk->editblock({x,y},block_generate);
            }
    }
    void basic_worldgenerator::setRawTerrain(chunk* inchunk){
        debug("game_worldgenerate: Process of creating chunk(id = " + convert.to_string(inchunk->id) + "): start setting raw terrain");
        for(long long x = inchunk->id * chunkWidth;x < (inchunk->id + 1) * chunkWidth;++x)
            setRawTerrainX(inchunk,x);
    }
    void basic_worldgenerator::correctTerrain(chunk* inchunk){
        debug("game_worldgenerate: Process of creating chunk(id = " + convert.to_string(inchunk->getid()) + "): start correct terrain");
        const int delta_x[] = {-1, 0, 1,-1, 1,-1, 0, 1};
        const int delta_y[] = {-1,-1,-1, 0, 0, 1, 1, 1};
        for(long long x = inchunk->getid() * chunkWidth;x < (inchunk->getid()+1) * chunkWidth;++x){
            for(long long y = 0;y < worldMaxinumHeight;++y){
                bool has_sameblock = false;
                block_t nowblock = inchunk->getblock({x,y});
                std::set<block_t>block_list;
                for(int i= 0;i < 8;++i){
                    if(inchunk->getblock({x + delta_x[i],y + delta_y[i]}) == nowblock){
                        has_sameblock = true;
                        break;
                    }else
                        block_list.insert(inchunk->getblock({x + delta_x[i],y + delta_y[i]}));
                }
                if(block_list.size() == 1 && !has_sameblock && nowblock != id_block_bedrock)
                    inchunk->editblock({x,y},*block_list.begin());
            }
        }//浮空方块处理
        long long height_list[chunkWidth + 2];
        long long x_base = inchunk->getid()*chunkWidth - 1;
        for(long long x = x_base;x <= (inchunk->getid() + 1) * chunkWidth;++x)
            height_list[x-x_base] = worldgenerator.getheight(x);
        for(long long x = x_base + 1;x < (inchunk->getid() + 1) * chunkWidth;++x){
            long long height_differ = height_list[x - x_base] - height_list[x - x_base - 1];
            long long height_merge = height_differ / (height_differ > 8?8:4);
            if(std::abs(height_differ) >= 3){
                srand(x + worldset.seed);
                long long target_height = height_list[x - x_base - 1] + height_merge + (std::abs(height_differ) > 32?(height_merge == 0?1:0):0);
                setRawTerrainX(inchunk,x,target_height);
                height_list[x - x_base] = target_height;
            }
        }
    }
    void basic_worldgenerator::setSecondaryTerrain(chunk* inchunk,world* _inworld){
        long long id = inchunk->id;
        debug("game_worldgenerate: Process of creating chunk(id = " + convert.to_string(id) + "): create secondary terrain");
        for(long long x = (id - 2) * chunkWidth;x < (id + 2) * chunkWidth;++x){
            srand(worldset.seed+x*id);
            long long set_plant_y = basic_worldgenerator::find_first_not_block(inchunk,x,id_block_air);
            if(!block_list[inchunk->getblock({x,set_plant_y})].hastag(tag_plant))
                continue;
            int posibility = rand()%100;
            if(posibility < biome_list[getbiome(id)].density_plant){
                srand(worldset.seed + x * id + set_plant_y);
                inchunk->editblock({x,set_plant_y - 1},rand()%100 < 80?id_block_short_grass:id_block_rose);
            }
            if(posibility < biome_list[getbiome(id)].density_tree){
                srand(worldset.seed + x * id);
                debug("game_worldgenerate: Process of creating chunk(id = " + convert.to_string(id) + "): create tree at " + position(x,set_plant_y).to_string());
                basic_worldgenerator::setTree(inchunk,_inworld,{x,set_plant_y},rand()%4 + 2,0);    
            }
        }
    }
    position spawn_pos_entity(chunk* spawn_chunk,const position& spawn_pos){
        long long find_y = worldgenerator.find_first_not_block(spawn_chunk,spawn_pos.x,id_block_air);
        debug("game_functional: try spawn pos at " + position(spawn_pos.x,find_y - 1).to_string());
        if(find_y == -1)
            return {-1,-1};
        return {spawn_pos.x,find_y - 1};
    }
    void basic_worldgenerator::setEntity(chunk* inchunk,world* _inworld){
        long long id = inchunk->getid();
        for(long long x = id * chunkWidth;x < (id + 1) * chunkWidth;++x){
            srand(worldset.seed+x*id);
            int posibility = rand()%100;
            if(posibility < 10){
                inchunk->addentity(
                    entity(
                        basic_entity_id(rand()%3 + 3),
                        spawn_pos_entity(inchunk,{x,worldset.sea_level})
                    )
                );
            }
        }
    }
    chunk basic_worldgenerator::generate_chunk(long long id,int world_type){
        debug("game_worldgenerate: Start process of creating chunk(id = " + convert.to_string(id) + ")");
        if(worldset.world_spawn_type == id_worldtype_void){
            debug("game_worldgenerate: world_spawn_type = id_worldtype_void(euqal to " + convert.to_string(int(id_worldtype_void)) + "), return a void chunk");
            chunk tmp(id,&MainWorld);
            tmp.generated = true;
            return tmp;
        }
        //虚空世界则直接返回一个空区块
        chunk return_chunk(id,&MainWorld);
        return_chunk.generated = false;
        basic_worldgenerator::setRawTerrain(&return_chunk);
        //此过程生成一个纯一级地形的区块
        basic_worldgenerator::correctTerrain(&return_chunk);
        //此过程将尝试改正游戏所不认可的地形（如：过于突兀的断层，浮空方块等）
        basic_worldgenerator::setSecondaryTerrain(&return_chunk,&MainWorld);
        //此过程会尝试在区块的一级地形基础上生成二级地形
        //basic_worldgenerator::setStructure(&return_chunk);
        //此过程尝试生成结构
        basic_worldgenerator::setEntity(&return_chunk,&MainWorld);
        return_chunk.applyBlockMerge();//保证跨区块的二级地形生成能在本区块生效（如树木，结构）
        return_chunk.generated = true;
        return return_chunk;
    }
    inline int inworld(const position& inpos){
        return (0 <= inpos.x && inpos.x < positive_crash_line && 0 <= inpos.y && inpos.y < worldMaxinumHeight);
    }
    void setworldtype(Worldset *inset,const std::string& input){
        if(input == "Normal")
            inset->world_spawn_type = id_worldtype_normal;
        else if(input == "Flat")
            inset->world_spawn_type = id_worldtype_flat;
        else if(input == "Froze")
            inset->world_spawn_type = id_worldtype_froze;
        else if(input == "Void")
            inset->world_spawn_type = id_worldtype_void;
        else if(input == "eRr0|^")
            inset->world_spawn_type = id_worldtype_error;
        else if(input == "Arrakis")
            inset->world_spawn_type = id_worldtype_arrakis;
        else if(input == "Ocean")
            inset->world_spawn_type = id_worldtype_ocean;
        else
            inset->world_spawn_type = id_worldtype_normal;
    }
    void speedtest(){
        long long tid = 0;
        clock_t c = clock();
        chunk tmp_chunk(tid,&MainWorld);
        while(clock() - c < CLOCKS_PER_SEC)
            tmp_chunk = worldgenerator.generate_chunk(tid++,0);
        std::cout << "性能测试：在" << CLOCKS_PER_SEC << "个时钟单元内生成了" << tid << "个区块" << std::endl;
        
    }
    inline long long actual_y(long long input){
        return gamerule.reverse_y?worldMaxinumHeight - 1 - input:input;
    }
    Worldset ui_worldset(){
        doclear();
        Worldset tmp_set;
        std::vector<std::string> biome_tlist;
        for(int i = 0;i < biome_list.size();++i)
            biome_tlist.push_back(biome_list[i].name);
        biome_tlist.push_back("无设置");
        short choose = uniselect<std::string>({"名称","种子","世界类型设置","地形设置","预处理指令","结束更改"});
        long long a = 0;
        std::string b;
        std::string seed_tmp;
        while(choose != 6){
            switch(choose){
                case 1:
                    switch(uniselect<std::string>({"玩家名称","世界名称"})){
                        case 1:
                            tmp_set.playername = formin("给予她名字: ",20);
                            break;
                        case 2:
                            tmp_set.worldname = formin("写下世界之名: ",20);
                            break;
                    }
                    break;
                case 2:
                    seed_tmp = formin("输入种子：",20);
                    if(seed_tmp == convert.to_string(convert.to_int(seed_tmp)))
                        tmp_set.seed = convert.to_int(seed_tmp);
                    else
                        tmp_set.seed = hash_str(seed_tmp);
                    break;
                case 3:
                    doclear();
                    switch(uniselect<std::string>({"单一生物群系","其他类型","无更改"})){
                        case 1:
                            doclear();
                            tmp_set.world_single_biome = uniselect<std::string>(biome_tlist)-1;
                            if(tmp_set.world_single_biome == biome_list.size() + 1)
                                tmp_set.world_single_biome = -1;
                            break;
                        case 2:
                            setworldtype(&tmp_set,formin("输入: ",15));
                            break;
                        default:
                            break;
                    }
                    break;
                case 4:
                    doclear();
                    switch(uniselect<std::string>({"海平面","地形取样密度","群系取样密度","地形缩放系数","岩浆层高度"})){
                        case 1:
                            b = formin("输入海平面高度(0至"+convert.to_string(worldMaxinumHeight-1)+"之间的数字): ",10);
                            a = convert.to_int(b);
                            tmp_set.sea_level = worldMaxinumHeight - a;
                            break;
                        case 2:
                            worldgenerator.sample_terrain = convert.to_float(formin("输入一个小数(建议在0.001至1.000间): ",10));
                            break;
                        case 3: 
                            worldgenerator.sample_biome = convert.to_float(formin("输入一个小数(建议在0.001至1.000间): ",10));
                            break;
                        case 4:
                            tmp_set.terrain_scale = convert.to_float(formin("输入一个正小数: ",10));
                            break;
                        case 5:
                            worldgenerator.lava_layer_height = convert.to_int(formin("输入[0,512)之间的整数(推荐值为16): "));
                        default:
                            break;
                    }
                    break;
                case 5:
                    tmp_set.pre_execute_command = formin("输入预处理的命令组: ",30);
                    break;
            }
            doclear();
            choose = uniselect<std::string>({"名称","种子","世界类型设置","地形设置","预处理指令","结束更改"});
        }
        worldset.seed = tmp_set.seed;
        TerrainNoise = noise(0);
        BiomeTemperatureNoise = noise(1);
        TerrainGraniteNoise = noise(2);
        TerrainLimeStoneNoise = noise(3);
        CaveNoise = noise(4);
        return tmp_set;
    }
    int update_chunk(world* at_world,long long from_cid,long long to_cid){
        for(long long cid = from_cid;cid <= to_cid;cid++){
            debug("Call to update chunk(id = " + convert.to_string(cid) + ")");
            if(cid >= 0 && cid <= positive_crash_line / chunkWidth){
                if(!at_world->inchunklist(cid))
                    at_world->pushchunk(worldgenerator.generate_chunk(cid,0));
                else
                    at_world->getchunkiter(cid)->second.update();
            }
        }
        return 0;
    }
    int getcommandid(const std::string& input){
        for(int i = 0;i<command_list.size();++i){
            if(input == command_list[i].identifier)
                return i;
        }
        return -1;
    }
    block_t blockid(const std::string& inblock){
        for(long long i = 0;i < block_list.size();++i){
            if(inblock == block_list[i].universal_name)
                return block_t(i);
        }
        return id_block_empty;
    }
    basic_entity_id entityid(const std::string& inentity){
        for(long long i = 0;i < block_list.size();++i){
            if(inentity == entity_list[i].universal_name)
                return basic_entity_id(i);
        }
        return entity_void;
    }
    int itemid(const std::string& initem){
        long long ret = 0;
        for(auto&&i:items_list){
            if(i.universal_name == initem)
                return ret;
            ret++;
        }
        return -1;
    }
    template<class Predicator>
    bool predication_block(const world* inworld,const position& pos,Predicator predicate){
        return predicate(inworld->getblock(pos));
    }
    template<class Predicator>
    bool predication_block(const world* inworld,const position& pos1,const position& pos2,Predicator predicate){
        const position pos_start(std::min(pos1.x,pos2.x),std::min(pos1.y,pos2.y)),
                       pos_end(std::max(pos1.x,pos2.x),std::max(pos1.y,pos2.y));
        //std::cout << "Chunk [" << getcid(pos_start.x) << " to " << getcid(pos_end.x) << "] in list: " << inworld->inchunklist(getcid(pos_start.x)) << std::endl;
        for(long long x = 0;x <= pos_end.x - pos_start.x;++x){
            for(long long y = 0;y <= pos_end.y - pos_start.y;++y){
                //std::cout << "Block: " << inworld->getblock(pos_start.delta(x,y)) << " Predicate: "<< predicate(inworld->getblock(pos_start.delta(x,y))) << std::endl;
                if(!predicate(inworld->getblock(pos_start.delta(x,y))))
                    return false;
            }
        }
        return true;
    }
    int command_move(char input){
        input = towlower(input);
        short delta_x = 0,delta_y = 0;
        switch(input){
            case 'w':delta_x = 0;delta_y = -1;break;
            case 's':delta_x = 0;delta_y = +1;break;
            case 'a':delta_x = -1;delta_y = 0;break;
            case 'd':delta_x = +1;delta_y = 0;break;
        }
        block_t target_block = player.at_world->getblock(player.pos.delta(delta_x,delta_y));
        if(block_list[target_block].hastag(tag_through)){
            player.pos = player.pos.delta(delta_x,delta_y);
            return 1;
        }else if((input == 'a' || input == 'd') && gamerule.auto_jump){
            if(block_list[player.at_world->getblock(player.pos.delta(delta_x,delta_y - 1))].hastag(tag_through) && 
               block_list[player.at_world->getblock(player.pos.delta(0,delta_y - 1))].hastag(tag_through))
            player.pos = player.pos.delta(delta_x,delta_y - 1);
            return 1;
        }else
            return 0;
    
    }
    #define BLOCK_SET_SP_SIGN "SPECIAL_USE_BACKPACK"
    int command_set(char direction,long long distance,const std::string& inblock){
        block_t use_block = blockid(inblock);
        item pointat_item;
        if(distance > (gamerule.gamemode == gamemode_creative?16:4)){
            pushNewInfo("/set指令错误: 放置距离过远(" + convert.to_string(distance) + " > " + (gamerule.gamemode == gamemode_creative?"16":"4"));
            return 0;
        }
        if(inblock == BLOCK_SET_SP_SIGN && gamerule.gamemode == gamemode_survival){
            pointat_item = player.backpack.getitem(player.backpack_pointer);        
            if(isValidBlock(items_list[pointat_item.type].relate_block))
                use_block = items_list[pointat_item.type].relate_block;
        }
        if(isValidBlock(use_block)){
            long long delta_x = 0,delta_y = 0;
            switch(direction){
                case 'w':delta_x = 0;delta_y = 0 - distance;break;
                case 's':delta_x = 0;delta_y = distance;break;
                case 'a':delta_x = 0 - distance;delta_y = 0;break;
                case 'd':delta_x = distance;delta_y = 0;break;
                default:
                    pushNewInfo("/set指令错误 (未知的方向-\'" + convert.to_string(direction) + "\')");
                    return 0;
                break;
            }
            position track_start = player.pos.delta(delta_x == 0?0:delta_x / std::abs(delta_x),
                                                    delta_y == 0?0:delta_y / std::abs(delta_y));
            if(!predication_block(player.at_world,track_start,player.pos.delta(delta_x,delta_y),isthrough)){
                pushNewInfo("/set指令错误: 目标方向上有方块阻挡！");
                return 0;
            }
            
            if(gamerule.gamemode != gamemode_creative){
                if(player.at_world->getblock(player.pos.delta(delta_x,delta_y)) != id_block_air)
                    return 0;
                if(pointat_item.total > 0){
                    player.backpack.mergeitem(player.backpack_pointer,{pointat_item.type,pointat_item.total - 1});
                    if(pointat_item.total == 1)
                        player.backpack.mergeitem(player.backpack_pointer,{id_item_void,0});
                }
                else{
                    pointat_item.type = id_item_void;
                    player.backpack.mergeitem(player.backpack_pointer,{id_item_void,0});
                }
            }
            player.at_world->editblock(player.pos.delta(delta_x,delta_y),use_block);
            return 1;
        }else{
            if(gamerule.gamemode != gamemode_survival || inblock != "SPECIAL_USE_BACKPACK")
                pushNewInfo("/set指令错误 (未知的方块-\"" + inblock + "\")");
            return 0;
        }
    }
    int command_break(char direction,long long distance){
        long long delta_x = 0,delta_y = 0;
        if(distance > (gamerule.gamemode == gamemode_creative?16:4)){
            pushNewInfo("/break指令错误: 尝试破坏的距离过远(" + convert.to_string(distance) + " > " + (gamerule.gamemode == gamemode_creative?"16":"4"));
            return 0;
        }
        switch(direction){
            case 'w':delta_x = 0;delta_y = 0 - distance;break;
            case 's':delta_x = 0;delta_y = distance;break;
            case 'a':delta_x = 0 - distance;delta_y = 0;break;
            case 'd':delta_x = distance;delta_y = 0;break;
            default:
                pushNewInfo("/break指令错误 (未知的方向-\'" + convert.to_string(direction) + "\')");
                return 0;
            break;
        }
        int direction_x = delta_x > 0?1:(delta_x == 0?0:-1),
            direction_y = delta_y > 0?-1:(delta_y == 0?0:1);
        position track_start = player.pos,track_end = player.pos;
        if(std::abs(delta_x) > 1 || std::abs(delta_y) > 1){
            track_start = track_start.delta(direction_x,direction_y);
            track_end = track_start.delta(direction_x * (distance - 1),direction_y * (distance - 1));
        }
        if((std::abs(delta_x) > 1 || std::abs(delta_y) > 1) && !predication_block(player.at_world,track_start,track_end,isthrough)){
            pushNewInfo("/break指令错误: 目标方向上有方块阻挡！");
            return 0;
        }
        block_t target_block = player.at_world->getblock(player.pos.delta(delta_x,delta_y));
        if(block_list[target_block].hastag(tag_unbreakable) && gamerule.gamemode != gamemode_creative)
            return 0;
        if(block_itemid[target_block] != id_item_void){
            item tmp_item{block_itemid[target_block],1};
            player.backpack.pushNewItem(tmp_item);    
        }
        player.at_world->editblock(player.pos.delta(delta_x,delta_y),id_block_air);
        return 1;
    }
    int command_fill(const std::string& sx,const std::string& sy,
                     const std::string& ex,const std::string& ey,
                     const std::string& use_block){
        long long pos_sx = sx[0] == '~'?player.pos.x + convert.to_int(sx):convert.to_int(sx),
                  pos_ex = ex[0] == '~'?player.pos.x + convert.to_int(ex):convert.to_int(ex),
                  pos_sy = sy[0] == '~'?player.pos.y + (gamerule.reverse_y?-1:1) * convert.to_int(sy):actual_y(convert.to_int(sy)),
                  pos_ey = ey[0] == '~'?player.pos.y + (gamerule.reverse_y?-1:1) * convert.to_int(ey):actual_y(convert.to_int(ey));
        block_t use_blockid = blockid(use_block);
        if(!isValidBlock(blockid(use_block))){
            pushNewInfo("/fill指令错误 (未知的方块-\"" + use_block + "\")");
            return 0;
        }
        for(long long nx = std::min(pos_sx,pos_ex);nx <= std::max(pos_sx,pos_ex);nx++){
            for(long long ny = std::min(pos_sy,pos_ey);ny <= std::max(pos_sy,pos_ey);ny++)
                player.at_world->editblock({nx,ny},use_blockid);
        }
        return 1;
    }
    int command_tp(const std::string& tx,const std::string& ty){
        long long pos_tx = tx[0] == '~'?player.pos.x + convert.to_int(tx):convert.to_int(tx),
                  pos_ty = ty[0] == '~'?player.pos.y + (gamerule.reverse_y?-1:1) * convert.to_int(ty):actual_y(convert.to_int(ty));
        player.pos = {pos_tx,pos_ty};
        update_chunk(player.at_world,getcid(player.pos.x) - 2,getcid(player.pos.x) + 2);
        return 1;
    }
    int command_clone(const std::string& sx,const std::string& sy,
                      const std::string& ex,const std::string& ey,
                      const std::string& tx,const std::string& ty){
        long long pos_sx = sx[0] == '~'?player.pos.x + convert.to_int(sx):convert.to_int(sx),
                  pos_ex = ex[0] == '~'?player.pos.x + convert.to_int(ex):convert.to_int(ex),
                  pos_sy = sy[0] == '~'?player.pos.y + (gamerule.reverse_y?-1:1) * convert.to_int(sy):actual_y(convert.to_int(sy)),
                  pos_ey = ey[0] == '~'?player.pos.y + (gamerule.reverse_y?-1:1) * convert.to_int(ey):actual_y(convert.to_int(ey)),
                  pos_tx = tx[0] == '~'?player.pos.x + convert.to_int(tx):convert.to_int(tx),
                  pos_ty = ty[0] == '~'?player.pos.y + (gamerule.reverse_y?-1:1) * convert.to_int(ty):actual_y(convert.to_int(ty));                
        range xran = range(pos_sx,pos_ex),yran = range(pos_sy,pos_ey);
        if(xran.inrange(pos_tx) && yran.inrange(pos_ty)){
            pushNewInfo("/clone指令错误 (目标坐标在源区域内)");
            return 0;
        }//与源区域重叠
        else if(!inworld({pos_sx,pos_sy}) || !inworld({pos_ex,pos_ey}) || !inworld({pos_tx,pos_ty})){
            pushNewInfo("/clone指令错误 (区域坐标超出世界范围)");   
            return 0;
        }//超出世界范围
        else{
            for(long long tmpx = 0;tmpx <= xran.size();tmpx++){
                for(long long tmpy = 0;tmpy <= yran.size();tmpy++)
                    player.at_world->editblock(position(pos_tx,pos_ty).delta(tmpx,tmpy),player.at_world->getblock(position(pos_sx,pos_sy).delta(tmpx,tmpy)));
            }
            return 1;
        }
    }
    int command_gamemode(const std::string& inmode){
        if(inmode == "creative"){
            gamerule.gamemode = gamemode_creative;
            player.operate_permission = OPERATOR;
        }
        else if(inmode == "survival"){
            gamerule.gamemode = gamemode_survival;
            player.operate_permission = VISITOR;
        }
        else if(contain_onlydigit(inmode)){
            gamerule.gamemode = range(0,2).setin(convert.to_int(inmode));
            player.operate_permission = PERMISSION(gamerule.gamemode);
        }
        else{
            pushNewInfo("/gamemode指令错误 (未知的游戏模式-\"" + inmode + "\")");
            return 0;
        }
        return 1;
    }
    int command_backpack(){
        if(gameinfo.active_screen == INTERFACE_MAINSCREEN)
            gameinfo.active_screen = INTERFACE_BACKPACK;
        else if(gameinfo.active_screen == INTERFACE_BACKPACK){
            gameinfo.active_screen = INTERFACE_MAINSCREEN;
            player.operating_container_pos = void_position;
            crafting_table_ui.clear();
            simple_crafting_table_ui.clear();
        }
        else{
            gameinfo.active_screen = INTERFACE_MAINSCREEN;
            player.operating_container_pos = void_position;
            crafting_table_ui.clear();
            simple_crafting_table_ui.clear();
        }
        return 1;
    }
    int getgameruleid(const std::string& input){
        for(int i = 0;i < gamerule_identifier.size();++i){
            if(input == gamerule_identifier[i])
                return i;
        }
        return -1;
    }
    int get_vision_mode_id(const std::string& input){
        if(contain_onlydigit(input))
            return range(0,3).inrange(convert.to_int(input))?convert.to_int(input):0;
        else{
            if(input == vision_mode_identifier[0])
                return 0;
            else if(input == vision_mode_identifier[1])
                return 1;
            else if(input == vision_mode_identifier[2])
                return 2;
            else if(input == vision_mode_identifier[3])
                return 3;
            else
                return 0;
        }
    }
    int command_gamerule(const std::string& incommand){
        std::vector<std::string>argument_list = split(incommand,' ');
        int gameruleid = getgameruleid(argument_list[0]);
        if(gameruleid == -1){
                pushNewInfo("未知的游戏规则: " + (*argument_list.begin())
                           + "(第0字符至" + convert.to_string((*argument_list.begin()).length() - 1) + "字符)","命令解析器");
                pushNewInfo("命令不合法","命令解析器");
            return 0;
        }else if(argument_list.size() - 1 < gamerule_argnum[gameruleid]){
            pushNewInfo("该游戏规则的参数不足 (" + convert.to_string(argument_list.size() - 1) + "<" + convert.to_string(gamerule_argnum[gameruleid]) + ")","命令解析器");
            pushNewInfo("命令不合法","命令解析器");
            return 0;
        }else if(argument_list.size() - 1 > gamerule_argnum[gameruleid]){
            pushNewInfo("该游戏规则的参数过多 (" + convert.to_string(argument_list.size() - 1) + ">" + convert.to_string(gamerule_argnum[gameruleid]) + ")","命令解析器");
            pushNewInfo("命令不合法","命令解析器");
            return 0;
        }else;
        std::vector<short> gamerule_arglist;
        for(int j = 1;j < argument_list.size();++j){
            short tmp_type = 0;
            if(contain_onlydigit(argument_list[j]))//数字类型
                tmp_type = 0;
            else if(argument_list[j] == "true" || argument_list[j] == "false")
                tmp_type = 1;
            else if(argument_list[j].length() == 1)//字符类型
                tmp_type = 3;
            else
                tmp_type = 2;
            gamerule_arglist.push_back(tmp_type);
        }
        if(gamerule_argtype[gameruleid] != "n"){
            int start_char = argument_list[0].length()+1;
            bool flag_continue = false;
            for(int j = 0;j < gamerule_arglist.size();++j){
                if(gamerule_arglist[j] != (gamerule_argtype[gameruleid][j] - '0')){
                    if(gamerule_argtype[gameruleid][j] != '2'){
                        pushNewInfo("参数类型不符(第" + convert.to_string(start_char) + "至" + convert.to_string(start_char+argument_list[j].length()- 1) + "字符): 判定为["
                                   + command_argname[gamerule_arglist[j]] + "]类型,应当为[" + command_argname[gamerule_argtype[gameruleid][j] - '0'] + "]类型","命令解析器");
                        flag_continue = true;
                    }else
                        gamerule_arglist[j] = 2;//其他参数可以转换为字符串
                }
                start_char += argument_list[j].length() + 1;
            }
            if(flag_continue){
                pushNewInfo("/gamerule指令的参数不合法","命令解析器");
                return 0;
            }    
        }
        std::vector<long long> integer_arglist;
        std::vector<bool> boolean_arglist;
        std::vector<std::string> string_arglist;
        std::vector<char> character_arglist;
        for(int j = 0;j < gamerule_arglist.size();++j){
            switch(gamerule_arglist[j]){
                case 0:integer_arglist.push_back(convert.to_int(argument_list[j + 1]));break;
                case 1:boolean_arglist.push_back(argument_list[j + 1] == "true");break;//仅对true进行判别
                case 2:string_arglist.push_back(argument_list[j + 1]);break;
                case 3:character_arglist.push_back(argument_list[j + 1][0]);break;
                default:break;
            }
        }//最终将所有类型的参数放入各自类型的数组内
        std::string merge_gamerule = argument_list[0],merge_value;
    
        switch(gameruleid){
            case 0:merge_value = worldset.playername = string_arglist[0];break;
            case 1:merge_value = worldset.worldname = string_arglist[0];break;
            case 2:gamerule.vision_mode = get_vision_mode_id(string_arglist[0]);              merge_value = vision_mode_identifier[gamerule.vision_mode];break;
            case 3:gamerule.auto_jump = boolean_arglist[0];                                   merge_value = boolean_arglist[0]?"true":"false";break;
            case 4:gamerule.no_enter = boolean_arglist[0];                                    merge_value = boolean_arglist[0]?"true":"false";break;
            case 5:gamerule.respawn_point = position(integer_arglist[0],integer_arglist[1]);  merge_value = gamerule.respawn_point.to_string();break;
            case 6:gamerule.reverse_y = boolean_arglist[0];                                   merge_value = boolean_arglist[0]?"true":"false";break;
            case 7:gamerule.knowledge = boolean_arglist[0];                                   merge_value = boolean_arglist[0]?"true":"false";break;
            case 8:gamerule.auto_savefile = boolean_arglist[0];                               merge_value = boolean_arglist[0]?"true":"false";break;
            case 9:gamerule.longest_timeleap = integer_arglist[0];                           merge_value = convert.to_string(integer_arglist[0]);break;
            case 10:gamerule.command_replace = boolean_arglist[0];                            merge_value = boolean_arglist[0]?"true":"false";break;
            case 11:gamerule.maxinum_debuginfo = integer_arglist[0];                          merge_value = convert.to_string(integer_arglist[0]);break;
        }
        pushNewInfo("成功将gamerule." + merge_gamerule + "的值修改为 " + merge_value);
        return 1;
    }
    int command_testblock(const std::string& x,const std::string& y){
        long long pos_x = (x[0] == '~'?player.pos.x:0) + convert.to_int(x),
                  pos_y = y[0] == '~'?player.pos.y + (gamerule.reverse_y?-1:1)*convert.to_int(y):actual_y(convert.to_int(y));
        pushNewInfo("坐标" + position(pos_x,pos_y).to_string() + "的方块: " + block_list[player.at_world->getblock({pos_x,pos_y})].name);
        return 1;
    }
    int command_eat(){
        player.hunger+=5;
        return 1;
    }
    int command_setblock(const std::string& x,const std::string& y,const std::string& use_block){
        long long pos_x = (x[0] == '~'?player.pos.x:0) + convert.to_int(x),
                  pos_y = y[0] == '~'?player.pos.y + (gamerule.reverse_y?-1:1)*convert.to_int(y):actual_y(convert.to_int(y));
        block_t block_id = blockid(use_block);
        if(!inworld({pos_x,pos_y}) || !isValidBlock(block_id))
            return 0;
        else
            player.at_world->editblock({pos_x,pos_y},block_id);
        return 1;
    }
    int command_seed(){
        pushNewInfo("世界种子: " + convert.to_string(worldset.seed));
        return 1;
    }
    int command_biome(){
        pushNewInfo("当前群系: " + biome_list[worldgenerator.getbiome(getcid(player.pos.x))].name);
        return 1;
    }
    int command_give(const std::string& item_name,long long total){
        long long pushitem_id = itemid(item_name);
        if(pushitem_id != -1){
            if(total < 0){
                pushNewInfo("物品数量不合法(" + convert.to_string(total) + " < 0)");
                return 0;
            }
            item tmpitem = {item_t(pushitem_id),total};
            player.backpack.pushNewItem(tmpitem);
            return 1;
        }else{
            pushNewInfo("未知的物品: "+item_name);
            return 0;
        }
    }
    int command_throw(long long index){
        if(index > 0 && index <= 36)
            player.backpack.mergeitem(index - 1,{id_item_void,0});
        else{
            pushNewInfo("未知的背包位置: " + convert.to_string(index));
            return 0;
        }
        return 1;
    }
    int command_exchange(long long index1,long long index2){
        if(index1 <= 0 || index1 > 36 || index2 <= 0 || index2 > 36){
            pushNewInfo("未知的背包位置: " + convert.to_string(index1) + "/" + convert.to_string(index2));
            return 0;
        }
        player.backpack.exchangeitem(index1,index2);
        return 1;
    }
    int command_spawn(const std::string& type,const std::string& x,const std::string& y){
        basic_entity_id spawn_id = entityid(type);
        if(isValidEntity(spawn_id) == entity_void){
            pushNewInfo("尝试生成未知实体(\"" + type + "\"?)");
            return 0;
        }
        long long pos_x = (x[0] == '~'?player.pos.x:0) + convert.to_int(x),
                  pos_y = y[0] == '~'?player.pos.y + (gamerule.reverse_y?-1:1)*convert.to_int(y):actual_y(convert.to_int(y));
        position spawn_pos(pos_x,pos_y);
        if(!inworld(spawn_pos)){
            pushNewInfo("不能在世界外(坐标" + spawn_pos.to_string() + ")生成实体");
            return 0;
        }
        player.at_world->getchunkiter(getcid(spawn_pos.x))->second.addentity(entity(spawn_id,spawn_pos));
        return 1;
    }
    int command_damage(const std::string& x,const std::string& y,long long damage){
        long long pos_x = (x[0] == '~'?player.pos.x:0) + convert.to_int(x),
                  pos_y = y[0] == '~'?player.pos.y + (gamerule.reverse_y?-1:1)*convert.to_int(y):actual_y(convert.to_int(y));
        position find_pos(pos_x,pos_y);
        if(!inworld(find_pos)){
            pushNewInfo("不能在世界外(坐标" + find_pos.to_string() + ")攻击实体");
            return 0;
        }
        for(auto && i : player.at_world->getchunkiter(getcid(find_pos.x))->second.entity_list){
            if(i.pos == find_pos){
                i.health -= damage;
                return 1;
            }
        }
        return 0;
    }
    int command_dokill(const std::string& x,const std::string& y){
        long long pos_x = (x[0] == '~'?player.pos.x:0) + convert.to_int(x),
                  pos_y = y[0] == '~'?player.pos.y + (gamerule.reverse_y?-1:1)*convert.to_int(y):actual_y(convert.to_int(y));
        position find_pos(pos_x,pos_y);
        if(!inworld(find_pos)){
            pushNewInfo("不能在世界外(坐标" + find_pos.to_string() + ")击杀实体");
            return 0;
        }
        std::vector<entity>* tmp = &player.at_world->getchunkiter(getcid(find_pos.x))->second.entity_list;
        for(auto i = tmp->begin();i < tmp->end();++i){
            if(i->pos == find_pos){
                tmp->erase(i);
                return 1;
            }
        }
        return 0;
    }
    int command_chunkinfo(long long id){
        if(!inworld({id * chunkWidth,0})){
            pushNewInfo("不能检查世界外的区块(id = " + convert.to_string(id) + ")");
            return 0;
        }
        chunk* info = nullptr;
        bool is_in_chunklist = player.at_world->inchunklist(id);
        if(is_in_chunklist)
            info = &player.at_world->getchunkiter(id)->second;
        std::cout << std::endl << id << "号区块信息: " << std::endl;
        std::cout << "已生成: " << (is_in_chunklist?"是":"否") << std::endl;
        if(is_in_chunklist){
            std::cout << "区块号: " << id << std::endl
                      << "生物群系: " << biome_list[worldgenerator.getbiome(id)].name << std::endl
                      << "实体数量: " << info->entity_list.size() << std::endl
                      << "所属世界: " << info->related_world->type << std::endl;
        }
        PAUSE();
        return 1;
    }
    int command_exit(){
        std::cout << std::endl << "是否退出游戏?(0/1)";
        if(digitin() == 1){
            doclear();
            std::cout << std::endl << "自动保存存档" << std::endl;
            command_savefile(gameinfo.filename);
            printdebug();
            std::cout << "已退出游戏" << std::endl;
            exit(0);
        }
        else
            return 1;
    }
    std::string numpress_str(std::vector<block_t> input){
        std::string output_nps;
        long long npslen = input.size();
        block_t now_int = input[0];
        for(long long npsi = 0;npsi < npslen;npsi++){
            long long conti_num = 0;
            while(input[npsi] == now_int && npsi < npslen){
                conti_num++;
                npsi++;
            }
            output_nps += convert.to_string(now_int);
            if(conti_num>1)
                output_nps += ("*" + convert.to_string(conti_num));
            output_nps += "/";
            now_int = input[npsi];
            npsi--;
        }
        return output_nps;
    }//按连续数据压缩数组
    std::vector<block_t> depress_str(const std::string& input){
        std::vector<std::string>unit_depr = split(input,'/');
        std::vector<block_t> out_deprstr;
        for(long long depi = 0;depi < unit_depr.size();depi++){
            std::vector<std::string> part_unit_depr = split(unit_depr[depi],'*');
            if(part_unit_depr.size() > 1){
                for(long long deppi = 0;deppi < convert.to_int(part_unit_depr[1]);deppi++)
                    out_deprstr.push_back(block_t(convert.to_int(part_unit_depr[0])));
            }else
                out_deprstr.push_back(block_t(convert.to_int(part_unit_depr[0])));
        }
        return out_deprstr;
    }//解压数组
    std::string getchunkCode(const chunk& input){
        std::string output_gCC;
        output_gCC += (convert.to_string(input.getid()) + ":");//区块号
        std::vector<block_t> chunk_block;
        for(long long gcci = 0;gcci < worldMaxinumHeight * chunkWidth;gcci++)
            chunk_block.push_back(input.getblockindex(gcci));
        output_gCC += (numpress_str(chunk_block) + "$");
        for(auto && i : input.entity_list)
            output_gCC += (i.to_string() + "/");
        return output_gCC;
    }//获取区块储存码
    inline std::string bool_tostr(bool input){
        return input?"true":"false";
    }
    inline bool str_tobool(const std::string& input){
        return input == "true"?true:false;
    }
    void printfile(){
        std::cout << "#" << GameVersion;
        std::cout << "#" << gameinfo.game_time << "," << gameinfo.filename << "," << gameinfo.file_savetime;
        std::cout << "#" << player.pos.x << "," << player.pos.y << "," << player.health << "," << player.hunger << "," << player.oxygen;
        std::cout << "#" << bool_tostr(gamerule.auto_jump) << ","
                           << bool_tostr(gamerule.show_command_parse) << "," 
                           << bool_tostr(gamerule.no_enter) << "," 
                           << bool_tostr(gamerule.reverse_y) << "," 
                           << bool_tostr(gamerule.knowledge) << "," 
                           << bool_tostr(gamerule.auto_savefile) << "," 
                           << gamerule.gamemode << "," 
                           << gamerule.vision_mode << "," 
                           << gamerule.longest_timeleap << "," 
                           << gamerule.respawn_point.x << "," 
                           << gamerule.respawn_point.y;
        std::cout << "#";
        for(auto&&i:MainWorld.chunk_list){
            std::string chunkcode = getchunkCode(i.second);
            for(auto&&j:chunkcode){
                std::cout << j;
                if(online_xes)
                    usleep(100);
            }
            std::cout << "&";
            if(online_xes)
                usleep(10000);
        }
        std::cout << "#" << worldset.seed << "," 
                           << worldset.sea_level << ","
                           << worldset.world_spawn_type << ","
                           << worldset.world_single_biome << ","
                           << worldset.terrain_scale << ","
                           << worldgenerator.sample_terrain << ","
                           << worldgenerator.sample_biome << ","
                           << worldgenerator.sample_cave;
        std::cout << "#";
        for(auto&&i:MainWorld.merge_list)
            std::cout << i.first.x << "," << i.first.y << "," << i.second.block_id << "/";
        std::cout << "#";
        for(auto&&i:player.backpack.item_list)
            std::cout << i.to_stdstr() << "/";
        std::cout << std::endl;
    }
    bool available_version(const std::string& inver){
        for(auto&&i:available_versions){
            if(inver == i)
                return true;
        }
        return false;
    }
    std::string getFileSizeUnit(const std::string& filein){
        long long file_unitID = 0;
        double filelen = filein.length();
        while(filelen > 1024){
            file_unitID++;
            filelen /= 1024.0;
        }
        return convert.to_string(CUIL_std::half_precision(filelen)) + size_unit[file_unitID];
    }
    int ui_readfile(){
        gameinfo.file = "#Survive 1.5.2#570,a,1661537970#32752,370,20,20,20.00000#true,false,true,true,true,true,1,0,320,32768,384#2043:0*5987/13*3/0*12/13*5/0*11/13*2/9/13*2/0*11/13*2/9/13*2/0*12/16/9/0*5/16/0*2/16/0*2/3*4/4/3*11/4*33/1/4*12/1/4/1*2/4/1*2/4/1/4*2/1*3/21*4/1*11/21*5/1*10/21*6/1*10/21*6/1*10/21*6/1*11/21*5/1*13/21*3/22/1*13/21*2/22/1*15/22/1*144/21/1*14/21*2/1*262/22*2/1*66/22/1*12/22*6/1*11/22*6/1*10/22*6/1*10/22*6/1*9/22*7/1*10/22*6/1*10/22*6/1*9/22*7/1*9/22*7/1*9/22*7/1*9/22*7/1*10/22*6/1*10/22*5/1*11/22*3/1*555/22*2/1*5/22/1*7/22*4/1*3/22*2/1*8/22*2/1*3/22*3/1*7/21/22/21*2/1*11/21*5/1*8/21/1/21*4/1*7/21*10/1*6/21*10/1*6/21*10/1*6/21*9/1*7/21*9/1*11/21*5/1*14/21*2/1*288/22/1*14/22*3/1*12/22*2/1*51/8/1*6/8/1*3/8/1/8/1*3/8/1*3/8*2/1*3/8*4/1/8/1/8*2/1/8/1*2/8*5/1/8*6/1/8*8/1*2/8*22/$(4,32692,373,10,20,1,-)/&2044:0*5968/13*2/0*14/13*3/0*13/9/13*2/0*13/9/13*2/0*13/9/0*2/17/0*2/16*2/0*3/16*4/0/4/3*15/4*37/1/4*5/1*2/4*3/21/1*5/4/1*2/4/1*6/21/1*63/21/1*15/21*4/1*12/21*6/1*10/21*6/1*12/21*4/1*12/21*2/1*256/4/1*15/4*2/1*133/21*5/1*11/21*5/1*10/21*6/1*10/21*6/1*11/21*5/1*11/21*5/1*12/21*4/22/1*9/21*6/22*4/1*7/21*5/22*4/1*6/21*6/22*5/1*5/21*6/22*5/1*5/21*5/4/22*4/1*6/21*3/1*2/21/22*3/1*13/22*3/1*13/22*3/1*13/22*2/1*14/22*2/1*461/21/1*14/21*2/1*14/21*2/1*14/21*2/1*9/21*3/1/21*3/1*9/21*7/1*9/21*7/1*8/21*2/22*2/21*4/1*9/21*7/1*8/21*8/22/1*11/21/1*2/21/22*2/1*8/4*2/21/1*12/4*3/1/22*2/1*10/4*4/22*2/1*9/4*5/22*3/1*8/4*5/1*2/22/1*10/4*3/1*42/4*3/1*13/4/1*312/22/1*70/8/1*13/8*2/1*4/8*2/1*2/8*2/1*5/8*4/1*2/8*2/1*2/8*4/1/8/1*2/8*2/1*2/8*2/1*2/8*10/1/8/1/8*19/$(4,32704,372,10,20,1,-)/(4,32716,376,10,20,1,-)/(4,32719,377,10,20,1,-)/&2045:0*5895/13/0*12/13*7/0*2/13*3/0*3/13*13/0*3/13*13/0*3/13*3/9/13*9/0*3/13*4/9/13*8/0*3/13*4/9/13*8/0*3/13*4/9/13*8/0*3/13*4/9/13*8/0/16/0*2/16*3/9/0*5/16/17/16/3*7/4/3*8/4*35/1/4*7/1/4*4/1/4/1*2/4/1*39/22/1*10/22/1*3/22*2/1*10/22/1*3/22*4/1*11/22*6/1*10/22*6/1*12/22*4/1*13/22*3/1*95/21/1*14/21*2/1*14/21/1*208/21/1*27/21*4/1*11/21*5/1*2/21/1/21*3/1*2/21*39/1/21*15/1/21*13/1*3/21*8/1*8/21*9/1*7/21*8/1*8/21*5/1*11/21*4/1*12/21*4/1*12/21*4/1*12/21*4/1*12/21*3/1*541/21*2/1*11/21*9/1*4/21*13/1*3/21*22/1*2/21*27/22*2/21*6/22*6/21*2/22*2/21*6/22*3/21*5/22*2/21*3/1*2/21/1/22/21*8/1/21*5/1/21*9/1/21*2/1/21/1*2/21*10/1*6/21*10/1*6/21*10/1*5/21*11/1*4/21*12/1*3/21*13/1*3/21*13/1*3/21*13/1*4/21*12/1*4/21*11/1*6/21*10/1*5/21*12/1*3/21*13/1*3/21*12/1*5/21*10/1*6/21*10/1*8/21*7/1*11/21*3/1*33/21/1*12/21/1/21*2/1*12/21/1/21/1/21/1*14/21*4/1*9/21*7/1*9/21*7/1*9/21*7/1*9/21*7/1*9/21*7/1*9/21*7/1*9/21*7/1*9/21*7/1*9/21*7/1*7/21*9/1*6/21*10/1*7/21*9/1*4/8/1*3/21*6/8/21/1/8*4/1*3/8/21*2/8*2/21*3/1*4/8/1/8*4/21/8*2/21/8/21/8/1/8*7/1/8*4/21*2/8*16/$(4,32724,374,10,20,1,-)/(4,32726,371,10,20,1,-)/(5,32730,375,10,20,1,-)/(4,32735,377,10,20,1,-)/(4,32735,373,10,20,1,-)/&2046:0*5888/13/0*15/13*4/0*12/13*5/0*11/13*5/0*11/13*5/0*10/13/9/13*4/0*10/13/9/13*4/0*10/13/9/13*4/0*10/13/9/13*4/0*10/13/9/0*4/16/17/0/17/0*3/16/0/16*2/4/3*15/4*33/1/4/1/4*7/1*2/4/1/4/1*4/4/1*3/4/1*6/4/1*64/22/1*15/22*2/1*14/22*2/1*14/22*2/1*94/21/1*48/21*2/1*14/21*4/1*11/21*6/1*10/21*7/1*9/21*4/1*14/21*2/1*940/21*2/1*14/21*5/1*11/21*5/1*11/21*5/1*11/21*6/1*10/21*7/1*9/21*7/1*10/21/1/21*2/1*11/21*2/1*14/21/1*15/21/1*15/21*2/1*14/21*2/1*14/21*2/1*14/21*2/1*14/21*3/1*13/21*3/1*13/21*3/1*15/21*2/1*14/21*2/1*28/21/1*143/21*5/1*11/21*5/1*11/21*7/1*9/21*7/1*9/21*6/1*10/21*6/1*10/21*5/1*11/21*6/1*10/21*6/1*3/22*3/1*4/21*6/1/22*5/1*4/21*6/1*3/22*3/1*4/21*6/1*4/22/1*5/21*7/1*9/21*6/1*10/21*3/8/21/1/8*2/1*4/8/1*3/21*3/8/21/1/8/1*2/8/1*5/8/21/8*2/21*2/8/1*2/8*6/1/8*5/1*2/8*2/1/8*5/1/8*17/$&2047:0*5936/13*5/0*3/13*5/0*3/13*6/0/13*7/0*2/13*6/0/13*7/0*2/13*2/9/13*3/0/13*3/9/13*3/0*2/13*2/9/13*3/0/13*3/9/13*3/0*2/13*2/9/13*3/0/13*3/9/13*3/0*3/17/9/0*4/16*2/0/9/0*5/3*2/4/3*7/4/3*5/4*43/1/4*5/1*3/4*3/1*2/4/1*159/4*5/1*10/4*7/1*8/4*7/1*9/4*8/1*9/4*7/21/1*8/4*7/21/1*8/4*7/21/1*7/21/4*8/1*6/21*4/4*5/21/1*7/21*9/1*6/4*3/21*7/1*6/4*4/21*6/1*6/4*4/1*2/21*2/1*8/4*4/1*11/4*5/1*10/4/1/4*3/1*14/4/1*222/22/1/22*3/1*9/22*8/1*5/22*11/1*5/22*12/1*4/22*12/1*3/22*14/1*2/22*14/1*2/22*14/1*2/22*15/1/22*14/1*3/22*11/1*6/22*10/1*7/22*9/1*9/22*6/1*11/22*5/1*12/22*2/1*23/21/1*5/22/1*15/22*2/1*13/22*2/1*15/22*2/1*12/22*3/1*14/22*4/1*12/22*2/1*15/22/1*49/22*3/1*13/22*3/1*13/22*2/1*14/22/1*77/22/1*14/22*2/1*13/22*4/1*13/22*2/1*740/21/1*6/8/1/8/1*2/8/1/21*4/1*3/8/1*2/8/1/8/1/8/1/21*4/8/21/8/1*2/8*2/1*2/8*2/1/8*2/21/8*5/1/8*6/1/8/1/8*21/$(5,32754,373,10,20,1,-)/(4,32756,374,10,20,1,-)/(3,32767,377,10,20,1,-)/(4,32766,377,10,20,1,-)/(5,32753,377,10,20,1,-)/&2048:0*6048/3*3/0/16/0*3/16/17/0/16/0*4/4*3/3*13/4*32/1*4/4*7/1/4*4/1*6/4/1*7/4/1*106/22*2/1*2/22/1*11/22*4/1*13/22*2/1*132/21/1*126/22/1*14/22*2/1*14/22*2/1*14/22*2/1*13/22*3/1*8/22*8/1*6/22*10/1*6/22*10/1*4/22*12/1*4/22*12/1*4/22*12/1*6/22*10/1/22*2/1*4/22*8/1*2/22/1/22/1*2/22*7/1*8/22*7/1*5/22*10/1*11/22*4/1*19/21*3/1*12/21*4/1*12/21*4/1*12/21*4/1*12/21*4/1*12/21*4/1*13/21*3/1*13/21*3/1*14/21*2/1*13/21*3/1*13/21*3/1*12/21*4/1*11/21*5/1*11/21*5/1*9/21*7/1*9/21*7/1*10/21*6/1*9/21*7/1*9/21*7/1*13/21*3/1*14/21/1*144/22/1*55/21/1*15/21/1*14/21*3/1*13/21*3/1*13/21*3/1*12/21*4/1*11/21*5/1*10/21*7/1*10/21*5/1*10/21*5/1*12/21*3/1*13/21*2/1*63/21/1*15/21/1*63/21*8/1*9/21*10/1*7/21*9/1*7/21*9/1*8/21*8/1*6/21*10/1*5/21*11/1*5/21*11/1*7/21*9/1*10/21*6/1*10/21*6/1*10/21*6/1*9/21*7/1*8/21*8/1*7/21*9/1*6/21*10/1*6/21*10/1*4/21*12/1*5/21*11/1*6/21*10/1*11/21*5/1*129/8/1*11/8/1*2/8*3/1*3/8/1*3/8/1*3/8/1/8*3/1/8*2/1*3/8*2/1/8/1/8/1/8*3/1/8*28/$(5,32781,378,10,20,1,-)/&2049:0*5985/13*3/0*12/13*5/0*11/13*2/9/13*2/0*11/13*2/9/13*2/0*13/9/0*4/16/0*2/16*2/0/16*2/0/3*2/4/3*13/4*48/1/4*3/1*8/4/1*387/22/1*15/22/1*15/22*2/1*14/22*2/1*14/22*3/1*13/22*3/1*13/22*3/1*8/21*3/1*2/22*3/1*8/21*2/1*3/22*3/1*6/21*5/1*2/22*3/1*4/21*7/1*2/22*3/1*4/21*5/1*4/22/1*3/21*5/1*10/21*6/1*9/21*6/1*9/21*8/1*8/21*8/1*8/21*8/1*7/21*8/1*8/21*6/1*10/21*5/1*11/21*5/1*11/21*3/1*13/21*2/1*14/21*2/1*14/21*2/1*14/21*2/1*14/21*3/1*13/21*3/1*13/21*3/1*13/21*2/1*14/21*2/1*14/21*2/1*14/21*2/1*14/21*2/1*14/21*2/1*3/22/1*10/21*2/1*3/22/1*10/21/1*4/22*3/1*12/22*6/1*8/22*9/1*5/22*10/1*6/22*10/1*6/22*10/1*6/22*10/1*6/22*9/1*8/22*8/1*7/22*4/1*2/22/1*6/21*2/1/22*3/1*10/21*3/22*4/1*9/21*3/1*13/21*3/1*13/21*3/1*14/21*2/1*15/21/1*304/21*2/1*14/21*2/1*14/21*3/1*13/21*4/1*12/21*4/1*12/21*5/1*11/21*4/1*12/21*5/1*11/21*5/1*11/21*6/1*10/21*6/1*10/21*7/1*9/21*6/1*10/21*6/1/21*2/1*7/21*8/1*8/21*8/1*8/21*7/1*9/21*6/1*10/21*6/1*10/21*5/1*11/21*5/1*12/21*2/1/21/1/21/1*15/21/1*91/8/1/8/1*12/8*2/1*3/8*2/1*2/8/1*7/8/1*3/8*3/1/8*14/1*2/8*22/$(3,32790,378,10,20,1,-)/(3,32792,378,10,20,1,-)/&2050:0*5988/13*3/0*12/13*5/0*11/13*2/9/13*2/0*11/13*2/9/13*2/0*9/16/0*3/9/0*2/16*2/0*2/16/0/16/17/3*5/4/3*10/4*33/1/4*10/1/4*3/1*3/4/1/4*2/1/4*4/1/4/1/4/1*363/4*2/1*525/21*5/1*10/21*7/1*4/21*12/1*3/21*13/1*3/21*13/1*4/21*12/1*4/21*12/1*4/21*12/1*5/21*11/1*6/21*10/1*6/21*10/1*5/21*11/1*5/21*11/1*5/21*11/1*4/21*13/1*3/21*43/1/21*15/1/21*13/1*3/21*12/1*4/21*11/1*5/21*11/1*5/21*11/1*5/21*10/1*7/21*9/1*7/21*7/1*11/21*3/1*249/21/1*14/21*2/1*14/21*2/1*154/22*2/1/22*2/1*9/22*7/1*9/22*8/1*8/22*7/1*150/8/1*12/8/1/8*2/1/8/1*12/8/1*2/8*2/1/8/1/8*3/1/8*6/1/8*2/1*2/8*12/1/8*24/$(4,32805,373,10,20,1,-)/(4,32808,377,10,20,1,-)/&2051:0*6035/16*5/0*9/3*14/0/3/4*11/0*4/4*11/0*5/4*5/1/4*5/1*2/0*3/4/1/4/1*6/4/1*5/0/1*734/4*2/1*13/4*2/1*14/4*3/1*13/4*3/1*173/21/1*2/21/1*12/21*2/1*14/21*4/1*13/21*4/1*14/21*4/1*12/21*7/1*9/21*8/1*8/21*9/1*7/21*8/1*8/21*9/1*7/21*7/1*9/21*3/1*397/21*2/1*14/21*2/1*14/21*2/1*14/21*2/1*395/22/1*5/8/1*3/8/1/8/22/8*2/22*2/8/1*5/8/1/8*2/22/8/22*4/1/8*4/1/8/1/8*5/22/8*16/1/8*18/$&#8869311,384,0,-1,1.00000,0.00098,0.00098,0.00195#32702,374,13/32702,375,13/32702,376,13/32703,373,13/32703,374,13/32703,375,13/32703,376,13/#0*0/1*64/1*64/1*64/1*64/1*64/1*64/1*64/1*64/1*64/1*64/1*64/1*64/1*64/1*64/1*64/7*64/7*64/2*64/2*64/0*0/0*0/0*0/0*0/0*0/0*0/0*0/0*0/0*0/0*0/0*0/0*0/0*0/0*0/0*0/1*64/";
        if(gameinfo.file.length() == 0){
            std::cout << "您还未放入游戏存档！请检查位置并重新运行游戏。" << std::endl;
            PAUSE();
            return 0;
        }
        std::vector<std::string>file_part = split(gameinfo.file,'#');
        //游戏版本
        if(!available_version(file_part[0])){
            std::cout << "存档版本过高/过低，游戏无法解析！" << std::endl;
            PAUSE();
            return 0;
        }
        try{
            std::vector<std::string>file_gameinfo_part = split(file_part.at(1),',');
            gameinfo.game_time = convert.to_int(file_gameinfo_part.at(0));
            gameinfo.filename = file_gameinfo_part.at(1);
            gameinfo.file_savetime = convert.to_int(file_gameinfo_part.at(2));
        }catch(...){
            std::cout << "游戏信息部分缺少！解析失败" << std:: endl;
            PAUSE();
            return 0;
        }
        try{
            std::vector<std::string>file_playerinfo_part = split(file_part.at(2),',');
            player.pos.x = convert.to_int(file_playerinfo_part.at(0));
            player.pos.y = convert.to_int(file_playerinfo_part.at(1));
            player.health = convert.to_int(file_playerinfo_part.at(2));
            player.hunger = convert.to_int(file_playerinfo_part.at(3));
            player.oxygen = convert.to_float(file_playerinfo_part.at(4));
        }catch(...){
            std::cout << "玩家信息部分缺少！解析失败" << std:: endl;
            PAUSE();
            return 0;
        }
        try{
            std::vector<std::string>file_gamerule_part = split(file_part.at(3),',');
            gamerule.auto_jump = str_tobool(file_gamerule_part.at(0));
            gamerule.show_command_parse = str_tobool(file_gamerule_part.at(1));
            gamerule.no_enter = str_tobool(file_gamerule_part.at(2));
            gamerule.reverse_y = str_tobool(file_gamerule_part.at(3));
            gamerule.knowledge = str_tobool(file_gamerule_part.at(4));
            gamerule.auto_savefile = str_tobool(file_gamerule_part.at(5));
            gamerule.gamemode = convert.to_int(file_gamerule_part.at(6));
            gamerule.vision_mode = convert.to_int(file_gamerule_part.at(7));
            gamerule.longest_timeleap = convert.to_int(file_gamerule_part.at(8));
            gamerule.respawn_point.x = convert.to_int(file_gamerule_part.at(9));
            gamerule.respawn_point.y = convert.to_int(file_gamerule_part.at(10));
        }catch(...){
            std::cout << "游戏设置部分缺少！解析失败" << std::endl;
            PAUSE();
            return 0;
        }
        std::vector<std::string>file_gamemap_part;
        try{
            file_gamemap_part = split(file_part.at(4),'&');
            for(auto&&chunkcode:file_gamemap_part){
                std::vector<std::string>maininfo_chunk = split(chunkcode,'$');
                std::vector<std::string>gamemap_chunk = split(maininfo_chunk.at(0),':');
                chunk tmp_chunk = chunk(convert.to_int(gamemap_chunk.at(0)),&MainWorld);
                std::vector<block_t> depress_block_list = depress_str(gamemap_chunk.at(1));
                long long index = 0;
                for(auto&&i:depress_block_list){
                    if(index >= worldMaxinumHeight * chunkWidth)
                        break;
                    tmp_chunk.block[index] = isValidBlock(i)?i:id_block_air;
                    index++;
                }
                try{
                    std::vector<std::string>entity_map = split(maininfo_chunk.at(1),'/');
                    for(auto && i : entity_map){
                        i.erase(i.begin());
                        i.erase(i.end() - 1);
                        std::vector<std::string> entity_info = split(i,',');
                        tmp_chunk.entity_list.push_back(
                        entity(
                            basic_entity_id(convert.to_int(entity_info.at(0))),
                            {convert.to_int(entity_info.at(1)),convert.to_int(entity_info.at(2))},
                            &MainWorld,
                            convert.to_int(entity_info.at(3)),
                            convert.to_int(entity_info.at(4)),
                            convert.to_int(entity_info.at(5))
                        )
                        );
                    }
                }catch(...){}
                MainWorld.pushchunk(tmp_chunk);
            }
        }catch(...){
            std::cout << "游戏地图部分缺少！解析失败" << std::endl;
            PAUSE();
            return 0;
        }
        try{
            std::vector<std::string> file_worldset_part = split(file_part.at(5),',');
            worldset.seed = convert.to_int(file_worldset_part.at(0));
            worldset.sea_level = convert.to_int(file_worldset_part.at(1));
            worldset.world_spawn_type = basic_worldtype_id(convert.to_int(file_worldset_part.at(2)));
            worldset.world_single_biome = convert.to_int(file_worldset_part.at(3));
            worldset.terrain_scale = convert.to_float(file_worldset_part.at(4));
        }catch(...){
            std::cout << "世界生成设置部分缺少！解析失败" << std::endl;
            PAUSE();
            return 0;
        }
        try{
            std::vector<std::string> file_worldmerge_part = split(file_part.at(6),'/');
            for(auto&&i:file_worldmerge_part){
                std::vector<std::string> worldmerge_pack = split(i,',');
                MainWorld.merge_list.insert(std::make_pair<position,block_operation>({convert.to_int(worldmerge_pack[0]),convert.to_int(worldmerge_pack[1])},block_t(convert.to_int(worldmerge_pack[2]))));
            }
        }catch(...){
    
        }
        try{
            std::vector<std::string> backpack_info = split(file_part.at(7),'/');
            long long index = 0;
            for(auto && i : backpack_info){
                std::vector<std::string> tmp = split(i,'*');
                item Itmp = item(item_t(convert.to_int(tmp.at(0))),convert.to_int(tmp.at(1)));
                player.backpack.mergeitem(index,Itmp);
                index ++;
            }
        }catch(...){
            
        }
        std::cout << "存档解析成功，包含以下信息: " << std::endl;
        std::cout << "#游戏信息" << std::endl
                   << "    存档名称: " << gameinfo.filename << std::endl
                   << "    存档时间: " << gameinfo.file_savetime << std::endl
                   << "    存档大小: " << getFileSizeUnit(gameinfo.file) << std::endl;
        std::cout << "#玩家信息" << std::endl
                   << "    玩家名称: " << worldset.playername << std::endl
                   << "    玩家位置: " << player.pos.to_string() << std::endl
                   << "    玩家生命值: " << player.health << std::endl
                   << "    玩家饥饿值: " << player.hunger << std::endl
                   << "    玩家氧气值: " << player.oxygen << std::endl;
        std::cout << "#游戏设置: " << std::endl 
                   << "    世界名称: " << worldset.worldname << std::endl
                   << "    gamerule.auto_jump: " << bool_tostr(gamerule.auto_jump) << std::endl
                   << "    gamerule.show_command_parse: " << bool_tostr(gamerule.show_command_parse) << std::endl
                   << "    gamerule.no_enter: " << bool_tostr(gamerule.no_enter) << std::endl
                   << "    gamerule.reverse_y: " << bool_tostr(gamerule.reverse_y) << std::endl
                   << "    gamerule.knowledge: " << bool_tostr(gamerule.knowledge) << std::endl
                   << "    gamerule.auto_savefile: " << bool_tostr(gamerule.auto_savefile) << std::endl
                   << "    gamerule.gamemode: " << gamemode_name[gamerule.gamemode] << std::endl
                   << "    gamerule.vision_mode: " << gamerule.vision_mode << std::endl
                   << "    gamerule.longest_timeleap: " << gamerule.longest_timeleap << std::endl
                   << "    gamerule.respawn_point: " << gamerule.respawn_point.to_string() << std::endl;
        std::cout << "#世界生成信息: " << std::endl
                   << "    该存档包含了: " << MainWorld.chunk_list.size() << "个区块" << std::endl 
                   << "    生成种子: " << worldset.seed << std::endl
                   << "    海平面: " << worldset.sea_level << std::endl
                   << "    单一生物群系: " << (worldset.world_single_biome == -1?"无设置":biome_list[worldset.world_single_biome].name) << std::endl
                   << "    世界生成类型: " << worldset.world_spawn_type << std::endl
                   << "    地形缩放系数: " << worldset.terrain_scale << std::endl;
        PAUSE();
        return 1;
    }
    int command_savefile(const std::string& name){
        std::cout << std::endl;
        gameinfo.filename = name;
        gameinfo.file_savetime = time(0);
        printfile();
        PAUSE();
        return 1;
    }
    int gettimeid(const std::string& intime){
        for(int i = 0;i < time_total;++i){
            if(gametime_show[i] == intime)
                return i;
        }
        return -1;
    }
    int command_timeset(const std::string& arg1,const std::string& arg2){
        if(arg1 == "set"){
            int timeid = gettimeid(arg2);
            if(timeid != -1){
                switch(timeid){
                    case 0:gameinfo.game_time = 1;break;
                    case 1:gameinfo.game_time = 301;break;
                    case 2:gameinfo.game_time = 2101;break;
                    case 3:gameinfo.game_time = 2401;break;
                    case 4:gameinfo.game_time = 3901;break;
                    case 5:gameinfo.game_time = 4201;break;
                    case 6:gameinfo.game_time = 5701;break;
                }
            }else{
                gameinfo.game_time = convert.to_int(arg2);    
                gameinfo.game_time %= 6000;
                gameinfo.game_time++;
            }
        }else if(arg1 == "add"){
            gameinfo.game_time += convert.to_int(arg2);    
            gameinfo.game_time %= 6000;
            gameinfo.game_time++;
        }else;
        return 1;
    }
    int command_info(){
        std::cout << std::endl << std::endl;
        std::cout << "世界名称: " << worldset.worldname << std::endl;//世界名称
        std::cout << "玩家名称: " << worldset.playername << std::endl;//玩家名称
        std::cout << "玩家坐标: " << player.pos.to_string() << std::endl;//世界绝对坐标
        std::cout << "游戏模式: " << gamemode_name[gamerule.gamemode] << std::endl;//当前游戏模式
        std::cout << "玩家权限: " << permission_identifier[player.operate_permission] << std::endl;
        std::cout << "游戏版本: " << GameVersion << std::endl;//游戏版本
        std::cout << "游戏时间: " << gameinfo.game_time << " - " << gametime_intershow[getGameTimeID(gameinfo.game_time)] << std::endl;
        std::cout << "游戏已运行" << time(0) - game_starttime << "秒" << std::endl;
        std::cout << "存档名称: " << (gameinfo.filename == ""?"无":gameinfo.filename) << std::endl;//存档名
        std::cout << "存档保存时间: " << (gameinfo.file_savetime==0?"未保存":convert.to_string(gameinfo.file_savetime)) << std::endl;//存档保存时间
        std::cout << "存档大小: " << gameinfo.file.length() << getFileSizeUnit(gameinfo.file) << std::endl;//存档大小
        PAUSE();
        return 1;
    }//全部信息显示
    int command_chunkload(long long id){
        if(!player.at_world->inchunklist(id))
            player.at_world->pushchunk(worldgenerator.generate_chunk(id,0));
        else
            return 0;
        return 1;
    }
    int command_chunkreload(long long id){
        if(player.at_world->inchunklist(id))
            player.at_world->getchunk(id) = worldgenerator.generate_chunk(id,0);
        else
            return 0;
        return 1;
    }
    int command_chunkclear(long long id){
        if(player.at_world->inchunklist(id))
            player.at_world->getchunk(id) = chunk(0,player.at_world);    
        else    
            return 0;
        return 1;
    }
    int command_chunkcopy(long long id1,long long id2){
        if(player.at_world->inchunklist(id1) && player.at_world->inchunklist(id2))
            player.at_world->getchunk(id2).copy(player.at_world->getchunk(id1));
        else
            return 0;
        return 1;
    }
    int command_permission(const std::string& permission_in){
        if(permission_in == "VISITOR")
            player.operate_permission = VISITOR;
        else if(permission_in == "OPERATOR")
            player.operate_permission = OPERATOR;
        else if(permission_in == "TRUSTABLE")
            player.operate_permission = TRUSTABLE;
        else if(contain_onlydigit(permission_in))
            player.operate_permission = PERMISSION(std::min(convert.to_int(permission_in),3ll));
        else{
            pushNewInfo("未知的权限模式\"" + permission_in + "\"");
            return 0;
        }
        return 1;
    }
    int command_copyright(){
        doclear();
    std::cout << "    Survive——A fully console sandbox game based on C plus plus\n\
        Copyright (C) 2022  张歆睿\n\
        Distrubuted under GPL 3.0 License\n\
    \n\
        This program is free software: you can redistribute it and/or modify\n\
        it under the terms of the GNU General Public License as published by\n\
        the Free Software Foundation, either version 3 of the License, or\n\
        (at your option) any later version.\n\
    \n\
        This program is distributed in the hope that it will be useful,\n\
        but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\
        GNU General Public License for more details.\n\
    \n\
        You should have received a copy of the GNU General Public License\n\
        along with this program.  If not, see <http://www.gnu.org/licenses/>.\n\
    " << std::endl;
        PAUSE();
        doclear();
        return 1;
    }
    int command_use(char ch){
        position operate_pos = player.pos;
        player.operating_container_pos = void_position;
        switch(ch){
            case 'w':operate_pos = player.pos.delta(0,-1);break;
            case 'a':operate_pos = player.pos.delta(-1,0);break;
            case 's':operate_pos = player.pos.delta(0,+1);break;
            case 'd':operate_pos = player.pos.delta(+1,0);break;
            default:pushNewInfo("未知的操作字符 \'" + convert.to_string(ch) + "\'");
        }
        block_t operate_block = player.at_world->getblock(operate_pos);
        chunk* op_at_chunk = &(player.at_world->getchunkiter(getcid(operate_pos.x))->second);
        item& use_item = player.backpack.getitem(player.backpack_pointer);
        for(auto&& i : op_at_chunk->entity_list){
            if(i.pos == operate_pos){
                i.health -= items_list[use_item.type].health_damage;    
                if(items_list[use_item.type].use_type != TOOL)
                    use_item.damage -= 2;
                else
                    use_item.damage -= 1;
                return 1;
            }
        }//首先检查是否攻击实体
        if(block_list[operate_block].hastag(tag_interaction)){
            switch(operate_block){
                case id_block_crafting_table: gameinfo.active_screen = INTERFACE_CRAFTING_TABLE; break;
                case id_block_furnace: gameinfo.active_screen = INTERFACE_FURNACE; break;
                default: gameinfo.active_screen = INTERFACE_MAINSCREEN; break;
            }
            player.operating_container_pos = operate_pos;
            return 1;
        }//检查是否是可交互方块
        if(items_list[use_item.type].relate_block != id_block_empty && block_list[operate_block].hastag(tag_replaceable)){
            use_item.total--;
            if(use_item.total <= 0)
                use_item.type = id_item_void;
            player.at_world->editblock(operate_pos,items_list[use_item.type].relate_block);
        }//最后检查是否放置方块
        return 1;
    }
    int command_crash(){
        std::cout << "此操作将导致游戏崩溃。" << std::endl;
        std::cout << "是否继续操作？你的存档可能不会保留。 >>> ";
        if(datain(true))
            player.at_world->getchunkiter(positive_crash_line / chunkWidth + 1)->second.editblock(player.pos,id_block_empty);
        return 0;
    }
    int command_put(long long from_index,long long to_index,long long put_num = -1){
        container* from_container = &player.backpack;
        block_t find_block = player.at_world->getblock(player.operating_container_pos);
        if(gameinfo.active_screen != INTERFACE_BACKPACK && player.operating_container_pos != void_position && !block_list[int(find_block)].hastag(tag_interaction)){
            pushNewInfo("尝试操作方块不可交互");
            return 0;
        }
        auto check_operate_iter = map_block_interface.find(find_block);
        item* operate_item = nullptr;
        item* move_item = nullptr;
        if(gameinfo.active_screen != INTERFACE_BACKPACK && player.operating_container_pos != void_position && check_operate_iter == map_block_interface.end()){
            pushNewInfo("尝试交互方块无映射界面");
            return 0;
        }
        else{
            move_item = from_index > 0 && from_index <= player.backpack.max_size ? &player.backpack.getitem(from_index - 1) : nullptr;
            if(gameinfo.active_screen == INTERFACE_BACKPACK && player.operating_container_pos == void_position){
                operate_item = to_index > 0 && to_index <= simple_crafting_table_ui.set_size ? &simple_crafting_table_ui.material[to_index - 1] : nullptr;    
                simple_crafting_table_ui.check_inventory();
            }  
            else{
                switch(check_operate_iter->second){
                    case INTERFACE_CRAFTING_TABLE:
                        operate_item = to_index > 0 && to_index <= crafting_table_ui.set_size ? &crafting_table_ui.material[to_index - 1] : nullptr;
                        crafting_table_ui.check_inventory();                        
                    break;
                    case INTERFACE_FURNACE:
                        operate_item = to_index > 0 && to_index <= furnace_ui.set_size ? &furnace_ui.material[to_index - 1] : nullptr;
                    break;
                    default:
                        operate_item = nullptr;
                    break;
                }
            }
        }
        if(move_item == nullptr){
            pushNewInfo("错误的访问下标: " + convert.to_string(from_index));    
            return 0;
        }
        else if(operate_item == nullptr){
            pushNewInfo("错误的访问下标：" + convert.to_string(to_index));
            return 0;
        }
        else{
            if(put_num == -1){
                if(operate_item->type == move_item->type && move_item->type != id_item_void)
                    move_item->combine(*operate_item);
                else
                    std::swap(*move_item,*operate_item);
            }else{
                put_num = std::min(std::max(0ll,put_num),move_item->total);
                item tmp = move_item->total_change(put_num);
                operate_item->combine(tmp);    
                move_item->total -= put_num;   
                if(move_item->total <= 0)
                    move_item->type = id_item_void;
            }
            return 1;
        }
        return 1;
    }
    int command_remove(long long op_index,long long remove_num = -1){
        block_t find_block = player.at_world->getblock(player.operating_container_pos);
        if(gameinfo.active_screen != INTERFACE_BACKPACK && player.operating_container_pos != void_position && !block_list[int(find_block)].hastag(tag_interaction)){
            pushNewInfo("尝试操作方块不可交互");
            return 0;
        }
        auto check_operate_iter = map_block_interface.find(find_block);
        item* operate_item = nullptr;
        if(gameinfo.active_screen == INTERFACE_BACKPACK && player.operating_container_pos == void_position)
            operate_item = op_index > 0 && op_index <= simple_crafting_table_ui.set_size ? &simple_crafting_table_ui.material[op_index - 1] : nullptr;    
        else{
            switch(check_operate_iter->second){
                case INTERFACE_CRAFTING_TABLE:
                    operate_item = 0 < op_index && op_index <= crafting_table_ui.set_size ? &crafting_table_ui.material[op_index - 1] : nullptr;
                break;
                case INTERFACE_FURNACE:
                    operate_item = 0 < op_index && op_index <= furnace_ui.set_size ? &furnace_ui.material[op_index - 1] : nullptr;
                break;
                default:
                    operate_item = nullptr;
                break;
            }
        }
        if(operate_item != nullptr){
            if(remove_num == -1){
                player.backpack.pushNewItem(*operate_item);
                if(operate_item->total <= 0)
                    operate_item->type = id_item_void;
            }else{
                remove_num = std::min(std::max(0ll,remove_num),operate_item->total);
                item tmp = operate_item->total_change(remove_num);
                player.backpack.pushNewItem(tmp);
                operate_item->total -= remove_num;
            }
            return 1;
        }
        else
            return 0;
    }
    int command_get(long long get_total){
        block_t find_block = player.at_world->getblock(player.operating_container_pos);
        if(gameinfo.active_screen != INTERFACE_BACKPACK && player.operating_container_pos != void_position && !block_list[int(find_block)].hastag(tag_interaction)){
            pushNewInfo("尝试操作方块不可交互");
            return 0;
        }
        auto check_operate_iter = map_block_interface.find(find_block);
        item* operate_item = nullptr;
        std::vector<item>* operate_list = nullptr;
        if(gameinfo.active_screen == INTERFACE_BACKPACK && player.operating_container_pos == void_position){
            operate_item = &simple_crafting_table_ui.product;
            operate_list = &simple_crafting_table_ui.material;
        }else{
            switch(check_operate_iter->second){
                case INTERFACE_CRAFTING_TABLE:
                    operate_item = &crafting_table_ui.product;
                    operate_list = &crafting_table_ui.material;
                break;
                case INTERFACE_FURNACE:
                    operate_item = &furnace_ui.product;
                break;
                default:
                    operate_item = nullptr;
                break;
            }
        }
        long long actual_decrease = get_total;
        if(operate_list != nullptr){
            for(auto&& i : *operate_list){
                if(i.type != id_item_void)
                    actual_decrease = std::min(actual_decrease,i.total);
            }
            for(auto&& i : *operate_list){
                if(i.type != id_item_void)
                    i.total -= actual_decrease;
                if(i.total <= 0)
                    i.type = id_item_void;
            }
        }
        if(operate_item != nullptr){
            item tmp = operate_item->total_change(actual_decrease * operate_item->total);
            player.backpack.movein_item(tmp,actual_decrease);
        }
        else
            return 0;
        return 1;
    }
    int command_clear(){
        player.backpack = container();
        return 1;
    }
    std::string CONSTANT_replace(const std::string& instr){
        std::vector<std::string> words = split(instr,' ');
        for(int i = 0;i < words.size();++i){
            if(words[i] == "PCID")
                words[i] = convert.to_string(player.pos.x / chunkWidth);
            else if(words[i] == "WORLDHEIGHT")
                words[i] = convert.to_string(worldMaxinumHeight);
            else if(words[i] == "POSITIVE_XLIMIT")
                words[i] = convert.to_string(positive_crash_line);
            else if(words[i] == "MAX_INT")
                words[i] = "2147483647";
            else if(words[i] == "MAX_LONG_LONG")
                words[i] = "9223372036854775807";
            else if(words[i] == "MIN_INT")  
                words[i] = "-2147483648";
            else if(words[i] == "MIN_LONG_LONG")
                words[i] = "-9223372036854775808";
        }
        std::string out;
        for(int i = 0;i < words.size();++i){
            out += words[i];
            if(i < words.size() - 1)
                out += " ";
        }
        return out;
    }
    void command_parser(const std::string& command){
        debug("game_functional: Parse command[" + command + "]");
        std::vector<std::string> command_single = split(command,';');
        for(int i = 0;i < command_single.size();++i){
            debug("CommandParser: parse single command[" + command_single[i] + "]");
            if(gamerule.command_replace)
                command_single[i] = CONSTANT_replace(command_single[i]);
            std::vector<std::string> command_words = split(command_single[i],' ');
            int commandid = getcommandid(command_words[0]);
            std::string overall_argument;
            if(commandid == -1){
                pushNewInfo("未知的命令: " + (*command_words.begin()) + "(第0字符至" + convert.to_string((*command_words.begin()).length() - 1) + "字符)","命令解析器");
                pushNewInfo("命令不合法","命令解析器");
                continue;
            }else if(command_list[commandid].arg_num == -1){
                for(int j = 1;j < command_words.size();++j)
                    overall_argument += (command_words[j] + " ");
            }else if(command_words.size() - 1 < command_list[commandid].arg_num){
                if(command_words[0] == "/set" &&
                   gamerule.gamemode == gamemode_survival &&
                   command_words.size() == command_list[commandid].arg_num){
                }
                else if(command_words[0] == "/get" && command_words.size() == command_list[commandid].arg_num){ }
                else if(command_words[0] == "/remove" && command_words.size() == command_list[commandid].arg_num){ }
                else if(command_words[0] == "/put" && command_words.size() == command_list[commandid].arg_num){ }
                else{
                    pushNewInfo("命令参数不足 (" + convert.to_string(command_words.size() - 1) + "<" + convert.to_string(command_list[commandid].arg_num) + ")","命令解析器");
                    pushNewInfo("命令不合法","命令解析器");
                    continue;
                }
            }else if(command_words.size() - 1 > command_list[commandid].arg_num){
                pushNewInfo("命令参数过多 (" + convert.to_string(command_words.size() - 1) + ">" + convert.to_string(command_list[commandid].arg_num) + ")","命令解析器");
                pushNewInfo("命令不合法","命令解析器");
                continue;
            }else;
            if(player.operate_permission < command_list[commandid].permission){
                pushNewInfo("没有使用该命令的权限");
                continue;
            }
            std::vector<short> command_arglist;
            for(int j = 1;j < command_words.size();++j){
                short tmp_type = 0;
                if(contain_onlydigit(command_words[j]))//数字类型
                    tmp_type = 0;
                else if(command_words[j] == "true" || command_words[j] == "false" || 
                        command_words[j] == "True" || command_words[j] == "False" ||
                        command_words[j] == "TRUE" || command_words[j] == "FALSE"
                       )
                    tmp_type = 1;
                else if(command_words[j].length() == 1)//字符类型
                    tmp_type = 3;
                else
                    tmp_type = 2;
                command_arglist.push_back(tmp_type);
            }
            if(command_list[commandid].arg_type != "n"){
                int start_char = command_words[0].length() + 1;
                bool flag_continue = false;
                for(int j = 0;j < command_arglist.size();++j){
                    if(command_arglist[j] != (command_list[commandid].arg_type[j] - '0')){
                        if(command_list[commandid].arg_type[j] != '2'){
                                pushNewInfo("参数类型不符(第" + convert.to_string(start_char) + "至" + convert.to_string(start_char + command_words[j].length() - 1) + "字符): 判定为["
                                           + command_argname[command_list[commandid].arg_type[j]] + "]类型,应当为[" + command_argname[command_list[commandid].arg_type[j] - '0'] + "]类型","命令解析器");
                            flag_continue = true;
                        }else
                            command_arglist[j] = 2;//其他参数可以转换为字符串
                    }
                    start_char += command_words[j].length() + 1;
                }
                if(flag_continue){
                    pushNewInfo("命令不合法","命令解析器");
                    continue;
                }    
            }
            std::vector<long long>      integer_arglist;
            std::vector<bool>           boolean_arglist;
            std::vector<std::string>     string_arglist;
            std::vector<char>         character_arglist;
            for(int j = 0;j < command_arglist.size();++j){
                switch(command_arglist[j]){
                    case 0:integer_arglist.push_back(convert.to_int(command_words[j + 1]));break;
                    case 1:boolean_arglist.push_back(command_words[j + 1] == "true");break;//仅对true进行判别
                    case 2:string_arglist.push_back(command_words[j + 1]);break;
                    case 3:character_arglist.push_back(command_words[j + 1][0]);break;
                    default:break;
                }
            }//最终将所有类型的参数放入各自类型的数组内
            //按照命令类型，调用各自函数
            switch(commandid){
                case 0:case 1:case 2:case 3:command_move(command_words[0][0]);break;
                case 4:command_move(character_arglist[0]);break;
                case 5:
                    if(gamerule.gamemode != gamemode_survival)
                        command_set(character_arglist[0],integer_arglist[0],string_arglist[0]);
                    else
                        command_set(character_arglist[0],integer_arglist[0],BLOCK_SET_SP_SIGN);break;
                case 6:command_break(character_arglist[0],integer_arglist[0]);break;
                case 7:command_fill(string_arglist[0],string_arglist[1],string_arglist[2],string_arglist[3],string_arglist[4]);break;
                case 8:command_tp(string_arglist[0],string_arglist[1]);break;
                case 9:command_clone(string_arglist[0],string_arglist[1],string_arglist[2],string_arglist[3],string_arglist[4],string_arglist[5]);break;
                case 10:command_gamemode(string_arglist[0]);break;
                case 11:pushNewInfo("游戏的帮助请见Survive Wiki哦！\n网址: https://code.xueersi.com/home/project/detail?lang=code&pid=18357289&version=cpp&form=cpp&langType=cpp");break;
                case 12:command_backpack();break;
                case 13:command_gamerule(overall_argument);break;
                case 14:command_testblock(string_arglist[0],string_arglist[1]);break;
                case 15:
                    player.pos = playerborn(&MainWorld,gamerule.respawn_point);
                    pushNewInfo(worldset.playername+"清除了自己");
                break;
                case 16:command_eat();break;
                case 17:command_setblock(string_arglist[0],string_arglist[1],string_arglist[2]);break;
                case 18:command_seed();break;
                case 19:command_biome();break;
                case 20:pushNewInfo(overall_argument,worldset.playername);break;
                case 21:command_give(string_arglist[0],integer_arglist[0]);break;
                case 22:command_throw(integer_arglist[0]);break;
                case 23:command_savefile(string_arglist[0]);break;
                case 24:command_timeset(string_arglist[0],string_arglist[1]);break;
                case 25:command_info();break;
                case 26:case 27:case 28:
                case 29:case 30:case 31:
                case 32:case 33:case 34:player.backpack_pointer = command_words[0][0] - '1';break;
                case 35:player.backpack_pointer = player.backpack_pointer > 0 ? player.backpack_pointer - 1 : 8;break;
                case 36:player.backpack_pointer = player.backpack_pointer < 8 ? player.backpack_pointer + 1 : 0;break;
                case 37:command_exchange(integer_arglist[0],integer_arglist[1]);break;
                case 38:command_chunkload(integer_arglist[0]);break;
                case 39:command_chunkreload(integer_arglist[0]);break;
                case 40:command_chunkclear(integer_arglist[0]);break;
                case 41:command_chunkcopy(integer_arglist[0],integer_arglist[1]);break;
                case 42:command_permission(string_arglist[0]);break;
                case 43:command_copyright();break;
                case 44:doclear();printdebug();PAUSE();break;
                case 45:command_spawn(string_arglist[0],string_arglist[1],string_arglist[2]);break;
                case 46:command_damage(string_arglist[0],string_arglist[1],integer_arglist[2]);break;
                case 47:command_dokill(string_arglist[0],string_arglist[1]);break;
                case 48:command_chunkinfo(integer_arglist[0]);break;
                case 49:command_exit();break;
                case 50:case 51:case 52:case 53:command_use(command_words[0][1]);break;    
                case 54:command_crash();break;
                case 55:
                    if(integer_arglist.size() > 2)
                        command_put(integer_arglist[0],integer_arglist[1],integer_arglist[2]);
                    else
                        command_put(integer_arglist[0],integer_arglist[1]);
                break;
                case 56:
                    if(integer_arglist.size() > 1)
                        command_remove(integer_arglist[0],integer_arglist[1]);
                    else
                        command_remove(integer_arglist[0]);
                break;
                case 57:
                    if(integer_arglist.size() > 0)
                        command_get(integer_arglist[0]);
                    else
                        command_get(1);
                break;
                case 58:command_clear();break;
                default:
                break;
            }
        }
    }
    std::string getcommand(){
        std::string ret_command;
        char first_command = datain(false),tmp_first_command;
        tmp_first_command = tolower(first_command);
        if(
            (tmp_first_command == 'w' || tmp_first_command == 's' ||
             tmp_first_command == 'a' || tmp_first_command == 'd' ||
             tmp_first_command == 'e' || isdigit(tmp_first_command) || 
             tmp_first_command == 'r' || tmp_first_command == 'f'
             ) && gamerule.no_enter
        ){
            return convert.to_string(tmp_first_command);
        }else
            std::getline(std::cin,ret_command);
        return convert.to_string(first_command) + ret_command;
    }
    position playerborn(world* spawn_world,const position& spawn_pos){
        for(long long nx = spawn_pos.x - chunkWidth;nx < spawn_pos.x+chunkWidth;++nx){
            update_chunk(spawn_world,getcid(nx),getcid(nx));
            chunk* tmp_chunk = &(spawn_world->chunk_list.find(getcid(nx))->second);
            long long find_y = worldgenerator.find_first_not_block(tmp_chunk,nx,id_block_air);
            if(find_y == -1)
                continue;
            block_t top_block = spawn_world->getblock({nx,find_y});
            if(!block_list[spawn_world->getblock({nx,find_y-1})].hastag(tag_fluid)&&block_list[top_block].hastag(tag_through)){
                player.at_world = spawn_world;
                player.pos = position(nx,find_y - 1);
                player.oxygen = 20;
                player.health = 20;
                player.hunger = 20;
                return player.pos;
            }
        }
        player.pos = spawn_pos;
        player.oxygen = 20;
        player.health = 20;
        player.hunger = 20;
        player.at_world->editblock(spawn_pos,id_block_air);
        debug("game_setupinfo: player born at " + player.pos.to_string());
        return spawn_pos;
    }
    std::string setcolor_time(){
        return getGameTimeID(gameinfo.game_time) >= 5 ? text_white : text_dark;
    }
    void screen_print(){
        debug("game_ui: start rendering screen");
        update_nowsky_color();
        int vision_range_x = 16,vision_range_y = 16;
        switch(gamerule.vision_mode){
            case 1:vision_range_x = 32;vision_range_y = 32;break;
            case 2:vision_range_x = 32;vision_range_y = 16;break;
            case 3:vision_range_x = 64;vision_range_y = 64;break;
        }
        long long maxlen = 0;
        for(int i = 0;i < 9;++i){
            if(player.backpack.getitem(i).type != id_item_void)
                maxlen = std::max(maxlen,showlen(player.backpack.getitem(i).to_string()));
        }
        debug("game_ui: render entity");
        image_text entity_render_map(vision_range_y,vision_range_x);
        long long render_count = 0;
        for(long long tid = getcid(player.pos.x) - 2;tid <= getcid(player.pos.x) + 2;++tid){
            if(player.at_world->inchunklist(tid)){
                for(auto&& i : player.at_world->getchunkiter(tid)->second.entity_list){
                    if(i.type != entity_player){
                        render_count++;
                        debug("game_ui: render entity(" +convert.to_string(render_count) + " in all): pos at " + i.pos.to_string());
                        debug("game_ui: render entity(at screen) pos at: " + position(i.pos.x - player.pos.x + vision_range_x / 2,i.pos.y - player.pos.y + vision_range_y / 2).to_string());
                        entity_render_map.imgcover(entity_list[i.type].img,i.pos.x - player.pos.x + vision_range_x / 2,i.pos.y - player.pos.y + vision_range_y / 2,pixel_black);
                    }
                }
            }
        }
        // entity_render_map.setspeed(200);
        // entity_render_map.show(true);
        debug("game_ui: rendered " + convert.to_string(render_count) + "entity");
        if(maxlen > 0)
            maxlen+=2;
        std::cout << "┏━";
        for(int i = 0;i < vision_range_x * 2 + maxlen + (maxlen > 0?4:0);++i)
            std::cout << "━";
        std::cout << "┓" << std::endl;
        std::string void_line1,void_line2;
        if(maxlen > 0){
            for(long long tmp = 0;tmp < maxlen - 1;++tmp){
                void_line1 += "━";
                void_line2 += " ";
            }
        }
        for(long long j = player.pos.y - vision_range_y / 2;j <= player.pos.y + vision_range_y / 2 - (vision_range_y%2 == 0?1:0);++j){
            block_t lastblock = id_block_empty;
            std::string print_out = "┃ ";
            for(long long i = player.pos.x - vision_range_x / 2;i <= player.pos.x + vision_range_x / 2 - (vision_range_x%2 == 0?1:0);++i){
                long long render_x = i - player.pos.x + vision_range_x / 2,
                          render_y = j - player.pos.y + vision_range_y / 2;
                block_t nowblock = player.at_world->getblock({i,j});
                pixel_text tmppix = entity_render_map.get(render_x,render_y);
                std::string add_str = "  ",background_str = "";
                if(i == player.pos.x && j == player.pos.y){
                    add_str = ((block_list[nowblock].transparent ? now_sky_color.make_show_RGB() : block_list[nowblock].color.make_show_RGB()) + setcolor_time() + "！");
                    lastblock = id_block_empty;
                }//玩家单独处理
                else if(tmppix.pix != pixel_white || tmppix.text != "  "){
                    if(nowblock == id_block_air)
                        background_str = now_sky_color.make_show_RGB();
                    else
                        background_str = block_list[nowblock].transparent ? now_sky_color.make_show_RGB() : block_list[nowblock].color.make_show_RGB();
                    if(tmppix.pix == pixel_white && tmppix.text != "  ")
                        add_str = (background_str + setcolor_time() + tmppix.text);
                    else if(tmppix.pix != pixel_white)
                        add_str = (tmppix.pix.make_show_RGB() + "  ");
                    else;
                    lastblock = id_block_empty;
                }//实体部分
                else if(isValidBlock(nowblock) && nowblock != lastblock){
                    if(block_list[nowblock].transparent)
                        add_str = (now_sky_color.make_show_RGB() + block_list[nowblock].color.text);
                    else
                        add_str = block_list[nowblock].color.pix.make_show_RGB() + block_list[nowblock].color.text;
                    if(block_list[nowblock].color.text != "  ")
                        lastblock = id_block_empty;
                    else
                        lastblock = nowblock;
                }//方块处理
                else
                    add_str = "  ";//输出优化或者不满足任何一个分类
                #ifdef __hasPrintSpeedLimit
                    usleep(800);
                #endif
                print_out += add_str;
            }
            std::cout << "\r" << print_out << _CLEAREFFECT_STR << "┃ ";
            // \r是为了回到开头输出以覆盖连续输入的按键型命令
            long long backpack_index = j - player.pos.y + vision_range_y / 2;
            if(maxlen > 0){
                if(backpack_index == player.backpack_pointer)
                    std::cout << " > ";
                else if(backpack_index == 9)
                    std::cout << "━━━";
                else
                    std::cout << "   ";
            }
            if(backpack_index < 9 && player.backpack.getitem(backpack_index).type != id_item_void){
                debug("game_functional: show item(info as " + player.backpack.getitem(backpack_index).to_stdstr() + ")");
                std::cout << str_setw(maxlen - 2,player.backpack.getitem(backpack_index).to_string()) << " ┃" << std::endl;
            }
            else if(maxlen > 0){
                if(backpack_index == 9)
                    std::cout << void_line1 << "┃" << std::endl;
                else
                    std::cout << void_line2 << "┃" << std::endl;
            }
            else 
                std::cout << std::endl;
        }
        std::cout << "┗━";
        for(int i = 0;i < vision_range_x * 2 + maxlen + (maxlen > 0?4:0);++i)
            std::cout << "━";
        std::cout << "┛" << std::endl;
    }
    TIME getGameTimeID(long long realtime){
        long long roundtime = realtime % 6000 + 1;
        if(0 <= roundtime && roundtime < 300)
            return SUNRISE;
        else if(300 <= roundtime && roundtime < 2100)
            return DAY;
        else if(2100 <= roundtime && roundtime < 2400)
            return NOON;
        else if(2400 <= roundtime && roundtime < 3900)
            return AFTERNOON;
        else if(3900 <= roundtime && roundtime < 4200)
            return SUNSET;
        else if(4200 <= roundtime && roundtime < 5700)
            return NIGHT;
        else
            return MIDNIGHT;
    }
    pixel update_nowsky_color(){
        switch(getGameTimeID(gameinfo.game_time)){
            case SUNRISE:    return t256[sunrise_color[(gameinfo.game_time%6000) * 11 / 300]];       break;
            case DAY:        return pixel(127,255,255);                                              break;
            case NOON:       return t256[noon_color];                                                break;
            case AFTERNOON:  return t256[afternoon_color];                                           break;
            case SUNSET:     return t256[sunset_color[(gameinfo.game_time%6000 - 3900) * 9 / 300]];  break;
            case NIGHT:      return t256[night_color[(gameinfo.game_time%6000 - 4200) / 375]];       break;
            case MIDNIGHT:   return t256[midnight_color[(gameinfo.game_time%6000 - 5700) / 50]];     break;
        }
        return pixel(0,255,255);
    }
    inline void update_time(long long t){
        gameinfo.game_time += std::min(5 + int((time(0) - t) * 20),int(gamerule.longest_timeleap));
    }
    void ui_gamemain(){
        doclear();
        debug("game_ui: print gamemain UI");
        if(gameinfo.active_screen == INTERFACE_MAINSCREEN)
            screen_print(); 
        else if(gameinfo.active_screen == INTERFACE_BACKPACK){
            simple_crafting_table_ui.check_inventory();
            simple_crafting_table_ui.show();
            std::cout << std::endl;
            player.backpack.print(3);
        }
        else if(gameinfo.active_screen == INTERFACE_CRAFTING_TABLE){
            crafting_table_ui.check_inventory();
            crafting_table_ui.show();
            player.backpack.print(3);
        }
        else if(gameinfo.active_screen == INTERFACE_FURNACE){
            furnace_ui.show();
            player.backpack.print(3);
        }
        else;
        std::cout << "┃ " << str_rsetw(16,"生命值: " + convert.to_string(player.health)) << str_rsetw(16,"饥饿值: " + convert.to_string(player.hunger)) << std::endl;
        if(player.oxygen < 20 && gamerule.gamemode != gamemode_creative)
            std::cout << "┃ " << str_rsetw(32,"氧气值: " + convert.to_string(player.oxygen,1)) << "┃" << std::endl;
        std::cout << "┃ " << str_rsetw(16,"x:" + convert.to_string(player.pos.x) + "  y:" + convert.to_string(actual_y(player.pos.y))) << str_rsetw(16,"游戏模式: " + gamemode_name[gamerule.gamemode]) << std::endl;
        while(!info_list.empty()){
            std::cout << "┃ " << info_list.front().deliverer << ": " << info_list.front().content << std::endl;
            info_list.pop();
        }
        std::cout << "┃ 命令>>>";
        
    }
    void print_gamelogo(){
        doclear();
        image logo(17,17);
        logo.line(11,0,4,4,pixel{232,232,0});
        logo.line(6,16,13,12,pixel{232,232,0});
        logo.line(13,12,4,4,pixel{232,232,0});
        logo.circle(8,8,4,pixel{192,255,255});
        logo.circle(8,8,3,pixel{128,255,255});
        pixel left_green{0,240,0},right_blue{0,128,240};
        logo.line(1,4,1,9,left_green);
        logo.line(2,7,2,10,left_green);
        logo.edit(2,10,left_green);
        logo.edit(3,10,left_green);
        logo.line(3,11,5,11,left_green);
        logo.line(4,12,7,12,left_green);
        logo.line(10,4,13,4,right_blue);
        logo.line(12,5,14,5,right_blue);
        logo.line(13,6,15,6,right_blue);
        logo.line(15,7,15,12,right_blue);
        logo.line(14,6,14,9,right_blue);
        logo.circle(8,8,2,pixel_cyan);
        logo.setspeed(1e+308);
        logo.show();
    }
    void show_check_gamerun(){
        print("系统检查：",printformat,false);
        print("| -- CUIL库自检：",printformat,false);
        print("|      O -- CUIL版本符合要求：      " + make_shapebool(CUIL_VERSIONINFO >= REQUIRE_CUIL_VERSION),printformat,false);
        print("| -- Survive运行自检：",printformat,false);
        print("|      | -- 游戏版本：" + GameVersion,printformat,false);
        print("|      | -- 适用于在线版：          " + make_shapebool(online_xes),printformat,false);
        print("|      O -- CUIL已向上兼容",printformat,false);
        print("O      ",printformat,false);
        print("如果你认为这会影响你的游戏，请询问作者",printformat,false);
        print("注：不接受非正式版本的询问",printformat,false);
        print("我准备好开始游戏了！ (0/1)>>> ",printformat,false,5,false);
    }
    void game_startui(){
        print_gamelogo();   
        sleep(2);
        doclear();
        show_check_gamerun();
        if(digitin() == 0)
            exit(0);
        doclear();
        usleep(500000);
        print(italic + "欢迎来到Survive！");
        PAUSE();
        doclear();
        std::cout << R"(
         ______________
        /___________  /
                   / /
                  / /
       __________/ /
      / __________/
     / /
    / /
   / /__________
  /____________/
)" << std::endl;
        print(italic + "Survive游戏发布2周年纪念");
        print(italic + "2020/08/26 - 2022/08/26");
        PAUSE();
        doclear();
        std::cout << "Survive 1.5.2———合成与创造\n\
0.游戏二周年！！！！！\n\
    2年风风雨雨，从最初的0.0.1，到一周年1.5.0，再到1.5.1与1.5.2，这一年来的每一个版本更新都极为重磅！1.5.2相较于1.5.1新增了700行源码，1.5.0.1开始的10个次版本更新，将游戏的整体水平提升了一大截！\n\
    感谢各位对于Survive项目的支持，你们的热情让游戏成为了全社区最强大的C++沙盒游戏！\n\
    游戏总计代码行数达到了6100+行，相较于1.5.1单次增加800行！\n\
1.游戏内容\n\
    全方位的物品系统加入！\n\
    你可以在背包界面(输入e打开)找到简易工作台，通过/put放入采集到的木头后，你就可以用木板合成工作台！\n\
    在工作台上，你可以获得游戏绝大部分的工具与物品，方块等！\n\
2.指令\n\
    加入了如下指令:\n\
    ·   /w，/a，/s，/d\n\
        是交互的基础指令，相较于移动指令，加入了/前缀以区分\n\
        w,a,s,d的含义与移动相同，交互指令会尝试进行如下操作:\n\
        1.当前方块上存在实体，攻击\n\
        2.当前方块为可交互方块，交互\n\
        3.当前方块是可以被替换成其他方块的（如空气），尝试放置背包快捷栏所对应的方块\n\
    ·   /exit <无参数> \n\
        输入该指令以退出游戏，在退出游戏前，你将得到当前游戏下的存档与最后的调试信息\n\
        无权限要求(权限为VISITOR级别)\n\
    ·   /crash <无参数> \n\
        输入该指令以从底层方面令游戏崩溃，可能不会触发游戏的崩溃保护机制，请谨慎使用\n\
        权限要求：TRUSTABLE\n\
    ·   /put <背包内物品下标> <容器内顺序下标> <可选：放入物品的数量>\n\
        输入该指令，你可以将指定数量（如果未指定，则默认全部放入）的背包物品放入一个交互界面或容器内，是物品系统的基础指令之一\n\
        无权限要求(权限为VISITOR级别)\n\
    ·   /remove <容器内顺序下标> <可选：移出物品的数量>\n\
        输入该指令，你可以从容器或交互界面中拿出指定数量的物品（如果未指定数量，默认全部拿出）\n\
        无权限要求(权限为VISITOR级别)\n\
    ·   /get <可选：获取数量>\n\
        输入该指令，在当前UI拥有“产物”这一概念的情况下（如工作台有合成产物），获得指定数量的物品\n\
        对于工作台，如果一次合成能得到多个物品，则/get N得到的物品数等于N * 单次合成得到的物品数量\n\
        未指定获取数量则默认为1\n\
        由于游戏不具备“掉落物”等物品暂存的概念，/get指令获得的物品若超出背包空间，则不会保留，在背包空间不足的情况下谨慎使用\n\
        无权限要求(权限为VISITOR级别)\n\
    ·   /clear <无参数>\n\
        清空玩家背包\n\
        权限要求：OPERATOR\n\
3.底层\n\
    ·   存档结构\n\
        新增存档附加区#9，存储玩家背包信息\n\
        新增存档-区块信息附加区#1，存储实体信息\n\
        对于在生成后未修改的区块，会以一个'U'代替地形信息，实体信息存储不变\n\
    ·   对先前代码的修订与增补\n\
4.功能\n\
    ·   加入预处理指令选项\n\
        在\"创建新世界 - 预处理指令\"选项内，你可以输入指令组，以在进入世界前直接执行\n\
        例如，如果你将预处理指令设定为/gamemode 1，则在游戏一开始时，就会执行该指令，将你的游戏模式变为创造模式，适合调试过程中的使用\n\
5.其他\n\
    ·   修复了已知bug\n\
    " << std::endl;
    PAUSE();
        doclear();
    }
    void api_addblock(const std::string& name,const std::string& universal_name,
                      const std::set<basic_tag_id>& tags,
                      const pixel_text& color){
        block_list.push_back({name,universal_name,color,tags});
    }
    bool str_contain(const std::string& input,char testchar){
        for(auto&&i : input){
            if(i == testchar)
                return true;
        }
        return false;
    }
    void api_merge_command_identifier(const std::string& identifier,int index){
        if(str_contain(identifier,' '))
            return ;
        else
            command_list.at(index).identifier = identifier;        
    }
    void exit_debug(){
        std::cerr << "游戏异常退出，以下是游戏最后输出的日志：" << std::endl;
        printdebug();
    }
}//namespace survive结束
using namespace survive;

void article_block_air(){
    print("方块——空气\n");
    print("“如果你认为蓝天上没有任何方块，那就错了！空气无处不在的充斥着整个世界，并让蓝天有了色彩的轮回。”————Pasy");
    print("\n加入游戏时间：2020/08/26  v0.0.1");
    print("方块id: 0");
    print("标准名称: air");
    print("颜色: \033[48;2;0;255;255m  \033[m");
    print("拥有tag: through,replaceable");
    print("\n    空气被定义为：任何无实体方块区域的填充方块。");
    print("    空气是玩家之所以能够活动的基础，玩家的任何行为都与空气有关，如行走，下坠。");
    print("    空气没有一个固定的颜色，天空的颜色本质是空气的颜色，空气方块的颜色就能反映当前的时间————在地下，你可以直接通过背后矿道的空气颜色来判断时间。");
    print("    空气是整个世界最常见的方块，占据了整个世界的60%以上。");
    print("    玩家的/set与/break指令其实都是对于空气方块的操作，/set指令的本质是将一个非实体方块替代为指定方块，而/break指令的本质是将目标方块替换为空气。");
    print("    空气在最初的版本中是全黑的，1.5.0则变为了蓝色，直到1.5.0.5时间系统正式加入后，空气才变成了如今变化的彩色。");
}
void article_block_stone(){
    print("方块——石头\n");
    print("“石头，世界的基础，游戏的第一个方块，你可以在世界的任何地方见到它”————Pasy");
    print("\n加入游戏时间：2020/08/26  v0.0.1");
    print("方块id: 1");
    print("标准名称: stone");
    print("颜色: \033[48;2;192;192;192m  \033[m");
    print("拥有tag: ore_replaceable");
    print("\n    石头是任何一个正常世界中最常见的方块，仅次于空气。");
    print("    石头同时是最古老的实体方块，游戏的第一个版本中，石头就以一个“O”的形式出现，可以被玩家放置，摧毁。");
    print("    石头最初是以层叠形式“铺”在世界上的（该类知识请移步“世界生成”页面），在版本迭代中，石头被定义为：任何海平面及地平线下空气方块的替代。");
    print("    这也就导致了石头成了整个世界最常见的实体方块，即使是有少量花岗岩和石灰岩掺杂在其中，石头仍然是整个世界的基础。");
}
void article_block_cobblestone(){
    print("方块——圆石\n");
    print("“和石头一起诞生的方块，但到游戏一周年才正式启用”————Pasy");
    print("\n加入游戏时间：2020/08/26  v0.0.1");
    print("方块id: 2");
    print("标准名称: cobblestone");
    print("颜色: \033[48;2;128;128;128m  \033[m");
    print("拥有tag: 暂无");
    print("\n    圆石事实上在世界中很少见，它只会生成在岩浆海的底部。");
    print("    圆石的颜色是石头的加深，这是为了体现其“裂纹”的形态————圆石的设计初衷是作为“裂纹石头”出现的，但由于古早版本并未有设计好的世界生成系统，在生成中通常只会有石头。");
}
void article_block_grass(){
    print("方块——草方块\n");
    print("“这是承载自然与生命气息的方块”————Pasy");
    print("\n加入游戏时间：2020/08/26  v0.0.1");
    print("方块id: 3");
    print("标准名称: grass");
    print("颜色: \033[48;2;118;254;0m  \033[m");
    print("拥有tag: plant");
    print("\n    草方块自然生成在大部分生物群系中，从平原到繁茂高原，草方块总是透露着鲜艳的绿色。");
    print("    草方块与泥土是目前唯二能生成植物的方块，这使得植被也通常随草方块的存在与否而变化。");
}
void article_block_dirt(){
    print("方块——泥土\n");
    print("“默默承担着生命的重力”————Pasy");
    print("\n加入游戏时间：2020/08/26  v0.0.1");
    print("方块id: 4");
    print("标准名称: dirt");
    print("颜色: \033[48;2;128;255;0m  \033[m(1.3.3至1.5.0.8)  \033[48;5;52m  \033[m(1.5.0.9以后)");
    print("拥有tag: plant");
    print("\n    与圆石一样，泥土直到1.5.0才正式作为平原等群系的次表层方块生成，在此之前，地表方块只有草方块一种。");
    print("    泥土会在树木底部生成————任何一棵树的树干底都将被自动替换为泥土。");
}
void article_block_barrier(){
    print("方块——屏障\n");
    print("“不可逾越的威严”————Pasy");
    print("\n加入游戏时间：2020/08/26  v0.0.1");
    print("方块id: 5");
    print("标准名称: barrier");
    print("颜色: \033[48;2;128;64;192m  \033[m(1.3.3至1.5.0.8)  \033[48;2;147;112;219m  \033[m(1.5.0.9以后)");
    print("拥有tag: unbreakable");
    print("\n    屏障不会自然生成，在这里得区分是自然地在世界上生成，事实上屏障会作为阻挡玩家超出世界范围的限制，出现在x<0与x>9223372036854757775的地区。");
    print("    边界屏障会在理论上无限延伸，该知识点详见：世界生成————世界边界");
}
void article_block_water(){
    print("方块——水");
    print("“润物细无声”————Pasy");
    print("\n加入游戏时间：2020/08/26  v0.0.1");
    print("方块id: 6");
    print("标准名称: water");
    print("颜色: \033[48;2;0;128;255m  \033[m");
    print("拥有tag: fluid,oxygen,through,replaceable");
    print("\n    水是游戏中的第一个“流体方块”，它会让身处其中的玩家以每回合2点的速度消耗氧气，同时玩家在其中可以自由上下移动而不坠落。");
    print("    水会自然生成在海洋类群系与常温群系低于海平面的地方，在低温群系里，表层的水也会被替换为冰层。");
}
void article_block_lava(){
    print("方块——岩浆");
    print("“炽热地底”————Pasy");
    print("\n加入游戏时间：2020/08/26  v0.0.1");
    print("方块id: 7");
    print("标准名称: lava");
    print("颜色: \033[48;2;255;96;0m  \033[m");
    print("拥有tag: fluid,oxygen,through,replaceable");
    print("\n    岩浆会让身处其中的玩家以每回合2点的速度消耗氧气，每回合4点的速度消耗生命值，对玩家而言十分危险。");
    print("    岩浆会自然生成在岩浆海，火山，岩浆陆与其他超高温群系地表，同时在y<16的地方，岩浆也会代替空气，形成“岩浆层”(加入于1.5.0.9)。");
}
void article_block_bedrock(){
    print("方块——基岩");
    print("“世界真正的基石”————Pasy");
    print("\n加入游戏时间：2020/08/26  v0.0.1");
    print("方块id: 8");
    print("标准名称: bedrock");
    print("颜色: \033[48;2;64;64;64m  \033[m(1.3.3至1.5.0.8)  \033[48;2;32;32;32m  \033[m(1.5.0.9以后)");
    print("拥有tag: unbreakable");
    print("\n    基岩会自然生成在y<5的地区，是阻挡玩家进入虚空的天然屏障。");
    print("    基岩不可破坏，其在世界生成中永远是最高等级，即始终最后生成基岩并不可替代，同时，y=0的地方将完全被基岩代替。");
    print("    基岩的生成概率遵循p = 100 - y*20，这意味着只可能在y<5的地方出现基岩，且越低生成几率越高。");
}
void article_block_wood(){
    print("方块——木头");
    print("“生命存在之证明”————Pasy");
    print("\n加入游戏时间：2020/08/27 pre1.1.0");
    print("方块id: 9");
    print("标准名称: wood");
    print("颜色: \033[48;2;128;128;16m  \033[m");
    print("拥有tag: through(1.5.0.7及以前)  无(1.5.0.8后)");
    print("\n    木头是树木结构的一部分，它会自然的生成在大部分平原类地形。");
    print("    木头的世界生成优先级大于树叶，在跨区块生成树时，树叶不会覆盖木头。");
}
void article_block_furnace(){
    print("方块——熔炉");
    print("“炽热的内在”————Pasy");
    print("\n加入游戏时间：2020/11/21 pre1.2.3");
    print("方块id: 10");
    print("标准名称: furnace");
    print("颜色: \033[48;2;192;192;160m  \033[m");
    print("拥有tag: interaction");
    print("\n    (该方块暂无实际用途)");
}
void article_block_crafting_table(){
    print("方块——工作台");
    print("“创造一切”————Pasy");
    print("\n加入游戏时间：2020/11/21 pre1.2.3");
    print("方块id: 11");
    print("标准名称: crafting_table");
    print("颜色: \033[48;2;192;160;64m  \033[m");
    print("拥有tag: interaction");
    print("\n    1.5.2之后，玩家可以通过多样的操作指令来在工作台上合成物品与工具！");
    print("    工作台的UI与方块是独立的，使用该方块会调出单独的界面，本质上，工作台方块与其他方块没有不同。");
}
void article_block_sand(){
    print("方块——沙子");
    print("“破碎之岩聚集在一起，也有改造世界的力量。”————Pasy");
    print("\n加入游戏时间: 2021/01/30 1.3.2-21w1a");
    print("方块id: 12");
    print("标准名称: sand");
    print("颜色: \033[48;2;240;240;128m  \033[m");
    print("拥有tag: gravity");
    print("\n    沙子会自然生成在沙漠与海底，是一种常见的自然方块。");
    print("    沙子虽然携带了gravity标签，但目前不会受重力影响。");
}
void article_block_leaf(){
    print("方块——树叶");
    print("“竭尽所能吸收着阳光，这就是生命”————Pasy");
    print("\n加入游戏时间: 2021/01/30 1.3.2-21w1a");
    print("方块id: 13");
    print("标准名称: leaf");
    print("颜色: \033[48;2;64;192;32m  \033[m");
    print("拥有tag: through");
    print("\n    树叶属于树木结构的一部分，跟随着树生成在大部分群系。");
    print("    树叶暂无树种上的分类。");
}
void article_block_unknown_block(){
    print("方块——未知方块");
    print("“一切未知”————Pasy");
    print("\n加入游戏时间: 2021/01/30 1.3.2-21w1a");
    print("方块id: 14");
    print("标准名称: unknown_block");
    print("颜色: [\033[48;2;0;0;0m  \033[m]");
    print("拥有tag: 无");
    print("\n    未知方块加入的初衷是作为id未知方块的代替，但实际开发中并未有过此类情况，因而实际上未知方块从来不会自然生成。");
    print("    未知方块是纯黑的，其仅能通过/fill,/setblock,/set放置。");
}
void article_block_coal_ore(){
    print("方块——煤矿石");
    print("“矿物，世界的馈赠”————Pasy");
    print("\n加入游戏时间: 2021/2/8 1.3.5");
    print("方块id: 15");
    print("标准名称: coal_ore");
    print("颜色: \033[48;2;128;128;96m  \033[m");
    print("拥有tag: 无");
    print("\n    (该方块暂无实际用途)");
}
void article_block_short_grass(){
    print("方块——矮草丛");
    print("“低小，但顽强”————Pasy");
    print("\n加入游戏时间: 2021/08/26 1.5.0");
    print("方块id: 16");
    print("标准名称: short_grass");
    print("颜色: \033[48;2;0;255;255m\033[38;5;0;255mω \033[m");
    print("拥有tag: through,replaceable");
    print("\n    矮草丛随着1.5.0自然更新加入，直接推动游戏的基础字符编码从ASCII到UTF-8，使用宽字符。");
    print("    矮草丛是游戏内第一个在颜色显示的情况下仍旧显示字符的方块，会自然生成在大部分的平原类群系与繁茂高原等地形的表面。");
    print("    曾经考虑过使用w代替ω(omega)，但后者观感更好，便予以保留。");
}
void article_block_rose(){
    print("方块——玫瑰");
    print("“绽放是唯一的目的”————Pasy");
    print("\n加入游戏时间: 2021/08/26 1.5.0");
    print("方块id: 17");
    print("标准名称: rose");
    print("颜色: \033[48;2;0;255;255m\033[38;5;9m✿ \033[m");
    print("拥有tag: through,replaceable");
    print("\n    玫瑰会自然生成在大部分的平原类群系与繁茂高原等地形的表面。");
    print("    玫瑰限于显示精度，其显示字符为Unicode内置的花朵字符。");
}
void article_block_snow(){
    print("方块——雪");
    print("“冰晶透折出的洁白”————Pasy");
    print("\n加入游戏时间: 2021/12/09 1.5.0.4");
    print("方块id: 18");
    print("标准名称: snow");
    print("颜色: \033[48;2;250;250;250m  \033[m");
    print("拥有tag: 无");
    print("\n    雪方块会自然生成在大部分寒冷的平原类群系与高山群系地表。");
    print("    目前的游戏中并无“落雪”设定，因而雪在目前的获取途径便是挖掘得到与直接获得。");
}
void article_block_ice(){
    print("方块——冰");
    print("“固化的水，永恒坚冰”————Pasy");
    print("\n加入游戏时间: 2021/12/09 1.5.0.4");
    print("方块id: 19");
    print("标准名称: ice");
    print("颜色: \033[48;2;192;255;255m  \033[m");
    print("拥有tag: 无");
    print("\n    冰会自然生成在大部分寒冷的海洋类群系与极限高山群系地表。");
    print("    在寒冷的海洋上，冰层的厚度随群系温度的降低而增大，最厚可达16层。");
}
void article_block_magma_block(){
    print("方块——岩浆方块");
    print("“亟待爆发”————Pasy");
    print("\n加入游戏时间: 2022/1/11 1.5.0.7");
    print("方块id: 20");
    print("标准名称: magma_block");
    print("颜色: \033[48;2;128;96;96m  \033[m");
    print("拥有tag: 无");
    print("\n    岩浆方块目前只会自然生成在岩浆陆群系。作为与火山群系的过渡。");
}
void article_block_granite(){
    print("方块——花岗岩");
    print("“自然的鬼斧神工”————Pasy");
    print("\n加入游戏时间: 2022/04/19 1.5.0.8");
    print("方块id: 21");
    print("标准名称: granite");
    print("颜色: \033[48;2;224;176;160m  \033[m");
    print("拥有tag: 无");
    print("\n    花岗岩是地质方块，会生成在任何群系的地下。");
    print("    花岗岩通过单独的二维噪声来控制生成，有时候可以见到壮观的大型脉络。");
}
void article_block_limestone(){
    print("方块——石灰岩");
    print("“自然的鬼斧神工”————Pasy");
    print("\n加入游戏时间: 2022/04/19 1.5.0.8");
    print("方块id: 22");
    print("标准名称: limestone");
    print("颜色: \033[48;2;224;224;224m  \033[m");
    print("拥有tag: 无");
    print("\n    石灰岩是地质方块，会生成在任何群系的地下。");
    print("    与花岗岩一样，石灰岩也通过单独的二维噪声来控制生成。");
}
void article_block_wood_plank(){
    print("方块——木板");
    print("能工巧匠————Pasy");
    print("\n加入游戏时间：2022/08/26");
    print("方块id: 23");
    print("标准名称: wood_plank");
    print("颜色: \033[48;2;240;224;128m  \033[m");
    print("拥有tag: 无");
    print("\n    在未加入遗迹前，木板是第一种只能靠合成得到物品形式的方块，在任何一个合成界面中，可以在任意位置放入木头以得到4倍数量的木板。");
}
void interface_block(){
    std::vector<std::string> block_chooselist;
    for(auto&& i : survive::block_list)
        block_chooselist.push_back(i.name + "(" + i.universal_name + ")");
    int choose = CUIL_std::uniselect<std::string>(block_chooselist);
    doclear();
    switch(choose){
        case 1:article_block_air();break;
        case 2:article_block_stone();break;
        case 3:article_block_cobblestone();break;
        case 4:article_block_grass();break;
        case 5:article_block_dirt();break;
        case 6:article_block_barrier();break;
        case 7:article_block_water();break;
        case 8:article_block_lava();break;
        case 9:article_block_bedrock();break;
        case 10:article_block_wood();break;
        case 11:article_block_furnace();break;
        case 12:article_block_crafting_table();break;
        case 13:article_block_sand();break;
        case 14:article_block_leaf();break;
        case 15:article_block_unknown_block();break;
        case 16:article_block_coal_ore();break;
        case 17:article_block_short_grass();break;
        case 18:article_block_rose();break;
        case 19:article_block_snow();break;
        case 20:article_block_ice();break;
        case 21:article_block_magma_block();break;
        case 22:article_block_granite();break;
        case 23:article_block_limestone();break;
        case 24:article_block_wood_plank();break;
    }
    PAUSE();
}


void article_command_move(){
    print("命令——w,a,s,d与/move");
    print("用途：\n让玩家移动");
    print("权限：VISITOR(生存模式)");
    print("格式:");
    print("w a s d输入单独字符即可");
    print("/move <w,a,s,d>    其中w,a,s,d任选其一。");
    print("w等价于/move w，以此类推。");
    print("含义: ");
    print("命令中，w始终指代的是上方向（y轴正半轴）,s指代下方向（y轴负方向）");
    print("a指代左方向（x轴负半轴），d指代右方向（x轴正方向）");
    print("你也可以使用大写字母WASD，不影响判定。（仅限单字符的移动指令）");
}
void article_command_set(){
    print("命令——/set");
    print("用途：\n在指定位置放置背包中的方块（仅生存模式）/放置指定方块（仅创造模式）");
    print("权限：VISITOR(生存模式)");
    print("格式:");
    print("/set <w,a,s,d> <Distance> <block>   其中w,a,s,d任选其一，Distance必需，block在生存模式下不会生效。");
    print("含义: ");
    print("以/set a 1 stone为例，如果玩家是创造模式，那么将会在左侧的第一个方块放置一个石头(stone)");
    print("而/set a 1 stone在生存模式下无效，需要省略第三个参数，并保证玩家的背包指针指向的快捷栏有方块型物品，此时可以在指定位置放置所使用的方块，并消耗一个物品。");
    print("例如，玩家背包快捷栏中有一个石头物品，且快捷栏指针指向该物品，则可以使用/set a 1在左侧放置一个方块。");
    print("w,a,s,d的含义见命令——移动指令。");
    print("/set指令在生存模式下能够放置的最大距离为4（创造模式为16），如果中间有实体方块阻挡，则不会生效。");
}
void article_command_break(){
    print("命令——/break");
    print("用途：破坏方块并得到方块的物品形式");
    print("权限：VISITOR(生存模式)");
    print("格式:");
    print("/break <w,a,s,d> <Distance>");
    print("含义：");
    print("以/break s 1为例，方向为向下，距离为1，则会破坏从玩家位置开始，向下的第一个方块。");
    print("假设玩家脚下的方块是石头，则会在背包内新增一个石头物品，其他方块的行为类似，流体方块则不会被破坏(从1.5.2.1开始)");
    print("w,a,s,d的含义见命令——移动指令。");
    print("/break指令在各个游戏模式下的破坏距离与/set相同。");
}
void article_command_fill(){
    print("命令——/fill");
    print("用途：在指定区域内填充特定方块");
    print("权限：OPERATOR(创造模式)");
    print("格式:");
    print("/fill <起始x坐标的相对/绝对表示> <起始y坐标的相对/绝对表示> <终止x坐标的相对/绝对表示> <终止y坐标的相对/绝对表示> <填充方块的名称>");
    print("含义：");
    print("以/fill 100 100 110 110 stone为例，会将坐标区域(100,100)与(110,110)之间所有的方块强制替换为石头。");
    print("/fill同时支持相对坐标表示，如果玩家的坐标为(100,100)，那么，下行的命令就与前文的等价：");
    print("/fill ~ ~ ~10 ~10 stone");
    print("相对坐标以~开头，后接的数字表示偏离距离，不写则与玩家保持一致，上一行的命令里，前两个~就表示玩家的x坐标,y坐标，而后两个~10表示玩家x,y坐标加10的结果，即(110,110)");
    print("偏移距离如果为负数，则表示从玩家位置开始，向左（如果表示的是x坐标）/下（如果表示的是y坐标，反转y轴开启后为上方向）偏移其绝对值个方块");
    print("例如：/fill ~-10 ~-10 ~10 ~10 stone表示从玩家左下10格方块开始，到玩家右上10格方块结束，中间区域填充石头。");
    print("/fill指令能填充的最大方块数量没有上限，但其不会填充世界范围之外的方块。");
}
void article_command_tp(){
    print("命令——/tp");
    print("用途：传送到指定坐标");
    print("权限：OPERATOR(创造模式)");
    print("格式:");
    print("/tp <终点x坐标的相对/绝对表示> <终点y坐标的相对/绝对表示>");
    print("含义：");
    print("以/tp 100 100为例，会将玩家坐标变更为(100,100)。");
    print("/tp同时支持相对坐标表示，如果玩家的坐标为(90,90)，那么，下行的命令就与前文的等价：");
    print("/tp ~10 ~10");
    print("相对坐标的使用可以见/fill指令的介绍");
}
void article_command_clone(){
    print("命令——/clone");
    print("用途：将一定范围的方块复制到另一区域");
    print("权限：OPERATOR(创造模式)");
    print("格式:");
    print("/clone <复制起始的x坐标> <复制起始的y坐标> <复制终止的x坐标> <复制终止的y坐标>  <新区域的起始x坐标>  <新区域的起始y坐标>");
    print("含义：");
    print("以/clone 100 100 110 110 200 200为例，会将(100,100)到(110,110)间的方块复制到以(200,200)为起始点的区域。");
    print("/clone同时支持相对坐标表示，如果玩家的坐标为(90,90)，那么，下行的命令就与前文的等价：");
    print("/clone ~10 ~10 ~20 ~20 ~110 ~110");
    print("相对坐标的使用可以见/fill指令的介绍");
    print("/clone指令的两个区域如果互相重叠，则不会生效，例如：");
    print("/clone 10 10 20 20 15 15，两个区域分别为(10,10)->(20,20)，(15,15)->(25,25)，两个区域有重叠部分，则不会复制。");
}
void article_command_gamemode(){
    print("命令——/gamemode");
    print("用途：修改玩家的游戏模式");
    print("权限：VISITOR(生存模式)");
    print("格式:");
    print("/gamemode <游戏模式的全称或id>");
    print("含义：");
    print("当前的游戏有两种模式，它们的全称与id如下：");
    print("创造模式：creative  1");
    print("生存模式：survival  0");
    print("如果输入/gamemode 1或/gamemode creative，则会将玩家游戏模式变为创造模式，生存模式同理。");
}
void article_command_help(){
    print("命令——/help");
    print("用途：打开帮助信息");
    print("权限：VISITOR(生存模式)");
    print("格式:");
    print("/help <不需要参数>");
    print("含义：");
    print("/help会在消息栏中打印Survive Wiki（也即该作品）的现行链接，作为游戏操作的帮助。");
}
void article_command_e(){
    print("命令——e");
    print("用途：打开背包或关闭界面");
    print("权限：VISITOR(生存模式)");
    print("格式:");
    print("e");
    print("含义：");
    print("如果当前游戏界面为主界面，则会打开背包界面，如果为其他交互方块界面，则会关闭并回到主界面");
}
void article_command_gamerule(){
    print("命令——/gamerule");
    print("用途：修改游戏规则");
    print("权限：OPERATOR");
    print("格式：");
    print("/gamerule <游戏规则名称> <非固定长度的参数>");
    print("含义：");
    print("/gamerule的解析是单独的，以下为目前的游戏规则名称，用途，参数要求，实例：");
    print(R"(
player_name                修改玩家名称              <字符串：表示新名称>      
/gamerule player_name Pasy    ————>将玩家名称修改为Pasy
world_name                 修改世界名称              <字符串：表示新名称>      
/gamerule world_name World    ————>将世界名称修改为World
vision_mode              修改游戏显示模式            <字符串：表示修改后的显示模式>
/gamerule vision_mode large   ————>将显示模式修改为large（详见游戏界面——显示模式）
auto_jump                决定是否自动跳跃            <布尔值：表示开启与否>
/gamerule auto_jump false      ————>将自动跳跃设置为false（也可以使用0表示，true同理）
no_enter                决定启用无回车输入           <布尔值：表示开启与否>
/gamerule no_enter false       ————>将无回车输入设置为false
respawn_point             修改玩家出生点             <整型值1：表示新出生点的x坐标> <整型值2：表示新出生点的y坐标>
/gamerule respawn_point 100 100  ————>将出生点设置为(100,100)
reverse_y             决定反转y轴的开启与否          <布尔值：表示开启与否>
/gamerule reverse_y true       ————>将反转y轴设置为true
knowledge               决定是否分享小知识           <布尔值：表示开启与否>
/gamerule knowledge false      ————>将分享知识设置为false(否)
auto_savefile          决定是否自动输出存档          <布尔值：表示开启与否>
/gamerule auto_savefile false  ————>将输出存档设置为false
longest_timeleap     决定单回合最长的时间前进        <整型值：表示新的值>
/gamerule longest_timeleap 100 ————>将单回合最长的时间前进设置为100
command_replace       决定是否启用命令宏替换         <布尔值：表示开启与否>
/gamerule command_replace false ————>关闭命令宏替换
maxinum_debug       修改debug信息最大的保存数量      <整型值：表示新的值>
/gamerule maxinum_debug 1000   ————>将调试信息的最大保存数量调至1000
)");
}
void article_command_testblock(){
    print("命令——/testblock");
    print("用途：检查指定位置上的方块信息");
    print("权限：OPERATOR(创造模式)");
    print("格式:");
    print("/testblock <检查x坐标的相对/绝对表示> <检查y坐标的相对/绝对表示>");
    print("含义：");
    print("以/testblock 100 100为例，会检查(100,100)上的方块信息，并在消息栏内展示结果");
    print("/testblock支持相对坐标表示，其含义详见/fill指令讲解");
}
void article_command_kill(){
    print("命令——/kill");
    print("用途：清除玩家，回到出生点");
    print("权限：OPERATOR(创造模式)");
    print("格式:");
    print("/kill <无参数>");
    print("含义：");
    print("不考虑其他条件，直接让玩家回到出生点。");
}
void article_command_eat(){
    print("命令——/eat");
    print("用途：增加玩家饥饿值");
    print("权限：OPERATOR(创造模式)");
    print("格式:");
    print("/eat <无参数>");
    print("含义：");
    print("不考虑其他条件，让玩家的饥饿值增加5点");
}
void article_command_setblock(){
    print("命令——/setblock");
    print("用途：在指定位置上强制放置方块");
    print("权限：OPERATOR(创造模式)");
    print("格式:");
    print("/setblock <放置x坐标的相对/绝对表示> <放置y坐标的相对/绝对表示> <方块名称>");
    print("含义：");
    print("以/setblock 100 100 stone为例，会在(100,100)上强制放置石头，并在消息栏内展示结果");
    print("/setblock支持相对坐标表示，其含义详见/fill指令讲解");
    print("/setblock会强制放置，不考虑该位置上原先的方块是什么。");
}
void article_command_seed(){
    print("命令——/seed");
    print("用途：展示当前世界的生成种子");
    print("权限：VISITOR(生存模式)");
    print("格式:");
    print("/seed <无参数>");
    print("含义：");
    print("在消息栏内打印当前世界的生成种子");
}
void article_command_biome(){
    print("命令——/biome");
    print("用途：输出玩家当前所在区块的生物群系");
    print("权限：VISITOR(生存模式)");
    print("格式:");
    print("/biome <无参数>");
    print("含义：");
    print("在消息栏内打印玩家当前所在区块的生物群系信息");
}
void article_command_say(){
    print("命令——/say");
    print("用途：在聊天栏内输出消息");
    print("权限：VISITOR(生存模式)");
    print("格式:");
    print("/say <所说的话>");
    print("含义：");
    print("以/say Hello Survive!为例，会在聊天栏内输出Hello Survive!");
}
void article_command_give(){
    print("命令——/give");
    print("用途：给予玩家物品");
    print("权限：OPERATOR(创造模式)");
    print("格式：");
    print("/give <物品名称> <物品数量>");
    print("含义：");
    print("以/give stone 64为例，会向玩家背包内新增64个石头物品。");
}
void article_command_throw(){
    print("命令——/throw");
    print("用途：丢弃背包内指定位置的物品");
    print("权限：VISITOR(生存模式)");
    print("格式：");
    print("/throw <丢弃物品下标>");
    print("含义：");
    print("以/throw 1为例，假设背包内第一个物品为64个石头，则会将其丢弃，丢弃的物品无法找回。");
}
void article_command_savefile(){
    print("命令——/savefile");
    print("用途：设置存档名称，并打印存档");
    print("权限：VISITOR(生存模式)");
    print("格式:");
    print("/savefile <存档名称>");
    print("含义：");
    print("以/savefile FILE为例，会将存档名称设置为FILE，并输出存档信息。");
}
void article_command_time(){
    print("命令——/time");
    print("用途：更改游戏时间");
    print("权限：OPERATOR(创造模式)");
    print("格式：");
    print("/time <修改模式> <修改值>");
    print("含义：");
    print("/time有两种模式：");
    print("1.set");
    print("如果使用set模式，则修改值为七个时间段的表示，如下：");
    print(R"(
sunrise       日出
day           白日
noon          中午
afternoon     下午
sunset        日落
night         夜晚
midnight      午夜
)");
    print("修改值也可为整数，此时，该整数将会作为新的时间值。");
    print("实例：/time set day和/time set 300都可以将时间调整到白日阶段");
    print("2.add");
    print("如果使用add模式，则修改值应是一个整数，表示从当前时间增加的时间刻数（如果该值为负数，则是减去）");
    print("例如，/time add 100会在当前时间基础上增加100刻");
}
void article_command_info(){
    print("命令——/info");
    print("用途：输出游戏当前信息");
    print("权限：VISITOR(生存模式)");
    print("格式:");
    print("/info <无参数>");
    print("含义：");
    print("在消息栏内打印游戏当前的基本信息，可能会不断拓展");
}
void article_command_backpack_pointer(){
    print("该页面是11种命令的集合，都是对背包快捷栏指针的操作。");
    print("1.数字1-9命令");
    print("输入对应数字，就会将背包快捷栏指针移动到对应的位置，例如，输入2会将背包快捷栏指针移动到第2个物品处");
    print("2.r,f");
    print("输入r,f会上下移动快捷栏指针。");
    print("输入r，指针上移一格，f则是下移，如果到顶或到底，则会移动到底端/顶端，即不断地循环");
}
void article_command_exchange(){
    print("命令——/exc");
    print("用途：交换指定下标的物品");
    print("权限：VISITOR(生存模式)");
    print("格式:");
    print("/exc <操作的物品下标1> <操作的物品下标2>");
    print("含义：");
    print("以/exc 1 3为例，会交换背包内顺序第1和第3个物品");
}
void article_command_cload(){
    print("命令——/cload");
    print("用途：强制生成某一个区块");
    print("权限：TRUSTABLE");
    print("格式: ");
    print("/cload <尝试生成的区块id>");
    print("含义：");
    print("以/cload 100为例，将会生成第100号区块，如果该区块未生成，则会强制令其生成。");
    print("该指令只能在最高权限模式下使用，请谨慎对待。");
}
void article_command_creload(){
    print("命令——/creload");
    print("用途：强制重新生成某一个区块");
    print("权限：TRUSTABLE");
    print("格式: ");
    print("/creload <尝试重新生成的区块id>");
    print("含义：");
    print("以/cload 100为例，将会重新生成第100号区块，如果该区块未生成，则不会执行。");
    print("该指令只能在最高权限模式下使用，且操作不可逆，请谨慎对待。");
}
void article_command_cclear(){
    print("命令——/cclear");
    print("用途：强制清空某一个区块");
    print("权限：TRUSTABLE");
    print("格式: ");
    print("/cclear <尝试清空的区块id>");
    print("含义：");
    print("以/cclear 100为例，如果该区块已生成，则会直接清空其所有数据，所有方块替换为空气。");
    print("该指令只能在最高权限模式下使用，且操作不可逆，请谨慎对待。");
}
void article_command_ccopy(){
    print("命令——/ccopy");
    print("用途：强制将某一个区块复制到另一个区块上");
    print("权限：TRUSTABLE");
    print("格式: ");
    print("/ccopy <源区块id> <目标区块id>");
    print("含义：");
    print("以/ccopy 100 101为例，会将第100号区块的信息复制到101号区块。");
    print("该指令只能在最高权限模式下使用，且操作不可逆，请谨慎对待。");
}
void article_command_permission(){
    print("命令——/permission");
    print("用途：修改玩家权限");
    print("权限：VISITOR(生存模式)");
    print("格式：");
    print("/permission <权限代号>");
    print("含义：");
    print("权限代号包括三种：");
    print(R"(
VISITOR    访客级权限（生存模式固定权限）
OPERATOR   操作员权限（创造模式权限）
TRUSTABLE  信任玩家权限（最高级别权限）
)");
    print("输入/permission OPERATOR，即可切换至操作员权限，使用创造模式命令。");
}
void article_command_copyright(){
    print("命令——/copyright");
    print("用途：显示版权信息");
    print("权限：VISITOR(生存模式)");
    print("格式：");
    print("/copyright <无参数>");
    print("含义：");
    print("输入该指令会打印游戏目前的版权信息");
}
void article_command_debug(){
    print("命令——/debug");
    print("用途：显示调试信息");
    print("权限：VISITOR(生存模式)");
    print("格式：");
    print("/debug <无参数>");
    print("含义：");
    print("输入该指令会打印游戏的调试信息");
}
void article_command_spawn(){
    print("命令——/spawn");
    print("用途：在指定位置上生成实体");
    print("权限：OPERATOR(创造模式)");
    print("格式:");
    print("/spawn <生成x坐标的相对/绝对表示> <生成y坐标的相对/绝对表示> <实体名称>");
    print("含义：");
    print("以/spawn 100 100 sheep为例，会在(100,100)上生成羊，并在消息栏内展示结果");
    print("/spawn支持相对坐标表示，其含义详见/fill指令讲解");
}
void article_command_damage(){
    print("命令——/damage");
    print("用途：尝试攻击指定位置上的实体");
    print("权限：OPERATOR(创造模式)");
    print("格式:");
    print("/damage <攻击x坐标的相对/绝对表示> <攻击y坐标的相对/绝对表示> <攻击伤害>");
    print("含义：");
    print("以/damage 100 100 10为例，会寻找坐标为(100,100)的实体，如果有则造成10点伤害，并在消息栏内展示结果");
    print("/damage支持相对坐标表示，其含义详见/fill指令讲解");
}
void article_command_dokill(){
    print("命令——/dokill");
    print("用途：尝试击杀指定位置上的实体");
    print("权限：OPERATOR(创造模式)");
    print("格式:");
    print("/dokill <击杀x坐标的相对/绝对表示> <击杀y坐标的相对/绝对表示>");
    print("含义：");
    print("以/damage 100 100 10为例，会寻找坐标为(100,100)的实体，如果有则击杀，并在消息栏内展示结果");
    print("/dokill支持相对坐标表示，其含义详见/fill指令讲解");
}
void article_command_chunkinfo(){
    print("命令——/chunkinfo");
    print("用途：输出玩家当前所处区块的信息");
    print("权限：VISITOR(生存模式)");
    print("格式:");
    print("/chunkinfo <无参数>");
    print("含义：");
    print("在消息栏内打印玩家当前所在区块的基本信息，可能会不断拓展");
}
void article_command_exit(){
    print("命令——/exit");
    print("用途：以一个完整的流程退出游戏");
    print("权限：VISITOR(生存模式)");
    print("格式:");
    print("/exit <无参数>");
    print("含义：");
    print("会在退出游戏前输出玩家当前的存档与最近的调试信息，是一个完整的退出流程。");
}
void article_command_use(){
    print("该页面是方块操作命令的集合。");
    print(R"(
/w,/a,/s,/d
wasd的含义与移动指令等相同，表示操作方向。
输入这些指令会尝试在对应方向上第一个方块进行操作，会按照如下顺序执行：
1.如果该方块上有实体，攻击
2.如果该方块为可交互的，打开其交互界面
这些指令是与交互性方块交互的基础指令。
)");
}
void article_command_crash(){
    print("命令——/crash");
    print("用途：从底层方面使游戏崩溃");
    print("权限：TRUSTABLE");
    print("格式:");
    print("/crash <无参数>");
    print("含义：");
    print("使游戏直接崩溃，可能不会触发游戏的崩溃保护机制，请谨慎使用。");
}
void article_command_put(){
    print(R"(命令——/put
用途：向容器内放入指定物品
权限：VISITOR(生存模式)
格式：
/put <背包内操作物品下标> <容器内顺序坐标> <可选：放入物品数量>
含义：
以打开工作台界面为例，/put 1 2表示将背包内第1个物品放入工作台的第二个物品位（第一行第二列），如果为/put 1 2 1，则只会放入一个物品，第三参数如果省略则默认全部放入。
/put命令是生存模式下重要的物品操作命令之一，请务必熟记用法
)");
}
void article_command_remove(){
    print(R"(
命令——/remove
用途：从容器内移出指定物品
权限：VISITOR(生存模式)
格式：
/remove <容器内顺序坐标> <可选：移出物品数量>
含义：
以打开工作台界面为例，/remove 1表示将工作台内第1个物品放入背包，如果为/remove 1 1，则只会移出一个物品，第二参数如果省略则默认全部移出。
/remove命令是生存模式下重要的物品操作命令之一，请务必熟记用法
)");
}
void article_command_get(){
    print(R"(
命令——/get
用途：从容器内取出产物
权限：VISITOR(生存模式)
格式：
/get <可选：取出物品次数>
含义：
以打开工作台界面为例，/get表示将工作台的合成产物放入背包，如果为/get 2，则会取出两次，第二参数如果省略则默认取出一次。
/get命令是生存模式下重要的物品操作命令之一，请务必熟记用法
)");
}
void article_command_clear(){
    print(R"(
命令——/clear
用途：清空玩家背包
权限：OPERATOR（创造模式）
格式：
/clear <无参数>
含义：
将玩家内所有的物品全部清空
此操作不可逆，请谨慎使用
)");
}
void interface_command(){
    std::vector<std::string> creative_command,high_permission_command;
    for(auto&& i : command_list){
        if(i.permission == OPERATOR)
            creative_command.push_back(i.identifier);
        if(i.permission == TRUSTABLE)
            high_permission_command.push_back(i.identifier);
    }
    switch(uniselect<std::string>({"生存模式命令","创造模式命令","高权限指令"})){
        case 1:
            switch(uniselect<std::string>({"移动指令","方块操作指令","物品操作指令","信息展示指令","游戏操作指令"})){
                case 1:
                    article_command_move();
                break;
                case 2:
                    switch(uniselect<std::string>({"/set指令","/break指令","交互方块指令"})){
                        case 1:article_command_set();break;
                        case 2:article_command_break();break;
                        case 3:article_command_use();break;
                        default:break;
                    }
                break;
                case 3:
                    switch(uniselect<std::string>({"/throw指令","/exc指令","/put指令","/remove指令","/get指令"})){
                        case 1:article_command_throw();break;
                        case 2:article_command_exchange();break;
                        case 3:article_command_put();break;
                        case 4:article_command_remove();break;
                        case 5:article_command_get();break;
                        default:break;
                    }
                break;
                case 4:
                    switch(uniselect<std::string>({"/help指令","/seed指令","/biome指令","/say指令","/info指令","/copyright指令","/debug指令","/chunkinfo指令","/screenshot指令"})){
                        case 1:article_command_help();break;
                        case 2:article_command_seed();break;
                        case 3:article_command_biome();break;
                        case 4:article_command_say();break;
                        case 5:article_command_info();break;
                        case 6:article_command_copyright();break;
                        case 7:article_command_debug();break;
                        case 8:article_command_chunkinfo();break;
                        //case 9:article_command_screenshot();break;
                        default:break;
                    }
                break;
                case 5:
                    switch(uniselect<std::string>({"/gamemode指令","背包操作指令","背包快捷栏指令","/savefile指令","/permission指令","/exit指令"})){
                        case 1:article_command_gamemode();break;
                        case 2:article_command_e();break;
                        case 3:article_command_backpack_pointer();break;
                        case 4:article_command_savefile();break;
                        case 5:article_command_permission();break;
                        case 6:article_command_exit();break;
                        default:break;
                    }
                break;
            }
        break;
        case 2:
            switch(uniselect<std::string>(creative_command)){
                case 1:article_command_fill();break;
                case 2:article_command_tp();break;
                case 3:article_command_clone();break;
                case 4:article_command_gamerule();break;
                case 5:article_command_testblock();break;
                case 6:article_command_kill();break;
                case 7:article_command_eat();break;
                case 8:article_command_setblock();break;
                case 9:article_command_give();break;
                case 10:article_command_time();break;
                case 11:article_command_spawn();break;
                case 12:article_command_damage();break;
                case 13:article_command_dokill();break;
                case 14:article_command_clear();break;
                default:break;
            }
        break;
        case 3:
            switch(uniselect<std::string>(high_permission_command)){
                case 1:article_command_cload();break;
                case 2:article_command_creload();break;
                case 3:article_command_cclear();break;
                case 4:article_command_ccopy();break;
                case 5:article_command_crash();break;
                default:break;
            }
        break;
    }
    PAUSE();
}
void article_introduction_newcome(){
    doclear();
    usleep(500000);
    print("欢迎来到全社区最强大的C++沙盒游戏Survive！");
    print("首先，你可以记住游戏的logo：");
    sleep(2);
    survive::print_gamelogo();
    PAUSE();
    doclear();
    print("你现在将学习的版本是：" + survive::GameVersion + ",所使用的Survive Wiki始终与最新版本同步，在新手教程内，你将学会如何使用最基础的功能与指令，由于游戏的操作完全依赖指令，在学习初期的成果与进度直接决定了你之后进行其他功能学习的能力，Survive直到目前共有" + convert.to_string(survive::command_list.size()) + "种指令，这将是个漫长的学习过程。");
    PAUSE();
    doclear();
    print("首先，我们学习游戏的前置界面：\n");
    print("系统检查：",printformat,false);
    print("| -- CUIL库自检：",printformat,false);
    print("|      O -- CUIL版本符合要求：      " + make_shapebool(CUIL_VERSIONINFO >= REQUIRE_CUIL_VERSION),printformat,false);
    print("| -- Survive运行自检：",printformat,false);
    print("|      | -- 游戏版本：" + GameVersion,printformat,false);
    print("|      | -- 适用于在线版：          " + make_shapebool(online_xes),printformat,false);
    print("|      O -- CUIL已向上兼容",printformat,false);
    print("O      ",printformat,false);
    print("如果你认为这会影响你的游戏，请询问作者",printformat,false);
    print("注：不接受非正式版本的询问",printformat,false);
    print("我准备好开始游戏了！ (0/1)>>> ",printformat,false,5,false);
    print("\n这一部分是游戏的运行环境检查，一般不用管，输入1以继续");
    PAUSE();
    doclear();
    print(R"(
选择：
>  1.加载存档
   2.创建新世界
（w,s上下切换选项,y确定）
>>>
)",printformat,false);
    print("\n\n这一部分是选择游戏的运行方式，如果你选择存档模式，游戏将先会检查你是否放入存档，如果没有则会强制停止游戏，我们默认读者尚未阅读与存档存储相关的文章，所以请选择“创建新世界”选项，按一下s即可",printformat,5.0);
    PAUSE();
    doclear();
    print(R"(
选择：
>  1.名称
   2.种子
   3.世界类型设置
   4.地形设置
   5.预处理指令
   6.结束更改
（w,s上下切换选项,y确定）
>>>
)",printformat,false);
    print("\n这一部分就是设置世界的生成模式，鉴于各位应该是第一次见到这个界面，我们不会在这里讲解所有的功能与其原理，对于各位，设置一个名称即可。");
    print("按下y进入名称设置选项：\n");
    PAUSE();
    doclear();
    print(R"(
选择：
>  1.玩家名称
   2.世界名称
（w,s上下切换选项,y确定）
>>>
)",printformat,false);
    print("\n然后，各位愿意的话，只需要点进每个选项并设置名称即可，由于选项界面没有“上一页”功能，需要各位重新进入一次名称设置界面，也算是熟悉界面了。");
    print("你应当见到如下界面：\n");
    print(R"(
选择：
>  1.玩家名称
   2.世界名称
（w,s上下切换选项,y确定）
>>>y
给予她名字: Pasy_______________
)",printformat,false);
    print(R"(
选择：
   1.玩家名称
>  2.世界名称
（w,s上下切换选项,y确定）
>>>y
写下世界之名: Survive____________
)",printformat,false);
    print("\n\n像实例一样输入回车即可，这样，我们就可以准备进入世界了！");
    print("向下移动选项到“结束更改”，输入y确定，游戏会输出如下内容：");
    print(R"(Survive世界生成设置：
.   她之名: Pasy
.   世界种子: 8869311
.   海平面: 384
.   世界类型: Normal
.   世界群系设置: 正常群系设置
.   地形缩放: 1.000倍
.   地形采样密度: 0.00098每方块
.   群系采样密度: 0.00098每方块
.   洞穴采样密度: 0.00195每方块
.   预处理指令: []
确认设置? (0/1) >>>)",printformat,false);
    print("\n从第二行起的所有内容现在都不需要了解，输入1回车即可进入游戏了！");
    print("游戏界面引导请参阅第二页面。");
}
void article_introduction_gameinterface(){
    print("在观看上一页面后，你应当进入了游戏，此时，游戏的界面应当如下：");
    print("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n\
┃ \033[48;2;127;255;255m                                \033[m┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃\n\
┃ \033[48;2;127;255;255m                \033[48;2;127;255;255m\033[38;5;232m！\033[48;2;127;255;255m              \033[m┃\n\
┃ \033[48;2;127;255;255m                \033[48;2;64;192;32m      \033[48;2;248;248;248m  \033[48;2;190;190;190m  \033[48;2;127;255;255m      \033[m┃\n\
┃ \033[48;2;127;255;255m              \033[48;2;64;192;32m              \033[48;2;127;255;255m  \033[48;2;64;192;32m  \033[m┃\n\
┃ \033[48;2;127;255;255m              \033[48;2;64;192;32m              \033[48;2;127;255;255m  \033[48;2;64;192;32m  \033[m┃\n\
┃ \033[48;2;127;255;255m              \033[48;2;64;192;32m      \033[48;2;128;128;16m\033[38;2;139;69;19m▒▒\033[48;2;64;192;32m      \033[48;2;127;255;255m  \033[48;2;64;192;32m  \033[m┃\n\
┃ \033[48;2;127;255;255m              \033[48;2;64;192;32m      \033[48;2;128;128;16m\033[38;2;139;69;19m▒▒\033[48;2;64;192;32m      \033[48;2;127;255;255m  \033[48;2;64;192;32m  \033[m┃\n\
┃ \033[48;2;127;255;255m            \033[48;2;248;248;248m  \033[48;2;64;192;32m      \033[48;2;128;128;16m\033[38;2;139;69;19m▒▒\033[48;2;64;192;32m      \033[48;2;127;255;255m  \033[48;2;64;192;32m  \033[m┃\n\
┃ \033[38;2;255;0;0m\033[48;2;127;255;255m✿ \033[48;2;127;255;255m      \033[38;2;0;175;0m\033[48;2;127;255;255mω \033[48;2;127;255;255m  \033[38;2;0;175;0m\033[48;2;127;255;255mω \033[38;2;0;175;0m\033[48;2;127;255;255mω \033[48;2;127;255;255m  \033[38;2;255;0;0m\033[48;2;127;255;255m✿ \033[48;2;128;128;16m\033[38;2;139;69;19m▒▒\033[48;2;127;255;255m        \033[38;2;0;175;0m\033[48;2;127;255;255mω \033[m┃\n\
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n",printformat,true,10000.0);
    print(R"( 生命值: 20      饥饿值: 20
┃ x:32752  y:141  游戏模式: 生存模式
┃ 命令>>>)",printformat,false);
    PAUSE();
    doclear();
    print("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n\
┃ \033[48;2;127;255;255m                                \033[m┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃  <--游戏的地图，默认为16*16\n\
┃ \033[48;2;127;255;255m                                \033[m┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃\n\
┃ \033[48;2;127;255;255m                \033[48;2;127;255;255m\033[38;5;232m！\033[48;2;127;255;255m              \033[m┃  <--这一行的黑色感叹号就是玩家\n\ 
┃ \033[48;2;127;255;255m                \033[48;2;64;192;32m      \033[48;2;248;248;248m  \033[48;2;190;190;190m  \033[48;2;127;255;255m      \033[m┃  <--这里白色与灰色是实体羊和牛\n\
┃ \033[48;2;127;255;255m              \033[48;2;64;192;32m              \033[48;2;127;255;255m  \033[48;2;64;192;32m  \033[m┃\n\
┃ \033[48;2;127;255;255m              \033[48;2;64;192;32m              \033[48;2;127;255;255m  \033[48;2;64;192;32m  \033[m┃\n\
┃ \033[48;2;127;255;255m              \033[48;2;64;192;32m      \033[48;2;128;128;16m\033[38;2;139;69;19m▒▒\033[48;2;64;192;32m      \033[48;2;127;255;255m  \033[48;2;64;192;32m  \033[m┃\n\
┃ \033[48;2;127;255;255m              \033[48;2;64;192;32m      \033[48;2;128;128;16m\033[38;2;139;69;19m▒▒\033[48;2;64;192;32m      \033[48;2;127;255;255m  \033[48;2;64;192;32m  \033[m┃\n\
┃ \033[48;2;127;255;255m            \033[48;2;248;248;248m  \033[48;2;64;192;32m      \033[48;2;128;128;16m\033[38;2;139;69;19m▒▒\033[48;2;64;192;32m      \033[48;2;127;255;255m  \033[48;2;64;192;32m  \033[m┃  <------一棵典型的树\n\
┃ \033[38;2;255;0;0m\033[48;2;127;255;255m✿ \033[48;2;127;255;255m      \033[38;2;0;175;0m\033[48;2;127;255;255mω \033[48;2;127;255;255m  \033[38;2;0;175;0m\033[48;2;127;255;255mω \033[38;2;0;175;0m\033[48;2;127;255;255mω \033[48;2;127;255;255m  \033[38;2;255;0;0m\033[48;2;127;255;255m✿ \033[48;2;128;128;16m\033[38;2;139;69;19m▒▒\033[48;2;127;255;255m        \033[38;2;0;175;0m\033[48;2;127;255;255mω \033[m┃  <------这里你可以看到花草\n\
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n",printformat,true,10000.0);
    print(R"(
┃ 生命值: 20      饥饿值: 20         <------这里的信息顾名思义
┃ x:32752  y:141  游戏模式: 生存模式 <------两个数字表示你的x,y坐标
┃ 命令>>>                            <------在这里输入指令操作)",printformat,false);
    print("\n请观察下面示例输入的代码，并在游戏内跟着输入：\n");
        print("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n\
┃ \033[48;2;127;255;255m                                \033[m┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃\n\
┃ \033[48;2;127;255;255m                \033[48;2;127;255;255m\033[38;5;232m！\033[48;2;127;255;255m              \033[m┃\n\
┃ \033[48;2;127;255;255m                \033[48;2;64;192;32m      \033[48;2;248;248;248m  \033[48;2;190;190;190m  \033[48;2;127;255;255m      \033[m┃\n\
┃ \033[48;2;127;255;255m              \033[48;2;64;192;32m              \033[48;2;127;255;255m  \033[48;2;64;192;32m  \033[m┃\n\
┃ \033[48;2;127;255;255m              \033[48;2;64;192;32m              \033[48;2;127;255;255m  \033[48;2;64;192;32m  \033[m┃\n\
┃ \033[48;2;127;255;255m              \033[48;2;64;192;32m      \033[48;2;128;128;16m\033[38;2;139;69;19m▒▒\033[48;2;64;192;32m      \033[48;2;127;255;255m  \033[48;2;64;192;32m  \033[m┃\n\
┃ \033[48;2;127;255;255m              \033[48;2;64;192;32m      \033[48;2;128;128;16m\033[38;2;139;69;19m▒▒\033[48;2;64;192;32m      \033[48;2;127;255;255m  \033[48;2;64;192;32m  \033[m┃\n\
┃ \033[48;2;127;255;255m            \033[48;2;248;248;248m  \033[48;2;64;192;32m      \033[48;2;128;128;16m\033[38;2;139;69;19m▒▒\033[48;2;64;192;32m      \033[48;2;127;255;255m  \033[48;2;64;192;32m  \033[m┃\n\
┃ \033[38;2;255;0;0m\033[48;2;127;255;255m✿ \033[48;2;127;255;255m      \033[38;2;0;175;0m\033[48;2;127;255;255mω \033[48;2;127;255;255m  \033[38;2;0;175;0m\033[48;2;127;255;255mω \033[38;2;0;175;0m\033[48;2;127;255;255mω \033[48;2;127;255;255m  \033[38;2;255;0;0m\033[48;2;127;255;255m✿ \033[48;2;128;128;16m\033[38;2;139;69;19m▒▒\033[48;2;127;255;255m        \033[38;2;0;175;0m\033[48;2;127;255;255mω \033[m┃\n\
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n",printformat,true,10000.0);
    print(R"( 生命值: 20      饥饿值: 20
┃ x:32752  y:141  游戏模式: 生存模式
┃ 命令>>>/break s 1)",printformat,false);
    PAUSE();
    doclear();
    print("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n\
┃ \033[48;2;127;255;255m                                \033[m┃ > 树叶 * 1 ┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃            ┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃            ┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃            ┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃            ┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃            ┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃            ┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃            ┃\n\
┃ \033[48;2;127;255;255m                \033[48;2;127;255;255m\033[38;5;232m！\033[48;2;127;255;255m              \033[m┃            ┃\n\
┃ \033[48;2;127;255;255m                  \033[48;2;64;192;32m        \033[48;2;127;255;255m      \033[m┃━━━━━━━━━━━━┃\n\
┃ \033[48;2;127;255;255m              \033[48;2;64;192;32m              \033[48;2;127;255;255m  \033[48;2;64;192;32m  \033[m┃            ┃\n\
┃ \033[48;2;127;255;255m              \033[48;2;64;192;32m              \033[48;2;127;255;255m  \033[48;2;64;192;32m  \033[m┃            ┃\n\ 
┃ \033[48;2;127;255;255m              \033[48;2;64;192;32m      \033[48;2;128;128;16m\033[38;2;139;69;19m▒▒\033[48;2;64;192;32m      \033[48;2;127;255;255m  \033[48;2;64;192;32m  \033[m┃            ┃\n\
┃ \033[48;2;127;255;255m              \033[48;2;64;192;32m      \033[48;2;128;128;16m\033[38;2;139;69;19m▒▒\033[48;2;64;192;32m      \033[48;2;127;255;255m  \033[48;2;64;192;32m  \033[m┃            ┃\n\
┃ \033[48;2;127;255;255m              \033[48;2;64;192;32m      \033[48;2;128;128;16m\033[38;2;139;69;19m▒▒\033[48;2;64;192;32m      \033[48;2;127;255;255m  \033[48;2;64;192;32m  \033[m┃            ┃\n\
┃ \033[38;2;255;0;0m\033[48;2;127;255;255m✿ \033[48;2;127;255;255m    \033[48;2;248;248;248m  \033[38;2;0;175;0m\033[48;2;127;255;255mω \033[48;2;127;255;255m  \033[38;2;0;175;0m\033[48;2;127;255;255mω \033[38;2;0;175;0m\033[48;2;127;255;255mω \033[48;2;127;255;255m  \033[38;2;255;0;0m\033[48;2;127;255;255m✿ \033[48;2;128;128;16m\033[38;2;139;69;19m▒▒\033[48;2;127;255;255m  \033[48;2;190;190;190m  \033[48;2;248;248;248m  \033[48;2;127;255;255m  \033[38;2;0;175;0m\033[48;2;127;255;255mω \033[m┃            ┃\n\
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n",printformat,false);
print(R"( 生命值: 20      饥饿值: 20
┃ x:32752  y:141  游戏模式: 生存模式
┃ 命令>>>/break s 1)",printformat,false);
    print("\n右侧多出来的界面就是你的背包快捷栏界面，在这里你可以查看背包中的前9个物品，并通过指令修改使用的物品！");
    print("接下来，我们输入指令e：");
    PAUSE();
    doclear();
    print("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n\
┃ \033[48;2;127;255;255m                                \033[m┃ > 树叶 * 1 ┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃            ┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃            ┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃            ┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃            ┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃            ┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃            ┃\n\
┃ \033[48;2;127;255;255m                                \033[m┃            ┃\n\
┃ \033[48;2;127;255;255m                \033[48;2;127;255;255m\033[38;5;232m！\033[48;2;127;255;255m              \033[m┃            ┃\n\
┃ \033[48;2;127;255;255m                  \033[48;2;64;192;32m        \033[48;2;127;255;255m      \033[m┃━━━━━━━━━━━━┃\n\
┃ \033[48;2;127;255;255m              \033[48;2;64;192;32m              \033[48;2;127;255;255m  \033[48;2;64;192;32m  \033[m┃            ┃\n\
┃ \033[48;2;127;255;255m              \033[48;2;64;192;32m              \033[48;2;127;255;255m  \033[48;2;64;192;32m  \033[m┃            ┃\n\ 
┃ \033[48;2;127;255;255m              \033[48;2;64;192;32m      \033[48;2;128;128;16m\033[38;2;139;69;19m▒▒\033[48;2;64;192;32m      \033[48;2;127;255;255m  \033[48;2;64;192;32m  \033[m┃            ┃\n\
┃ \033[48;2;127;255;255m              \033[48;2;64;192;32m      \033[48;2;128;128;16m\033[38;2;139;69;19m▒▒\033[48;2;64;192;32m      \033[48;2;127;255;255m  \033[48;2;64;192;32m  \033[m┃            ┃\n\
┃ \033[48;2;127;255;255m              \033[48;2;64;192;32m      \033[48;2;128;128;16m\033[38;2;139;69;19m▒▒\033[48;2;64;192;32m      \033[48;2;127;255;255m  \033[48;2;64;192;32m  \033[m┃            ┃\n\
┃ \033[38;2;255;0;0m\033[48;2;127;255;255m✿ \033[48;2;127;255;255m    \033[48;2;248;248;248m  \033[38;2;0;175;0m\033[48;2;127;255;255mω \033[48;2;127;255;255m  \033[38;2;0;175;0m\033[48;2;127;255;255mω \033[38;2;0;175;0m\033[48;2;127;255;255mω \033[48;2;127;255;255m  \033[38;2;255;0;0m\033[48;2;127;255;255m✿ \033[48;2;128;128;16m\033[38;2;139;69;19m▒▒\033[48;2;127;255;255m  \033[48;2;190;190;190m  \033[48;2;248;248;248m  \033[48;2;127;255;255m  \033[38;2;0;175;0m\033[48;2;127;255;255mω \033[m┃            ┃\n\
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n",printformat,false);
print(R"( 生命值: 20      饥饿值: 20
┃ x:32752  y:141  游戏模式: 生存模式
┃ 命令>>>e)",printformat,false);
    PAUSE();
    doclear();
    print(R"(#简易工作台
 -     -
 -     -
产物 >>>

#背包
#物品列表：
  1: 树叶 * 1       2:                3:
  4:                5:                6:
  7:                8:                9:
 10:               11:               12:
 13:               14:               15:
 16:               17:               18:
 19:               20:               21:
 22:               23:               24:
 25:               26:               27:
 28:               29:               30:
 31:               32:               33:
 34:               35:               36:
┃ 生命值: 20      饥饿值: 20
┃ x:32752  y:141  游戏模式: 生存模式
┃ 命令>>>)",printformat,false);
    print("\n执行成功后，你会看到如下界面，上方是简易工作台界面，是游戏初期合成的必要工具，下方是你的背包，共计有36个物品栏。");
    print("再次输入e即可退出背包界面。");
    print("\n该部分内容结束，接下来请阅读第三页面，了解如何使用基础的指令。");
}
void article_introduction_command(){
    print(R"(在这一节里，你将学习使用指令。从一无所有到合成自己的工作台！

1.移动指令
首先，玩家在标准显示模式下能看到16*16范围的方块信息，在生成的默认世界内（假如你没有更改种子），你的旁边应该就是一棵树。
使用w,a,s,d来向上/左/下/右移动，试试看！
接着，观察周围的地形，你应当移动到树木根部位置。

2.破坏与放置

现在你来到了树木旁边，如果你的右侧是树木，请输入/break d 1
这段指令的含义是：破坏右侧第一个方块
其中/break即为指令标识符，d是一个方向参数，对于所有包含方向参数的指令，都使用wasd表示，其含义与移动指令相同。
1则是距离参数，也即指定方向上的第一个方块
如果你的左侧是树木，则输入/break a 1，a的含义不必多说，也与移动指令相同
/break指令最远能破坏4格远的方块，但你需要保证到指定方块的路径上，不存在能阻挡的方块，除了花草，水与岩浆等的方块大都能阻挡你的挖掘，此时，游戏会挖掘路径上的第一个方块。

如果你站在了正确的位置，游戏的结果应当如下：

)");

}
void interface_introduction(){
    doclear();
    switch(uniselect<std::string>({"初入游戏","界面引导","指令操作"})){
        case 1:article_introduction_newcome();break;
        case 2:article_introduction_gameinterface();break;
        case 3:article_introduction_command();break;
    }    
    PAUSE();
}
int main()
{
    print("欢迎来到Survive Wiki!这里是游戏最大的官方性百科");
    PAUSE();
    while(true){
        doclear();
        switch(uniselect<std::string>({"方块Wiki","命令Wiki","新手入门","退出Wiki"})){
            case 1:interface_block();break;
            case 2:interface_command();break;
            case 3:interface_introduction();break;
            case 4:print("欢迎再次阅读Survive Wiki!");exit(0);break;
        }
    }
    return 0;
}