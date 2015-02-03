#ifndef CSV2EXT_H
#define CSV2EXT_H

class csv2Ext
{
public:
    csv2Ext(int argc, char *argv[]);
    void Open_Files(int argc, char *argv[]);
    void Read_Lines();
    void Put_Weapons();
    void Put_Magazines();
    void Close_Files();
    int extract();
    int PutWeapon(char *wep, int amount);

private:
    FILE *csv;
    FILE *desc;
    char line[1024];
    char out[1024];
    char *ptr;
};

#endif // CSV2EXT_H
