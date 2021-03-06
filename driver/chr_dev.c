#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/tty.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <asm/uaccess.h>
#include <linux/slab.h>

#define CHR_DEV_NAME "battery" // 디바이스 파일 이름
#define CHR_DEV_MAJOR 240 // 디바이스 파일의 주번호

static char *buffer = NULL;

int chr_open(struct inode *inode, struct file *filp)

{

int number = MINOR(inode->i_rdev); // 부번호를 number에 저장

printk("Virtual Character Device Open: Minor Number is %d\n", number);

return 0;

}



ssize_t chr_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos)

{

copy_from_user(buffer, buf, count); // 디바이스 파일에 데이터 기록

printk("write data: %s\n", buf); // 응용프로그램 write()

// 함수의 buf 값을 커널 메시지에 출력

return count;

}



ssize_t chr_read(struct file *filp, const char *buf, size_t count, loff_t *f_pos)

{

copy_to_user(buf, buffer, count); // 디파이스 파일에 있는 데이터 읽기

printk("read data: %s\n", buf); // 응용프로그램 read()

// 함수의 buf 값을 커널 메시지에 출력

return count;

}



int chr_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)

{

switch(cmd) { // ioctl 함수로 전달된 cmd 값을 출력

case 0: printk("cmd value is %d\n", cmd); break;

case 4: printk("cmd value is %d\n", cmd); break;

}

return 0;

}



int chr_release(struct inode *inode, struct file *filp)

{

printk("Virtual Character Device Release\n");

return 0;

}



struct file_operations chr_fops =
{

owner: THIS_MODULE,

unlocked_ioctl: chr_ioctl,

write: chr_write,

read: chr_read,

open: chr_open,

release: chr_release

};

int sample_init(void)// 디바이스를 커널에 모듈로 적재시 수행되는 함수

{

int registration;; // registration에 주번호나 반환값을 저장

printk("Registration Character Device to Kernel\n");

registration = register_chrdev(CHR_DEV_MAJOR,CHR_DEV_NAME, &chr_fops);

if(registration < 0)
	return registration;

printk("Major Number:%d\n", registration);

buffer = (char*)kmalloc(1024, GFP_KERNEL); // buffer 메모리 할당


if(buffer != NULL) // buffer 값이 null일 때 buffer 값 초기화

	memset(buffer, 0, 1024);


return 0;

}



void sample_cleanup(void)// 커널에서 디바이스를 제거할 때 수행되는 함수

{

printk("Unregistration Character Device to Kernel\n");

unregister_chrdev(CHR_DEV_MAJOR, CHR_DEV_NAME);

kfree(buffer); // buffer 메모리 해제

}



MODULE_LICENSE("GPL");

module_init(sample_init);

module_exit(sample_cleanup);
