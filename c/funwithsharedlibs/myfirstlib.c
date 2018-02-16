#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "bttools.h"
#include "mylibs.h"

#define INDENT 4

void
myfirstlib_atexit(void)
{
	BT_INFO(INDENT, "1==> myfirstlib_atexit()\n");
}

void
myfirstlib_func()
{
	BT_INFO(INDENT, "1==> myfirstlib_func()\n");
	mysecondlib_func();
}

__attribute__((constructor)) void
myfirstlib_init(void)
{
	int rc;
	void *handle;
	void (*func)(void);
	char *error;

	BT_INFO(INDENT, "1==> myfirstlib_constructor()\n");

	BT_INFO(INDENT, "1==> dlopen libmysecondlib.so\n");

	handle = dlopen("libmysecondlib.so", RTLD_NOW);
	//handle = dlopen("libmysecondlib.so", RTLD_LAZY);
	if (handle == NULL) {
		BT_ERROR("dlopen() failed\n");
		return;
	}

	BT_INFO(INDENT, "1==> Load mysecondlib_func symbol\n");

	dlerror(); /* Clear any existing error */

	*(void **) (&func) = dlsym(handle, "mysecondlib_func");

	if ((error = dlerror()) != NULL)  {
        BT_ERROR("%s\n", error);
        return;
    }

	func();

	BT_INFO(INDENT, "1==> register myfirstlib_atexit()\n");

	rc = atexit(myfirstlib_atexit);
	if (rc != 0) {
		BT_ERROR("atexit() failed\n");
	}
}

__attribute__((destructor)) void
myfirstlib_fini(void)
{
	BT_INFO(INDENT, "1==> myfirstlib_destructor()\n");
}
