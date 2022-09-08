# Microsoft Visual C++ generated build script - Do not modify

PROJ = SOCKMAN3
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\IP_PROGS\SOCKMAN3\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = COMMON3.CPP 
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
DEFFILE = SOCKMAN3.DEF
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
SBRS = COMMON3.SBR \
		LOOKUP3.SBR \
		SOCKMAN3.SBR \
		FINGER3.SBR


WINSOCK_DEP = 

COMMON3_DEP = c:\ip_progs\winsock.h \
	c:\ip_progs\sockman3\sockman3.h \
	c:\ip_progs\sockman3\global3.h


LOOKUP3_DEP = c:\ip_progs\winsock.h \
	c:\ip_progs\sockman3\sockman3.h \
	c:\ip_progs\sockman3\global3.h


SOCKMAN3_DEP = c:\ip_progs\winsock.h \
	c:\ip_progs\sockman3\sockman3.h


SOCKMAN3_RCDEP = c:\ip_progs\sockman3\sockman3.h \
	c:\ip_progs\winsock.h \
	c:\ip_progs\sockman3.ico


FINGER3_DEP = c:\ip_progs\winsock.h \
	c:\ip_progs\sockman3\sockman3.h \
	c:\ip_progs\sockman3\global3.h


all:	$(PROJ).EXE $(PROJ).BSC

COMMON3.OBJ:	COMMON3.CPP $(COMMON3_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c COMMON3.CPP

LOOKUP3.OBJ:	LOOKUP3.CPP $(LOOKUP3_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c LOOKUP3.CPP

SOCKMAN3.OBJ:	SOCKMAN3.CPP $(SOCKMAN3_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SOCKMAN3.CPP

SOCKMAN3.RES:	SOCKMAN3.RC $(SOCKMAN3_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r SOCKMAN3.RC

FINGER3.OBJ:	FINGER3.CPP $(FINGER3_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c FINGER3.CPP


$(PROJ).EXE::	SOCKMAN3.RES

$(PROJ).EXE::	COMMON3.OBJ LOOKUP3.OBJ SOCKMAN3.OBJ FINGER3.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
COMMON3.OBJ +
LOOKUP3.OBJ +
SOCKMAN3.OBJ +
FINGER3.OBJ +
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
	$(RC) $(RESFLAGS) SOCKMAN3.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	SOCKMAN3.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) SOCKMAN3.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
