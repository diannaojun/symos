/* Symbol DT
 * SymOS
 * DiannaoJun
 * 2024-08-01
 */

int main (void){
  int i=0xb8001;
  for(i;i<0xb8016;++i)
    *((char*)i)=0x0f;
  *((char*)0xb8000)='L';
  *((char*)0xb8002)='O';
  *((char*)0xb8004)='N';
  *((char*)0xb8006)='G';
  *((char*)0xb8008)=' ';
  *((char*)0xb800a)='M';
  *((char*)0xb800c)='O';
  *((char*)0xb800e)='D';
  *((char*)0xb8010)='E';
  *((char*)0xb8012)='!';
  *((char*)0xb8014)=' ';
  // print "LONG MODE"
  F:goto F;
  return 0;
}
