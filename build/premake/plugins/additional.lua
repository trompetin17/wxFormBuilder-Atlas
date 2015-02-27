-----------------------------------------------------------------------------
--  Name:        additional.lua
--  Purpose:     Additional controls plugin project build script.
--  Author:      Andrea Zanellato
--  Modified by: 
--  Created:     21/10/2011
--  Copyright:   (c) 2011 wxFormBuilder Team
--  Licence:     GNU General Public License Version 2
-----------------------------------------------------------------------------
project "additional-components-plugin"
    kind                "SharedLib"
    targetname          "additional"
    files               {"../../../plugins/additional/additional.cpp"}
    includedirs
    {
        "../../../sdk/tinyxml", "../../../sdk/plugin_interface"
    }
    defines             {"BUILD_DLL", "TIXML_USE_TICPP"}
    flags               {"ExtraWarnings"}
    links               {"plugin-interface", "TiCPP"}

    local libs = "std,richtext,propgrid,stc,ribbon"
if wxUseMediaCtrl then
    defines             {"USE_MEDIACTRL"}
    libs                = libs .. ",media"
end

	if wxArchitecture then
		buildoptions	{"-arch " .. wxArchitecture}
	end
	
    configuration "not windows"
        targetdir       "../../../output/lib/wxformbuilder"

    configuration "windows"
        targetprefix    "lib"
        targetdir       "../../../output/plugins/additional"

    configuration "Debug"
        targetsuffix    ( DebugSuffix )
        wx_config       { Libs=libs, Debug="yes" }

    configuration "Release"
        buildoptions    {"-fno-strict-aliasing"}
        wx_config       { Libs=libs }
