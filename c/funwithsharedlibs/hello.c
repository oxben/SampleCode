#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "bttools.h"
#include "mylibs.h"

#define INDENT 0

//
// Usage: LD_LIBRARY_PATH=$PWD LD_PRELOAD=./libmyfirstlib.so ./myprogram
//

void
hello_atexit(void)
{
	BT_INFO(INDENT, "==> hello_atexit()\n");
}

int
main(int argc, char **argv)
{
	int rc;
	void *handle;
	void (*func)(void);
	char *error;

	BT_INFO(INDENT, "==> Hello world!\n");

	BT_INFO(INDENT, "==> register hello_atexit()\n");
	rc = atexit(hello_atexit);
	if (rc != 0) {
		BT_ERROR("atexit() failed\n");
		return 1;
	}

#if 0
	BT_INFO(INDENT, "dlopen libmyfirstlib.so\n");

	handle = dlopen("libmyfirstlib.so", RTLD_NOW|RTLD_DEEPBIND);
	//handle = dlopen("libmyfirstlib.so", RTLD_LAZY);
	if (handle == NULL) {
		BT_ERROR("dlopen() failed\n");
		return 1;
	}

	BT_INFO(INDENT, "Load myfirstlib_func symbol\n");

	dlerror(); /* Clear any existing error */

	*(void **) (&func) = dlsym(handle, "myfirstlib_func");

	if ((error = dlerror()) != NULL)  {
        BT_ERROR("%s\n", error);
        return 1;
    }

	func();
#endif
	BT_INFO(INDENT, "==> Exiting\n");
	return 0;
}
