#ifndef __BTTOOLS_H
#define __BTTOOLS_H

#define BT_INFO(fmt, ...) \
    printf("[INFO] %s:%d: " fmt, __func__, __LINE__, ##__VA_ARGS__)

#define BT_ERROR(fmt, ...) \
    printf("[ERROR] %s:%d: " fmt, __func__, __LINE__, ##__VA_ARGS__)

#endif /* __BTTOOLS_H */

