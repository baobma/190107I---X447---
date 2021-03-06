; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=MainDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "hustndt.h"
LastPage=0

ClassCount=19
Class1=CARDSET
Class2=DataSetDlg
Class3=ChooseFileDlg
Class4=CHUSTNDTApp
Class5=CAboutDlg
Class6=CHUSTNDTDoc
Class7=CHUSTNDTView
Class8=IntialSetDlg
Class9=CIOStatusDlg
Class10=MainDlg
Class11=CMainFrame
Class12=MParDlg
Class13=MsgDlg
Class14=PARSET
Class15=PrintReportDlg
Class16=ReportDlg
Class17=ShowSet
Class18=CStaticPIC
Class19=CStrParDlg

ResourceCount=16
Resource1=IDD_DIALOG_SHOWSET
Resource2=IDD_ABOUTBOX
Resource3=IDD_DIALOG_SETCARD
Resource4=IDD_DIALOG_STRPAR
Resource5=IDD_DIALOG_CHOOSEFILE
Resource6=IDD_DIALOG_INTIALSET
Resource7=IDR_MAINFRAME
Resource8=IDD_DIALOG_MSGDLG
Resource9=IDR_ENVIROMENT_MENU
Resource10=IDD_DIALOG_MAIN
Resource11=IDD_DIALOG_DATASET
Resource12=IDD_DIALOG_M_Par
Resource13=IDD_DIALOG_PARSET
Resource14=IDD_DIALOG_REPORTS
Resource15=IDD_DIALOG_IOSTATUS
Resource16=IDD_DIALOG_PRINTREPORT

[CLS:CARDSET]
Type=0
BaseClass=CDialog
HeaderFile=ARDSET.h
ImplementationFile=ARDSET.cpp

[CLS:DataSetDlg]
Type=0
BaseClass=CDialog
HeaderFile=DataSetDlg.h
ImplementationFile=DataSetDlg.cpp

[CLS:ChooseFileDlg]
Type=0
BaseClass=CDialog
HeaderFile=hooseFileDlg.h
ImplementationFile=hooseFileDlg.cpp
LastObject=ID_ThickPipe
Filter=D
VirtualFilter=dWC

[CLS:CHUSTNDTApp]
Type=0
BaseClass=CWinApp
HeaderFile=HUSTNDT.h
ImplementationFile=HUSTNDT.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=HUSTNDT.cpp
ImplementationFile=HUSTNDT.cpp

[CLS:CHUSTNDTDoc]
Type=0
BaseClass=CDocument
HeaderFile=HUSTNDTDoc.h
ImplementationFile=HUSTNDTDoc.cpp

[CLS:CHUSTNDTView]
Type=0
BaseClass=CView
HeaderFile=HUSTNDTView.h
ImplementationFile=HUSTNDTView.cpp

[CLS:IntialSetDlg]
Type=0
BaseClass=CDialog
HeaderFile=IntialSetDlg.h
ImplementationFile=IntialSetDlg.cpp

[CLS:CIOStatusDlg]
Type=0
BaseClass=CDialog
HeaderFile=IOStatusDlg.h
ImplementationFile=IOStatusDlg.cpp

[CLS:MainDlg]
Type=0
BaseClass=CDialog
HeaderFile=MainDlg.h
ImplementationFile=MainDlg.cpp
LastObject=IDC_EDIT_HELP
Filter=D
VirtualFilter=dWC

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:MParDlg]
Type=0
BaseClass=CDialog
HeaderFile=MParDlg.h
ImplementationFile=MParDlg.cpp

[CLS:MsgDlg]
Type=0
BaseClass=CDialog
HeaderFile=MsgDlg.h
ImplementationFile=MsgDlg.cpp

[CLS:PARSET]
Type=0
BaseClass=CDialog
HeaderFile=PARSET.h
ImplementationFile=PARSET.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT_menxian

[CLS:PrintReportDlg]
Type=0
BaseClass=CDialog
HeaderFile=PrintReportDlg.h
ImplementationFile=PrintReportDlg.cpp

[CLS:ReportDlg]
Type=0
BaseClass=CDialog
HeaderFile=ReportDlg.h
ImplementationFile=ReportDlg.cpp

