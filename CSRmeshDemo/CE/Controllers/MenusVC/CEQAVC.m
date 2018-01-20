//
//  CEQAVC.m
//  CSRmeshDemo
//
//  Created by chencheng on 2018/1/17.
//  Copyright © 2018年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "CEQAVC.h"

@interface CEQAVC ()<UIWebViewDelegate>

@property(nonatomic,strong) UILabel *tipLbl;
@property(nonatomic,strong) UIButton *startBtn;

@property(nonatomic,strong) UIWebView *webView;

@end

@implementation CEQAVC

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self createUI];
}

# pragma mark - UI
- (void)createUI {
    
    self.view.backgroundColor = [UIColor whiteColor];
    
    _startBtn = [[UIButton alloc] init];
    [self.view addSubview:_startBtn];
    [_startBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.center.equalTo(self.view);
        make.width.equalTo(@100);
        make.height.equalTo(@40);
    }];
    
    [_startBtn setTitle:@"start" forState:UIControlStateNormal];
    [_startBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    _startBtn.backgroundColor = [UIColor orangeColor];
    _startBtn.layer.cornerRadius = 20.0f;
    [_startBtn addTarget:self action:@selector(startBtnEvent:) forControlEvents:UIControlEventTouchUpInside];
    
    _tipLbl = [[UILabel alloc] init];
    [self.view addSubview:_tipLbl];
    [_tipLbl mas_makeConstraints:^(MASConstraintMaker *make) {
        make.bottom.equalTo(_startBtn.mas_top).offset(-50.0f);
        make.left.right.equalTo(self.view);
    }];
    _tipLbl.textAlignment = NSTextAlignmentCenter;
    _tipLbl.text = @"Follow my action !";
}

- (void)startBtnEvent:(UIButton *)sender {
    [self loadGif];
}

- (void)loadGif {
    
    [self showWebViewToAnimationWith:1];
    NSString *path = [[NSBundle mainBundle] pathForResource:@"qagif" ofType:@"gif"];
    
    NSURLRequest *request = [NSURLRequest requestWithURL:[NSURL fileURLWithPath:path]];
    [self.webView loadRequest:request];
    
    //38张图，每张1s，所以总时长是38s，懒得用data计算了，真要算的话参考: https://www.jianshu.com/p/6cd7132e8997
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(38 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        CCLog(@"播放完成");
    });
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)((38 + 5) * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        CCLog(@"隐藏");
        [self showWebViewToAnimationWith:0];
    });
}

- (void)showWebViewToAnimationWith:(CGFloat)alpha {
    [UIView animateWithDuration:0.2f animations:^{
        self.webView.alpha = alpha;
    }];
}

- (UIWebView *)webView {
    if (!_webView) {
        _webView = [[UIWebView alloc] init];
        _webView.delegate = self;
        _webView.alpha = 0;
        [self.view addSubview:_webView];
        [_webView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(self.view).offset(StateBarAndNavBarHeight);
            make.left.right.bottom.equalTo(self.view);
        }];
        _webView.scalesPageToFit = YES;
//        _webView.layer.borderColor = [UIColor redColor].CGColor;
//        _webView.layer.borderWidth = 2.0f;
    }
    return _webView;
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
