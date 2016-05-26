#ifndef _LINUXBRIDGE_H_
#define _LINUXBRIDGE_H_

#include <sys/types.h>
#include <uuid/uuid.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <signal.h>
#include <errno.h>
#include <sys/time.h>

#undef SIG_IGN
__sighandler_t SIG_IGN = (__sighandler_t)1;

extern inline int linux_fcntl_get(int fd, int cmd)
{
	return fcntl(fd, cmd);
}

extern inline int linux_fcntl_set(int fd, int cmd, int value)
{
	return fcntl(fd, cmd, value);
}

extern inline int linux_open(const char *path, int oflag, mode_t mode)
{
	return open(path, oflag, mode);
}

extern inline int linux_errno()
{
	return errno;
}

extern inline int pthread_cond_timedwait_relative_np(pthread_cond_t * cond, pthread_mutex_t * mutx, const struct timespec * tmspec)
{
	struct timeval time;
	struct timespec timeout;
	gettimeofday(&time, NULL);
	timeout.tv_sec = time.tv_sec + tmspec->tv_sec;
	timeout.tv_nsec = (time.tv_usec * 1000) + tmspec->tv_nsec;
	
	timeout.tv_sec += timeout.tv_nsec / 1000000000;
	timeout.tv_nsec %= 1000000000;
	
	int i = pthread_cond_timedwait(cond, mutx, &timeout);
	return i;
}

#endif
