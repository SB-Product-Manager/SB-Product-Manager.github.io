# Microsoft Visual C++ generated build script - Do not modify

PROJ = SOCKMAN2
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\IP_PROGS\SOCKMAN2\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = COMMON2.CPP 
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
DEFFILE = SOCKMAN2.DEF
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
SBRS = COMMON2.SBR \
		LOOKUP2.SBR \
		SOCKMAN2.SBR


WINSOCK_DEP = 

COMMON2_DEP = c:\ip_progs\winsock.h \
	c:\ip_progs\sockman2\sockman2.h \
	c:\ip_progs\sockman2\global2.h


LOOKUP2_DEP = c:\ip_progs\winsock.h \
	c:\ip_progs\sockman2\sockman2.h \
	c:\ip_progs\sockman2\global2.h


SOCKMAN2_DEP = c:\ip_progs\winsock.h \
	c:\ip_progs\sockman2\sockman2.h


SOCKMAN2_RCDEP = c:\ip_progs\sockman2\sockman2.h \
	c:\ip_progs\winsock.h \
	c:\ip_progs\sockman2.ico


all:	$(PROJ).EXE $(PROJ).BSC

COMMON2.OBJ:	COMMON2.CPP $(COMMON2_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c COMMON2.CPP

LOOKUP2.OBJ:	LOOKUP2.CPP $(LOOKUP2_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c LOOKUP2.CPP

SOCKMAN2.OBJ:	SOCKMAN2.CPP $(SOCKMAN2_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SOCKMAN2.CPP

SOCKMAN2.RES:	SOCKMAN2.RC $(SOCKMAN2_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r SOCKMAN2.RC


$(PROJ).EXE::	SOCKMAN2.RES

$(PROJ).EXE::	COMMON2.OBJ LOOKUP2.OBJ SOCKMAN2.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
COMMON2.OBJ +
LOOKUP2.OBJ +
SOCKMAN2.OBJ +
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
	$(RC) $(RESFLAGS) SOCKMAN2.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	SOCKMAN2.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) SOCKMAN2.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