[CLS:ShowSet]
Type=0
BaseClass=CDialog
HeaderFile=ShowSet.h
ImplementationFile=ShowSet.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_COMBO_VACC

[CLS:CStaticPIC]
Type=0
BaseClass=CStatic
HeaderFile=StaticPIC.h
ImplementationFile=StaticPIC.cpp

[CLS:CStrParDlg]
Type=0
BaseClass=CDialog
HeaderFile=StrParDlg.h
ImplementationFile=StrParDlg.cpp

[DLG:IDD_DIALOG_SETCARD]
Type=1
Class=CARDSET
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_COMBO_CARDCHOOSE,combobox,1344340226
Control4=IDC_STATIC_SAMPLESPEED,static,1342308352
Control5=IDC_EDIT_SAMPLESPEED,edit,1350631552
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC_CHANNELNUM,static,1342308352
Control8=IDC_EDIT_CHANNELNUM,edit,1350631552
Control9=IDC_STATIC_BLOCK,static,1342308352
Control10=IDC_EDIT_BLOCK,edit,1350631552
Control11=IDC_CHECK_CODING,button,1073807363
Control12=IDC_STATIC_STARTCH,static,1342308352
Control13=IDC_EDIT_SYSTEMSTARTCH,edit,1484849280
Control14=IDC_LIST1,listbox,1352728835

[DLG:IDD_DIALOG_DATASET]
Type=1
Class=DataSetDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_COMBO_DATASET,combobox,1344339970

[DLG:IDD_DIALOG_CHOOSEFILE]
Type=1
Class=ChooseFileDlg
ControlCount=24
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_FILENAME,edit,1350631552
Control5=IDC_LIST_BACK,listbox,1084293379
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_MAN,edit,1350631552
Control9=IDC_LIST_FILENAMELIST,SysListView32,1350631425
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT_FIND,edit,1350631552
Control12=IDC_STATIC,static,1073872896
Control13=IDC_EDIT_SID,edit,1082196096
Control14=IDC_RADIO1,button,1342308361
Control15=IDC_RADIO2,button,1342177289
Control16=IDC_EDIT_STEEL,edit,1350631552
Control17=IDC_EDIT_PLY,edit,1350631552
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_EDIT_GUIGE,edit,1350631552
Control21=IDC_STATIC,static,1342308352
Control22=IDC_RADIO3,button,1073872905
Control23=IDC_RADIO4,button,1073741833
Control24=IDC_CHECK_JPG,button,1342242819

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC_VERSION,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DIALOG_INTIALSET]
Type=1
Class=IntialSetDlg
ControlCount=7
Control1=IDC_BUTTON_SINGLE,button,1342242816
Control2=IDC_BUTTON_NET,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,button,1342177287
Control5=IDC_EDIT_SINGLE,edit,1350631552
Control6=IDC_EDIT_NET,edit,1350631552
Control7=IDC_CHECK_AUTO,button,1342242819

[DLG:IDD_DIALOG_IOSTATUS]
Type=1
Class=CIOStatusDlg
ControlCount=27
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC1,static,1342177294
Control3=IDC_STATIC2,static,1342177294
Control4=IDC_STATIC3,static,1342177294
Control5=IDC_STATIC4,static,1342177294
Control6=IDC_STATIC5,static,1342177294
Control7=IDC_STATIC6,static,1342177294
Control8=IDC_STATIC7,static,1342177294
Control9=IDC_STATIC8,static,1342177294
Control10=IDC_BUTTON1,button,1342242816
Control11=IDC_BUTTON2,button,1342242816
Control12=IDC_BUTTON3,button,1342242816
Control13=IDC_BUTTON4,button,1342242816
Control14=IDC_BUTTON5,button,1342242816
Control15=IDC_BUTTON6,button,1342242816
Control16=IDC_BUTTON7,button,1342242816
Control17=IDC_BUTTON8,button,1342242816
Control18=IDC_CHECK_PLUS,button,1342242819
Control19=IDC_STATIC_DI1,static,1342308352
Control20=IDC_STATIC_DI2,static,1342308352
Control21=IDC_STATIC_DI3,static,1342308352
Control22=IDC_STATIC_DI4,static,1342308352
Control23=IDC_STATIC_DI5,static,1342308352
Control24=IDC_STATIC_DI6,static,1342308352
Control25=IDC_STATIC_DI7,static,1342308352
Control26=IDC_STATIC_DI8,static,1342308352
Control27=IDC_BUTTON_STOP,button,1342242816

