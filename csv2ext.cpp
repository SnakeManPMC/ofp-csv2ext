#include <QtCore/QCoreApplication>
#include "csv2ext.h"
#include <cstdio>
#include <cstdlib>

csv2Ext::csv2Ext(int argc, char *argv[])
{
    Open_Files(argc, argv);
    Read_Lines();
    Close_Files();
}


int csv2Ext::extract()
{
    char oggname[50];
    char temp[50];
    char kala[1024];

    ptr = (char *)&line;

    while (*ptr && (*ptr !=',')) ptr++;

    *ptr = 0;

    sprintf(oggname,"%s",line);

    printf("oggname: %s\n",oggname);
    sprintf(temp,"%s",oggname+5);
    printf("temped: %s\n",temp);
    sprintf(kala,"\tclass %s\n\t{\n\t\tname = \"%s\";\n\t\tsound[] = {\"%s.ogg\", db+0, 1.0};\n\t\ttitle = $STRM_%s;\n\t};\n\n",temp,temp,temp,temp);
    fputs(kala,desc);

    return 0;
}


int csv2Ext::PutWeapon(char *wep, int amount)
{
    char bufa[256];

    sprintf(bufa, "\tclass %s\n\t{\n\t\tcount = %i;\n\t};\n", wep, amount);

    fputs(bufa, desc);
    return 0;
}


void csv2Ext::Open_Files(int argc, char *argv[])
{
    // check if there is enough parameters
    if (argc < 3)
    {
        printf("Not enought parameters!\n\n\tCsv2Ext CSV EXT\n\n");
        exit (1);
    }

    csv = fopen(argv[1], "rt");
    if (!csv)
    {
        printf("error at %s!\n", argv[1]);
        exit(1);
    }

    desc = fopen(argv[2], "wt");
    if (!desc)
    {
        printf("error at %s!\n", argv[2]);
        exit(1);
    }
}


void csv2Ext::Read_Lines()
{
    /*
    fputs("respawn=\"group\";\n\n// Title that appears on screen in briefing\nonLoadIntro=\"noname\";\n\n// Title that appears on screen at beginning of mission\nonLoadMission=\"noname\";\n\n\nclass CfgRadio\n{\n\tsounds[] = { };\n\n",desc);
    */
    fputs("respawn=\"group\";\n\n// Title that appears on screen in briefing\nonLoadIntro=$STRD_Rmissname;\n\n// Title that appears on screen at beginning of mission\nonLoadMission=$STRL_Rload;\n\nclass CfgRadio\n{\n\tsounds[] = {};\n\n",desc);

    fgets(line, 1024, csv);

    while (!feof(csv))
    {
        if (strstr(line,"STRM_")) extract();
        fgets(line, 1024, csv);
    }

    fputs("};\n\n", desc);

    Put_Weapons();

    Put_Magazines();
}


void csv2Ext::Put_Weapons()
{
    /* insert the WEAPONS */
    fputs("class Weapons\n{\n", desc);
    PutWeapon("M16", 12);
    PutWeapon("M16GrenadeLauncher", 12);
    PutWeapon("M4", 12);
    PutWeapon("M60", 12);
    PutWeapon("HK", 12);
    PutWeapon("M21", 12);
    PutWeapon("CarlGustavLauncher", 12);
    PutWeapon("LAWLauncher", 12);
    PutWeapon("Binocular", 12);
    PutWeapon("NVGoggles", 12);
    PutWeapon("Beretta", 12);
    PutWeapon("Glock", 12);
    PutWeapon("Glocks", 12);
    PutWeapon("HKG3", 12);
    PutWeapon("G36A", 12);
    /*	PutWeapon("MM1", 12);*/
    PutWeapon("Steyr", 12);
    PutWeapon("XMS", 12);
    PutWeapon("AALauncher", 12);
    fputs("};\n\n",desc);
}


