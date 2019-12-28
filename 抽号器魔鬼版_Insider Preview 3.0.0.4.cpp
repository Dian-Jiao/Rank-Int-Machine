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
#define IDB_Check_Update 1018 //��tm��ǰ����Щ���Ǹ�ɶ�õ��Ҷ����ˡ��������������������ɺ�ϰ�ߺ� 
#define IDB_Help_Update 1019 
#define IDB_Help_Update_Text 1020 



ofstream logs;



#define IDE_ITEMTEXT 2000

#define IDB_Tips 1003

char szClassName[] = "Windows App w/controls";
char text[] = "rbh";

string name[100];
int high[10]={0,-70,-75,-80,-85,-90,-95,-97,-98,-99},low[10]={0,20,30,40,50,60,70,80,90,100},n,p[101],p2[101];
string tips[9]={"","���˴����ĳ���������������������Ź��ܸ��������������ø�����������","��ʾ�����Ե���������Ϸ��ġ��鿴��־���鿴�����ʷ","Copyright (C) 2018-2020 GZC, All Rights Reserved.","���֣������֣�������һ���������Ǽ���","��ӭʹ��ȫ�µĳ����\n�����_Insider PreviewԤ������汾3.0.0.4","������������ް���**�еĸ���","��ʵ���������Ĵ���ǰ����һ��\nMinecraft Launcher����","���������ȥ��ע�ͺ�һ��760�д��룡��"}; 
int user_num=0;
bool ex=false;
time_t last_time=time(NULL)-3;
time_t now_time;
int tn,n2;
int nt=0; 
int sm[2]={0,1};
int sr[2];
string str;//log·�� 

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
	//���ļ�������
		//���ļ�
	//���ļ�
	CreateDirectory("logs", NULL); //������־�ļ���
	
	SYSTEMTIME curTime;
	GetLocalTime(&curTime);
	//printf("%d %d %d %d %d %d",curTime.wYear,curTime.wMonth,curTime.wHour,curTime.wMinute,curTime.wSecond);
	str="logs\\"+zh(curTime.wYear)+"_"+zh(curTime.wMonth)+"_"+zh(curTime.wDay)+"_"+zh(curTime.wHour)+"-"+zh(curTime.wMinute)+"-"+zh(curTime.wSecond)+".log";
	
	cout<<str;
	logs.open(str.c_str());
	logs<<ntime()<<"��־��¼��ʼ"<<endl;
	
	srand(time(0));
	ifstream read;
	read.open("name");
	read>>n;
	n2=n;
	if(n==0) 
	{
		logs<<ntime()<<"��ⲻ�������ļ������������ļ�"<<endl;
		ofstream outfile;
		outfile.open("name");
		outfile.close();
		nf=1;
		
	}
	else
	{
		logs<<ntime()<<"��ʼ��ȡ�����ļ�"<<endl;
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
			if(name[nt]=="���ա�") n2--;
		}
		read.close(); 
		logs<<ntime()<<"��ȡ�����ļ����"<<endl; 
	} 
	logs<<ntime()<<"��ʼ��ȡ�����ļ�"<<endl; 
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
	logs<<ntime()<<"��ȡ�����ļ����"<<endl;
	
	//���ļ�����
	
	
	
	 
	
	
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

//��ȡ��Ļ������
	int sx=GetSystemMetrics(SM_CXSCREEN);
	int sy=GetSystemMetrics(SM_CYSCREEN);