[DLG:IDD_DIALOG_MAIN]
Type=1
Class=MainDlg
ControlCount=84
Control1=IDC_BUTTON_START,button,1342242816
Control2=IDC_BUTTON_STOP,button,1342242816
Control3=IDC_BUTTON_DEMOCRATE,button,1342242816
Control4=IDC_BUTTON_PARSET,button,1342242816
Control5=IDC_BUTTON_DATABASE,button,1073807360
Control6=IDC_BUTTON_CARDSET,button,1342242816
Control7=IDC_BUTTON_REPORT,button,1342177280
Control8=IDC_BUTTON_SHOWSET,button,1342242816
Control9=IDC_PROGRESS,msctls_progress32,1082130432
Control10=IDC_EDIT_HELP,edit,1350631556
Control11=IDC_STATIC1,static,1342308352
Control12=IDC_STATIC2,static,1342308352
Control13=IDC_STATIC3,static,1342308352
Control14=IDC_STATIC4,static,1342308352
Control15=IDC_STATIC5,static,1342308352
Control16=IDC_STATIC6,static,1342308352
Control17=IDC_STATIC7,static,1342308352
Control18=IDC_STATIC8,static,1342308352
Control19=IDC_BUTTON_OPEN,button,1342242816
Control20=IDC_BUTTON_ANALYSIS,button,1342242816
Control21=IDC_BUTTON_RESHOW,button,1342242816
Control22=IDC_BUTTON_DATASAVESET,button,1342242816
Control23=IDC_BUTTON_1p,button,1073807360
Control24=IDC_BUTTON_1n,button,1073807360
Control25=IDC_BUTTON_2p,button,1073807360
Control26=IDC_BUTTON_2n,button,1073807360
Control27=IDC_BUTTON_3p,button,1073807360
Control28=IDC_BUTTON_3n,button,1073807360
Control29=IDC_BUTTON_4p,button,1073807360
Control30=IDC_BUTTON_4n,button,1073807360
Control31=IDC_BUTTON_5p,button,1073807360
Control32=IDC_BUTTON_5n,button,1073807360
Control33=IDC_BUTTON_6p,button,1073807360
Control34=IDC_BUTTON_6n,button,1073807360
Control35=IDC_BUTTON_7p,button,1073807360
Control36=IDC_BUTTON_7n,button,1073807360
Control37=IDC_BUTTON_8p,button,1073807360
Control38=IDC_BUTTON_8n,button,1073807360
Control39=IDC_BUTTON_pp1,button,1073807360
Control40=IDC_BUTTON_pp2,button,1073807360
Control41=IDC_BUTTON_pp3,button,1073807360
Control42=IDC_BUTTON_pp4,button,1073807360
Control43=IDC_BUTTON_pp5,button,1073807360
Control44=IDC_BUTTON_pp6,button,1073807360
Control45=IDC_BUTTON_pp7,button,1073807360
Control46=IDC_BUTTON_pp8,button,1073807360
Control47=IDC_BUTTON_allpp,button,1342242816
Control48=IDC_BUTTON_allp,button,1342242816
Control49=IDC_BUTTON_alln,button,1342242816
Control50=IDC_BUTTON_allnn,button,1342242816
Control51=IDC_STATIC_CURRENTNUM,static,1342308352
Control52=IDC_EDIT_CURRENTNUM,edit,1350631552
Control53=IDC_BUTTON_GONUM,button,1342242816
Control54=IDC_BUTTON_wavepp,button,1342242816
Control55=IDC_BUTTON_wavep,button,1342242816
Control56=IDC_BUTTON_wavenn,button,1342242816
Control57=IDC_BUTTON_waven,button,1342242816
Control58=IDC_BUTTON_nn1,button,1073807360
Control59=IDC_BUTTON_nn2,button,1073807360
Control60=IDC_BUTTON_nn3,button,1073807360
Control61=IDC_BUTTON_nn4,button,1073807360
Control62=IDC_BUTTON_nn5,button,1073807360
Control63=IDC_BUTTON_nn6,button,1073807360
Control64=IDC_BUTTON_nn7,button,1073807360
Control65=IDC_BUTTON_nn8,button,1073807360
Control66=IDC_STATIC_T1,static,1342308352
Control67=IDC_STATIC_T2,static,1342308352
Control68=IDC_STATIC_T3,static,1342308352
Control69=IDC_STATIC_T4,static,1342308352
Control70=IDC_STATIC_T5,static,1342308352
Control71=IDC_STATIC_T6,static,1342308352
Control72=IDC_STATIC_T7,static,1342308352
Control73=IDC_STATIC_T8,static,1342308352
Control74=IDC_LIST_MSG,listbox,1353777409
Control75=IDC_BUTTON_IOSTATUS,button,1342242816
Control76=IDC_BUTTON_SPRENT,button,1342242816
Control77=IDC_STATIC_CURRENTPLY,static,1073872896
Control78=IDC_EDIT_CURRENTPLY,edit,1082196096
Control79=IDC_STATIC9,static,1073872896
Control80=IDC_STATIC_POSITION,static,1073872896
Control81=IDC_EDIT_POSITION,edit,1082196096
Control82=IDC_STATIC_MINPLY,static,1073872896
Control83=IDC_EDIT_MINPLY,edit,1082196096
Control84=IDC_STATIC_LEN,static,1073872896

