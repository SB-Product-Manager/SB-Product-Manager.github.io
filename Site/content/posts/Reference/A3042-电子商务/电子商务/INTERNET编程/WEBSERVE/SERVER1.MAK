# Microsoft Visual C++ generated build script - Do not modify

PROJ = SERVER1
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\IP_PROGS\WEBSERVE\
USEMFC = 1
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = /YcSTDAFX.H
CUSEPCHFLAG = 
CPPUSEPCHFLAG = /YuSTDAFX.H
FIRSTC =             
FIRSTCPP = STDAFX.CPP  
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /W3 /Zi /AM /Od /D "_DEBUG" /FR /GA /Fd"SERVER.PDB"
CFLAGS_R_WEXE = /nologo /Gs /G2 /W3 /AM /O1 /D "NDEBUG" /FR /GA
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE
LIBS_D_WEXE = mafxcwd oldnames libw mlibcew commdlg shell 
LIBS_R_WEXE = mafxcw oldnames libw mlibcew commdlg shell 
RCFLAGS = /nologo /z
RESFLAGS = /nologo /t
RUNFLAGS = 
DEFFILE = SERVER1.DEF
OBJS_EXT = 
LIBS_EXT = ..\WINSOCK.LIB 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE)
LFLAGS = $(LFLAGS_D_WEXE)
LIBS = $(LIBS_D_WEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WEXE)
LFLAGS = $(LFLAGS_R_WEXE)
LIBS = $(LIBS_R_WEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = STDAFX.SBR \
		SERVER1.SBR \
		MAINFRM1.SBR \
		SERV1DOC.SBR \
		SERV1VW.SBR


WINSOCK_DEP = 

STDAFX_DEP = c:\ip_progs\webserve\stdafx.h


SERVER1_DEP = c:\ip_progs\webserve\stdafx.h \
	c:\ip_progs\webserve\server1.h \
	c:\ip_progs\winsock.h \
	c:\ip_progs\webserve\mainfrm1.h \
	c:\ip_progs\webserve\serv1doc.h \
	c:\ip_progs\webserve\serv1vw.h


SERVER1_RCDEP = c:\ip_progs\webserve\res\server1.ico \
	c:\ip_progs\webserve\res\quick2.ico \
	c:\ip_progs\webserve\res\jp_logo2.ico \
	c:\ip_progs\webserve\res\socket2.ico \
	c:\ip_progs\webserve\res\sockman0.ico \
	c:\ip_progs\webserve\res\web2.ico \
	c:\ip_progs\webserve\res\server.rc2


MAINFRM1_DEP = c:\ip_progs\webserve\stdafx.h \
	c:\ip_progs\webserve\server1.h \
	c:\ip_progs\winsock.h \
	c:\ip_progs\webserve\mainfrm1.h


SERV1DOC_DEP = c:\ip_progs\webserve\stdafx.h \
	c:\ip_progs\webserve\server1.h \
	c:\ip_progs\winsock.h \
	c:\ip_progs\webserve\serv1doc.h


SERV1VW_DEP = c:\ip_progs\webserve\stdafx.h \
	c:\ip_progs\webserve\server1.h \
	c:\ip_progs\winsock.h \
	c:\ip_progs\webserve\serv1doc.h \
	c:\ip_progs\webserve\serv1vw.h


all:	$(PROJ).EXE $(PROJ).BSC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

SERVER1.OBJ:	SERVER1.CPP $(SERVER1_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SERVER1.CPP

SERVER1.RES:	SERVER1.RC $(SERVER1_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r SERVER1.RC

MAINFRM1.OBJ:	MAINFRM1.CPP $(MAINFRM1_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM1.CPP

SERV1DOC.OBJ:	SERV1DOC.CPP $(SERV1DOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SERV1DOC.CPP

SERV1VW.OBJ:	SERV1VW.CPP $(SERV1VW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SERV1VW.CPP


$(PROJ).EXE::	SERVER1.RES

$(PROJ).EXE::	STDAFX.OBJ SERVER1.OBJ MAINFRM1.OBJ SERV1DOC.OBJ SERV1VW.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
SERVER1.OBJ +
MAINFRM1.OBJ +
SERV1DOC.OBJ +
SERV1VW.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
.\+
C:\MSVC\CDK16\LIB\+
C:\MSVC\LIB\+
C:\MSVC\MFC\LIB\+
..\WINSOCK.LIB+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) SERVER1.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	SERVER1.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) SERVER1.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
