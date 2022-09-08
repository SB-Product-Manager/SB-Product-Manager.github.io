# Microsoft Visual C++ generated build script - Do not modify

PROJ = QWEBLIB
DEBUG = 0
PROGTYPE = 1
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG 
R_RCDEFINES = /dNDEBUG 
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\IP_PROGS\QWEBLIB\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = QWEBLIB.CPP 
RC = rc
CFLAGS_D_WDLL = /nologo /G2 /W3 /Zi /ASw /Od /D "_DEBUG" /FR /GD /Fd"QWEBLIB.PDB"
CFLAGS_R_WDLL = /nologo /W3 /ASw /O1 /D "NDEBUG" /FR /GD 
LFLAGS_D_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP:FULL
LIBS_D_WDLL = oldnames libw sdllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WDLL = oldnames libw sdllcew commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo 
RESFLAGS = /nologo 
RUNFLAGS = 
DEFFILE = QWEBLIB.DEF
OBJS_EXT = 
LIBS_EXT = ..\WINSOCK.LIB 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WDLL)
LFLAGS = $(LFLAGS_D_WDLL)
LIBS = $(LIBS_D_WDLL)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WDLL)
LFLAGS = $(LFLAGS_R_WDLL)
LIBS = $(LIBS_R_WDLL)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = QWEBLIB.SBR


WINSOCK_DEP = 

QWEBLIB_DEP = c:\ip_progs\winsock.h


QWEBLIB_RCDEP = c:\ip_progs\qfinger.ico \
	c:\ip_progs\qftp1.ico \
	c:\ip_progs\qftp2.ico \
	c:\ip_progs\qlookup.ico \
	c:\ip_progs\qping.ico \
	c:\ip_progs\qpop3.ico \
	c:\ip_progs\qsmtp.ico \
	c:\ip_progs\qtime.ico \
	c:\ip_progs\quick.ico \
	c:\ip_progs\server.ico \
	c:\ip_progs\smftp.ico \
	c:\ip_progs\smweb.ico \
	c:\ip_progs\socket.ico \
	c:\ip_progs\sockman.ico \
	c:\ip_progs\sockman1.ico \
	c:\ip_progs\sockman2.ico \
	c:\ip_progs\sockman3.ico \
	c:\ip_progs\sockman4.ico \
	c:\ip_progs\sockman5.ico \
	c:\ip_progs\web.ico


all:	$(PROJ).DLL $(PROJ).BSC

QWEBLIB.OBJ:	QWEBLIB.CPP $(QWEBLIB_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c QWEBLIB.CPP

QWEBLIB.RES:	QWEBLIB.RC $(QWEBLIB_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r QWEBLIB.RC


$(PROJ).DLL::	QWEBLIB.RES

$(PROJ).DLL::	QWEBLIB.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
QWEBLIB.OBJ +
$(OBJS_EXT)
$(PROJ).DLL
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
	$(RC) $(RESFLAGS) QWEBLIB.RES $@
	@copy $(PROJ).CRF MSVC.BND
	implib /nowep $(PROJ).LIB $(PROJ).DLL

$(PROJ).DLL::	QWEBLIB.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) QWEBLIB.RES $@

run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