[DLG:IDD_DIALOG_M_Par]
Type=1
Class=MParDlg
ControlCount=20
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_EDIT2,edit,1350631552
Control5=IDC_EDIT3,edit,1350631552
Control6=IDC_EDIT4,edit,1350631552
Control7=IDC_EDIT5,edit,1350631552
Control8=IDC_EDIT6,edit,1350631552
Control9=IDC_EDIT7,edit,1350631552
Control10=IDC_EDIT8,edit,1350631552
Control11=IDC_STATIC1,static,1342308352
Control12=IDC_STATIC2,static,1342308352
Control13=IDC_STATIC3,static,1342308352
Control14=IDC_STATIC4,static,1342308352
Control15=IDC_STATIC5,static,1342308352
Control16=IDC_STATIC6,static,1342308352
Control17=IDC_STATIC7,static,1342308352
Control18=IDC_STATIC8,static,1342308352
Control19=IDC_BUTTON_RESET,button,1342242816
Control20=IDC_BUTTON_RESUME,button,1342242816

[DLG:IDD_DIALOG_MSGDLG]
Type=1
Class=MsgDlg
ControlCount=1
Control1=IDC_STATIC_MSG,static,1342308353

[DLG:IDD_DIALOG_PARSET]
Type=1
Class=PARSET
ControlCount=13
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST_PAR,SysListView32,1350631685
Control4=IDC_BUTTON_RESET,button,1073807360
Control5=IDC_COMBO_INDEX,combobox,1075904514
Control6=IDC_STATIC,static,1073872896
Control7=IDC_BUTTON_SAVE,button,1073807360
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT_SPEED,edit,1350631552
Control10=IDC_EDIT_menxian,edit,1082196096
Control11=IDC_STATIC,static,1073872896
Control12=IDC_BUTTON_H,button,1342242816
Control13=IDC_BUTTON_Z,button,1342242816

[DLG:IDD_DIALOG_PRINTREPORT]
Type=1
Class=PrintReportDlg
ControlCount=5
Control1=IDC_BUTTON_PRINTALL,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=IDC_BUTTON_PRINTCURRENT,button,1342242816
Control4=IDC_BUTTON_UPPAGE,button,1342242816
Control5=IDC_BUTTON_NEXTPAGE,button,1342242816

[DLG:IDD_DIALOG_REPORTS]
Type=1
Class=ReportDlg
ControlCount=3
Control1=IDCANCEL,button,1342242816
Control2=IDC_LIST_REPORT,SysListView32,1350631425
Control3=IDC_BUTTON_EXCEL,button,1073807360

