/****************************************************************************************
 *   程序名：procctl.cpp，此程序是服务程序的调度程序，周期性启动服务程序或shell脚本。      
*****************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc,char *argv[])
{
    if (argc<3)
    {
        printf("Using:./procctl_my timetvl program argv ...\n");
        printf("Example:/myproject/tools/bin/procctl_my 10 /usr/bin/tar zcvf /tmp/tmp.tgz /usr/include\n");
  	    printf("Example:/myproject/tools/bin/procctl_my 60 /myproject/idc/bin/crtsurfdata /myproject/idc/ini/stcode.ini /myproject/dataFile/idc/surfdata /myproject/log/idc/crtsurfdata.log csv,xml,json\n");

        printf("本程序是服务程序的调度程序，周期性启动服务程序或shell脚本。\n");
        printf("timetvl 运行周期，单位：秒。\n");
        printf("        被调度的程序运行结束后，在timetvl秒后会被procctl重新启动。\n");
        printf("        如果被调度的程序是周期性的任务，timetvl设置为运行周期。\n");
        printf("        如果被调度的程序是常驻内存的服务程序，timetvl设置小于5秒。\n");
        printf("program 被调度的程序名，必须使用全路径。\n");
        printf("...     被调度的程序的参数。\n");
        printf("注意，本程序不会被kill杀死，但可以用kill -9强行杀死。\n\n\n");
        return -1;

    }
	
	// 关闭信号和I/O，本程序不希望被打扰。
    // 注意：1）为了防调度程序被误杀，不处理退出信号；
    //       2）如果忽略信号和关闭了I/O，将影响被调度的程序（被调度程序也会忽略信号和关闭I/O）。 why？因为被调度的程序取代了子进程，子进程会继承父进程的信号处理方式和I/O。
    for(int i=0;i<64;i++)
    {
        signal(i,SIG_IGN);close(i);
    }
	
	// 生成子进程，父进程退出，让程序运行在后台，由系统1号进程托管，不受shell的控制。
    if(fork()!=0)exit(0);

	 // 把子进程退出的信号SIGCHLD恢复为默认行为，让父进程可以调用wait()函数等待子进程退出。
    signal(SIGCHLD,SIG_IGN);

	// 定义一个和argv一样大的指针数组，存放被调度程序名及其参数。
    char* setdd[argc];
    for(int i =2;i<argc;i++)
    {
        setdd[i-2]=argv[i];
    }
	// 空表示参数已结束。
    setdd[argc-2]=nullptr;

    while(true)
    {
        if(fork()==0)
        {
            execv(argv[2],setdd);
			//execv调用调用程序后，新进程取代了原进程的代码段、数据栈和堆栈，\
				所以只有execv函数失败，才会执行下面的exit（0）代码
            exit(0);
        }
        else{
			// 父进程等待子进程终止（被调度的程序运行结束）。
            //int status; //保存子进程退出的状态，如果不关心子进程退出的状态，设为nullptr
            //wait(&status);           // wait()函数会阻塞，直到被调度的程序终止。
            wait(nullptr);
            sleep(atoi(argv[1]));
        }
    }
}