void csv2Ext::Put_Magazines()
{
    /* insert the MAGAZINES */
    fputs("class Magazines\n{\n",desc);
    PutWeapon("M16", 40);
    PutWeapon("HandGrenade", 40);
    PutWeapon("GrenadeLauncher", 40);
    PutWeapon("M4", 40);
    PutWeapon("M60", 40);
    PutWeapon("M21", 40);
    PutWeapon("HK", 40);
    PutWeapon("CarlGustavLauncher", 40);
    PutWeapon("LAWLauncher", 40);
    PutWeapon("Mine", 40);
    PutWeapon("PipeBomb", 40);
    PutWeapon("TimeBomb", 40);
    PutWeapon("Mortar", 40);
    PutWeapon("Flare", 40);
    PutWeapon("FlareRed", 40);
    PutWeapon("FlareGreen", 40);
    PutWeapon("FlareYellow", 40);
    PutWeapon("SmokeShell", 40);
    PutWeapon("SmokeShellGreen", 40);
    PutWeapon("SmokeShellRed", 40);
    PutWeapon("BerettaMag", 40);
    PutWeapon("GlockMag", 40);
    PutWeapon("HKG3Mag", 40);
    PutWeapon("GlocksMag", 40);
    PutWeapon("G36aMag", 40);
    /*	PutWeapon("MM1magazine", 40);*/
    PutWeapon("Steyrmag", 40);
    PutWeapon("AALauncher", 40);
    fputs("};\n",desc);
}


void csv2Ext::Close_Files()
{
    fclose(csv);
    fclose(desc);
}

/*
        mission.sqm entrys
        briefingName="Shark eyes";
        briefingDescription="Recon for enemy airbase";

STRM_Ralphaready,"PAPA BEAR YOU ARE GAY. ALPHA OUT.",alpha

respawn = "group";

// Title that appears on screen in briefing
onLoadIntro="King of my Castle";

// Title that appears on screen at beginning of mission
onLoadMission="Its good to be the King";

class CfgRadio
{
    sounds[] = { };

    class Rechoready
    {
        name = "Rechoready";
        sound[] = {"Rechoready.ogg", db+0, 1.0};
        title = $STRM_Rechoready;
    };
};

// This class indicates what weapons to make available to the player in the mission
// briefing.  Each subclass is optional.  The count field in each subclass indicates
// the number of that weapon to make available.
// NEED TO FIGURE OUT THE OTHER TYPES
class Weapons
{
    class M16
    {
    count = 10;
    };
    class M16GrenadeLauncher
    {
    count = 10;
    };
    class M4
    {
    count = 10;
    };
    class M60
    {
    count = 10;
    };
    class HK
    {
    count = 10;
    };
    class M21
    {
    count = 10;
    };
    class CarlGustavLauncher
    {
    count = 10;
    };
    class LAWLauncher
    {
    count = 10;
    };
    class Binocular
    {
    count = 4;
    };
    class NVGoggles
    {
    count = 4;
    };
    class Beretta
    {
        count = 10;
    };
    class Glock
    {
        count = 10;
    };
    class Glocks
    {
        count = 10;
    };
    class HKG3
    {
        count = 10;
    };
    class G36A
    {
        count = 10;
    };
    class MM1
    {
        count = 10;
    };
};

// This class indicates what weapon magazines to make available to the player in the mission
// briefing.  Each subclass is optional.  The count field in each subclass indicates
// the number of that magazine to make available.
class Magazines
{
    class M16
    {
    count = 40;
    };
    class HandGrenade
    {
    count = 40;
    };
    class GrenadeLauncher
    {
    count = 40;
    };
    class M4
    {
    count = 40;
    };
    class M60
    {
    count = 40;
    };
    class M21
    {
    count = 40;
    };
    class HK
    {
    count = 40;
    };
    class Mine
    {
    count = 40;
    };
    class PipeBomb
    {
    count = 40;
    };
    class TimeBomb
    {
    count = 10;
    };
    class CarlGustavLauncher
    {
    count = 10;
    };
    class LAWLauncher
    {
    count = 10;
    };
    class Mortar
    {
    count = 10;
    };
    class Flare
    {
    count = 10;
    };
    class FlareRed
    {
    count = 10;
    };
    class FlareGreen
    {
    count = 10;
    };
    class FlareYellow
    {
    count = 10;
    };
    class SmokeShell
    {
    count = 10;
    };
    class SmokeShellGreen
    {
    count = 10;
    };
    class SmokeShellRed
    {
    count = 10;
    };
    class BerettaMag
    {
        count = 10;
    };
    class GlockMag
    {
        count = 10;
    };
    class HKG3Mag
    {
        count = 10;
    };
    class GlocksMag
    {
        count = 10;
    };
    class G36aMag
    {
        count = 10;
    };
    class MM1magazine
    {
        count = 10;
    };
};

*/
