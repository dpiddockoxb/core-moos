INCLUDE(CheckIncludeFileCxx)
Check_Include_File_Cxx ("tr1/unordered_map" HAVE_TR1_UNORDERED_MAP_H)
Check_Include_File_Cxx ("unordered_map" HAVE_STD_UNORDERED_MAP_H)


if(HAVE_TR1_UNORDERED_MAP_H)	
	ADD_DEFINITIONS( -DHAVE_TR1_UNORDERED_MAP )	
endif() 
if(HAVE_STD_UNORDERED_MAP_H)	
	ADD_DEFINITIONS( -DHAVE_STD_UNORDERED_MAP )	
endif() 
