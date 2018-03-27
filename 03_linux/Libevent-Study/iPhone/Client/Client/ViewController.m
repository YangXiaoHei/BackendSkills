//
//  ViewController.m
//  Client
//
//  Created by YangHan on 2018/3/27.
//  Copyright © 2018年 YangHan. All rights reserved.
//

#import "ViewController.h"
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h>

@interface ViewController ()
@property (weak, nonatomic) IBOutlet UIButton *recvButton;
@property (weak, nonatomic) IBOutlet UILabel *recvMsgLabel;
@property (weak, nonatomic) IBOutlet UIButton *socketButton;
@property (weak, nonatomic) IBOutlet UIButton *connectButton;
@property (weak, nonatomic) IBOutlet UITextField *msgTF;
@property (weak, nonatomic) IBOutlet UIButton *sendButton;
@property (weak, nonatomic) IBOutlet UIButton *closeButton;
@property (nonatomic,assign) int sockfd;
@property (weak, nonatomic) IBOutlet UIButton *close;
@property (nonatomic,strong) NSValue * serv_addr;
@property (nonatomic,assign) pthread_t tid;
@end

@implementation ViewController

- (IBAction)tcp_socket_create:(UIButton *)sender {
    struct sockaddr_in *serv_addr = malloc(sizeof(struct sockaddr_in));
    bzero(serv_addr, sizeof(struct sockaddr_in));
    serv_addr->sin_family = AF_INET;
    serv_addr->sin_port = htons(5555);
    const char *ipstr = "10.10.3.7";
    inet_aton(ipstr, &serv_addr->sin_addr);
    
    NSString *relstring = nil;
    
    // 检测 IP 是否有效
    if (serv_addr->sin_addr.s_addr == 0) {
        [sender setTitle:@"IP 地址无效" forState:UIControlStateNormal];
        return;
    }
    [sender setTitle:@"IP 合法" forState:UIControlStateNormal];
    usleep(1000000 * 0.3);

    // 创建 socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        const char *errstr = strerror(errno);
        relstring = [NSString stringWithUTF8String:errstr];
        [sender setTitle:relstring forState:UIControlStateNormal];
        return;
    }
    [sender setTitle:@"创建socket成功" forState:UIControlStateNormal];
    usleep(1000000 * 0.3);
    
    // 存储 serv_addr
    _serv_addr = [NSValue valueWithPointer:serv_addr];
    _sockfd = sockfd;
}

- (IBAction)connect:(UIButton *)sender {
    
    struct sockaddr_in *serv_addr = (struct sockaddr_in *)[_serv_addr pointerValue];
    
    int rel = connect(_sockfd, (struct sockaddr *)serv_addr, sizeof(struct sockaddr_in));
    
    if (rel < 0) {
        const char *errstr = strerror(errno);
        [sender setTitle:[NSString stringWithUTF8String:errstr] forState:UIControlStateNormal];
        return;
    }
    [sender setTitle:@"三次握手成功" forState:UIControlStateNormal];
}

- (IBAction)send_msg:(UIButton *)sender {
   
    NSString *msg = _msgTF.text;
    if (msg.length == 0) return;
    
    const char *m = [_msgTF.text cStringUsingEncoding:NSUTF8StringEncoding];
    
    ssize_t nbytes = send(_sockfd, m, strlen(m), 0);
    
    if (nbytes < 0) {
        const char *errstr = strerror(errno);
        [sender setTitle:[NSString stringWithUTF8String:errstr] forState:UIControlStateNormal];
        return;
    }
    _msgTF.text = @"";
    [sender setTitle:@"发送成功" forState:UIControlStateNormal];
    
    usleep(1000000 * 0.4);
    
    [sender setTitle:@"发送" forState:UIControlStateNormal];
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    [self.view endEditing:YES];
}

- (IBAction)close:(id)sender {
    int rel = close(_sockfd);
    if (rel < 0) {
        const char *errstr = strerror(errno);
        [sender setTitle:[NSString stringWithUTF8String:errstr] forState:UIControlStateNormal];
        return;
    }
    [_socketButton setTitle:@"socket" forState:UIControlStateNormal];
    [_connectButton setTitle:@"connect" forState:UIControlStateNormal];
    _msgTF.text = @"";
    
}
- (IBAction)begin_recv:(UIButton *)sender {
    pthread_t tid;
    pthread_create(&tid, NULL, thr_handler, (void *)CFBridgingRetain(self));
}

void *thr_handler(void *arg) {
    ViewController *vc = (ViewController *)CFBridgingRelease(arg);
    char buf[1024];
    bzero(buf, sizeof(buf));
    
    ssize_t len = recv(vc->_sockfd, buf, sizeof(buf), 0);
    if (len < 0) {
        const char *errstr = strerror(errno);
        dispatch_async(dispatch_get_main_queue(), ^{
            vc->_recvMsgLabel.text = [NSString stringWithUTF8String:errstr];
        });
        pthread_exit(NULL);
    } else if (len == 0) {
        dispatch_async(dispatch_get_main_queue(), ^{
            vc->_recvMsgLabel.text = @"没读到数据";
        });
    } else {
        buf[len] = 0;
        NSString *str = [NSString stringWithUTF8String:buf];
        dispatch_async(dispatch_get_main_queue(), ^{
            vc->_recvMsgLabel.text = str;
        });
    }
    return (void *)1;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
}

@end
