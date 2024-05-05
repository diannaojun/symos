/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-04-05
 */
#include <lib/loader/loader.h>

BOOL check64();

void main (void){
    u32 cases;
    char df[512];
    initPrint();
    initDisk();
    // initFloppy();
    printdl(0x0123456789abcdef);
    printsl("Symbol Zsuey Systom -- Geno-apu-ym\n\r");
    printsl("deno DiannaoJun, Symbol Devep Gtem Zce\n\r");
    printsl("\n\rNambixim UaotSyksa Zangian (0x55aa):");
    printdl(0x55aa),printsl("\n\r");
    cases=checkSupport64();
    if(cases){
        switch(cases){
        case 0x02:
            printel("la IMK yanientoq net la CPUID Linda! Tit iztoq maeyt cozebe "
                "Ini no CPU iztoq az daont az la i486.\n\r",0x02);break;
        case 0x03:
            printel("la IMK yanientoq net la IA-32e Mokziy!\n\r",0x03);break;
        default:
            printel("imjisvoto Ylom!\n\r",cases);
        }
        _fin();
    }
    printel("imYlom cakan, ieli imiSvo.\n\r",0x00);
    printsl("Paging soyanientoqszed.\n\r");
    printsl("Find Bootloader in Floppy.\n\r");
    if(TRUE){
        (((struct DiskOpt*)(ATA[0].operation))->readSec)
        (ATA[0].object,df,0,1);
        printsl(df);
    }
    // enter64();
    _fin();
    return ;
}
