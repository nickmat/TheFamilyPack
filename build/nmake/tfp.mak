# =========================================================================
#     This makefile was generated by
#     Bakefile 0.2.9 (http://www.bakefile.org)
#     Do not modify, all changes will be overwritten!
# =========================================================================



# -------------------------------------------------------------------------
# These are configurable options:
# -------------------------------------------------------------------------

# C compiler 
CC = cl

# C++ compiler 
CXX = cl

# Standard flags for CC 
CFLAGS = 

# Standard flags for C++ 
CXXFLAGS = 

# Standard preprocessor flags (common for CC and CXX) 
CPPFLAGS = 

# Standard linker flags 
LDFLAGS = 

# Use debug build of wxWidgets (linked with debug CRT)? [0,1]
#   0 - Release
#   1 - Debug
WX_DEBUG = 1

# Version of the wx library to build against. 
WX_VERSION = 29

# The directory where wxWidgets library is installed 
WX_DIR = $(WXWIN)

# Architecture of the CPU for which to build the executables and libraries [X86,AMD64,IA64]
#   X86 - i386-compatible
#   AMD64 - AMD 64 bit
#   IA64 - Itanium 64 bit
TARGET_CPU = X86



# -------------------------------------------------------------------------
# Do not modify the rest of this file!
# -------------------------------------------------------------------------

### Variables: ###

