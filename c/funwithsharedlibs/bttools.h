#ifndef __BTTOOLS_H
#define __BTTOOLS_H

#define BT_INFO(_indent, _fmt, ...)	  \
	printf("[INFO] %-20s:%-4d:%*s" _fmt, __func__, __LINE__, _indent, "", ##__VA_ARGS__)

#define BT_ERROR(_fmt, ...) \
	printf("[ERROR] %-20s:%-4d: " _fmt, __func__, __LINE__, ##__VA_ARGS__)

#endif /* __BTTOOLS_H */

