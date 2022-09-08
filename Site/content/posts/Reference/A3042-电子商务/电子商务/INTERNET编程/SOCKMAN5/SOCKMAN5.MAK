# Microsoft Visual C++ generated build script - Do not modify

PROJ = SOCKMAN5
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\IP_PROGS\SOCKMAN5\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = COMMON5.CPP 
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
DEFFILE = SOCKMAN5.DEF
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
SBRS = COMMON5.SBR \
		LOOKUP5.SBR \
		SOCKMAN5.SBR \
		FINGER5.SBR \
		TIME5.SBR \
		PING5.SBR


WINSOCK_DEP = 

COMMON5_DEP = c:\ip_progs\winsock.h \
	c:\ip_progs\sockman5\sockman5.h \
	c:\ip_progs\sockman5\global5.h


LOOKUP5_DEP = c:\ip_progs\winsock.h \
	c:\ip_progs\sockman5\sockman5.h \
	c:\ip_progs\sockman5\global5.h


SOCKMAN5_DEP = c:\ip_progs\winsock.h \
	c:\ip_progs\sockman5\sockman5.h \
	c:\ip_progs\sockman5\global5.h


SOCKMAN5_RCDEP = c:\ip_progs\sockman5\sockman5.h \
	c:\ip_progs\winsock.h \
	c:\ip_progs\sockman5.ico


FINGER5_DEP = c:\ip_progs\winsock.h \
	c:\ip_progs\sockman5\sockman5.h \
	c:\ip_progs\sockman5\global5.h


TIME5_DEP = c:\ip_progs\winsock.h \
	c:\ip_progs\sockman5\sockman5.h \
	c:\ip_progs\sockman5\global5.h


PING5_DEP = c:\ip_progs\winsock.h \
	c:\ip_progs\sockman5\sockman5.h \
	c:\ip_progs\sockman5\global5.h \
	c:\ip_progs\sockman5\sockraw5.h


all:	$(PROJ).EXE $(PROJ).BSC

COMMON5.OBJ:	COMMON5.CPP $(COMMON5_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c COMMON5.CPP

LOOKUP5.OBJ:	LOOKUP5.CPP $(LOOKUP5_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c LOOKUP5.CPP

SOCKMAN5.OBJ:	SOCKMAN5.CPP $(SOCKMAN5_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SOCKMAN5.CPP

SOCKMAN5.RES:	SOCKMAN5.RC $(SOCKMAN5_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r SOCKMAN5.RC

FINGER5.OBJ:	FINGER5.CPP $(FINGER5_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c FINGER5.CPP

TIME5.OBJ:	TIME5.CPP $(TIME5_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TIME5.CPP

PING5.OBJ:	PING5.CPP $(PING5_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c PING5.CPP


$(PROJ).EXE::	SOCKMAN5.RES

$(PROJ).EXE::	COMMON5.OBJ LOOKUP5.OBJ SOCKMAN5.OBJ FINGER5.OBJ TIME5.OBJ PING5.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
COMMON5.OBJ +
LOOKUP5.OBJ +
SOCKMAN5.OBJ +
FINGER5.OBJ +
TIME5.OBJ +
PING5.OBJ +
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
	$(RC) $(RESFLAGS) SOCKMAN5.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	SOCKMAN5.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) SOCKMAN5.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
