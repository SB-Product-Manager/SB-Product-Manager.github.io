# Microsoft Visual C++ generated build script - Do not modify

PROJ = SOCKMAN1
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\IP_PROGS\SOCKMAN1\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = SOCKMAN1.CPP
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /W3 /Zi /AM /Od /D "_DEBUG" /FR /GA /Fd"SOCKMAN.PDB"
CFLAGS_R_WEXE = /nologo /W3 /AM /O1 /D "NDEBUG" /FR /GA 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = oldnames libw mlibcew commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WEXE = oldnames libw mlibcew commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = SOCKMAN1.DEF
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
SBRS = SOCKMAN1.SBR \
		COMMON1.SBR


WINSOCK_DEP = 

SOCKMAN1_DEP = c:\ip_progs\winsock.h \
	c:\ip_progs\sockman1\sockman1.h \
	c:\ip_progs\sockman1\global1.h


COMMON1_DEP = c:\ip_progs\winsock.h \
	c:\ip_progs\sockman1\sockman1.h \
	c:\ip_progs\sockman1\global1.h


SOCKMAN1_RCDEP = c:\ip_progs\sockman1\sockman1.h \
	c:\ip_progs\winsock.h \
	c:\ip_progs\sockman1.ico


all:	$(PROJ).EXE $(PROJ).BSC

SOCKMAN1.OBJ:	SOCKMAN1.CPP $(SOCKMAN1_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c SOCKMAN1.CPP

COMMON1.OBJ:	COMMON1.CPP $(COMMON1_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c COMMON1.CPP

SOCKMAN1.RES:	SOCKMAN1.RC $(SOCKMAN1_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r SOCKMAN1.RC


$(PROJ).EXE::	SOCKMAN1.RES

$(PROJ).EXE::	SOCKMAN1.OBJ COMMON1.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
SOCKMAN1.OBJ +
COMMON1.OBJ +
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
	$(RC) $(RESFLAGS) SOCKMAN1.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	SOCKMAN1.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) SOCKMAN1.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
