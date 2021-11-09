/*Canonical Input Processing*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>

/* baudrate settings are defined in <asm/termbits.h>, which is
included by <termios.h> */
#define BAUDRATE B38400
#define _POSIX_SOURCE 1 /* POSIX compliant source */

#define FALSE 0
#define TRUE 1

volatile int STOP=FALSE;

int main(int argc, char** argv)
{
    struct termios oldtio,newtio;

    if ( (argc < 2) || 
         ((strcmp("/dev/ttyS0", argv[1])!=0) && 
          (strcmp("/dev/ttyS1", argv[1])!=0) )) {
      printf("Usage:\twserial SerialPort\n\tex: wserial /dev/ttyS1\n");
      exit(1);
    }

    /*
    Open serial port device for writing and not as controlling tty
    because we don't want to get killed if linenoise sends CTRL-C.
    */

    fd = open(argv[1], O_WRONLY | O_NOCTTY );
    if (fd <0) {perror(argv[1]); exit(-1); }

    tcgetattr(fd,&oldtio); /* save current serial port settings */
    bzero(&newtio, sizeof(newtio)); /* clear struct for new port settings */

    newtio.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD;

    newtio.c_iflag = IGNPAR | ICRNL;

    newtio.c_oflag = 0;

    newtio.c_lflag = ICANON;

    newtio.c_cc[VINTR]    = 0;     /* Ctrl-c */
    newtio.c_cc[VQUIT]    = 0;     /* Ctrl-\ */
    newtio.c_cc[VERASE]   = 0;     /* del */
    newtio.c_cc[VKILL]    = 0;     /* @ */
    newtio.c_cc[VEOF]     = 4;     /* Ctrl-d */
    newtio.c_cc[VTIME]    = 0;     /* inter-character timer unused  //   */
    newtio.c_cc[VMIN]     = 1;     /* blocking read until 1 character arrives //     1 -> lê um carater de cada vez*/
    newtio.c_cc[VSWTC]    = 0;     /* '\0' */
    newtio.c_cc[VSTART]   = 0;     /* Ctrl-q */
    newtio.c_cc[VSTOP]    = 0;     /* Ctrl-s */
    newtio.c_cc[VSUSP]    = 0;     /* Ctrl-z */
    newtio.c_cc[VEOL]     = 0;     /* '\0' */
    newtio.c_cc[VREPRINT] = 0;     /* Ctrl-r */
    newtio.c_cc[VDISCARD] = 0;     /* Ctrl-u */
    newtio.c_cc[VWERASE]  = 0;     /* Ctrl-w */
    newtio.c_cc[VLNEXT]   = 0;     /* Ctrl-v */
    newtio.c_cc[VEOL2]    = 0;     /* '\0' */

    tcflush(fd, TCIFLUSH);
    tcsetattr(fd,TCSANOW,&newtio);
    
    writeBytes();
    
    sleep(1);

    tcsetattr(fd,TCSANOW,&oldtio);

    close(fd);
    exit(1);
}


int writeBytes(){
    int F = 0x7E;
    int A = 0x03;
    int C = 0x03;
    int BCC1 = A ^ C;

    int SET[5] = {F, A, C, BCC1, F};

    int fd, c, res = 0, i;
    char buf[255];

    for (int i = 0; i < 4; i++) buf[i] = 'a' + i % 26;
    buf[4] = '\0';

    res = write(fd,SET,5);
    printf("Bytes written = %d\n", res);
    return res;
}
