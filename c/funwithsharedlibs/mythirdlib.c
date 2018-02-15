#include <stdio.h>
#include <stdlib.h>

#include "bttools.h"
#include "mylibs.h"

void
mythirdlib_atexit(void)
{
	BT_INFO("3333 ==> mythirdlib_atexit()\n");
}

void
mythirdlib_func()
{
	BT_INFO("3333 ==> mythirdlib_func()\n");
}

__attribute__((constructor)) void 
mythirdlib_init(void) 
{
	int rc;
	BT_INFO("3333 ==> mythirdlib_constructor()\n");
	BT_INFO("3333 ==> register mythirdlib_atexit()\n");
	rc = atexit(mythirdlib_atexit);
	if (rc != 0) {
		BT_ERROR("atexit() failed\n");
	}
}

__attribute__((destructor)) void 
mythirdlib_fini(void)
{
	BT_INFO("3333 ==> mythirdlib_destructor()\n");
}
