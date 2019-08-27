/* selectdemo.c : watch for input on two devices AND timeout
 *         usage: selectdemo dev1 dev2 timeout
 *        action: reports on input from each file, and 
 *                reports timeouts
 */

/*
        breif: secect��ʹ�ã������������𣬲��ȴ��Ӳ�ֹһ��
               �ļ������������룬���Ĺ���ԭ��
               1. ��������ļ��������б�
               2. �����б���select
               3. select ����ֱ������һ���ļ������������ݵ���
               4. select ����һ�������е�����λ������֪ͨ������
                  һ���ļ����������������ݡ�
*/
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#define oops(m,x) { perror(m); exit(x); }

main(int ac, char *av[])
{
	int    fd1, fd2;           /* the fds to watch      */
	struct timeval timeout;    /* how long to wait      */
	fd_set readfds;            /* watch these for input */
	int    maxfd;		   /* max fd plus 1	    */
	int    retval;		   /* return from select    */

	if ( ac != 4 ){
		fprintf(stderr,"usage: %s file file timeout", *av);
		exit(1);
	}

	/** open files **/
	if ( (fd1 = open(av[1],O_RDONLY)) == -1 )
		oops(av[1], 2);
	if ( (fd2 = open(av[2],O_RDONLY)) == -1 )
		oops(av[2], 3);
	maxfd = 1 + (fd1>fd2?fd1:fd2);

    // ע�������һֱѭ��
	while(1) {
		/** make a list of file descriptors to watch **/
		FD_ZERO(&readfds);	   /* clear all bits  */
		FD_SET(fd1, &readfds);     /* set bit for fd1 */    // ��fd1��������б�
		FD_SET(fd2, &readfds);     /* set bit for fd2 */     // ��fd2��������б�

		/** set timeout value **/
		timeout.tv_sec = atoi(av[3]);  /* set seconds */
		timeout.tv_usec = 0;           /* no useconds */

		/** wait for input **/  // ���������ļ�����������ʱʱ��Ϊtimeout
		retval = select(maxfd,&readfds,NULL,NULL,&timeout);
		if( retval == -1 )
			oops("select",4);
			
		if ( retval > 0 ){          // timeout�������ݵ���
			/** check bits for each fd **/
			if ( FD_ISSET(fd1, &readfds) )
				showdata(av[1], fd1);
			if ( FD_ISSET(fd2, &readfds) )
				showdata(av[2], fd2);
		}
		else    // ��ʱ
			printf("no input after %d seconds\n", atoi(av[3]));
	}
}
showdata(char *fname, int fd)
{
	char buf[BUFSIZ];
	int  n;

	printf("%s: ", fname, n);
	fflush(stdout);
	n = read(fd, buf, BUFSIZ);
	if ( n == -1 )
		oops(fname,5);
	write(1, buf, n);
	write(1, "\n", 1);
}