[DLG:IDD_DIALOG_SHOWSET]
Type=1
Class=ShowSet
ControlCount=48
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST_SHOWCH,SysListView32,1350631425
Control4=IDC_STATIC1,static,1342308352
Control5=IDC_COMBO1,combobox,1344339970
Control6=IDC_STATIC2,static,1342308352
Control7=IDC_COMBO2,combobox,1344339970
Control8=IDC_STATIC3,static,1342308352
Control9=IDC_COMBO3,combobox,1344339970
Control10=IDC_STATIC4,static,1342308352
Control11=IDC_COMBO4,combobox,1344339970
Control12=IDC_STATIC5,static,1342308352
Control13=IDC_COMBO5,combobox,1344339970
Control14=IDC_STATIC6,static,1342308352
Control15=IDC_COMBO6,combobox,1344339970
Control16=IDC_STATIC7,static,1342308352
Control17=IDC_COMBO7,combobox,1344339970
Control18=IDC_STATIC8,static,1342308352
Control19=IDC_COMBO8,combobox,1344339970
Control20=IDC_STATIC_STEP,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_LIST_THR,SysListView32,1350631425
Control24=IDC_BUTTON_RESET,button,1073807360
Control25=IDC_CHECK1,button,1342242819
Control26=IDC_CHECK2,button,1342242819
Control27=IDC_CHECK3,button,1342242819
Control28=IDC_CHECK4,button,1342242819
Control29=IDC_CHECK5,button,1342242819
Control30=IDC_CHECK6,button,1342242819
Control31=IDC_CHECK7,button,1342242819
Control32=IDC_CHECK8,button,1342242819
Control33=IDC_STATIC_HALF,static,1342308352
Control34=IDC_RADIO1,button,1342308361
Control35=IDC_RADIO2,button,1342177289
Control36=IDC_RADIO3,button,1342177289
Control37=IDC_RADIO4,button,1342177289
Control38=IDC_RADIO5,button,1342177289
Control39=IDC_RADIO6,button,1342177289
Control40=IDC_RADIO7,button,1342177289
Control41=IDC_RADIO8,button,1342177289
Control42=IDC_BUTTON1,button,1342242816
Control43=IDC_STATIC,static,1342308352
Control44=IDC_COMBO_HACC,combobox,1344340226
Control45=IDC_STATIC,static,1342308352
Control46=IDC_COMBO_VACC,combobox,1344340226
Control47=IDC_STATIC,static,1342308352
Control48=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_STRPAR]
Type=1
Class=CStrParDlg
ControlCount=20
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_EDIT2,edit,1350631552
Control5=IDC_EDIT3,edit,1350631552
Control6=IDC_EDIT4,edit,1350631552
Control7=IDC_EDIT5,edit,1350631552
Control8=IDC_EDIT6,edit,1350631552
Control9=IDC_EDIT7,edit,1350631552
Control10=IDC_EDIT8,edit,1350631552
Control11=IDC_STATIC1,static,1342308352
Control12=IDC_STATIC2,static,1342308352
Control13=IDC_STATIC3,static,1342308352
Control14=IDC_STATIC4,static,1342308352
Control15=IDC_STATIC5,static,1342308352
Control16=IDC_STATIC6,static,1342308352
Control17=IDC_STATIC7,static,1342308352
Control18=IDC_STATIC8,static,1342308352
Control19=IDC_BUTTON_RESET,button,1342242816
Control20=IDC_BUTTON_RESUME,button,1342242816

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=MIAN
Command3=ID_APP_ABOUT
CommandCount=3

[MNU:IDR_ENVIROMENT_MENU]
Type=1
Class=?
Command1=ID_MENUITEM_NEXTC
Command2=ID_MENUITEM_PREC
Command3=ID_MENUITEM32786
Command4=ID_SIMPLE
Command5=ID_COMBINE
Command6=ID_DIFFER
Command7=ID_DIFFERENCE
Command8=ID_ThickPipe
CommandCount=8

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