//��ȡ��Ļ������ End
	hMainWindow = CreateWindowEx(WS_EX_TOPMOST, szClassName, "�����3.0.0.4_���԰�", /*WS_OVERLAPPEDWINDOW*/WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX, (sx-335)/2, (sy-195)/2, 335, 195, HWND_DESKTOP, NULL, hInstance, NULL);
	//�Ǳ��Ĺ��ģ�ԭֵΪ0

	if(hm((program_name()).c_str())>=2) 
	{
		logs<<ntime()<<"��⵽�����������У��˳�������"<<endl;
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

//�����Ƿ����


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
			//���� 
			hDefaultFont  = (HFONT) GetStockObject(DEFAULT_GUI_FONT); // Gets the default font object �����⣬����ɾ��
			
			
			hUse = CreateWindow("button",  // Class name of our button; leave this alone.. what we want is button
			                       "���˳��", /* Caption of our button; the and means the next character gets an
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
			                       "���˳��", /* Caption of our button; the and means the next character gets an
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
			                       "�����Ź��� >", 
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
			                       "����", 
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
			                       "������־", 
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
			                       "�鿴��־", 
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
			                       "���� ��", 
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
			                       "����", 
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
			                       "����", 
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
			                       (sr[1])?"���˳��ʱ����:��":"���˳��ʱ����:��", 
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
			                       "������", 
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
			                       "����", 
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
			                         "ÿ�γ�", /* Caption of our button; the and means the next character gets an
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
			                         (HMENU)IDB_T1, // �˰�ť��ID
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
			                         "��", /* Caption of our button; the and means the next character gets an
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
			                         (HMENU)IDB_T2, // �˰�ť��ID
			                         hApplicationInstance,
			                         NULL);
			SendMessage(hT2, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(FALSE, 0));
			
			hT3 = CreateWindow("STATIC",  // Class name of our button; leave this alone.. what we want is button
			                         "���ྫ�ʹ��ܾ����ڴ�\n����̣���������", /* Caption of our button; the and means the next character gets an
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
			                         (HMENU)IDB_T3, // �˰�ť��ID
			                         hApplicationInstance,
			                         NULL);
			SendMessage(hT3, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(FALSE, 0));
			
			hHelp_Update_Text = CreateWindow("STATIC",  // Class name of our button; leave this alone.. what we want is button
			                         "���ϣ������������������ӣ����߲鿴������Ĵ��룬����", /* Caption of our button; the and means the next character gets an
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
			                         (HMENU)IDB_Help_Update_Text, // �˰�ť��ID
			                         hApplicationInstance,
			                         NULL);
			SendMessage(hHelp_Update_Text, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(FALSE, 0));
			
			hT4 = CreateWindow("STATIC",  // Class name of our button; leave this alone.. what we want is button
			                         "��ŷ�Χ��1-", /* Caption of our button; the and means the next character gets an
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
			                         (HMENU)IDB_T4, // �˰�ť��ID
			                         hApplicationInstance,
			                         NULL);
			SendMessage(hT4, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(FALSE, 0));
			
			hT5 = CreateWindow("STATIC",  // Class name of our button; leave this alone.. what we want is button
			                         "��", /* Caption of our button; the and means the next character gets an
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
			                         (HMENU)IDB_T5, // �˰�ť��ID
			                         hApplicationInstance,
			                         NULL);
			SendMessage(hT5, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(FALSE, 0));
			
			hT6 = CreateWindow("STATIC",  // Class name of our button; leave this alone.. what we want is button
			                         "��Ҫ���������ȸ߼����ܣ�����", /* Caption of our button; the and means the next character gets an
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
			                         (HMENU)IDB_T6, // �˰�ť��ID
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
			                         (HMENU)IDB_Tips, // �˰�ť��ID
			                         hApplicationInstance,
			                         NULL);
			SendMessage(hTips, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(FALSE, 0));
			
			

			//ϹJB�޸ĵ�һ������

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
						logs<<ntime()<<"δ���ó�ŷ�Χ�����ʧ��"<<endl;
						MessageBox(GetActiveWindow(),"��δ���ó�ŷ�Χ�������·����á�","�����_���԰� - ��ʾ",0+48); 
						SetWindowPos(hMainWindow,NULL,NULL,NULL,335, 300,SWP_NOMOVE|SWP_NOZORDER),sitting=1,more=0,SetWindowText(hSitting,"���� ��"),SetWindowText(hMore,"�����Ź��� >");
					}
					else
					{
						ShowWindow(hwnd,SW_HIDE);
						logs<<ntime()<<"���뵥�˳��"<<endl;
						while(true)
						{
							int e=rand()%n+1;
							int second=rand()%(100+p[e])+1; 
							if(name[e]!="���ա�"&&second==1)
							{
								int j=MessageBox(GetActiveWindow(),("���γ鵽���ǵ�"+zh(e)+"��ͬѧ"+name[e]+"�� \n[ȷ��]�ٳ�һ��  [ȡ��]������").c_str(),"�����_���԰�",1+32);  
								logs<<ntime()<<"�鵽"+zh(e)+"��"+name[e]<<endl;
								if(j==2)break;
							}
						} 
						int l=MessageBox(GetActiveWindow(),"[ȷ��]������ҳ  [ȡ��]�˳�����\n��������Ҫ�Ĳ��� Ȼ��س���","�����_���԰� - ��ʾ",1+48);  
						if(l==2)ex=1;  
						else ShowWindow(hwnd,SW_SHOWNORMAL);	
					}
					break;
				}
							
				case IDB_User:    
				{
					if(nf) 
					{
						MessageBox(GetActiveWindow(),"��δ���ó�ŷ�Χ�������·����á�","�����_���԰� - ��ʾ",0+48); 
						SetWindowPos(hMainWindow,NULL,NULL,NULL,335, 300,SWP_NOMOVE|SWP_NOZORDER),sitting=1,more=0,SetWindowText(hSitting,"���� ��"),SetWindowText(hMore,"�����Ź��� >");
					}
					else
					{ 
						char *NewItem; // Pointer to the new item's text
						int nTextLen = (int)SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0); // Get the length of the edit box
						if (nTextLen > 0)    // If the text lenght is greater than 0 then
						{

							NewItem = (char*)malloc(nTextLen); // allocate the new space for the text

							//��ȡ���ݡ�����ܳ
							DWORD dwTextLength = GetWindowTextLength(hEdit);
							LPSTR pszText;
							pszText = LPSTR(GlobalAlloc(GPTR, dwTextLength + 1));
							GetWindowText(hEdit, pszText, dwTextLength + 1);
							string x=pszText;
							bool num=0;
							for(int a=0;a<x.size();a++) if(x[a]>'9'||x[a]<'0') num=1;
							if(num) 
							{
								logs<<ntime()<<"����ĳ���������зǷ��ַ�"<<endl;
								SetWindowText(hEdit, "");
								MessageBox(GetActiveWindow(),"������������","�����_���԰� - ��ʾ",MB_OK+48);
							}
							else 
							{
								int xn=zs(x);
								if(xn>n2) 
								{
									logs<<ntime()<<"����ĳ���������ڰ༶����"<<endl;
									SetWindowText(hEdit, "");
									MessageBox(GetActiveWindow(),"����������ֲ�Ҫ���ڰ༶����","�����_���԰� - ��ʾ",MB_OK+48);
								}
								else if(xn==0) 
								{
									logs<<ntime()<<"����ĳ������С��0"<<endl;
									SetWindowText(hEdit, "");
									MessageBox(GetActiveWindow(),"����������ֲ�Ҫ����0","�����_���԰� - ��ʾ",MB_OK+48);
								}
								else 
								{
									logs<<ntime()<<"������˳��"<<endl;
									ShowWindow(hwnd,SW_HIDE);
									while(true)
									{
										cout<<xn;
										string out="���γ鵽����\n";
										int c[101]={0};
										for(int a=1;a<=xn;)
										{
											bool go=1;
											int e=rand()%n+1;
											int second=rand()%(100+p[e])+1; 
											if(name[e]!="���ա�"&&second==1) 
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
										logs<<ntime()<<"�鵽";
										for(int a=1;a<=xn;a++)
										{
											logs<<zh(c[a])+"��"+name[c[a]]+"��";
											out+=zh(c[a]);
											out+="��ͬѧ";
											out+=name[c[a]];
											if(a!=xn) out+="��"; 
											if(a%3==0&&a!=xn) out+="\n";
										}
										logs<<endl;
										int j=MessageBox(GetActiveWindow(),(out+"�� \n\n[ȷ��]�ٳ�һ��  [ȡ��]������").c_str(),"�����_���԰�",1+32);  
										if(j==2)break;
									}
									int l=MessageBox(GetActiveWindow(),"[ȷ��]������ҳ  [ȡ��]�˳�����\n��������Ҫ�Ĳ��� Ȼ��س���","�����_���԰� - ��ʾ",1+48);  
									if(l==2)ex=1;  
									else ShowWindow(hwnd,SW_SHOWNORMAL);
								}
							}
							break;
						}
							 

						
						else
						{
							MessageBox(GetActiveWindow(),"������һ��Ҫ��ȡ������","�����_���԰� - ��ʾ",MB_OK+48);
						}
					}
					break;
				}
				
				case IDB_More:    
				{
					if(more==0) SetWindowPos(hMainWindow,NULL,NULL,NULL,535, 195,SWP_NOMOVE|SWP_NOZORDER),more=1,sitting=0,SetWindowText(hMore,"< �����Ź���"),SetWindowText(hSitting,"���� ��");
					else SetWindowPos(hMainWindow,NULL,NULL,NULL,335, 195,SWP_NOMOVE|SWP_NOZORDER),more=0,sitting=0,SetWindowText(hMore,"�����Ź��� >"),SetWindowText(hSitting,"���� ��");
					break;
				}
				
				case IDB_Help:    
				{
					MessageBox(GetActiveWindow(),"Copyright (C) 2018-2020 GZC, All Rights Reserved.\nʹ��˵��\n ���ã���ȡ���ţ��ϻ�-_-��\n\n �����������ţ�һ�ν���ȡһ���ˡ�\n ��������֣������֣���һ���������Ǽ�����ʱ��һ�ν��������������ݳ�ȡ��Ӧ����\n ����������Ź��ܡ�������ʹ��Ʃ��ֻ��������ֻ��Ů�����Զ����ŷ�Χ�ȹ��ܣ���δ���ţ������Ⱳ�Ӷ����Ὺ�ŵ�-_-��\n ������ã����ó����","������ų�ȡ��_���԰� - ʹ��˵��",0+32);
					break;
				}
				
				case IDB_txt:    
				{
					ofstream outfile;
					outfile.open("������־.txt");
					outfile<<"������־\n2018-04-18 ����-�������һ�д��롭��\n2018-04-18 13:44-1.0 �뵱�����������һ���汾���ǿ���̨���ڣ�\n    ����Waiting��ʱ���ŵĿӣ���Ҳ���Ǹ��£���\n2018-04-18 20:05-1.1 ��ҹ��bugֻΪ���ã�\n    ������������������ȡ�Ĺ�����\n    �޸����������鵽ͬһ�����ŵ�BUG\n    �޸��鵽���ա�λ����ǰ�����������ŵ�BUG\n    ������ �Լ�\n2018-04-20 18:49-1.2 �ó������ѭ�����޳飿���bug������ϧû�ˣ�\n    �޸�����ֵԽ�絼����ѭ����BUG\n2018-5-3 20:00-1.3 �ܶ���ǿ��Ҫ��Ҫ��1�����Ƶ��Ȼ���Ӵ˰汾���񣬻����˱������Ƶ��\n    �����˸�Ƶ�͵�Ƶ����\n2018-05-03 20:13-1.3.1 ��ģ�����ˣ���ͼ���ˣ�\n    ��Ƕ��ͼ�� �汾�ŵ���Ϣ\n2018-5-15-19:42-2.0 �����������ѿ��Ѳ����Ŀ���̨ �����ˡ����塱��Ȼ����ֻ����Ϣ����XP�¿�����Ҳ��զ�أ�\n    ��ȫʹ�ô�����ʾ�� �Ƴ����Լ칦��\n    �޸�����һ�γ�ź󷵻���ҳ�ٳ�ŵ�������ʾ��Զ��ʾ���һ�ŵ�BUG\n2018-06-20 10:08-2.1 ��ϲ���棬��ϲ���ӡ�ֻ��ͬʱ��һ����������ô�棻ֻ�ǸɰͰ͵����ֲ����棬��ͼƬ�źÿ���\n    ����ֻ��ͬʱ����һ�������\n    �Ż����Ӿ���ʾ\n2018-09-24 15:47-2.1.1 ǿ�ж��úܷ������������ʱ��С���أ�ɾ������ܺ��棬�����ɾ�����أ�\n    emmmU����������� �������¹����˴���\n    ɾ����Ȼ���ѵĸ�Ƶ��Ƶ����\n    �Ż�����������һ������Ĵ��� �޸��˷������������³�����޷��򿪵�BUG\n    �Ż���ʹ��˵��\n    �Ż����ļ���ȡ����\n    �Ż���ʹ������(��Ȼû����С����ť ���ǵ����κ��������ڼ�����С���ҿ���ͨ����������ʾ)\n    ��������ʾ��������(32λ��64λ)\n    �����˸�����������ӿ�ݷ�ʽ\n2018-09-24 17:13-2.2�����������ǿ��ģ���ĳЩ������������Ըı�һ���˵����⣺\n    �Ż��˸ߵ�Ƶ�㷨(����ϲ���ĸ�Ƶ������ ������)\n2018-12-21 22:31-2.3 ֻ��Ϊ�˷�����ʦ�������ĸ���:\n    �Ż��˼����ʵ�����еĴ��룬�޸��˸������޷�����BUG\n    �Ż���û�н�������ʱ����ʾ\n    �Ƴ��˸�����־����һ�㣬������־����������\n2019-02-10 00:10-_���԰�3.0.0.0 Ӧ**Ҫ���һ�����£�\n    һ���ܳ�����\n    ��ҳ���������Ĵ��壨Ȼ�������ˣ�\n    ������ʱ����Ƿ��������ٲ���һҳ����һ�������ˣ�\n    �Ż���ʹ��˵���͸�����־\n    �Ż������� \n2019-02-10 13:41-_���԰�3.0.0.1 DEBUG��\n    �޸������ú����ֶ�ʧ��bug\n    �Ż�������ʹ������\n    �޸����״�ʹ�������������bug \n2019-03-06 21:03-_���԰�3.0.0.2 DEBUG��\n    �޸����������������˿�����bug\n    �޸��˳������һ��û����������bug\n    ��г�˲�������\n    �����˸߼����õĳ���\n2019-05-19 15:03-_���԰�3.0.0.3 ��־���£�\n    ��������־���ܣ�����������Կ���\n2019-12-28 15:58-_���԰�3.0.0.4 ���Ӹ��£�\n    �����˹�������ӭ�������\n\nδ���������";
					outfile.close();
					WinExec("notepad.exe ������־.txt",SW_SHOWMAXIMIZED);
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
					if(sitting==0) SetWindowPos(hMainWindow,NULL,NULL,NULL,335, 300,SWP_NOMOVE|SWP_NOZORDER),sitting=1,more=0,SetWindowText(hSitting,"���� ��"),SetWindowText(hMore,"�����Ź��� >");
					else SetWindowPos(hMainWindow,NULL,NULL,NULL,335, 195,SWP_NOMOVE|SWP_NOZORDER),sitting=0,more=0,SetWindowText(hSitting,"���� ��"),SetWindowText(hMore,"�����Ź��� >");
					break;
				}
				
				case IDB_Save:    
				{
					char *NewItem; // Pointer to the new item's text
					int nTextLen = (int)SendMessage(hE2, WM_GETTEXTLENGTH, 0, 0); // Get the length of the edit box
					if (nTextLen > 0)    // If the text lenght is greater than 0 then
					{
						NewItem = (char*)malloc(nTextLen); // allocate the new space for the text
						//��ȡ���ݡ�����ܳ
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
							MessageBox(GetActiveWindow(),"����������","�����_���԰� - ��ʾ",MB_OK+48);
						}
						else 
						{
							int xn=zs(x);
							if(xn==0) 
							{
								SetWindowText(hE2, "");
								MessageBox(GetActiveWindow(),"����������ֲ�Ҫ����0","�����_���԰� - ��ʾ",MB_OK+48);
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
								for(int a=1;a<=n;a++) if(name[a]=="���ա�") n2--;
								
							
								MessageBox(GetActiveWindow(),"����ɹ���\n��������������������ġ����\n����ʹ�������߼���Ź��������Ϸ��ġ������Ź��ܡ�","�����_���԰� - ��ʾ",0+48);

							}
						}
					}
					else 
					{
						MessageBox(GetActiveWindow(),"�������ŷ�Χ�Ա���","�����_���԰� - ��ʾ",MB_OK+48);
					}
					break;
				}
				
				case IDB_S2:    
				{
					MessageBox(GetActiveWindow(),"Copyright (C) 2018-2020 GZC, All Rights Reserved.\n������ó������\n���ڰ�[ȷ��]֮��򿪵��ļ��ĵ�һ�����������������n������ŷ�ΧΪ1~n��\n�����Ҫ��ʾ���֣������Ǹ��ļ���2~n+1�������������Ŷ�Ӧ������\nTips1:��������ŵ���Ϊ�գ����á��ա����������ֵ�λ�ã����ʱ���Զ�����\nTips2:�����Ҫ��Ƶ��Ƶ���ã���������ǰ���+/-��[+��Ƶ -��Ƶ]���Ҳ�Ҫ�пո�\n�硰+9WAITING������-4MORNING��\n\n��ɺ󱣴沢�������������","�����_���԰� - ������ʾ",0+32);
					WinExec("notepad.exe name",SW_SHOWMAXIMIZED);
					ex=1;
					break;
				}
				
				case IDB_s1:    
				{
					if(sr[1])
					{
						sr[1]=0;
						SetWindowText(hs1,"���˳��ʱ����:��");
						ofstream wt;
						wt.open("sitting.ini");
						wt<<"#Copyright (C) 2018-2020 GZC, All Rights Reserved.\n";
						for(int a=1;a<=(sizeof(sm)/4-1);a++) wt<<sr[a];
						wt.close();
					}
					else
					{
						sr[1]=1;
						SetWindowText(hs1,"���˳��ʱ����:��");
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


