#define WIN32_LEAN_AND_MEAN

#include <malloc.h>
#include <stdlib.h>
#include <windows.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<tlhelp32.h>
#include<ctime>
#include<bits/stdc++.h>

using namespace std;


#define IDB_Use 1000
#define IDB_User 1001
#define IDB_T1 1002
#define IDB_Edit 1003
#define IDB_T2 1004
#define IDB_More 1005
#define IDB_Help 1006
#define IDB_txt 1007
#define IDB_Sitting 1008
#define IDB_T3 1009
#define IDB_T4 1010
#define IDB_T5 1011
#define IDB_E2 1012
#define IDB_Save 1013
#define IDB_T6 1014
#define IDB_S2 1015
#define IDB_s1 1016
#define IDB_rz 1017
#define IDB_Check_Update 1018 //我tm我前面那些名是干啥用的我都忘了。。。。。还是现在养成好习惯好 
#define IDB_Help_Update 1019 
#define IDB_Help_Update_Text 1020 



ofstream logs;



#define IDE_ITEMTEXT 2000

#define IDB_Tips 1003

char szClassName[] = "Windows App w/controls";
char text[] = "rbh";

string name[100];
int high[10]={0,-70,-75,-80,-85,-90,-95,-97,-98,-99},low[10]={0,20,30,40,50,60,70,80,90,100},n,p[101],p2[101];
string tips[9]={"","鸽了大半年的抽号器更新啦！！！更多抽号功能更新啦！！！设置更新啦！！！","提示：可以点击主界面上方的“查看日志”查看抽号历史","Copyright (C) 2018-2020 GZC, All Rights Reserved.","再闹，还在闹，再闹下一个就是你们几个","欢迎使用全新的抽号器\n抽号器_Insider Preview预览体验版本3.0.0.4","不是我想拉仇恨啊，**叫的更新","其实这个抽号器的代码前身是一个\nMinecraft Launcher（逃","整个抽号器去掉注释后一共760行代码！！"}; 
int user_num=0;
bool ex=false;
time_t last_time=time(NULL)-3;
time_t now_time;
int tn,n2;
int nt=0; 
int sm[2]={0,1};
int sr[2];
string str;//log路径 

HINSTANCE hApplicationInstance = NULL;

HWND hMainWindow = NULL;
//HWND hRemove = NULL;

HWND hT1 = NULL;
HWND hEdit = NULL;
HWND hT2 = NULL;
HWND hTips = NULL;
HWND hUse = NULL;
HWND hUser = NULL;
HWND hMore = NULL;
HWND hHelp = NULL;
HWND htxt = NULL;
HWND hSitting = NULL;
HWND hT3 = NULL;
HWND hT4 = NULL;
HWND hE2 = NULL;
HWND hSave = NULL;
HWND hT5 = NULL;
HWND hT6 = NULL;
HWND hS2 = NULL;
HWND hs1 = NULL;
HWND hrz = NULL;
HWND hCheck_Update = NULL;
HWND hHelp_Update = NULL;
HWND hHelp_Update_Text = NULL;





bool more=0,sitting=0,nf=0;

LRESULT AddItem(HWND hwnd, LPSTR lpstr); // This procedure adds an item to a listbox
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

