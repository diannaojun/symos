#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void err_exit(const char *msg){
    if(msg == NULL) exit(0);
    perror(msg);
    exit(errno);
}

int main (int argc, char **argv){
    char path[2048];
    sprintf(path, "%s.vmdk", argv[2]);
    if(freopen(path, "w", stdout) == NULL)
        err_exit("cannot open .vmdk file");
    fprintf(stdout, "# Disk DescriptorFile\n\
version=1\n\
encoding=\"GBK\"\n\
CID=fffffffe\n\
parentCID=ffffffff\n\
createType=\"monolithicFlat\"\n\
\n\
# Extent description\n\
RW %s FLAT \"%s.img\" 0\n\
\n\
# The Disk Data Base \n\
#DDB\n\
\n\
ddb.adapterType = \"lsilogic\"\n\
ddb.geometry.cylinders = \"512\"\n\
ddb.geometry.heads = \"128\"\n\
ddb.geometry.sectors = \"32\"\n\
ddb.longContentID = \"a9fc106a8f1de06953a0721bfffffffe\"\n\
ddb.uuid = \"60 00 C2 99 9a f1 b9 ac-7c d0 d8 7b 97 aa 4c ab\"\n\
ddb.virtualHWVersion = \"4\"\n", argv[1], argv[3]);
    fclose(stdout);
}