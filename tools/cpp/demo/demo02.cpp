#include "_public.h"
using namespace idc;

cpactive pactive;      // 进程心跳，用全局对象（保证析构函数会被调用）。

void EXIT(int sig)     // 程序退出和信号2、15的处理函数。
{
    printf("sig=%d\n",sig);

    exit(0);
}

int main(int argc,char *argv[])//参数1：心跳超时时间，参数2,：更新心跳的间隔时间
{
    // 处理程序的退出信号。
    //signal(SIGINT,EXIT); signal(SIGTERM,EXIT);
    closeioandsignal(true);//关闭所有IO，不能接受正常15信号，启用这一行，测试不能被15正常关闭的进程，用9杀死。
    
    pactive.addpinfo(atoi(argv[1]),"demo02");  // 把当前进程的信息加入共享内存进程组中。

    while (1)
    {
        sleep(atoi(argv[2]));
        pactive.uptatime(); // 更新进程的心跳。
    }

    return 0;
}
