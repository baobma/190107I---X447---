// HUSTNDT.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "HUSTNDT.h"

#include "MainFrm.h"
#include "HUSTNDTDoc.h"
#include "HUSTNDTView.h"
#include "IntialSetDlg.h"
#include "GobalData.h"
#include "atlbase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHUSTNDTApp

BEGIN_MESSAGE_MAP(CHUSTNDTApp, CWinApp)
	//{{AFX_MSG_MAP(CHUSTNDTApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHUSTNDTApp construction

CHUSTNDTApp::CHUSTNDTApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHUSTNDTApp object

CHUSTNDTApp theApp;
int  Ready_Only = 1;
/////////////////////////////////////////////////////////////////////////////
// CHUSTNDTApp initialization

BOOL CHUSTNDTApp::InitInstance()
{
	CString   mutexName = "HUSTNDT";   
	::CreateMutex(NULL,FALSE,mutexName);   
	if(GetLastError()==ERROR_ALREADY_EXISTS)   
	{   
		AfxMessageBox("The HUSTNDT  has  run already!");   
		return FALSE;
	}

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	HANDLE a = GetCurrentProcess();
	SetPriorityClass(a,HIGH_PRIORITY_CLASS);  //���ý������ȼ�

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("NdtSoft"));
//	EnableLoad();
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CHUSTNDTDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CHUSTNDTView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
    	ReadlvboToFile("par\\Expertor.par");
	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED); //ȫ����ʾ
	/*
	 *	ϵͳ��ʼ��
	 */
    myInit();
	m_pMainWnd->UpdateWindow();
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
/*
 *	���ڶԻ���
 */
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CHUSTNDTApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CHUSTNDTApp message handlers
/*
 *	�����ʼ��
 */
void CHUSTNDTApp::myInit()
{
	GobalData* g = GobalData::getGobalData();   //������ʼ��
	g->getAutoSetFromFile();                    //�����Զ�����ز���
	g->getShowCHSfromFile();                    //������ʾ��Χ
	AUTOSET a = g->getAutoSet();
	if(a.b_initalDlg)                           //�Ƿ��Զ����� ��ʼ������ �Ի���
	{
		IntialSetDlg dlg;
		dlg.DoModal();
	}
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	/*
	 *	�汾��Ϣ��ʾ
	 */
	GobalData* g = GobalData::getGobalData();
	CString str;
	str.Format("HUSTNDT VERSION %0.1f",g->VERSION);
	GetDlgItem(IDC_STATIC_VERSION)->SetWindowText(str);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*
 *	ͨ��ע���򵥵Ŀ���ʹ������
 */
void CHUSTNDTApp::EnableLoad()
{	
	CRegKey rk;
	if(rk.Open(HKEY_CURRENT_USER,"software\\NdtSoft\\NDTEnable\\HUSTNDT\\") != ERROR_SUCCESS)
    {
		AfxMessageBox("��Ȩ����ȷ");
		PostQuitMessage(0);
    }
	CString keyname = "EnableNum";
	DWORD num;
    if(rk.QueryValue(num,keyname) != ERROR_SUCCESS)
	{
        AfxMessageBox("��Ȩ����ȷ");
		PostQuitMessage(0);
	}
	if(num == 0)
	{
		AfxMessageBox("ʹ����Ȩ�ѹ����뼰ʱ����");
		PostQuitMessage(0);
		
	}
	else if(num == -1)
	{
		//AfxMessageBox("��Ȩʹ������: ����");
		return;
	}
	else
	{
		if(rk.SetValue(DWORD(num-1),keyname) != ERROR_SUCCESS)
		{
			AfxMessageBox("��Ȩ����ȷ");
			PostQuitMessage(0);
		}
		else
		{
			CString str;
			str.Format("��Ȩʹ������: �����������ʹ��%d��", num-1);
			AfxMessageBox(str);
		}
	}
}

void CHUSTNDTApp::ReadlvboToFile(CString strFileName)
{
	CStdioFile file;
	if (!file.Open(strFileName, CFile::modeRead)) 
	{
		WritelvboTofile(strFileName);	
		return;
	}
	
	CString strData;
	if (!file.ReadString(strData)) 
	{
		file.Close();
		return;
	}
	sscanf(strData.GetBuffer(0), "%d", &Ready_Only);	
	file.Close();
	
}
void CHUSTNDTApp::WritelvboTofile(CString strFileName)
{
	
	CStdioFile file;
	if (!file.Open(strFileName, CFile::modeCreate | CFile::modeWrite)) {
		return;
	}	
	CString strData;
	
	strData.Format("%ld\n",Ready_Only);
	file.WriteString(strData);


	file.Close();
	
}
