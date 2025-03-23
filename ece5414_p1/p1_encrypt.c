#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>
#include <linux/errno.h>

SYSCALL_DEFINE2(s2_encrypt, char __user *, user_str, int, key)
{
    char buf[256]; // Buffer for input string
    int i;

    // Validate key range
    if (key < 1 || key > 5)
        return -EINVAL;

    // Copy string from user space to kernel space
    if (strncpy_from_user(buf, user_str, sizeof(buf)) < 0)
        return -EFAULT;

    // Encrypt the string
    for (i = 0; buf[i] != '\0' && i < sizeof(buf) - 1; i++)
        buf[i] += key;

    // Print encrypted string
    printk(KERN_INFO "Encrypted String: %s\n", buf);

    return 0;
}
