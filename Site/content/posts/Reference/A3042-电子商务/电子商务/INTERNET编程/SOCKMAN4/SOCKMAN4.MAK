# Microsoft Visual C++ generated build script - Do not modify

PROJ = SOCKMAN4
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\IP_PROGS\SOCKMAN4\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = COMMON4.CPP 
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
DEFFILE = SOCKMAN4.DEF
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
SBRS = COMMON4.SBR \
		LOOKUP4.SBR \
		SOCKMAN4.SBR \
		FINGER4.SBR \
		TIME4.SBR


WINSOCK_DEP = 

COMMON4_DEP = c:\ip_progs\winsock.h \
	c:\ip_progs\sockman4\sockman4.h \
	c:\ip_progs\sockman4\global4.h


LOOKUP4_DEP = c:\ip_progs\winsock.h \
	c:\ip_progs\sockman4\sockman4.h \
	c:\ip_progs\sockman4\global4.h


SOCKMAN4_DEP = c:\ip_progs\winsock.h \
	c:\ip_progs\sockman4\sockman4.h


SOCKMAN4_RCDEP = c:\ip_progs\sockman4\sockman4.h \
	c:\ip_progs\winsock.h \
	c:\ip_progs\sockman4.ico


FINGER4_DEP = c:\ip_progs\winsock.h \
	c:\ip_progs\sockman4\sockman4.h \
	c:\ip_progs\sockman4\global4.h


TIME4_DEP = c:\ip_progs\winsock.h \
	c:\ip_progs\sockman4\sockman4.h \
	c:\ip_progs\sockman4\global4.h


all:	$(PROJ).EXE $(PROJ).BSC

COMMON4.OBJ:	COMMON4.CPP $(COMMON4_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c COMMON4.CPP

LOOKUP4.OBJ:	LOOKUP4.CPP $(LOOKUP4_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c LOOKUP4.CPP

SOCKMAN4.OBJ:	SOCKMAN4.CPP $(SOCKMAN4_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SOCKMAN4.CPP

SOCKMAN4.RES:	SOCKMAN4.RC $(SOCKMAN4_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r SOCKMAN4.RC

FINGER4.OBJ:	FINGER4.CPP $(FINGER4_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c FINGER4.CPP

TIME4.OBJ:	TIME4.CPP $(TIME4_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TIME4.CPP


$(PROJ).EXE::	SOCKMAN4.RES

$(PROJ).EXE::	COMMON4.OBJ LOOKUP4.OBJ SOCKMAN4.OBJ FINGER4.OBJ TIME4.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
COMMON4.OBJ +
LOOKUP4.OBJ +
SOCKMAN4.OBJ +
FINGER4.OBJ +
TIME4.OBJ +
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
	$(RC) $(RESFLAGS) SOCKMAN4.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	SOCKMAN4.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) SOCKMAN4.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
