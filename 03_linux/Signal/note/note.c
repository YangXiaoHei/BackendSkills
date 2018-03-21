
一，终端特殊摁键可以产生信号
    ctl + c  SIGINT

    /**
     *  暂停  使用 "fg 1" 唤醒恢复前台运行 使用 "bg 1" 唤醒恢复后台运行
        比如编写一个 while(1) {};
     */
    ctl + z SIGTSTP

    ctl + \ SIGQUIT // 退出，不同于 SIGINT

    可以使用 "kill -xx 进程号" 的方式给进程发送信号，比如发送 SIGINT 信号中断

二，硬件错误产生信号

    除 0 操作      // SIGFPE
    访问非法内存    // SIGSEGV

三，kill 函数或 kill 命令

    int kill(pid_t pid, int sig)

        pid > 0    // 发送给 ID 为 pid 的进程
        pid == 0   // 发送给同组的所有进程
        pid < 0   // 发送给组 ID 为 -pid 的所有进程
        pid = -1  // 发送给发送进程有权通知的所有进程

    ./exec & 表示将程序在后台运行

    raise (int sig) // 自己向自己发信号
    abort (void)  // 调用进程自己向自己发送 SIGABRT 信号

    四，某种软件条件已发生

    定时器 alarm 到时

    // 返回值 ： 剩多少秒
    // 参数 ：定时指定秒数，到描述到达时，向当前进程发送 SIGALRM 信号
    unsigned int alarm(unsigned int seconds);


五，进程处理信号行为

    1，默认处理动作
        Term    // 终止
        Ign
        Core    // 先终止进程，回收 core 文件，死后验尸
        Stop    // 暂停
        Cont    // 和 Stop 呼应继续这个进程的执行
    2, 忽略
    3, 捕捉  用户自定义信号处理函数

六，信号集处理函数

sigset_t 每一bit位代表一个信号

sigemptyset(sigset_t *set); // 将信号集全部置为 0
sigfillset(sigset_t *set); // 将信号集全部置为 1

// 设置信号屏蔽字
/**
 *  如果 set 为 NULL，将屏蔽字通过 oset 传出
    如果 oset 为 NULL, 将屏蔽字通过 set 设置
    如果都不为 NULL, 先用 oset 备份，再用 set 设置
 
    how
 
    SIG_BLOCK     // mask = mask | set
    SIG_UNBLOCK   // mask = mask & ~set
    SIG_SETMASK   // mask = set
 */
sigprocmask(int how, sigset_t *set, sigset_t *oset);











