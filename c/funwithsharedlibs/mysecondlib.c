#include <stdio.h>
#include <stdlib.h>

#include "bttools.h"
#include "mylibs.h"

#define INDENT 8

void
mysecondlib_atexit(void)
{
	BT_INFO(INDENT, "2==> mysecondlib_atexit()\n");
}

void
mysecondlib_func()
{
	BT_INFO(INDENT, "2==> mysecondlib_func()\n");
	mythirdlib_func();
}

__attribute__((constructor)) void
mysecondlib_init(void)
{
	int rc;
	BT_INFO(INDENT, "2==> mysecondlib_constructor()\n");
	BT_INFO(INDENT, "2==> register mysecondlib_atexit()\n");
	rc = atexit(mysecondlib_atexit);
	if (rc != 0) {
		BT_ERROR("atexit() failed\n");
	}
}

__attribute__((destructor)) void
mysecondlib_fini(void)
{
	BT_INFO(INDENT, "2==> mysecondlib_destructor()\n");
}