COMPILER_PREFIX = vc
TFP_CXXFLAGS = /MD$(VAR_43) /DWIN32 /D_UNICODE $(__WXDEBUG_DEFINE_p) /D__WXMSW__ \
	/I$(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib\msw$(WXLIBPOSTFIX) \
	/I$(WX_DIR)\include $(VAR) $(VAR_42) $(p) /Fdtfp.pdb /D_WINDOWS \
	/I..\..\include /I..\..\src /GR /EHsc /Yu"wx/wxprec.h" /Fp"wxprec_tfp.pch" \
	$(CPPFLAGS) $(CXXFLAGS)
TFP_OBJECTS =  \
	tfp_dlgEd.obj \
	tfp_dlgEdContact.obj \
	tfp_dlgEdDate.obj \
	tfp_dlgEdEvent.obj \
	tfp_dlgEdFamily.obj \
	tfp_dlgEdIndEvent.obj \
	tfp_dlgEdIndividual.obj \
	tfp_dlgEdName.obj \
	tfp_dlgEdNamePart.obj \
	tfp_dlgEdPersona.obj \
	tfp_dlgEdPlace.obj \
	tfp_dlgEdReference.obj \
	tfp_dlgEdRelationship.obj \
	tfp_dlgEdResearcher.obj \
	tfp_dlgEdRole.obj \
	tfp_dlgEdSystem.obj \
	tfp_dlgNote.obj \
	tfp_dlgRecTableCtrl.obj \
	tfp_dlgSelect.obj \
	tfp_dlgSelEvent.obj \
	tfp_dlgSelIndividual.obj \
	tfp_fbDlg.obj \
	tfp_tfpApp.obj \
	tfp_tfpFrame.obj \
	tfp_tfpHtml.obj \
	tfp_tfpMemory.obj \
	tfp_tfpRdGed.obj \
	tfp_tfpVersion.obj \
	tfp_tfpWrAdmin.obj \
	tfp_tfpWrChart.obj \
	tfp_tfpWrEvent.obj \
	tfp_tfpWrFamily.obj \
	tfp_tfpWrIndividual.obj \
	tfp_tfpWrName.obj \
	tfp_tfpWrNotes.obj \
	tfp_tfpWrReference.obj \
	tfp_webviewfshandler.obj \
	tfp_dummy.obj
TFP_RESOURCES =  \
	tfp_tfp.res
CALENDAR_CXXFLAGS = /MD$(VAR_43) /DWIN32 /D_UNICODE $(__WXDEBUG_DEFINE_p) \
	/D__WXMSW__ \
	/I$(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib\msw$(WXLIBPOSTFIX) \
	/I$(WX_DIR)\include $(VAR) $(VAR_42) $(p) /Fdcalendar$(WXLIBPOSTFIX).pdb \
	/I..\..\include\cal /I..\..\include /GR /EHsc /Yu"wx/wxprec.h" \
	/Fp"wxprec_calendar.pch" $(CPPFLAGS) $(CXXFLAGS)
CALENDAR_OBJECTS =  \
	calendar_calendar.obj \
	calendar_calGregorian.obj \
	calendar_calJDay.obj \
	calendar_calJulian.obj \
	calendar_calLatin.obj \
	calendar_dummy.obj
TESTS_CXXFLAGS = /MD$(VAR_43) /DWIN32 /D_UNICODE $(__WXDEBUG_DEFINE_p) \
	/D__WXMSW__ \
	/I$(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib\msw$(WXLIBPOSTFIX) \
	/I$(WX_DIR)\include $(VAR) $(VAR_42) $(p) /Fdtests.pdb /D_CONSOLE \
	/I..\..\include /I..\..\tests /I$(CPPUNIT)\include /GR /EHsc /Yu"testprec.h" \
	/Fp"wxprec_tests.pch" $(CPPFLAGS) $(CXXFLAGS)
TESTS_OBJECTS =  \
	tests_dummy.obj \
	tests_test.obj \
	tests_testCalendar.obj \
	tests_testDatabase.obj
CALCALC_CXXFLAGS = /MD$(VAR_43) /DWIN32 /D_UNICODE $(__WXDEBUG_DEFINE_p) \
	/D__WXMSW__ \
	/I$(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib\msw$(WXLIBPOSTFIX) \
	/I$(WX_DIR)\include $(VAR) $(VAR_42) $(p) /Fdcalcalc.pdb /D_CONSOLE \
	/I..\..\include /GR /EHsc $(CPPFLAGS) $(CXXFLAGS)
CALCALC_OBJECTS =  \
	calcalc_calCalc.obj
FILE2CPP_CXXFLAGS = /MD$(VAR_43) /DWIN32 /D_UNICODE $(__WXDEBUG_DEFINE_p) \
	/D__WXMSW__ \
	/I$(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib\msw$(WXLIBPOSTFIX) \
	/I$(WX_DIR)\include $(VAR) $(VAR_42) $(p) /Fdfile2cpp.pdb /D_CONSOLE /GR /EHsc \
	$(CPPFLAGS) $(CXXFLAGS)
FILE2CPP_OBJECTS =  \
	file2cpp_fcMain.obj
WXSQLITE3_CFLAGS = /MD$(VAR_43) /DWIN32 /D_UNICODE $(__WXDEBUG_DEFINE_p) \
	/D__WXMSW__ \
	/I$(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib\msw$(WXLIBPOSTFIX) \
	/I$(WX_DIR)\include $(VAR) $(VAR_42) $(p) /Fdwxsqlite3$(WXLIBPOSTFIX).pdb \
	/DSQLITE_ENABLE_RTREE /I..\..\include $(CPPFLAGS) $(CFLAGS)
WXSQLITE3_CXXFLAGS = /MD$(VAR_43) /DWIN32 /D_UNICODE $(__WXDEBUG_DEFINE_p) \
	/D__WXMSW__ \
	/I$(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib\msw$(WXLIBPOSTFIX) \
	/I$(WX_DIR)\include $(VAR) $(VAR_42) $(p) /Fdwxsqlite3$(WXLIBPOSTFIX).pdb \
	/DSQLITE_ENABLE_RTREE /I..\..\include /GR /EHsc $(CPPFLAGS) $(CXXFLAGS)
WXSQLITE3_OBJECTS =  \
	wxsqlite3_wxsqlite3.obj \
	wxsqlite3_sqlite3.obj
REC_CXXFLAGS = /MD$(VAR_43) /DWIN32 /D_UNICODE $(__WXDEBUG_DEFINE_p) /D__WXMSW__ \
	/I$(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib\msw$(WXLIBPOSTFIX) \
	/I$(WX_DIR)\include $(VAR) $(VAR_42) $(p) /Fdrec$(WXLIBPOSTFIX).pdb \
	/I..\..\include\rec /I..\..\include /GR /EHsc /Yu"wx/wxprec.h" \
	/Fp"wxprec_rec.pch" $(CPPFLAGS) $(CXXFLAGS)
REC_OBJECTS =  \
	rec_recContact.obj \
	rec_recDatabase.obj \
	rec_recDate.obj \
	rec_recEvent.obj \
	rec_recGedParse.obj \
	rec_recIndividual.obj \
	rec_recLink.obj \
	rec_recName.obj \
	rec_recPersona.obj \
	rec_recPlace.obj \
	rec_recReference.obj \
	rec_recRelationship.obj \
	rec_recSource.obj \
	rec_recSystem.obj \
	rec_recUser.obj \
	rec_recVersion.obj \
	rec_dummy.obj
RECCL_CXXFLAGS = /MD$(VAR_43) /DWIN32 /D_UNICODE $(__WXDEBUG_DEFINE_p) \
	/D__WXMSW__ \
	/I$(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib\msw$(WXLIBPOSTFIX) \
	/I$(WX_DIR)\include $(VAR) $(VAR_42) $(p) /Fdreccl$(WXLIBPOSTFIX).pdb \
	/I..\..\include\rec /I..\..\include /GR /EHsc $(CPPFLAGS) $(CXXFLAGS)
RECCL_OBJECTS =  \
	reccl_reccl.obj
RECGUI_CXXFLAGS = /MD$(VAR_43) /DWIN32 /D_UNICODE $(__WXDEBUG_DEFINE_p) \
	/D__WXMSW__ \
	/I$(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib\msw$(WXLIBPOSTFIX) \
	/I$(WX_DIR)\include $(VAR) $(VAR_42) $(p) /Fdrecgui$(WXLIBPOSTFIX).pdb \
	/I..\..\include\rec /I..\..\include /GR /EHsc $(CPPFLAGS) $(CXXFLAGS)
RECGUI_OBJECTS =  \
	recgui_recgui.obj
SCRIPT_CXXFLAGS = /MD$(VAR_43) /DWIN32 /D_UNICODE $(__WXDEBUG_DEFINE_p) \
	/D__WXMSW__ \
	/I$(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib\msw$(WXLIBPOSTFIX) \
	/I$(WX_DIR)\include $(VAR) $(VAR_42) $(p) /Fdscript$(WXLIBPOSTFIX).pdb \
	/I..\..\..\tfp_ext\include\ts /I..\..\..\tfp_ext\include \
	/I..\..\..\tfp\include /GR /EHsc /Yu"wx/wxprec.h" /Fp"wxprec_script.pch" \
	$(CPPFLAGS) $(CXXFLAGS)
SCRIPT_OBJECTS =  \
	script_tsScript.obj \
	script_tsParse.obj \
	script_tsToken.obj \
	script_tsVar.obj \
	script_dummy.obj
RUNSCRIPT_CXXFLAGS = /MD$(VAR_43) /DWIN32 /D_UNICODE $(__WXDEBUG_DEFINE_p) \
	/D__WXMSW__ \
	/I$(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib\msw$(WXLIBPOSTFIX) \
	/I$(WX_DIR)\include $(VAR) $(VAR_42) $(p) /FdrunScript.pdb /D_CONSOLE \
	/I..\..\..\tfp_ext\include /GR /EHsc $(CPPFLAGS) $(CXXFLAGS)
RUNSCRIPT_OBJECTS =  \
	runScript_runScript.obj
PVC_CXXFLAGS = /MD$(VAR_43) /DWIN32 /D_UNICODE $(__WXDEBUG_DEFINE_p) /D__WXMSW__ \
	/I$(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib\msw$(WXLIBPOSTFIX) \
	/I$(WX_DIR)\include $(VAR) $(VAR_42) $(p) /Fdpvc.pdb /D_CONSOLE /GR /EHsc \
	$(CPPFLAGS) $(CXXFLAGS)
PVC_OBJECTS =  \
	pvc_pvcMain.obj
FILL_CXXFLAGS = /MD$(VAR_43) /DWIN32 /D_UNICODE $(__WXDEBUG_DEFINE_p) \
	/D__WXMSW__ \
	/I$(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib\msw$(WXLIBPOSTFIX) \
	/I$(WX_DIR)\include $(VAR) $(VAR_42) $(p) /Fdfill.pdb /D_CONSOLE \
	/I..\..\..\tfp_ext\include /I..\..\..\tfp_fill\src /I..\..\..\tfp\include \
	/GR /EHsc /Yu"wx/wxprec.h" /Fp"wxprec_fill.pch" $(CPPFLAGS) $(CXXFLAGS)
FILL_OBJECTS =  \
	fill_dummy.obj \
	fill_nkMain.obj \
	fill_nkRecHelpers.obj \
	fill_nkRefBreakdown.obj \
	fill_nkRefDocCustom.obj \
	fill_nkRefDocuments.obj \
	fill_nkTest.obj \
	fill_nkXmlHelpers.obj \
	fill_xml2.obj
SPATIALITE_CFLAGS = /MD$(VAR_43) /DWIN32 /D_UNICODE $(__WXDEBUG_DEFINE_p) \
	/D__WXMSW__ \
	/I$(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib\msw$(WXLIBPOSTFIX) \
	/I$(WX_DIR)\include $(VAR) $(VAR_42) $(p) /Fdspatialite$(WXLIBPOSTFIX).pdb \
	/I..\..\..\tfp_place\include $(CPPFLAGS) $(CFLAGS)
SPATIALITE_OBJECTS =  \
	spatialite_spatialite.obj \
	spatialite_win_iconv.obj \
	spatialite_localcharset_win.obj
FREEXL_CFLAGS = /MD$(VAR_43) /DWIN32 /D_UNICODE $(__WXDEBUG_DEFINE_p) \
	/D__WXMSW__ \
	/I$(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib\msw$(WXLIBPOSTFIX) \
	/I$(WX_DIR)\include $(VAR) $(VAR_42) $(p) /Fdfreexl$(WXLIBPOSTFIX).pdb \
	/I..\..\..\tfp_place\include $(CPPFLAGS) $(CFLAGS)
FREEXL_OBJECTS =  \
	freexl_freexl.obj
TP_CXXFLAGS = /MD$(VAR_43) /DWIN32 /D_UNICODE $(__WXDEBUG_DEFINE_p) /D__WXMSW__ \
	/I$(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib\msw$(WXLIBPOSTFIX) \
	/I$(WX_DIR)\include $(VAR) $(VAR_42) $(p) /Fdtp$(WXLIBPOSTFIX).pdb \
	/I..\..\..\tfp_place\include\tp /I..\..\..\tfp_place\include \
	/I..\..\..\tfp\include /GR /EHsc /Yu"wx/wxprec.h" /Fp"wxprec_tp.pch" \
	$(CPPFLAGS) $(CXXFLAGS)
TP_OBJECTS =  \
	tp_tpPlaces.obj \
	tp_tpVersion.obj \
	tp_dummy.obj
PE_CXXFLAGS = /MD$(VAR_43) /DWIN32 /D_UNICODE $(__WXDEBUG_DEFINE_p) /D__WXMSW__ \
	/I$(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib\msw$(WXLIBPOSTFIX) \
	/I$(WX_DIR)\include $(VAR) $(VAR_42) $(p) /Fdpe.pdb /D_WINDOWS \
	/I..\..\..\tfp_place\include /I..\..\..\tfp_place\utils\pe \
	/I..\..\..\tfp\src /I..\..\..\tfp\include /GR /EHsc /Yu"wx/wxprec.h" \
	/Fp"wxprec_pe.pch" $(CPPFLAGS) $(CXXFLAGS)
PE_OBJECTS =  \
	pe_peApp.obj \
	pe_peFrame.obj \
	pe_peVersion.obj \
	pe_dummy.obj
PE_RESOURCES =  \
	pe_pe.res

### Conditionally set variables: ###

!if "$(WX_DEBUG)" == "1"
WX3RDPARTYLIBPOSTFIX = d
!endif
!if "$(TARGET_CPU)" == "AMD64"
WXMACHINE_FLAG = /MACHINE:AMD64
!endif
!if "$(TARGET_CPU)" == "IA64"
WXMACHINE_FLAG = /MACHINE:IA64
!endif
!if "$(WX_DEBUG)" == "0"
____tfp__DEBUGINFO_9 = 
!endif
!if "$(WX_DEBUG)" == "1"
____tfp__DEBUGINFO_9 = $(VAR_37)
!endif
!if "$(WX_DEBUG)" == "0"
____tests__DEBUGINFO_34 = 
!endif
!if "$(WX_DEBUG)" == "1"
____tests__DEBUGINFO_34 = $(VAR_37)
!endif
!if "$(WX_DEBUG)" == "0"
____WX_DEBUG_39_p = cppunit.lib
!endif
!if "$(WX_DEBUG)" == "1"
____WX_DEBUG_39_p = cppunitd.lib
!endif
!if "$(WX_DEBUG)" == "0"
____calcalc__DEBUGINFO_49 = 
!endif
!if "$(WX_DEBUG)" == "1"
____calcalc__DEBUGINFO_49 = $(VAR_37)
!endif
!if "$(WX_DEBUG)" == "0"
____file2cpp__DEBUGINFO_62 = 
!endif
!if "$(WX_DEBUG)" == "1"
____file2cpp__DEBUGINFO_62 = $(VAR_37)
!endif
!if "$(WX_DEBUG)" == "0"
____runScript__DEBUGINFO_127 = 
!endif
!if "$(WX_DEBUG)" == "1"
____runScript__DEBUGINFO_127 = $(VAR_37)
!endif
!if "$(WX_DEBUG)" == "0"
____pvc__DEBUGINFO_140 = 
!endif
!if "$(WX_DEBUG)" == "1"
____pvc__DEBUGINFO_140 = $(VAR_37)
!endif
!if "$(WX_DEBUG)" == "0"
____fill__DEBUGINFO_153 = 
!endif
!if "$(WX_DEBUG)" == "1"
____fill__DEBUGINFO_153 = $(VAR_37)
!endif
!if "$(WX_DEBUG)" == "0"
____pe__DEBUGINFO_198 = 
!endif
!if "$(WX_DEBUG)" == "1"
____pe__DEBUGINFO_198 = $(VAR_37)
!endif
!if "$(WX_DEBUG)" == "1"
__WXDEBUG_DEFINE_p_0 = /d __WXDEBUG__
!endif
!if "$(WX_DEBUG)" == "0"
p_1 = 
!endif
!if "$(WX_DEBUG)" == "1"
p_1 = /d _DEBUG
!endif
!if "$(WX_DEBUG)" == "0"
VAR_35 = 
!endif
!if "$(WX_DEBUG)" == "1"
VAR_35 = /DEBUG
!endif
!if "$(WX_DEBUG)" == "0"
VAR_37 = /opt:ref /opt:icf
!endif
!if "$(WX_DEBUG)" == "1"
VAR_37 = 
!endif
!if "$(WX_DEBUG)" == "1"
__WXDEBUG_DEFINE_p = /D__WXDEBUG__
!endif
!if "$(WX_DEBUG)" == "0"
VAR = /O2
!endif
!if "$(WX_DEBUG)" == "1"
VAR = /Od
!endif
!if "$(WX_DEBUG)" == "0"
VAR_42 = 
!endif
!if "$(WX_DEBUG)" == "1"
VAR_42 = /Zi
!endif
!if "$(WX_DEBUG)" == "0"
p = 
!endif
!if "$(WX_DEBUG)" == "1"
p = /D_DEBUG
!endif
!if "$(WX_DEBUG)" == "0"
VAR_43 = 
!endif
!if "$(WX_DEBUG)" == "1"
VAR_43 = d
!endif
!if "$(WX_DEBUG)" == "0"
WXLIBPOSTFIX = u
!endif
!if "$(WX_DEBUG)" == "1"
WXLIBPOSTFIX = ud
!endif
!if "$(TARGET_CPU)" == "AMD64"
WXCPU = _x64
!endif
!if "$(TARGET_CPU)" == "IA64"
WXCPU = _ia64
!endif


### Targets: ###

all: test_for_selected_wxbuild tfp.exe calendar$(WXLIBPOSTFIX).lib tests.exe calcalc.exe file2cpp.exe wxsqlite3$(WXLIBPOSTFIX).lib rec$(WXLIBPOSTFIX).lib reccl$(WXLIBPOSTFIX).lib recgui$(WXLIBPOSTFIX).lib script$(WXLIBPOSTFIX).lib runScript.exe pvc.exe fill.exe spatialite$(WXLIBPOSTFIX).lib freexl$(WXLIBPOSTFIX).lib tp$(WXLIBPOSTFIX).lib pe.exe

clean: 
	-if exist .\*.obj del .\*.obj
	-if exist .\*.res del .\*.res
	-if exist .\*.pch del .\*.pch
	-if exist tfp.exe del tfp.exe
	-if exist tfp.ilk del tfp.ilk
	-if exist tfp.pdb del tfp.pdb
	-if exist calendar$(WXLIBPOSTFIX).lib del calendar$(WXLIBPOSTFIX).lib
	-if exist tests.exe del tests.exe
	-if exist tests.ilk del tests.ilk
	-if exist tests.pdb del tests.pdb
	-if exist calcalc.exe del calcalc.exe
	-if exist calcalc.ilk del calcalc.ilk
	-if exist calcalc.pdb del calcalc.pdb
	-if exist file2cpp.exe del file2cpp.exe
	-if exist file2cpp.ilk del file2cpp.ilk
	-if exist file2cpp.pdb del file2cpp.pdb
	-if exist wxsqlite3$(WXLIBPOSTFIX).lib del wxsqlite3$(WXLIBPOSTFIX).lib
	-if exist rec$(WXLIBPOSTFIX).lib del rec$(WXLIBPOSTFIX).lib
	-if exist reccl$(WXLIBPOSTFIX).lib del reccl$(WXLIBPOSTFIX).lib
	-if exist recgui$(WXLIBPOSTFIX).lib del recgui$(WXLIBPOSTFIX).lib
	-if exist script$(WXLIBPOSTFIX).lib del script$(WXLIBPOSTFIX).lib
	-if exist runScript.exe del runScript.exe
	-if exist runScript.ilk del runScript.ilk
	-if exist runScript.pdb del runScript.pdb
	-if exist pvc.exe del pvc.exe
	-if exist pvc.ilk del pvc.ilk
	-if exist pvc.pdb del pvc.pdb
	-if exist fill.exe del fill.exe
	-if exist fill.ilk del fill.ilk
	-if exist fill.pdb del fill.pdb
	-if exist spatialite$(WXLIBPOSTFIX).lib del spatialite$(WXLIBPOSTFIX).lib
	-if exist freexl$(WXLIBPOSTFIX).lib del freexl$(WXLIBPOSTFIX).lib
	-if exist tp$(WXLIBPOSTFIX).lib del tp$(WXLIBPOSTFIX).lib
	-if exist pe.exe del pe.exe
	-if exist pe.ilk del pe.ilk
	-if exist pe.pdb del pe.pdb

test_for_selected_wxbuild: 
	@if not exist $(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib\msw$(WXLIBPOSTFIX)\wx\setup.h \
	echo ----------------------------------------------------------------------------
	@if not exist $(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib\msw$(WXLIBPOSTFIX)\wx\setup.h \
	echo The selected wxWidgets build is not available!
	@if not exist $(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib\msw$(WXLIBPOSTFIX)\wx\setup.h \
	echo Please use the options prefixed with WX_ to select another wxWidgets build.
	@if not exist $(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib\msw$(WXLIBPOSTFIX)\wx\setup.h \
	echo ----------------------------------------------------------------------------
	@if not exist $(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib\msw$(WXLIBPOSTFIX)\wx\setup.h \
	exit 1

../../../tfp_place/src/generated/tfpText.ci: ..\..\src\tfpText.f2c ..\..\src\startup.htm
	file2cpp -v -o ../../src/generated/tfpText.ci ../../src/tfpText.f2c

../../../tfp_place/src/tfpMemory.cpp: ..\..\src\generated\tfpText.ci

tfp.exe: tfp_dummy.obj  $(TFP_OBJECTS) tfp_tfp.res wxsqlite3$(WXLIBPOSTFIX).lib rec$(WXLIBPOSTFIX).lib recgui$(WXLIBPOSTFIX).lib calendar$(WXLIBPOSTFIX).lib
	link /NOLOGO /OUT:$@  /LIBPATH:$(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib $(WXMACHINE_FLAG) $(VAR_35) /pdb:"tfp.pdb" $(____tfp__DEBUGINFO_9) /SUBSYSTEM:WINDOWS $(LDFLAGS) @<<
	$(TFP_OBJECTS) $(TFP_RESOURCES)  wxsqlite3$(WXLIBPOSTFIX).lib rec$(WXLIBPOSTFIX).lib recgui$(WXLIBPOSTFIX).lib calendar$(WXLIBPOSTFIX).lib wxmsw$(WX_VERSION)$(WXLIBPOSTFIX)_webview.lib wxmsw$(WX_VERSION)$(WXLIBPOSTFIX)_html.lib wxmsw$(WX_VERSION)$(WXLIBPOSTFIX)_adv.lib wxmsw$(WX_VERSION)$(WXLIBPOSTFIX)_core.lib wxbase$(WX_VERSION)$(WXLIBPOSTFIX).lib wxtiff$(WX3RDPARTYLIBPOSTFIX).lib wxjpeg$(WX3RDPARTYLIBPOSTFIX).lib wxpng$(WX3RDPARTYLIBPOSTFIX).lib wxzlib$(WX3RDPARTYLIBPOSTFIX).lib wxregex$(WXLIBPOSTFIX).lib wxexpat$(WX3RDPARTYLIBPOSTFIX).lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib
<<

calendar$(WXLIBPOSTFIX).lib: calendar_dummy.obj  $(CALENDAR_OBJECTS)
	if exist $@ del $@
	link /LIB /NOLOGO /OUT:$@ @<<
	$(CALENDAR_OBJECTS)
<<

tests.exe: tests_dummy.obj  $(TESTS_OBJECTS) calendar$(WXLIBPOSTFIX).lib wxsqlite3$(WXLIBPOSTFIX).lib reccl$(WXLIBPOSTFIX).lib rec$(WXLIBPOSTFIX).lib
	link /NOLOGO /OUT:$@  /LIBPATH:$(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib $(WXMACHINE_FLAG) $(VAR_35) /pdb:"tests.pdb" $(____tests__DEBUGINFO_34) /SUBSYSTEM:CONSOLE /LIBPATH:$(CPPUNIT)\lib $(LDFLAGS) @<<
	$(TESTS_OBJECTS)   calendar$(WXLIBPOSTFIX).lib wxsqlite3$(WXLIBPOSTFIX).lib reccl$(WXLIBPOSTFIX).lib rec$(WXLIBPOSTFIX).lib $(____WX_DEBUG_39_p) wxmsw$(WX_VERSION)$(WXLIBPOSTFIX)_core.lib wxbase$(WX_VERSION)$(WXLIBPOSTFIX).lib wxbase$(WX_VERSION)$(WXLIBPOSTFIX)_net.lib wxtiff$(WX3RDPARTYLIBPOSTFIX).lib wxjpeg$(WX3RDPARTYLIBPOSTFIX).lib wxpng$(WX3RDPARTYLIBPOSTFIX).lib wxzlib$(WX3RDPARTYLIBPOSTFIX).lib wxregex$(WXLIBPOSTFIX).lib wxexpat$(WX3RDPARTYLIBPOSTFIX).lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib
<<

calcalc.exe: $(CALCALC_OBJECTS) calendar$(WXLIBPOSTFIX).lib
	link /NOLOGO /OUT:$@  /LIBPATH:$(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib $(WXMACHINE_FLAG) $(VAR_35) /pdb:"calcalc.pdb" $(____calcalc__DEBUGINFO_49) /SUBSYSTEM:CONSOLE $(LDFLAGS) @<<
	$(CALCALC_OBJECTS)   calendar$(WXLIBPOSTFIX).lib wxbase$(WX_VERSION)$(WXLIBPOSTFIX).lib wxtiff$(WX3RDPARTYLIBPOSTFIX).lib wxjpeg$(WX3RDPARTYLIBPOSTFIX).lib wxpng$(WX3RDPARTYLIBPOSTFIX).lib wxzlib$(WX3RDPARTYLIBPOSTFIX).lib wxregex$(WXLIBPOSTFIX).lib wxexpat$(WX3RDPARTYLIBPOSTFIX).lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib
<<

file2cpp.exe: $(FILE2CPP_OBJECTS)
	link /NOLOGO /OUT:$@  /LIBPATH:$(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib $(WXMACHINE_FLAG) $(VAR_35) /pdb:"file2cpp.pdb" $(____file2cpp__DEBUGINFO_62) /SUBSYSTEM:CONSOLE $(LDFLAGS) @<<
	$(FILE2CPP_OBJECTS)   wxbase$(WX_VERSION)$(WXLIBPOSTFIX).lib wxtiff$(WX3RDPARTYLIBPOSTFIX).lib wxjpeg$(WX3RDPARTYLIBPOSTFIX).lib wxpng$(WX3RDPARTYLIBPOSTFIX).lib wxzlib$(WX3RDPARTYLIBPOSTFIX).lib wxregex$(WXLIBPOSTFIX).lib wxexpat$(WX3RDPARTYLIBPOSTFIX).lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib
<<

wxsqlite3$(WXLIBPOSTFIX).lib: $(WXSQLITE3_OBJECTS)
	if exist $@ del $@
	link /LIB /NOLOGO /OUT:$@ @<<
	$(WXSQLITE3_OBJECTS)
<<

../../../tfp_place/src/rec/generated/recSql.ci: ..\..\src\rec\recSql.f2c ..\..\src\rec\recCreate.sql
	file2cpp -v -o ../../src/rec/generated/recSql.ci ../../src/rec/recSql.f2c

../../../tfp_place/src/rec/recDatabase.cpp: ..\..\src\rec\generated\recSql.ci

rec$(WXLIBPOSTFIX).lib: rec_dummy.obj  $(REC_OBJECTS)
	if exist $@ del $@
	link /LIB /NOLOGO /OUT:$@ @<<
	$(REC_OBJECTS)
<<

reccl$(WXLIBPOSTFIX).lib: $(RECCL_OBJECTS)
	if exist $@ del $@
	link /LIB /NOLOGO /OUT:$@ @<<
	$(RECCL_OBJECTS)
<<

recgui$(WXLIBPOSTFIX).lib: $(RECGUI_OBJECTS)
	if exist $@ del $@
	link /LIB /NOLOGO /OUT:$@ @<<
	$(RECGUI_OBJECTS)
<<

script$(WXLIBPOSTFIX).lib: script_dummy.obj  $(SCRIPT_OBJECTS)
	if exist $@ del $@
	link /LIB /NOLOGO /OUT:$@ @<<
	$(SCRIPT_OBJECTS)
<<

runScript.exe: $(RUNSCRIPT_OBJECTS) calendar$(WXLIBPOSTFIX).lib wxsqlite3$(WXLIBPOSTFIX).lib rec$(WXLIBPOSTFIX).lib reccl$(WXLIBPOSTFIX).lib script$(WXLIBPOSTFIX).lib
	link /NOLOGO /OUT:$@  /LIBPATH:$(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib $(WXMACHINE_FLAG) $(VAR_35) /pdb:"runScript.pdb" $(____runScript__DEBUGINFO_127) /SUBSYSTEM:CONSOLE $(LDFLAGS) @<<
	$(RUNSCRIPT_OBJECTS)   calendar$(WXLIBPOSTFIX).lib wxsqlite3$(WXLIBPOSTFIX).lib rec$(WXLIBPOSTFIX).lib reccl$(WXLIBPOSTFIX).lib script$(WXLIBPOSTFIX).lib wxbase$(WX_VERSION)$(WXLIBPOSTFIX).lib wxtiff$(WX3RDPARTYLIBPOSTFIX).lib wxjpeg$(WX3RDPARTYLIBPOSTFIX).lib wxpng$(WX3RDPARTYLIBPOSTFIX).lib wxzlib$(WX3RDPARTYLIBPOSTFIX).lib wxregex$(WXLIBPOSTFIX).lib wxexpat$(WX3RDPARTYLIBPOSTFIX).lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib
<<

pvc.exe: $(PVC_OBJECTS)
	link /NOLOGO /OUT:$@  /LIBPATH:$(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib $(WXMACHINE_FLAG) $(VAR_35) /pdb:"pvc.pdb" $(____pvc__DEBUGINFO_140) /SUBSYSTEM:CONSOLE $(LDFLAGS) @<<
	$(PVC_OBJECTS)   wxbase$(WX_VERSION)$(WXLIBPOSTFIX).lib wxtiff$(WX3RDPARTYLIBPOSTFIX).lib wxjpeg$(WX3RDPARTYLIBPOSTFIX).lib wxpng$(WX3RDPARTYLIBPOSTFIX).lib wxzlib$(WX3RDPARTYLIBPOSTFIX).lib wxregex$(WXLIBPOSTFIX).lib wxexpat$(WX3RDPARTYLIBPOSTFIX).lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib
<<

fill.exe: fill_dummy.obj  $(FILL_OBJECTS) calendar$(WXLIBPOSTFIX).lib wxsqlite3$(WXLIBPOSTFIX).lib rec$(WXLIBPOSTFIX).lib reccl$(WXLIBPOSTFIX).lib
	link /NOLOGO /OUT:$@  /LIBPATH:$(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib $(WXMACHINE_FLAG) $(VAR_35) /pdb:"fill.pdb" $(____fill__DEBUGINFO_153) /SUBSYSTEM:CONSOLE $(LDFLAGS) @<<
	$(FILL_OBJECTS)   calendar$(WXLIBPOSTFIX).lib wxsqlite3$(WXLIBPOSTFIX).lib rec$(WXLIBPOSTFIX).lib reccl$(WXLIBPOSTFIX).lib wxmsw$(WX_VERSION)$(WXLIBPOSTFIX)_core.lib wxbase$(WX_VERSION)$(WXLIBPOSTFIX).lib wxbase$(WX_VERSION)$(WXLIBPOSTFIX)_net.lib wxtiff$(WX3RDPARTYLIBPOSTFIX).lib wxjpeg$(WX3RDPARTYLIBPOSTFIX).lib wxpng$(WX3RDPARTYLIBPOSTFIX).lib wxzlib$(WX3RDPARTYLIBPOSTFIX).lib wxregex$(WXLIBPOSTFIX).lib wxexpat$(WX3RDPARTYLIBPOSTFIX).lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib
<<

spatialite$(WXLIBPOSTFIX).lib: $(SPATIALITE_OBJECTS)
	if exist $@ del $@
	link /LIB /NOLOGO /OUT:$@ @<<
	$(SPATIALITE_OBJECTS)
<<

freexl$(WXLIBPOSTFIX).lib: $(FREEXL_OBJECTS)
	if exist $@ del $@
	link /LIB /NOLOGO /OUT:$@ @<<
	$(FREEXL_OBJECTS)
<<

tp$(WXLIBPOSTFIX).lib: tp_dummy.obj  $(TP_OBJECTS)
	if exist $@ del $@
	link /LIB /NOLOGO /OUT:$@ @<<
	$(TP_OBJECTS)
<<

pe.exe: pe_dummy.obj  $(PE_OBJECTS) pe_pe.res calendar$(WXLIBPOSTFIX).lib rec$(WXLIBPOSTFIX).lib recgui$(WXLIBPOSTFIX).lib tp$(WXLIBPOSTFIX).lib spatialite$(WXLIBPOSTFIX).lib freexl$(WXLIBPOSTFIX).lib wxsqlite3$(WXLIBPOSTFIX).lib
	link /NOLOGO /OUT:$@  /LIBPATH:$(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib $(WXMACHINE_FLAG) $(VAR_35) /pdb:"pe.pdb" $(____pe__DEBUGINFO_198) /SUBSYSTEM:WINDOWS /LIBPATH:..\..\..\tfp_place\lib\nmake $(LDFLAGS) @<<
	$(PE_OBJECTS) $(PE_RESOURCES)  calendar$(WXLIBPOSTFIX).lib rec$(WXLIBPOSTFIX).lib recgui$(WXLIBPOSTFIX).lib tp$(WXLIBPOSTFIX).lib spatialite$(WXLIBPOSTFIX).lib freexl$(WXLIBPOSTFIX).lib geos_c.lib proj.lib wxsqlite3$(WXLIBPOSTFIX).lib wxmsw$(WX_VERSION)$(WXLIBPOSTFIX)_adv.lib wxmsw$(WX_VERSION)$(WXLIBPOSTFIX)_core.lib wxbase$(WX_VERSION)$(WXLIBPOSTFIX).lib wxtiff$(WX3RDPARTYLIBPOSTFIX).lib wxjpeg$(WX3RDPARTYLIBPOSTFIX).lib wxpng$(WX3RDPARTYLIBPOSTFIX).lib wxzlib$(WX3RDPARTYLIBPOSTFIX).lib wxregex$(WXLIBPOSTFIX).lib wxexpat$(WX3RDPARTYLIBPOSTFIX).lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib oleacc.lib
<<

tfp_dlgEd.obj: .\..\..\src\dlg\dlgEd.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\dlg\dlgEd.cpp

tfp_dlgEdContact.obj: .\..\..\src\dlg\dlgEdContact.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\dlg\dlgEdContact.cpp

tfp_dlgEdDate.obj: .\..\..\src\dlg\dlgEdDate.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\dlg\dlgEdDate.cpp

tfp_dlgEdEvent.obj: .\..\..\src\dlg\dlgEdEvent.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\dlg\dlgEdEvent.cpp

tfp_dlgEdFamily.obj: .\..\..\src\dlg\dlgEdFamily.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\dlg\dlgEdFamily.cpp

tfp_dlgEdIndEvent.obj: .\..\..\src\dlg\dlgEdIndEvent.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\dlg\dlgEdIndEvent.cpp

tfp_dlgEdIndividual.obj: .\..\..\src\dlg\dlgEdIndividual.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\dlg\dlgEdIndividual.cpp

tfp_dlgEdName.obj: .\..\..\src\dlg\dlgEdName.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\dlg\dlgEdName.cpp

tfp_dlgEdNamePart.obj: .\..\..\src\dlg\dlgEdNamePart.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\dlg\dlgEdNamePart.cpp

tfp_dlgEdPersona.obj: .\..\..\src\dlg\dlgEdPersona.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\dlg\dlgEdPersona.cpp

tfp_dlgEdPlace.obj: .\..\..\src\dlg\dlgEdPlace.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\dlg\dlgEdPlace.cpp

tfp_dlgEdReference.obj: .\..\..\src\dlg\dlgEdReference.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\dlg\dlgEdReference.cpp

tfp_dlgEdRelationship.obj: .\..\..\src\dlg\dlgEdRelationship.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\dlg\dlgEdRelationship.cpp

tfp_dlgEdResearcher.obj: .\..\..\src\dlg\dlgEdResearcher.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\dlg\dlgEdResearcher.cpp

tfp_dlgEdRole.obj: .\..\..\src\dlg\dlgEdRole.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\dlg\dlgEdRole.cpp

tfp_dlgEdSystem.obj: .\..\..\src\dlg\dlgEdSystem.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\dlg\dlgEdSystem.cpp

tfp_dlgNote.obj: .\..\..\src\dlg\dlgNote.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\dlg\dlgNote.cpp

tfp_dlgRecTableCtrl.obj: .\..\..\src\dlg\dlgRecTableCtrl.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\dlg\dlgRecTableCtrl.cpp

tfp_dlgSelect.obj: .\..\..\src\dlg\dlgSelect.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\dlg\dlgSelect.cpp

tfp_dlgSelEvent.obj: .\..\..\src\dlg\dlgSelEvent.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\dlg\dlgSelEvent.cpp

tfp_dlgSelIndividual.obj: .\..\..\src\dlg\dlgSelIndividual.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\dlg\dlgSelIndividual.cpp

tfp_fbDlg.obj: .\..\..\src\dlg\fbDlg.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\dlg\fbDlg.cpp

tfp_tfpApp.obj: .\..\..\src\tfpApp.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\tfpApp.cpp

tfp_tfpFrame.obj: .\..\..\src\tfpFrame.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\tfpFrame.cpp

tfp_tfpHtml.obj: .\..\..\src\tfpHtml.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\tfpHtml.cpp

tfp_tfpMemory.obj: .\..\..\src\tfpMemory.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\tfpMemory.cpp

tfp_tfpRdGed.obj: .\..\..\src\tfpRdGed.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\tfpRdGed.cpp

tfp_tfpVersion.obj: .\..\..\src\tfpVersion.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\tfpVersion.cpp

tfp_tfpWrAdmin.obj: .\..\..\src\tfpWrAdmin.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\tfpWrAdmin.cpp

tfp_tfpWrChart.obj: .\..\..\src\tfpWrChart.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\tfpWrChart.cpp

tfp_tfpWrEvent.obj: .\..\..\src\tfpWrEvent.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\tfpWrEvent.cpp

tfp_tfpWrFamily.obj: .\..\..\src\tfpWrFamily.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\tfpWrFamily.cpp

tfp_tfpWrIndividual.obj: .\..\..\src\tfpWrIndividual.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\tfpWrIndividual.cpp

tfp_tfpWrName.obj: .\..\..\src\tfpWrName.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\tfpWrName.cpp

tfp_tfpWrNotes.obj: .\..\..\src\tfpWrNotes.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\tfpWrNotes.cpp

tfp_tfpWrReference.obj: .\..\..\src\tfpWrReference.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\tfpWrReference.cpp

tfp_webviewfshandler.obj: .\..\..\src\webviewfshandler.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) .\..\..\src\webviewfshandler.cpp

tfp_tfp.res: .\..\..\src\tfp.rc
	rc /fo$@  /d WIN32  /d _UNICODE $(__WXDEBUG_DEFINE_p_0) /d __WXMSW__ /i $(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib\msw$(WXLIBPOSTFIX) /i $(WX_DIR)\include $(p_1) /d _WINDOWS /i ..\..\include /i ..\..\src .\..\..\src\tfp.rc

tfp_dummy.obj: .\..\..\src\dummy.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TFP_CXXFLAGS) /Ycwx/wxprec.h .\..\..\src\dummy.cpp

calendar_calendar.obj: .\..\..\src\cal\calendar.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(CALENDAR_CXXFLAGS) .\..\..\src\cal\calendar.cpp

calendar_calGregorian.obj: .\..\..\src\cal\calGregorian.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(CALENDAR_CXXFLAGS) .\..\..\src\cal\calGregorian.cpp

calendar_calJDay.obj: .\..\..\src\cal\calJDay.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(CALENDAR_CXXFLAGS) .\..\..\src\cal\calJDay.cpp

calendar_calJulian.obj: .\..\..\src\cal\calJulian.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(CALENDAR_CXXFLAGS) .\..\..\src\cal\calJulian.cpp

calendar_calLatin.obj: .\..\..\src\cal\calLatin.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(CALENDAR_CXXFLAGS) .\..\..\src\cal\calLatin.cpp

calendar_dummy.obj: .\..\..\src\dummy.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(CALENDAR_CXXFLAGS) /Ycwx/wxprec.h .\..\..\src\dummy.cpp

tests_dummy.obj: .\..\..\tests\dummy.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TESTS_CXXFLAGS) /Yctestprec.h .\..\..\tests\dummy.cpp

tests_test.obj: .\..\..\tests\test.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TESTS_CXXFLAGS) .\..\..\tests\test.cpp

tests_testCalendar.obj: .\..\..\tests\cal\testCalendar.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TESTS_CXXFLAGS) .\..\..\tests\cal\testCalendar.cpp

tests_testDatabase.obj: .\..\..\tests\rec\testDatabase.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TESTS_CXXFLAGS) .\..\..\tests\rec\testDatabase.cpp

calcalc_calCalc.obj: .\..\..\utils\cal\calCalc.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(CALCALC_CXXFLAGS) .\..\..\utils\cal\calCalc.cpp

file2cpp_fcMain.obj: .\..\..\utils\file2cpp\fcMain.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(FILE2CPP_CXXFLAGS) .\..\..\utils\file2cpp\fcMain.cpp

wxsqlite3_wxsqlite3.obj: .\..\..\3rdparty\wxsqlite3\wxsqlite3.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(WXSQLITE3_CXXFLAGS) .\..\..\3rdparty\wxsqlite3\wxsqlite3.cpp

wxsqlite3_sqlite3.obj: .\..\..\3rdparty\wxsqlite3\sqlite3.c
	$(CC) /c /nologo /TC /Fo$@ $(WXSQLITE3_CFLAGS) .\..\..\3rdparty\wxsqlite3\sqlite3.c

rec_recContact.obj: .\..\..\src\rec\recContact.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(REC_CXXFLAGS) .\..\..\src\rec\recContact.cpp

rec_recDatabase.obj: .\..\..\src\rec\recDatabase.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(REC_CXXFLAGS) .\..\..\src\rec\recDatabase.cpp

rec_recDate.obj: .\..\..\src\rec\recDate.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(REC_CXXFLAGS) .\..\..\src\rec\recDate.cpp

rec_recEvent.obj: .\..\..\src\rec\recEvent.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(REC_CXXFLAGS) .\..\..\src\rec\recEvent.cpp

rec_recGedParse.obj: .\..\..\src\rec\recGedParse.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(REC_CXXFLAGS) .\..\..\src\rec\recGedParse.cpp

rec_recIndividual.obj: .\..\..\src\rec\recIndividual.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(REC_CXXFLAGS) .\..\..\src\rec\recIndividual.cpp

rec_recLink.obj: .\..\..\src\rec\recLink.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(REC_CXXFLAGS) .\..\..\src\rec\recLink.cpp

rec_recName.obj: .\..\..\src\rec\recName.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(REC_CXXFLAGS) .\..\..\src\rec\recName.cpp

rec_recPersona.obj: .\..\..\src\rec\recPersona.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(REC_CXXFLAGS) .\..\..\src\rec\recPersona.cpp

rec_recPlace.obj: .\..\..\src\rec\recPlace.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(REC_CXXFLAGS) .\..\..\src\rec\recPlace.cpp

rec_recReference.obj: .\..\..\src\rec\recReference.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(REC_CXXFLAGS) .\..\..\src\rec\recReference.cpp

rec_recRelationship.obj: .\..\..\src\rec\recRelationship.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(REC_CXXFLAGS) .\..\..\src\rec\recRelationship.cpp

rec_recSource.obj: .\..\..\src\rec\recSource.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(REC_CXXFLAGS) .\..\..\src\rec\recSource.cpp

rec_recSystem.obj: .\..\..\src\rec\recSystem.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(REC_CXXFLAGS) .\..\..\src\rec\recSystem.cpp

rec_recUser.obj: .\..\..\src\rec\recUser.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(REC_CXXFLAGS) .\..\..\src\rec\recUser.cpp

rec_recVersion.obj: .\..\..\src\rec\recVersion.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(REC_CXXFLAGS) .\..\..\src\rec\recVersion.cpp

rec_dummy.obj: .\..\..\src\dummy.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(REC_CXXFLAGS) /Ycwx/wxprec.h .\..\..\src\dummy.cpp

reccl_reccl.obj: .\..\..\src\rec\reccl.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(RECCL_CXXFLAGS) .\..\..\src\rec\reccl.cpp

recgui_recgui.obj: .\..\..\src\rec\recgui.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(RECGUI_CXXFLAGS) .\..\..\src\rec\recgui.cpp

script_tsScript.obj: .\..\..\..\tfp_ext\src\ts\tsScript.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(SCRIPT_CXXFLAGS) .\..\..\..\tfp_ext\src\ts\tsScript.cpp

script_tsParse.obj: .\..\..\..\tfp_ext\src\ts\tsParse.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(SCRIPT_CXXFLAGS) .\..\..\..\tfp_ext\src\ts\tsParse.cpp

script_tsToken.obj: .\..\..\..\tfp_ext\src\ts\tsToken.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(SCRIPT_CXXFLAGS) .\..\..\..\tfp_ext\src\ts\tsToken.cpp

script_tsVar.obj: .\..\..\..\tfp_ext\src\ts\tsVar.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(SCRIPT_CXXFLAGS) .\..\..\..\tfp_ext\src\ts\tsVar.cpp

script_dummy.obj: .\..\..\..\tfp_ext\src\dummy.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(SCRIPT_CXXFLAGS) /Ycwx/wxprec.h .\..\..\..\tfp_ext\src\dummy.cpp

runScript_runScript.obj: .\..\..\..\tfp_ext\utils\ts\runScript.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(RUNSCRIPT_CXXFLAGS) .\..\..\..\tfp_ext\utils\ts\runScript.cpp

pvc_pvcMain.obj: .\..\..\..\tfp_ext\utils\pvc\pvcMain.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(PVC_CXXFLAGS) .\..\..\..\tfp_ext\utils\pvc\pvcMain.cpp

fill_dummy.obj: .\..\..\..\tfp_fill\src\dummy.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(FILL_CXXFLAGS) /Ycwx/wxprec.h .\..\..\..\tfp_fill\src\dummy.cpp

fill_nkMain.obj: .\..\..\..\tfp_fill\src\nkMain.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(FILL_CXXFLAGS) .\..\..\..\tfp_fill\src\nkMain.cpp

fill_nkRecHelpers.obj: .\..\..\..\tfp_fill\src\nkRecHelpers.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(FILL_CXXFLAGS) .\..\..\..\tfp_fill\src\nkRecHelpers.cpp

fill_nkRefBreakdown.obj: .\..\..\..\tfp_fill\src\nkRefBreakdown.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(FILL_CXXFLAGS) .\..\..\..\tfp_fill\src\nkRefBreakdown.cpp

fill_nkRefDocCustom.obj: .\..\..\..\tfp_fill\src\nkRefDocCustom.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(FILL_CXXFLAGS) .\..\..\..\tfp_fill\src\nkRefDocCustom.cpp

fill_nkRefDocuments.obj: .\..\..\..\tfp_fill\src\nkRefDocuments.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(FILL_CXXFLAGS) .\..\..\..\tfp_fill\src\nkRefDocuments.cpp

fill_nkTest.obj: .\..\..\..\tfp_fill\src\nkTest.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(FILL_CXXFLAGS) .\..\..\..\tfp_fill\src\nkTest.cpp

fill_nkXmlHelpers.obj: .\..\..\..\tfp_fill\src\nkXmlHelpers.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(FILL_CXXFLAGS) .\..\..\..\tfp_fill\src\nkXmlHelpers.cpp

fill_xml2.obj: .\..\..\..\tfp_fill\src\xml2.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(FILL_CXXFLAGS) .\..\..\..\tfp_fill\src\xml2.cpp

spatialite_spatialite.obj: .\..\..\..\tfp_place\3rdparty\spatialite\spatialite.c
	$(CC) /c /nologo /TC /Fo$@ $(SPATIALITE_CFLAGS) .\..\..\..\tfp_place\3rdparty\spatialite\spatialite.c

spatialite_win_iconv.obj: .\..\..\..\tfp_place\3rdparty\spatialite\win_iconv.c
	$(CC) /c /nologo /TC /Fo$@ $(SPATIALITE_CFLAGS) .\..\..\..\tfp_place\3rdparty\spatialite\win_iconv.c

spatialite_localcharset_win.obj: .\..\..\..\tfp_place\3rdparty\spatialite\localcharset_win.c
	$(CC) /c /nologo /TC /Fo$@ $(SPATIALITE_CFLAGS) .\..\..\..\tfp_place\3rdparty\spatialite\localcharset_win.c

freexl_freexl.obj: .\..\..\..\tfp_place\3rdparty\freexl\freexl.c
	$(CC) /c /nologo /TC /Fo$@ $(FREEXL_CFLAGS) .\..\..\..\tfp_place\3rdparty\freexl\freexl.c

tp_tpPlaces.obj: .\..\..\..\tfp_place\src\tp\tpPlaces.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TP_CXXFLAGS) .\..\..\..\tfp_place\src\tp\tpPlaces.cpp

tp_tpVersion.obj: .\..\..\..\tfp_place\src\tp\tpVersion.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TP_CXXFLAGS) .\..\..\..\tfp_place\src\tp\tpVersion.cpp

tp_dummy.obj: .\..\..\..\tfp_place\src\dummy.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(TP_CXXFLAGS) /Ycwx/wxprec.h .\..\..\..\tfp_place\src\dummy.cpp

pe_peApp.obj: .\..\..\..\tfp_place\utils\pe\peApp.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(PE_CXXFLAGS) .\..\..\..\tfp_place\utils\pe\peApp.cpp

pe_peFrame.obj: .\..\..\..\tfp_place\utils\pe\peFrame.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(PE_CXXFLAGS) .\..\..\..\tfp_place\utils\pe\peFrame.cpp

pe_peVersion.obj: .\..\..\..\tfp_place\utils\pe\peVersion.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(PE_CXXFLAGS) .\..\..\..\tfp_place\utils\pe\peVersion.cpp

pe_pe.res: .\..\..\..\tfp_place\utils\pe\pe.rc
	rc /fo$@  /d WIN32  /d _UNICODE $(__WXDEBUG_DEFINE_p_0) /d __WXMSW__ /i $(WX_DIR)\lib\$(COMPILER_PREFIX)$(WXCPU)_lib\msw$(WXLIBPOSTFIX) /i $(WX_DIR)\include $(p_1) /d _WINDOWS /i ..\..\..\tfp_place\include /i ..\..\..\tfp_place\utils\pe /i ..\..\..\tfp\src /i ..\..\..\tfp\include .\..\..\..\tfp_place\utils\pe\pe.rc

pe_dummy.obj: .\..\..\..\tfp_place\src\dummy.cpp
	$(CXX) /c /nologo /TP /Fo$@ $(PE_CXXFLAGS) /Ycwx/wxprec.h .\..\..\..\tfp_place\src\dummy.cpp
