//
//  ChangePasscodeView.m
//  CSRmeshDemo
//
//  Created by double on 2017/10/26.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "ChangePasscodeView.h"

@interface ChangePasscodeView ()<UITextFieldDelegate>

@end

@implementation ChangePasscodeView
{
    NSArray *_itemsArr;
}

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        self = [[[NSBundle mainBundle] loadNibNamed:NSStringFromClass([ChangePasscodeView class]) owner:self options:nil] lastObject];
        
        _itemsArr = @[_label0,_label1,_label2,_label3];
        _textField.delegate = self;
        _textField.keyboardType = UIKeyboardTypeNumberPad;   //设置为数字键盘
        _textField.tintColor= [UIColor clearColor]; //隐藏光标
        _textField.textColor = [UIColor clearColor];    //隐藏文本
        _textField.secureTextEntry = YES;   //当设置为密码框时才不会被第三方键盘冲突，只是代价是显示为小圆点，但在这里是完全没有影响的
        
        //监听
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(textFieldTextChangeEvent:) name:UITextFieldTextDidChangeNotification object:nil];
        
        for (UILabel *label in _itemsArr) {
            UIView *lineView = [[UIView alloc] init];
            lineView.backgroundColor = [UIColor whiteColor];
            [label addSubview:lineView];
            [lineView mas_makeConstraints:^(MASConstraintMaker *make) {
                make.centerX.bottom.equalTo(label);
                make.width.equalTo(label).multipliedBy(0.9);
                make.height.equalTo(@(5));
            }];
        }
        
        [_textField becomeFirstResponder];
    }
    return self;
}

- (void)setPasscode:(NSString *)passcode {
    
    _passcode = passcode;
    if (_passcode.length == 4) {
        
        _textField.text = passcode;
        
        for (int i = 0; i < _passcode.length; i++) {
            UILabel *label = _itemsArr[i];
            label.text = [_passcode substringWithRange:NSMakeRange(i, 1)];
        }
        
    }else {
        
        for (int i = 0; i < _itemsArr.count; i++) {
            UILabel *label = _itemsArr[i];
            label.text = @"";
        }
    }

}

//监听键盘文本改变
- (void)textFieldTextChangeEvent:(NSNotification *)sender {
    UITextField * textField = sender.object;
    NSLog(@"text: %@",textField.text);
    
    //只允许全数字
    if (![BaseCommond validateNumber:_textField.text] && _textField.text.length != 0) {
        _textField.text = [_textField.text substringToIndex:_textField.text.length - 1];
    }else {
        [self changeLabelsUI];
        _passcode = _textField.text;
    }
    
}

- (void)changeLabelsUI {
    
    //限制在4范围内
    if (_textField.text.length > 4) {
        _textField.text = [_textField.text substringToIndex:4];
    }
    
    //显示出来
    for (int i = 0; i < _textField.text.length; i++) {
        UILabel *label = _itemsArr[i];
        label.text = [_textField.text substringWithRange:NSMakeRange(i, 1)];
    }
    
    //长度不够时说明点击了删除键
    NSInteger count = _itemsArr.count - _textField.text.length;
    for (int i = 1; i <= count; i++) {
        UILabel *label = _itemsArr[_itemsArr.count - i];
        label.text = @"";
    }
}



@end
