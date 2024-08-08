/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-04-05
 */
#include <lib/loader/loader.h>

void main (void){
    void*tempa=(void*)0x010000;
    void*tempb=(void*)0x020000;
    int i,j,k;
    initPrint();
    printsl("SymbolZsueySystom Loader.             \n\r");
    printsl("dee DiannaoJun, Symbol Devep Gtem Zce\n\r");
    printsl("PanS Uaotym Cian: Sy6.\n\r");
    printsl("Nambi Uaotym Cian: "),printdl(0x0123456789abcdefll),printsl("\n\r");
    if(!support_CPUID()){
        printel("la IMK yanien net la CPUID Linda! Titizt xyd decoze "
            "Ini no CLK izt az glaista deno I486.\n\r",0x02);
        goto errLabel;
    }else if(!support_long_mode()){
        printel("la IMK yanien net la IA-32e Mokziy!\n\r",0x03);
        goto errLabel;
    }
    DISK_INIT();
    (((struct DiskOpt*)(ATA[0].operation))->readSec)(ATA[0].object,tempa,0,1);
    SMYFS_INS_LOAD(ATA+0,tempa,((struct SMYFS*)tempa)->root_start,tempb);
    for(j=i=0;((struct SMYFS_FILE*)tempb)[i].name[0];++i)
        if(!strcmpn(((struct SMYFS_FILE*)tempb)[i].name,"SYS                        ",15)){
            j=((struct SMYFS_FILE*)tempb)[i].ptr;
            break;
        }
    if(!j){
        printel("la SYS_ROOT szsa ('/SYS/') izt paipibe!\n\r",0x04);
        goto errLabel;
    }
    SMYFS_INS_LOAD(ATA+0,tempa,j,tempb);
    for(j=i=0;((struct SMYFS_FILE*)tempb)[i].name[0];++i)
        if(!strcmpn(((struct SMYFS_FILE*)tempb)[i].name,"L64.SYS                ",15)){
            j=((struct SMYFS_FILE*)tempb)[i].ptr;
            break;
        }
    if(!j){
        printel("la L64.SYS szsa ('/SYS/L64.SYS') izt paipibe!\n\r",0x05);
        goto errLabel;
    }
    printsl("Found L64.SYS At "),printdl(j),printsl("\n\r");
    SMYFS_INS_LOAD(ATA+0,tempa,j,tempb);
    enter64();
    _fin();
    return ;
errLabel:
    printsl("HLT\n\r");
    _fin();
    return ;
    /*
    if(TRUE){
        for(i=0;i<512;++i){
            ((long long*)tempa)[i]=0;
        }
        printdl(sizeof(struct SMYFS_FILE));
        (((struct DiskOpt*)(ATA[0].operation))->readSec)(ATA[0].object,tempa,0,1);
        printsl("\n\rUUID: "),printdl(((struct SMYFS*)tempa)->uuid);
        printsl("\n\rOEM: "),printsl(((struct SMYFS*)tempa)->oemName);
        printsl("\n\rLABEL: "),printsl(((struct SMYFS*)tempa)->label);
        printsl("\n\rreservedSec: "),printdl(((struct SMYFS*)tempa)->resSec);
        printsl("\n\rSecs: "),printdl(((struct SMYFS*)tempa)->noS);
        printsl("\n\rSymbol?: "),printdl(((struct SMYFS*)tempa)->haveSys);
        printsl("\n\rroot_start: "),printdl(((struct SMYFS*)tempa)->root_start);
        for(i=0;i<0;++i){
        
            printsl("\n\r");
            printdl(((u64*)tempa)[i<<1]);
            printsl(" ");
            printdl(((u64*)tempa)[(i<<1)|1]);
        }
        SMYFS_INS_LIST(ATA+0,tempa,529,tempb);
        printsl("\n\r\n\r LIST_ROOT (/) \n\r");
        for(i=0;;++i){
            j=0;
            if(((struct SMYFS_FILE*)tempb)[i].name[0]==0)
                break;
            printsnl(((struct SMYFS_FILE*)tempb)[i].name, 15);
            printsl("\e0 | ");
            printdl(((struct SMYFS_FILE*)tempb)[i].length);
            printsl("B\n\r");
        }
        
        SMYFS_INS_LIST(ATA+0,tempa,530,tempb);
        printsl("\n\r\n\r LIST_SYS (/SYS/) \n\r");
        for(i=0;;++i){
            j=0;
            if(((struct SMYFS_FILE*)tempb)[i].name[0]==0)
                break;
            printsnl(((struct SMYFS_FILE*)tempb)[i].name, 15);
            printsl("\e0 | ");
            printdl(((struct SMYFS_FILE*)tempb)[i].length);
            printsl("B\n\r");`
        }
    }*/
    //enter64();
}
