
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

三，kill 函数或 raise abort 命令

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

   向读端关闭的 Pipe 中写数据


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
    sigaddset(sigset_t *set, int sig); // 将信号位置 1
    sigdelset(sigset_t *set, int sig); // 将信号位置 0

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

    /**
     *  SIGKILL 和 SIGSTOP 两个信号不能被阻塞，捕捉，忽略
     
        但通过 sigprocmask 设置时不会失败，但没有任何效果，
        给设置好的进程发送 SIGKILL 信号进程还会被杀死
        给设置好的进程发送 SIGSTOP 信号进程还会被暂停
     */

七，信号捕获

    int sigaction(int signum, const struct sigaction * act,
                  struct sigaction *oldact);

/**
 *  当你执行当前信号的捕获函数，这个信号的信号阻塞位被操作系统置为 1，即屏蔽该信号的再次触发，当捕获函数退出，那么这个阻塞位又恢复为 0，此时若未决信号位是 1，那么再次调用捕获函数，再将阻塞位置为 1，捕获函数退出，阻塞位又变为 0
 */
    struct sigaction {
        // 可以设置为 SIG_DEL ，即接收信号的默认动作
        // 可以设置为 SIG_IGN, 即接收信号但将其忽略
        void (*sa_handler)(int);
        
        void (*sa_sigaction)(int, siginfo_t *, void *);
        /**
         *  调用捕捉函数时，临时调用这个阻塞信号集，阻塞别的信号
            在退出捕获函数后，还原回原有的阻塞信号集
         */
        sigset_t sa_mask; // 可以设置阻塞信号集
        int sa_flags;  // 使用哪个函数指针
        void (*sa_restorer)(void); // 保留，但已过时
    }

八，两个 SIGUSER1 SIGUSER2 用户自定义信号
    这两个信号默认动作是 Term








