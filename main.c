/* Author: Joe Lovelace
 * Ack: Based on Lucio DiJasio code for GTSU: 5.4 Storage Flash
 * Requires: MLA 1306
 */

#include "uMB/PICconfig.h"
#include "HardwareProfile.h"
#include "M25P80.h"

char datain[ 15];           // ensure that ERASE_SECTOR_SIZE is divisible by sizeof(data)!
char dataout[ 15];

int main( void )
{
    DWORD address, i;

    for (i=0; i<sizeof(datain); i++)
        datain[i]="a";


    // Initializations
    uMBInit();                  // init pins and ports
    address = 0;        // absolute address

    // Erase first sector of flash (the only one we use)
    SST25SectorErase( address);

    // Write to device
    SST25WriteArray( address, datain, sizeof(datain));
    address += sizeof(datain);

    // Read from device
    for ( i=0; i<address; i++)
        dataout[i] = SST25ReadByte( i);

    // Nop chain to catch the breakpoint in the right scope
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    
    // Do nothing forever
    while( 1 );
}
