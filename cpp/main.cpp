#include <graphics.h>
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<string>
#define _USE_MATH_DEFINES
#include <math.h>

#define W 2025
#define H 1560
#define Pi M_PI
#define e 23.4
#define XP 100
#define YP 60
#define YE 2021

using namespace std;
using namespace ege;

float caculate(float x, float y, float South, float Lat, float Lont, float rt)
{
    static float z = 0;
    double T, L, JD, M, RT, Q, E0;

    JD = 2459215.5 + x + (y - Lont/15.0) / 24.0 - 1;

    T = (JD - 2451545.0) / 36525.0;

    M = 357.52910 + 35999.05030 * T - 0.0001559 * T * T - 0.00000048 * T * T * T;

    L = 280.46645 + 36000.76983 * T + 0.0003032 * T * T
    + (1.914600 - 0.004817 * T - 0.000014 * T * T) * sin(Pi / 180 * M)
    + (0.019993 - 0.000101 * T) * sin(Pi / 180 * 2 * M)
    + 0.000290 * sin(Pi / 180 * 3 * M);

    L = L - ((int)L / 360) * 360;

    E0 = 79.6764 + 0.2422 * (YE - 1985) - int(0.25 * (YE - 1985));

    Q = 2*Pi*(x-E0)/365.2422;

    if(rt == -1){
        RT = y + (Lont - 120)*4/60.0 +(0.0028 - 1.9857 * sin(Q) + 9.9059 * sin(2 * Q) - 7.0924 * cos(Q) - 0.6882 * cos(2 * Q)) / 60.0;
    }
    else{
        RT = rt;
    }

    //cout<<RT<<endl;
    z = (90 -
        abs((1.0 / Pi) *
        (180.0 * asin(sin(2.0 * Pi * ((L + South * 180) / 360.0)) *
        sin((Pi * Lat) / 180.0) * sin((Pi * e) / 180.0) +
        cos((Pi * Lat) / 180.0) * cos((1.0 / 180.0) * Pi * 15.0 * (RT - 12.0)) *
        cos(asin(sin(2.0 * Pi * ((L + South * 180) / 360.0)) * sin((Pi * e) / 180.0)))))
        - 90.0));
    return z;
}

