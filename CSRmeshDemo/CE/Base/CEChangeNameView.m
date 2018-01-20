//
//  CEChangeNameView.m
//  CSRmeshDemo
//
//  Created by double on 2017/10/24.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "CEChangeNameView.h"
#import "AlertControllerManager.h"

@implementation CEChangeNameView
{
    UIView *_superView;
}

- (instancetype)initWithFrame:(CGRect)frame superView:(UIView *)superView {
    if (self = [super initWithFrame:frame]) {
        
        _superView = superView;
        [self createControls];
    }
    return self;
}

/*
 老项目里摘抄下来的
 */
- (void)createControls {
    
    if (self.subviews.count) {
        return;
    }
    
    self.frame = CGRectMake(_superView.center.x - 150, _superView.center.y - 180, 300, 180);
    self.backgroundColor = [UIColor colorWithWhite:252/255. alpha:1.0];
    self.layer.cornerRadius = 15;
    
    _titleLbl = [[UILabel alloc] initWithFrame:CGRectMake(0, 10, 280, 50)];
    _titleLbl.numberOfLines = 2;
    _titleLbl.font = [UIFont systemFontOfSize:20];
    _titleLbl.textAlignment = NSTextAlignmentCenter;
    _titleLbl.text = @"Creat a new name for this \n group";
    [self addSubview:_titleLbl];
    
    _textField = [[UITextField alloc] initWithFrame:CGRectMake(20, 70, 260,40)];
    _textField.borderStyle = UITextBorderStyleRoundedRect;
    _textField.clearButtonMode = UITextFieldViewModeWhileEditing;
    _textField.layer.borderWidth = 0.5;
    _textField.layer.borderColor = [UIColor grayColor].CGColor;
    _textField.layer.cornerRadius = 8;
    [self addSubview:_textField];
    
    UIView * line = [[UIView alloc] initWithFrame:CGRectMake(0, 125, 300 , 1)];
    line.alpha = 0.3;
    line.backgroundColor = [UIColor grayColor];
    [self addSubview:line];
    
    UIButton * yes = [UIButton buttonWithType:UIButtonTypeSystem];
    yes.frame = CGRectMake(10, 135, 120, 30);
    //    yes.backgroundColor = [UIColor cyanColor];
    //    yes.font = [UIFont systemFontOfSize:20];
    [yes setTintColor:[UIColor colorWithRed:33/255. green:157/255. blue:252/255. alpha:1.0]];
    yes.layer.cornerRadius = 15;
    yes.tag = 1;
    [yes setTitle:@"Save Name" forState:UIControlStateNormal];
    [yes addTarget:self action:@selector(chageGroupName:) forControlEvents:UIControlEventTouchUpInside];
    [self addSubview:yes];
    
    line = [[UIView alloc] initWithFrame:CGRectMake(150, 125, 1 , 55)];
    line.alpha = 0.3;
    line.backgroundColor = [UIColor grayColor];
    [self addSubview:line];
    
    UIButton * no = [UIButton buttonWithType:UIButtonTypeSystem];
    no.frame = CGRectMake(170, 135, 120, 30);
    [no setTintColor:[UIColor colorWithRed:33/255. green:157/255. blue:252/255. alpha:1.0]];
    no.layer.cornerRadius = 15;
    no.tag = 0;
    [no setTitle:@"Cancel" forState:UIControlStateNormal];
    [no addTarget:self action:@selector(chageGroupName:) forControlEvents:UIControlEventTouchUpInside];
    [self addSubview:no];
}

- (void)chageGroupName:(UIButton *)sender {
    [_textField resignFirstResponder];
    self.hidden = YES;
    if (sender.tag) {
        if ([_textField.text isEqualToString:@""] || _textField.text.length == 0)  {
            
            UIAlertView * alert = [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"Warning", nil) message:NSLocalizedString(@"Input can not be empty", nil) delegate:nil cancelButtonTitle:NSLocalizedString(@"OK", nil) otherButtonTitles:nil];
            
            [alert show];
            
        }else{
            if (_newNameCallback) {
                _newNameCallback(_textField.text);
            }
        }
    }
    _textField.text = @"";
}

-(void)textFieldDidBeginEditing:(UITextField *)textField
{
    CGRect frame = textField.frame;
    int offset = frame.origin.y + 49 - (self.frame.size.height - 109.0);
    NSTimeInterval anm = 0.30f;
    [UIView beginAnimations:@"ResizeForKeyboard" context:nil];
    [UIView setAnimationDuration:anm];
    if(offset > 0) {
        self.frame = CGRectMake(_superView.center.x - 150, _superView.center.y - 180 - offset, self.frame.size.width, self.frame.size.height);
    }
    [UIView commitAnimations];
}

- (void)dealloc {
    NSLog(@"dealloc: %@",self);
}

@end
