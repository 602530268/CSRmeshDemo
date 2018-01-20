//
//  CEMoreLightsVC.m
//  CSRmeshDemo
//
//  Created by double on 2017/10/28.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "CEMoreLightsVC.h"

@interface CEMoreLightsVC ()<UIWebViewDelegate>

@property(nonatomic,strong) UIWebView *webView;
@property(nonatomic,strong)NSMutableData *dataM;

@end

@implementation CEMoreLightsVC

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self createUI];
}

#pragma mark - UI
- (void)createUI {
    [self navUI];
    [self createWebView];
}

- (void)navUI {
    self.title = @"get more lights";
    
    WeakSelf(weakSelf)
    [self customBackBarBtnItemTo:^{
        [weakSelf.navigationController popViewControllerAnimated:YES];
    }];
}

- (void)createWebView {
    
    CGFloat navHeight = 0;
    if ([[UIDevice currentDevice].systemVersion floatValue] >= 11.0f) {
        navHeight = StateBarAndNavBarHeight;
    }
    
    _webView = [[UIWebView alloc] init];
    _webView.delegate = self;
    [self.view addSubview:_webView];
    [_webView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.view).offset(navHeight);
        make.left.right.bottom.equalTo(self.view);
    }];
    
    [_webView loadRequest:[NSURLRequest requestWithURL:[[NSURL alloc] initWithString :@"http://www.homedepot.com"]]];
}

#pragma mark - Data

#pragma mark - Interaction Event

#pragma mark - Trigger Event

#pragma mark - UIWebViewDelegate
- (void)URLSession:(NSURLSession *)session task:(NSURLSessionTask *)task
didReceiveChallenge:(NSURLAuthenticationChallenge *)challenge
 completionHandler:(void (^)(NSURLSessionAuthChallengeDisposition disposition, NSURLCredential * __nullable credential))completionHandler
{
    NSLog(@"challenge = %@",challenge.protectionSpace.serverTrust);
    //判断是否是信任服务器证书
    if (challenge.protectionSpace.authenticationMethod == NSURLAuthenticationMethodServerTrust)
    {
        //创建一个凭据对象
        NSURLCredential *credential = [NSURLCredential credentialForTrust:challenge.protectionSpace.serverTrust];
        //告诉服务器客户端信任证书
        [challenge.sender useCredential:credential forAuthenticationChallenge:challenge];
        
    }
}

/**
 *  接收到服务器返回的数据时调用
 */
- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data
{
    NSLog(@"接收到的数据%zd",data.length);
    [self.dataM appendData:data];
}
/**
 *  请求完毕
 */
- (void)connectionDidFinishLoading:(NSURLConnection *)connection
{
//    NSString *html = [[NSString alloc]initWithData:self.dataM encoding:NSUTF8StringEncoding];
    
    NSLog(@"请求完毕");
//    [self.webView loadHTMLString:html baseURL:self.url];
}

#pragma mark - 懒加载
- (NSMutableData *)dataM
{
    if (_dataM == nil)
    {
        _dataM = [[NSMutableData alloc]init];
    }
    return _dataM;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