int main()
{

    float x = 0, y = 0, South = 0, Lat = 0, Lont =120 , h = 0, t1 = -100, t2 = 0, p = -1, l = -1;
    float a[12] = {1, 32, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
    int i, n, mp = -1, dp = -1, ml = -1, dl = -1;
    int quit;
    stringstream s;
    PIMAGE img;

    //cout << caculate(32, 6.5,  0, 40, 116, -1)<<endl;

    while(1){

        n = 24;
        quit = 0;

        //����
        cout << "���춥�� ����ƽ�� �ɼ�������㹤�� by WMinusL" << endl;
        cout << "ʹ�ñ���ʱ�� GMT+8" << endl;
        cout << "��ʹ�õ�ѡ������������ķ�ʽ�رհ�ɫ��ͼ���� �����޷���������" << endl << endl;

        cout << "1.���� Hemisphere" << endl << "(North ���������� 0 ,South �ϰ������� 1):";
        cin >> South;

        if(South != 0 && South != 1){
            cout << "wrong input, please try again" << endl;
            continue;
        }

        cout << "2.γ�� Latitude (input range 0~90):";
        cin >> Lat;

        if(Lat < 0 || Lat > 90){
            cout << "wrong input, please try again" << endl;
            continue;
        }

        cout << "3.���� Longitude (input range 0~180):";
        cin >> Lont;

        if(Lont < 0 || Lont > 180){
            cout << "wrong input, please try again" << endl;
            continue;
        }

        //����
        initgraph(W, H, INIT_RENDERMANUAL);
        setbkcolor(EGERGB(255, 255, 255));
        setfont(36, 0, "Times New Roman");
        setcolor(EGERGB(0, 0, 0));
        setlinestyle(CENTER_LINE, NULL, 1);

        img = newimage(W, H);
        cleardevice(img);

        //CHA�ɼ���Χ����
        for(i = 1; i <= 365; i++){          //��������

            t2 = caculate(i , 12,  South, Lat, Lont, 12);

            if(t1 != -100 && t2 > 57.8 && t1 < 57.8){
                p = i;
            }

            if(t1 != -100 && t2 < 57.8 && t1 > 57.8){
                l = i - 1;
            }

            t1 = t2;
        }
        //cout << p << endl << l << endl;

        for(i = 0; i < 12; i++){            //�������ڻ���
            if(a[i] > p && a[i - 1] <= p){

                dp = p - a[i - 1] + 1;
                mp = i;

            }
            if(a[i] > l && a[i - 1] <= l){

                dl = l - a[i - 1] + 1;
                ml = i;

            }
        }

        //���ڷ�Χ���
        cout << "����ƽ���ɼ�ʱ�� CHA visible (MM.DD):" << endl;
        cout << "��(start):" << setw(2) << setfill('0') << mp << "." << setw(2) << setfill('0') << dp << endl;
        cout << "ֹ(stop) :" << setw(2) << setfill('0') << ml << "." << setw(2) << setfill('0') << dl << endl << endl;
        cout << "��start����stop���ɼ�������stop֮ǰ��start֮�� if start > stop  ,visible date is earlier than 'stop',later than 'start' " << endl;
        cout << "����ʾ-1.-1,����ֽ����ڲ����� if output -1.-1 ,date doesn't exist" << endl;

        //��ͼ
        for(x = XP - 1; x < W - XP; x++){
            for(y = YP - 1; y < H - YP; y++){

                h = caculate(365.24 * (x - (XP - 1)) / (W - 2 * XP) + 1 , 24-24 * (y-(YP - 1)) / (H - 2 * YP), South, Lat, Lont, -1);
                //cout<<h;
                //cin>>h;
                if(h <= 0){
                    putpixel(x, y, EGERGB(50, 50, 112));
                }
                else if(h < 32.2){
                    putpixel(x, y, EGERGB(160, 200, 255));
                }
                else if(h < 57.8){
                    putpixel(x, y, EGERGB(245, 245, 245));
                }
                else{
                    putpixel(x, y, EGERGB(255, 165, 0));
                }
            }
        }

        //����̶�
        for(y = YP - 1; y <= H - YP; y = y + (H - 2 * YP) / 24.0){

            line(XP - 5, y + 0.5, W - XP - 1, y + 0.5);
            xyprintf(XP - 48, y + 0.5 - 18, "%3d", n);
            n = n - 1;

        }

        for(i = 0; i < 12; i++){

            line((a[i] - 1) * (W - 2 * XP) / 365.24 + XP - 0.5, YP, (a[i] - 1) * (W - 2 * XP) / 365.24 + XP - 0.5, H - YP);

        }

        //���ֱ�ע
        n = 1;
        for(i = 0; i < 12; i++){
            xyprintf((a[i] - 1) * (W - 2 * XP) / 365.24 + XP - 0.5 + 32, H - YP + 5, "%3d", n);
            n++;
        }

        if(South == 0){
            xyprintf(W - XP - 120, YP-40, "%.2f ��N", Lat);
        }
        else{
            xyprintf(W - XP - 120, YP - 40, "%.2f ��S", Lat);
        }

        //�߿�
        setlinestyle(SOLID_LINE, NULL, 1);
        rectangle(XP - 1, YP - 1, W - XP, H - YP);

        //ͼƬ���
        putimage(img, 0, 0, NULL);
        getch();
        closegraph();

        //����
        cout << "����1���� ��������ֵ����:";
        cin >> quit;

        if(quit == 1){
            s.str("");
            s.precision(4);
            s << Lat << "_" << Lont << "_" << (int)South << ".png";
            savepng(img, s.str().c_str());
        }

    }

    closegraph();
    return 0;
}