string zh(int sz)
{
	stringstream ss;
    ss<<sz;
    return ss.str();
}
int zs(string sz)
{
	stringstream ss;
    ss<<sz;
    int s2;
    ss>>s2;
    return s2;
}
string ntime() 
{
	SYSTEMTIME curTime;
	GetLocalTime(&curTime);
	return "["+zh(curTime.wHour)+":"+zh(curTime.wMinute)+":"+zh(curTime.wSecond)+"]";
}
string program_name()
{
	char szFileFullPath[MAX_PATH],szProcessName[MAX_PATH];
	::GetModuleFileNameA(NULL, szFileFullPath, MAX_PATH);
	int length=::strlen(szFileFullPath);
	for (int i=length-1;i>=0;i--)
	{
		if (szFileFullPath[i]=='\\')
		{
			i++;
			for (int j=0;i<=length;j++)
			{
				szProcessName[j]=szFileFullPath[i++];
			}
			break;
		}
	}
	return szProcessName;
} 
int hm(const char* ProcessName) 
{
	int a=0;
	HANDLE hSnapshot;
	PROCESSENTRY32 lppe;
	BOOL Found;
	hSnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	lppe.dwSize=sizeof(PROCESSENTRY32);
	Found=Process32First(hSnapshot,&lppe);
	while(Found)
	{
        if(strcmpi(ProcessName,lppe.szExeFile)==0) a++;
		Found = Process32Next(hSnapshot,&lppe);
	}
	CloseHandle(hSnapshot);
	return a;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPSTR lpCommandLine, int nShowCommand)
{
	//读文件放在这
		//读文件
	//读文件
	CreateDirectory("logs", NULL); //创建日志文件夹
	
	SYSTEMTIME curTime;
	GetLocalTime(&curTime);
	//printf("%d %d %d %d %d %d",curTime.wYear,curTime.wMonth,curTime.wHour,curTime.wMinute,curTime.wSecond);
	str="logs\\"+zh(curTime.wYear)+"_"+zh(curTime.wMonth)+"_"+zh(curTime.wDay)+"_"+zh(curTime.wHour)+"-"+zh(curTime.wMinute)+"-"+zh(curTime.wSecond)+".log";
	
	cout<<str;
	logs.open(str.c_str());
	logs<<ntime()<<"日志记录开始"<<endl;
	
	srand(time(0));
	ifstream read;
	read.open("name");
	read>>n;
	n2=n;
	if(n==0) 
	{
		logs<<ntime()<<"检测不到姓名文件，创建姓名文件"<<endl;
		ofstream outfile;
		outfile.open("name");
		outfile.close();
		nf=1;
		
	}
	else
	{
		logs<<ntime()<<"开始读取姓名文件"<<endl;
		string reads;
		while(read>>reads)
		{
			nt++;
			if(reads[0]=='+')
			{
				p2[nt]=reads[1]-'0';
				p[nt]=high[reads[1]-'0'];
				name[nt]=reads.substr(2,reads.size()-1);
			}
			else if(reads[0]=='-')
			{
				p2[nt]=0-(reads[1]-'0');
				p[nt]=low[reads[1]-'0'];
				name[nt]=reads.substr(2,reads.size()-1);
			}
			else name[nt]=reads;
			if(name[nt]=="【空】") n2--;
		}
		read.close(); 
		logs<<ntime()<<"读取姓名文件完成"<<endl; 
	} 
	logs<<ntime()<<"开始读取配置文件"<<endl; 
	ifstream rt;
	rt.open("sitting.ini");
	string temp;
	getline(rt,temp);
	if(temp.size()==0)
	{
		rt.close();
		ofstream wt;
		wt.open("sitting.ini");
		wt<<"#Copyright (C) 2018-2020 GZC, All Rights Reserved.\n";
		for(int a=1;a<=(sizeof(sm)/4-1);a++) wt<<sm[a],sr[a]=sm[a];
		wt.close();
	}
	else for(int a=1;a<=(sizeof(sm)/4-1);a++) rt>>sr[a];
	rt.close();
	logs<<ntime()<<"读取配置文件完成"<<endl;
	
	//读文件结束
	
	
	
	 
	
	
	MSG messages;
	WNDCLASSEX wcex;

	hApplicationInstance = hInstance;

	wcex.cbClsExtra = 0;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.cbWndExtra = 0;
	wcex.hbrBackground = (HBRUSH)(COLOR_3DFACE+1);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hIcon = LoadIcon(hInstance, "A");
	wcex.hIconSm = LoadIcon(hInstance,"A");
	wcex.hInstance = hInstance;
	wcex.lpfnWndProc = WindowProcedure;
	wcex.lpszClassName = szClassName;
	wcex.lpszMenuName = NULL;
	wcex.style = CS_HREDRAW | CS_VREDRAW;


	if (!RegisterClassEx(&wcex))
		return 0;

//获取屏幕正中央
	int sx=GetSystemMetrics(SM_CXSCREEN);
	int sy=GetSystemMetrics(SM_CYSCREEN);
//获取屏幕正中央 End
	hMainWindow = CreateWindowEx(WS_EX_TOPMOST, szClassName, "抽号器3.0.0.4_测试版", /*WS_OVERLAPPEDWINDOW*/WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX, (sx-335)/2, (sy-195)/2, 335, 195, HWND_DESKTOP, NULL, hInstance, NULL);
	//是被改过的，原值为0

	if(hm((program_name()).c_str())>=2) 
	{
		logs<<ntime()<<"检测到本程序已运行，退出本程序"<<endl;
		return 0;
	}
	
	ShowWindow(hMainWindow, nShowCommand);
	//logs.close() ;
	

	 
	while(GetMessage(&messages, NULL, 0, 0))
	{
		if (!IsDialogMessage(hMainWindow, &messages))    // <-- Added
		{
			TranslateMessage(&messages);
			DispatchMessage(&messages);
		} // <-- Added
		if(ex) return 0;
		now_time = time(NULL);
		if(now_time-last_time>=3)
		{
			last_time=now_time;
			if(tn==3)tn=1;
			else tn++;
			SetWindowText(hTips, (tips[tn]).c_str());
		}
	}

	return (int)messages.wParam;
}

//名字是否符合


LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	HGDIOBJ hDefaultFont = NULL;
	 
	switch(uMsg)
	{

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_CREATE:
		{
			//字体 
			hDefaultFont  = (HFONT) GetStockObject(DEFAULT_GUI_FONT); // Gets the default font object 出问题，所以删除
			
			
			hUse = CreateWindow("button",  // Class name of our button; leave this alone.. what we want is button
			                       "单人抽号", /* Caption of our button; the and means the next character gets an
                                       underscore.  That allows the user to hit alternate and the underscored
                                       letter to use it.  In this case alt+r would be the same as clicking our
                                       button. */
			                       BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, /* BS_PUSHBUTTON - create a push button and have it post wm_command to the window proc when clicked
                                                                                WS_CHILD - this window is a child window
                                                                                WS_VISIBLE - we would like this window to be visible
                                                                                WS_TABSTOP - we want tab to enable the user to stop on this item
                                                                             */
			                       10, 10, 310, 30, // Size and position of the button
			                       hwnd, // Check the listbox for info on this
			                       (HMENU)IDB_Use, // Set our control ID for this control
			                       hApplicationInstance,
			                       NULL);

			SendMessage(hUse, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(FALSE, 0)); // Use the default font for our button
			
			hUser = CreateWindow("button",  // Class name of our button; leave this alone.. what we want is button
			                       "多人抽号", /* Caption of our button; the and means the next character gets an
                                       underscore.  That allows the user to hit alternate and the underscored
                                       letter to use it.  In this case alt+r would be the same as clicking our
                                       button. */
			                       BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, /* BS_PUSHBUTTON - create a push button and have it post wm_command to the window proc when clicked
                                                                                WS_CHILD - this window is a child window
                                                                                WS_VISIBLE - we would like this window to be visible
                                                                                WS_TABSTOP - we want tab to enable the user to stop on this item
                                                                             */
			                       225, 50, 95, 30, // Size and position of the button
			                       hwnd, // Check the listbox for info on this
			                       (HMENU)IDB_User, // Set our control ID for this control
			                       hApplicationInstance,
			                       NULL); 
			SendMessage(hUser, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(FALSE, 0)); 

			 
			hMore = CreateWindow("button",  // Class name of our button; leave this alone.. what we want is button
			                       "更多抽号功能 >", 
			                       BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, /* BS_PUSHBUTTON - create a push button and have it post wm_command to the window proc when clicked
                                                                                WS_CHILD - this window is a child window
                                                                                WS_VISIBLE - we would like this window to be visible
                                                                                WS_TABSTOP - we want tab to enable the user to stop on this item
                                                                             */
			                       200, 90, 120, 30, // Size and position of the button
			                       hwnd, // Check the listbox for info on this
			                       (HMENU)IDB_More, // Set our control ID for this control
			                       hApplicationInstance,
			                       NULL); 

			SendMessage(hMore, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(FALSE, 0)); 
			
			hHelp = CreateWindow("button",  // Class name of our button; leave this alone.. what we want is button
			                       "帮助", 
			                       BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, /* BS_PUSHBUTTON - create a push button and have it post wm_command to the window proc when clicked
                                                                                WS_CHILD - this window is a child window
                                                                                WS_VISIBLE - we would like this window to be visible
                                                                                WS_TABSTOP - we want tab to enable the user to stop on this item
                                                                             */
			                       10, 90, 60, 30, // Size and position of the button
			                       hwnd, // Check the listbox for info on this
			                       (HMENU)IDB_Help, // Set our control ID for this control
			                       hApplicationInstance,
			                       NULL); 

			SendMessage(hHelp, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(FALSE, 0)); 
			
			htxt = CreateWindow("button",  // Class name of our button; leave this alone.. what we want is button
			                       "更新日志", 
			                       BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, /* BS_PUSHBUTTON - create a push button and have it post wm_command to the window proc when clicked
                                                                                WS_CHILD - this window is a child window
                                                                                WS_VISIBLE - we would like this window to be visible
                                                                                WS_TABSTOP - we want tab to enable the user to stop on this item
                                                                             */
			                       80, 90, 60, 30, // Size and position of the button
			                       hwnd, // Check the listbox for info on this
			                       (HMENU)IDB_txt, // Set our control ID for this control
			                       hApplicationInstance,
			                       NULL); 

			SendMessage(htxt, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(FALSE, 0)); 
			
			hrz = CreateWindow("button",  // Class name of our button; leave this alone.. what we want is button
			                       "查看日志", 
			                       BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, /* BS_PUSHBUTTON - create a push button and have it post wm_command to the window proc when clicked
                                                                                WS_CHILD - this window is a child window
                                                                                WS_VISIBLE - we would like this window to be visible
                                                                                WS_TABSTOP - we want tab to enable the user to stop on this item
                                                                             */
			                       10, 50, 60, 30, // Size and position of the button
			                       hwnd, // Check the listbox for info on this
			                       (HMENU)IDB_rz, // Set our control ID for this control
			                       hApplicationInstance,
			                       NULL); 

			SendMessage(hrz, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(FALSE, 0)); 
			
			hSitting = CreateWindow("button",  // Class name of our button; leave this alone.. what we want is button
			                       "设置 ﹀", 
			                       BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, /* BS_PUSHBUTTON - create a push button and have it post wm_command to the window proc when clicked
                                                                                WS_CHILD - this window is a child window
                                                                                WS_VISIBLE - we would like this window to be visible
                                                                                WS_TABSTOP - we want tab to enable the user to stop on this item
                                                                             */
			                       270, 140, 50, 20, // Size and position of the button
			                       hwnd, // Check the listbox for info on this
			                       (HMENU)IDB_Sitting, // Set our control ID for this control
			                       hApplicationInstance,
			                       NULL); 

			SendMessage(hSitting, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(FALSE, 0)); 
			
			hSave = CreateWindow("button",  // Class name of our button; leave this alone.. what we want is button
			                       "保存", 
			                       BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, /* BS_PUSHBUTTON - create a push button and have it post wm_command to the window proc when clicked
                                                                                WS_CHILD - this window is a child window
                                                                                WS_VISIBLE - we would like this window to be visible
                                                                                WS_TABSTOP - we want tab to enable the user to stop on this item
                                                                             */
			                       130, 180, 60, 20, // Size and position of the button
			                       hwnd, // Check the listbox for info on this
			                       (HMENU)IDB_Save, // Set our control ID for this control
			                       hApplicationInstance,
			                       NULL); 

			SendMessage(hSave, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(FALSE, 0)); 
			
			hS2 = CreateWindow("button",  // Class name of our button; leave this alone.. what we want is button
			                       "这里", 
			                       BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, /* BS_PUSHBUTTON - create a push button and have it post wm_command to the window proc when clicked
                                                                                WS_CHILD - this window is a child window
                                                                                WS_VISIBLE - we would like this window to be visible
                                                                                WS_TABSTOP - we want tab to enable the user to stop on this item
                                                                             */
			                       195, 205, 40, 20, // Size and position of the button
			                       hwnd, // Check the listbox for info on this
			                       (HMENU)IDB_S2, // Set our control ID for this control
			                       hApplicationInstance,
			                       NULL); 

			SendMessage(hS2, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(FALSE, 0)); 
			//cout<<sr[1];
			hs1 = CreateWindow("button",  // Class name of our button; leave this alone.. what we want is button
			                       (sr[1])?"多人抽号时排序:开":"多人抽号时排序:关", 
			                       BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, /* BS_PUSHBUTTON - create a push button and have it post wm_command to the window proc when clicked
                                                                                WS_CHILD - this window is a child window
                                                                                WS_VISIBLE - we would like this window to be visible
                                                                                WS_TABSTOP - we want tab to enable the user to stop on this item
                                                                             */
			                       5, 230, 120, 20, // Size and position of the button
			                       hwnd, // Check the listbox for info on this
			                       (HMENU)IDB_s1, // Set our control ID for this control
			                       hApplicationInstance,
			                       NULL); 
			SendMessage(hs1, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(FALSE, 0)); 

			                       
			hCheck_Update = CreateWindow("button",  // Class name of our button; leave this alone.. what we want is button
			                       "检查更新", 
			                       BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, /* BS_PUSHBUTTON - create a push button and have it post wm_command to the window proc when clicked
                                                                                WS_CHILD - this window is a child window
                                                                                WS_VISIBLE - we would like this window to be visible
                                                                                WS_TABSTOP - we want tab to enable the user to stop on this item
                                                                             */
			                       140, 230, 60, 20, // Size and position of the button
			                       hwnd, // Check the listbox for info on this
			                       (HMENU)IDB_Check_Update, // Set our control ID for this control
			                       hApplicationInstance,
			                       NULL); 

			SendMessage(hCheck_Update, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(FALSE, 0)); 
			
			hHelp_Update = CreateWindow("button",  // Class name of our button; leave this alone.. what we want is button
			                       "这里", 
			                       BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, /* BS_PUSHBUTTON - create a push button and have it post wm_command to the window proc when clicked
                                                                                WS_CHILD - this window is a child window
                                                                                WS_VISIBLE - we would like this window to be visible
                                                                                WS_TABSTOP - we want tab to enable the user to stop on this item
                                                                             */
			                       480, 70, 40, 20, // Size and position of the button
			                       hwnd, // Check the listbox for info on this
			                       (HMENU)IDB_Help_Update, // Set our control ID for this control
			                       hApplicationInstance,
			                       NULL); 

			SendMessage(hHelp_Update, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(FALSE, 0)); 
			
			hT1 = CreateWindow("STATIC",  // Class name of our button; leave this alone.. what we want is button
			                         "每次抽", /* Caption of our button; the and means the next character gets an
                                       underscore.  That allows the user to hit alternate and the underscored
                                       letter to use it.  In this case alt+r would be the same as clicking our
                                       button. */
			                         BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, /* BS_PUSHBUTTON - create a push button and have it post wm_command to the window proc when clicked
                                                                                WS_CHILD - this window is a child window
                                                                                WS_VISIBLE - we would like this window to be visible
                                                                                WS_TABSTOP - we want tab to enable the user to stop on this item
                                                                             */
			                         150, 57, 40, 20, // Size and position of the button
			                         hwnd, // Check the listbox for info on this
			                         (HMENU)IDB_T1, // 此按钮的ID
			                         hApplicationInstance,
			                         NULL);
			SendMessage(hT1, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(FALSE, 0));
			
			hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, // Put a border on the control
			                       "Edit",
			                       "",
			                       WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL, 
			                       188, 55, 20, 20,
			                       hwnd,
			                       (HMENU)IDE_ITEMTEXT,
			                       hApplicationInstance,
			                       NULL);

			SendMessage(hEdit, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(FALSE, 0)); 
			
			hE2 = CreateWindowEx(WS_EX_CLIENTEDGE, // Put a border on the control
			                       "Edit",
			                       "",
			                       WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL, 
			                       85, 180, 20, 20,
			                       hwnd,
			                       (HMENU)IDB_E2,
			                       hApplicationInstance,
			                       NULL);

			SendMessage(hE2, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(FALSE, 0)); 
			
			hT2 = CreateWindow("STATIC",  // Class name of our button; leave this alone.. what we want is button
			                         "人", /* Caption of our button; the and means the next character gets an
                                       underscore.  That allows the user to hit alternate and the underscored
                                       letter to use it.  In this case alt+r would be the same as clicking our
                                       button. */
			                         BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, /* BS_PUSHBUTTON - create a push button and have it post wm_command to the window proc when clicked
                                                                                WS_CHILD - this window is a child window
                                                                                WS_VISIBLE - we would like this window to be visible
                                                                                WS_TABSTOP - we want tab to enable the user to stop on this item
                                                                             */
			                         210, 57, 15, 20, // Size and position of the button
			                         hwnd, // Check the listbox for info on this
			                         (HMENU)IDB_T2, // 此按钮的ID
			                         hApplicationInstance,
			                         NULL);
			SendMessage(hT2, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(FALSE, 0));
			
			hT3 = CreateWindow("STATIC",  // Class name of our button; leave this alone.. what we want is button
			                         "更多精彩功能敬请期待\n（电教：咕咕咕）", /* Caption of our button; the and means the next character gets an
                                       underscore.  That allows the user to hit alternate and the underscored
                                       letter to use it.  In this case alt+r would be the same as clicking our
                                       button. */
			                         BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, /* BS_PUSHBUTTON - create a push button and have it post wm_command to the window proc when clicked
                                                                                WS_CHILD - this window is a child window
                                                                                WS_VISIBLE - we would like this window to be visible
                                                                                WS_TABSTOP - we want tab to enable the user to stop on this item
                                                                             */
			                         340, 10, 120, 40, // Size and position of the button
			                         hwnd, // Check the listbox for info on this
			                         (HMENU)IDB_T3, // 此按钮的ID
			                         hApplicationInstance,
			                         NULL);
			SendMessage(hT3, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(FALSE, 0));
			
			hHelp_Update_Text = CreateWindow("STATIC",  // Class name of our button; leave this alone.. what we want is button
			                         "如果希望帮助我填这里这个坑，或者查看抽号器的代码，请点击", /* Caption of our button; the and means the next character gets an
                                       underscore.  That allows the user to hit alternate and the underscored
                                       letter to use it.  In this case alt+r would be the same as clicking our
                                       button. */
			                         BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, /* BS_PUSHBUTTON - create a push button and have it post wm_command to the window proc when clicked
                                                                                WS_CHILD - this window is a child window
                                                                                WS_VISIBLE - we would like this window to be visible
                                                                                WS_TABSTOP - we want tab to enable the user to stop on this item
                                                                             */
			                         340, 40, 180, 30, // Size and position of the button
			                         hwnd, // Check the listbox for info on this
			                         (HMENU)IDB_Help_Update_Text, // 此按钮的ID
			                         hApplicationInstance,
			                         NULL);
			SendMessage(hHelp_Update_Text, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(FALSE, 0));
			
			hT4 = CreateWindow("STATIC",  // Class name of our button; leave this alone.. what we want is button
			                         "抽号范围：1-", /* Caption of our button; the and means the next character gets an
                                       underscore.  That allows the user to hit alternate and the underscored
                                       letter to use it.  In this case alt+r would be the same as clicking our
                                       button. */
			                         BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, /* BS_PUSHBUTTON - create a push button and have it post wm_command to the window proc when clicked
                                                                                WS_CHILD - this window is a child window
                                                                                WS_VISIBLE - we would like this window to be visible
                                                                                WS_TABSTOP - we want tab to enable the user to stop on this item
                                                                             */
			                         10, 180, 75, 20, // Size and position of the button
			                         hwnd, // Check the listbox for info on this
			                         (HMENU)IDB_T4, // 此按钮的ID
			                         hApplicationInstance,
			                         NULL);
			SendMessage(hT4, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(FALSE, 0));
			
			hT5 = CreateWindow("STATIC",  // Class name of our button; leave this alone.. what we want is button
			                         "号", /* Caption of our button; the and means the next character gets an
                                       underscore.  That allows the user to hit alternate and the underscored
                                       letter to use it.  In this case alt+r would be the same as clicking our
                                       button. */
			                         BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, /* BS_PUSHBUTTON - create a push button and have it post wm_command to the window proc when clicked
                                                                                WS_CHILD - this window is a child window
                                                                                WS_VISIBLE - we would like this window to be visible
                                                                                WS_TABSTOP - we want tab to enable the user to stop on this item
                                                                             */
			                         107, 180, 20, 20, // Size and position of the button
			                         hwnd, // Check the listbox for info on this
			                         (HMENU)IDB_T5, // 此按钮的ID
			                         hApplicationInstance,
			                         NULL);
			SendMessage(hT5, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(FALSE, 0));
			
			hT6 = CreateWindow("STATIC",  // Class name of our button; leave this alone.. what we want is button
			                         "如要设置姓名等高级功能，请点击", /* Caption of our button; the and means the next character gets an
                                       underscore.  That allows the user to hit alternate and the underscored
                                       letter to use it.  In this case alt+r would be the same as clicking our
                                       button. */
			                         BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, /* BS_PUSHBUTTON - create a push button and have it post wm_command to the window proc when clicked
                                                                                WS_CHILD - this window is a child window
                                                                                WS_VISIBLE - we would like this window to be visible
                                                                                WS_TABSTOP - we want tab to enable the user to stop on this item
                                                                             */
			                         10, 210, 180, 20, // Size and position of the button
			                         hwnd, // Check the listbox for info on this
			                         (HMENU)IDB_T6, // 此按钮的ID
			                         hApplicationInstance,
			                         NULL);
			SendMessage(hT6, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(FALSE, 0));

			
			
			hTips = CreateWindow("STATIC",  // Class name of our button; leave this alone.. what we want is button
			                         "", /* Caption of our button; the and means the next character gets an
                                       underscore.  That allows the user to hit alternate and the underscored
                                       letter to use it.  In this case alt+r would be the same as clicking our
                                       button. */
			                         BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, /* BS_PUSHBUTTON - create a push button and have it post wm_command to the window proc when clicked
                                                                                WS_CHILD - this window is a child window
                                                                                WS_VISIBLE - we would like this window to be visible
                                                                                WS_TABSTOP - we want tab to enable the user to stop on this item
                                                                             */
			                         5, 140, 265, 30, // Size and position of the button
			                         hwnd, // Check the listbox for info on this
			                         (HMENU)IDB_Tips, // 此按钮的ID
			                         hApplicationInstance,
			                         NULL);
			SendMessage(hTips, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(FALSE, 0));
			
			

			//瞎JB修改第一处结束

		}


		case WM_COMMAND:
		{
			//logs.open(str.c_str());

			// See, the loword of the wparam holds the control id's, so do a switch between them to handle them correct

			switch(LOWORD(wParam))
			{
				case IDB_Use:    
				{
					if(nf) 
					{
						logs<<ntime()<<"未设置抽号范围，抽号失败"<<endl;
						MessageBox(GetActiveWindow(),"您未设置抽号范围，请在下方设置。","抽号器_测试版 - 提示",0+48); 
						SetWindowPos(hMainWindow,NULL,NULL,NULL,335, 300,SWP_NOMOVE|SWP_NOZORDER),sitting=1,more=0,SetWindowText(hSitting,"设置 ︿"),SetWindowText(hMore,"更多抽号功能 >");
					}
					else
					{
						ShowWindow(hwnd,SW_HIDE);
						logs<<ntime()<<"进入单人抽号"<<endl;
						while(true)
						{
							int e=rand()%n+1;
							int second=rand()%(100+p[e])+1; 
							if(name[e]!="【空】"&&second==1)
							{
								int j=MessageBox(GetActiveWindow(),("本次抽到的是第"+zh(e)+"号同学"+name[e]+"。 \n[确定]再抽一次  [取消]不抽了").c_str(),"抽号器_测试版",1+32);  
								logs<<ntime()<<"抽到"+zh(e)+"号"+name[e]<<endl;
								if(j==2)break;
							}
						} 
						int l=MessageBox(GetActiveWindow(),"[确定]返回主页  [取消]退出程序\n输入你想要的操作 然后回车。","抽号器_测试版 - 提示",1+48);  
						if(l==2)ex=1;  
						else ShowWindow(hwnd,SW_SHOWNORMAL);	
					}
					break;
				}
							
				case IDB_User:    
				{
					if(nf) 
					{
						MessageBox(GetActiveWindow(),"您未设置抽号范围，请在下方设置。","抽号器_测试版 - 提示",0+48); 
						SetWindowPos(hMainWindow,NULL,NULL,NULL,335, 300,SWP_NOMOVE|SWP_NOZORDER),sitting=1,more=0,SetWindowText(hSitting,"设置 ︿"),SetWindowText(hMore,"更多抽号功能 >");
					}
					else
					{ 
						char *NewItem; // Pointer to the new item's text
						int nTextLen = (int)SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0); // Get the length of the edit box
						if (nTextLen > 0)    // If the text lenght is greater than 0 then
						{

							NewItem = (char*)malloc(nTextLen); // allocate the new space for the text

							//读取内容……我艹
							DWORD dwTextLength = GetWindowTextLength(hEdit);
							LPSTR pszText;
							pszText = LPSTR(GlobalAlloc(GPTR, dwTextLength + 1));
							GetWindowText(hEdit, pszText, dwTextLength + 1);
							string x=pszText;
							bool num=0;
							for(int a=0;a<x.size();a++) if(x[a]>'9'||x[a]<'0') num=1;
							if(num) 
							{
								logs<<ntime()<<"输入的抽号人数含有非法字符"<<endl;
								SetWindowText(hEdit, "");
								MessageBox(GetActiveWindow(),"请输入正整数","抽号器_测试版 - 提示",MB_OK+48);
							}
							else 
							{
								int xn=zs(x);
								if(xn>n2) 
								{
									logs<<ntime()<<"输入的抽号人数大于班级人数"<<endl;
									SetWindowText(hEdit, "");
									MessageBox(GetActiveWindow(),"请输入的数字不要大于班级人数","抽号器_测试版 - 提示",MB_OK+48);
								}
								else if(xn==0) 
								{
									logs<<ntime()<<"输入的抽号人数小于0"<<endl;
									SetWindowText(hEdit, "");
									MessageBox(GetActiveWindow(),"请输入的数字不要等于0","抽号器_测试版 - 提示",MB_OK+48);
								}
								else 
								{
									logs<<ntime()<<"进入多人抽号"<<endl;
									ShowWindow(hwnd,SW_HIDE);
									while(true)
									{
										cout<<xn;
										string out="本次抽到的是\n";
										int c[101]={0};
										for(int a=1;a<=xn;)
										{
											bool go=1;
											int e=rand()%n+1;
											int second=rand()%(100+p[e])+1; 
											if(name[e]!="【空】"&&second==1) 
											{
												for(int b=1;b<=a;b++)
												if(e==c[b]) go=0;
												if(go) 
												{
													c[a]=e;
													a++;
												}
											}
										}
										if(sr[1]) sort(c+1,c+1+xn);
										logs<<ntime()<<"抽到";
										for(int a=1;a<=xn;a++)
										{
											logs<<zh(c[a])+"号"+name[c[a]]+"、";
											out+=zh(c[a]);
											out+="号同学";
											out+=name[c[a]];
											if(a!=xn) out+="、"; 
											if(a%3==0&&a!=xn) out+="\n";
										}
										logs<<endl;
										int j=MessageBox(GetActiveWindow(),(out+"。 \n\n[确定]再抽一次  [取消]不抽了").c_str(),"抽号器_测试版",1+32);  
										if(j==2)break;
									}
									int l=MessageBox(GetActiveWindow(),"[确定]返回主页  [取消]退出程序\n输入你想要的操作 然后回车。","抽号器_测试版 - 提示",1+48);  
									if(l==2)ex=1;  
									else ShowWindow(hwnd,SW_SHOWNORMAL);
								}
							}
							break;
						}
							 

						
						else
						{
							MessageBox(GetActiveWindow(),"请输入一次要抽取的人数","抽号器_测试版 - 提示",MB_OK+48);
						}
					}
					break;
				}
				
				case IDB_More:    
				{
					if(more==0) SetWindowPos(hMainWindow,NULL,NULL,NULL,535, 195,SWP_NOMOVE|SWP_NOZORDER),more=1,sitting=0,SetWindowText(hMore,"< 更多抽号功能"),SetWindowText(hSitting,"设置 ﹀");
					else SetWindowPos(hMainWindow,NULL,NULL,NULL,335, 195,SWP_NOMOVE|SWP_NOZORDER),more=0,sitting=0,SetWindowText(hMore,"更多抽号功能 >"),SetWindowText(hSitting,"设置 ﹀");
					break;
				}
				
				case IDB_Help:    
				{
					MessageBox(GetActiveWindow(),"Copyright (C) 2018-2020 GZC, All Rights Reserved.\n使用说明\n 作用：抽取座号（废话-_-）\n\n 点击“正常抽号，一次将抽取一个人”\n 点击“再闹，还在闹，下一个就是你们几个”时，一次将根据输入框的内容抽取对应人数\n 点击“更多抽号功能”，可以使用譬如只抽男生，只抽女生，自定义抽号范围等功能（暂未开放，估计这辈子都不会开放的-_-）\n 点击设置，设置抽号器","随机座号抽取器_测试版 - 使用说明",0+32);
					break;
				}
				
				case IDB_txt:    
				{
					ofstream outfile;
					outfile.open("更新日志.txt");
					outfile<<"更新日志\n2018-04-18 中午-抽号器第一行代码……\n2018-04-18 13:44-1.0 想当初，抽号器第一个版本还是控制台窗口：\n    填了Waiting看时间抽号的坑（这也算是更新？）\n2018-04-18 20:05-1.1 连夜赶bug只为更好：\n    大幅度增加了随机数抽取的公正性\n    修复了连续抽会抽到同一个座号的BUG\n    修复抽到【空】位置向前推移三个座号的BUG\n    增加了 自检\n2018-04-20 18:49-1.2 让抽号器死循环无限抽？这个bug不错，可惜没了：\n    修复了数值越界导致死循环的BUG\n2018-5-3 20:00-1.3 很多人强烈要求要给1号设高频，然而从此版本至今，还无人被设过高频：\n    增加了高频和低频设置\n2018-05-03 20:13-1.3.1 像模像样了，有图标了：\n    内嵌了图标 版本号等信息\n2018-5-15-19:42-2.0 终于抛弃了难看难操作的控制台 换成了“窗体”，然而那只是消息框，在XP下看起来也不咋地：\n    完全使用窗体显示。 移除了自检功能\n    修复进行一次抽号后返回主页再抽号的姓名显示永远显示最后一号的BUG\n2018-06-20 10:08-2.1 你喜欢玩，我喜欢坑。只能同时开一个，让你怎么玩；只是干巴巴的文字不好玩，有图片才好看：\n    限制只能同时运行一个抽号器\n    优化了视觉显示\n2018-09-24 15:47-2.1.1 强行顶置很烦，如果可以暂时最小化呢；删抽号器很好玩，那如果删不了呢：\n    emmmU盘落电脑室了 所以重新构造了代码\n    删除了然并卵的高频低频设置\n    优化了限制运行一个程序的代码 修复了非正常结束导致抽号器无法打开的BUG\n    优化了使用说明\n    优化了文件读取代码\n    优化了使用体验(虽然没有最小化按钮 但是单击任何其他窗口即可最小化且可以通过任务栏显示)\n    主界面显示程序类型(32位或64位)\n    增加了附属程序检测添加快捷方式\n2018-09-24 17:13-2.2集体的力量是强大的，在某些情况下甚至可以改变一个人的主意：\n    优化了高低频算法(您们喜欢的高频又来了 高兴吗)\n2018-12-21 22:31-2.3 只是为了方便老师拷贝做的更新:\n    优化了检测多个实例运行的代码，修复了改名后无法检测的BUG\n    优化了没有进行设置时的提示\n    移除了更新日志加了一层，更新日志增加了日期\n2019-02-10 00:10-_测试版3.0.0.0 应**要求的一个更新：\n    一次能抽多个人\n    主页采用真正的窗体（然而更丑了）\n    抽多个人时检测是否抽过（至少不会一页几个一样的人了）\n    优化了使用说明和更新日志\n    优化了设置 \n2019-02-10 13:41-_测试版3.0.0.1 DEBUG：\n    修复了设置后名字丢失的bug\n    优化了其他使用体验\n    修复了首次使用设置完崩溃的bug \n2019-03-06 21:03-_测试版3.0.0.2 DEBUG：\n    修复了设置人数后抽多人卡死的bug\n    修复了抽多人下一次没有清空数组的bug\n    和谐了部分文字\n    加入了高级设置的雏形\n2019-05-19 15:03-_测试版3.0.0.3 日志更新：\n    增加了日志功能，在主界面可以看到\n2019-12-28 15:58-_测试版3.0.0.4 鸽子更新：\n    增加了官网，欢迎帮我填坑\n\n未完待续……";
					outfile.close();
					WinExec("notepad.exe 更新日志.txt",SW_SHOWMAXIMIZED);
					break;
				}
				
				case IDB_rz:    
				{
					WinExec("explorer.exe logs",SW_SHOWMAXIMIZED);
					break;
				}
				
				case IDB_Sitting:    
				{
					if(n!=0) SetWindowText(hE2, zh(n).c_str());
					if(sitting==0) SetWindowPos(hMainWindow,NULL,NULL,NULL,335, 300,SWP_NOMOVE|SWP_NOZORDER),sitting=1,more=0,SetWindowText(hSitting,"设置 ︿"),SetWindowText(hMore,"更多抽号功能 >");
					else SetWindowPos(hMainWindow,NULL,NULL,NULL,335, 195,SWP_NOMOVE|SWP_NOZORDER),sitting=0,more=0,SetWindowText(hSitting,"设置 ﹀"),SetWindowText(hMore,"更多抽号功能 >");
					break;
				}
				
				case IDB_Save:    
				{
					char *NewItem; // Pointer to the new item's text
					int nTextLen = (int)SendMessage(hE2, WM_GETTEXTLENGTH, 0, 0); // Get the length of the edit box
					if (nTextLen > 0)    // If the text lenght is greater than 0 then
					{
						NewItem = (char*)malloc(nTextLen); // allocate the new space for the text
						//读取内容……我艹
						DWORD dwTextLength = GetWindowTextLength(hE2);
						LPSTR pszText;
						pszText = LPSTR(GlobalAlloc(GPTR, dwTextLength + 1));
						GetWindowText(hE2, pszText, dwTextLength + 1);
						string x=pszText;
						cout<<x;
						bool num=0;
						for(int a=0;a<x.size();a++) if(x[a]>'9'||x[a]<'0') num=1;
						if(num) 
						{
							SetWindowText(hE2, "");
							MessageBox(GetActiveWindow(),"请输入整数","抽号器_测试版 - 提示",MB_OK+48);
						}
						else 
						{
							int xn=zs(x);
							if(xn==0) 
							{
								SetWindowText(hE2, "");
								MessageBox(GetActiveWindow(),"请输入的数字不要等于0","抽号器_测试版 - 提示",MB_OK+48);
							}
							else 
							{
								nf=0;
								ofstream outfile;
								outfile.open("name");
								outfile<<xn<<endl;
								n=xn;
								for(int a=1;a<=nt;a++) 
								{
									if(p2[a]>0) 
									{
										outfile<<"+";
										outfile<<p2[a];
									}
									else if(p2[a]<0) outfile<<p2[a];
									
									outfile<<name[a]<<endl;
								}
								outfile.close();
								n2=n;
								for(int a=1;a<=n;a++) if(name[a]=="【空】") n2--;
								
							
								MessageBox(GetActiveWindow(),"保存成功。\n如需设置姓名请点击下面的“这里”\n如需使用其他高级抽号功能请点击上方的“更多抽号功能”","抽号器_测试版 - 提示",0+48);

							}
						}
					}
					else 
					{
						MessageBox(GetActiveWindow(),"请输入抽号范围以保存","抽号器_测试版 - 提示",MB_OK+48);
					}
					break;
				}
				
				case IDB_S2:    
				{
					MessageBox(GetActiveWindow(),"Copyright (C) 2018-2020 GZC, All Rights Reserved.\n如何设置抽号器？\n请在按[确定]之后打开的文件的第一行输入班里的最高座号n（即抽号范围为1~n）\n如果需要显示名字，请在那个文件的2~n+1行依次输入座号对应的名字\nTips1:如果此座号的人为空，则用【空】来代替名字的位置，抽号时会自动跳过\nTips2:如果需要高频低频设置，请在名字前面打+/-，[+高频 -低频]，且不要有空格\n如“+9WAITING”、“-4MORNING”\n\n完成后保存并重启抽号器即可","抽号器_测试版 - 设置提示",0+32);
					WinExec("notepad.exe name",SW_SHOWMAXIMIZED);
					ex=1;
					break;
				}
				
				case IDB_s1:    
				{
					if(sr[1])
					{
						sr[1]=0;
						SetWindowText(hs1,"多人抽号时排序:关");
						ofstream wt;
						wt.open("sitting.ini");
						wt<<"#Copyright (C) 2018-2020 GZC, All Rights Reserved.\n";
						for(int a=1;a<=(sizeof(sm)/4-1);a++) wt<<sr[a];
						wt.close();
					}
					else
					{
						sr[1]=1;
						SetWindowText(hs1,"多人抽号时排序:开");
						ofstream wt;
						wt.open("sitting.ini");
						wt<<"#Copyright (C) 2018-2020 GZC, All Rights Reserved.\n";
						for(int a=1;a<=(sizeof(sm)/4-1);a++) wt<<sr[a];
						wt.close();
					}
					break;
				}
				
				case IDB_Check_Update:    
				{
					WinExec("explorer.exe https://github.com/Dian-Jiao/Rant-Int-Machine",SW_SHOWMAXIMIZED);
					break;
				}
				case IDB_Help_Update:    
				{
					WinExec("explorer.exe https://github.com/Dian-Jiao/Rant-Int-Machine",SW_SHOWMAXIMIZED);
					break;
				}
				
			}

		}


		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}


