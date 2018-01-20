//
//  TemperatureBottomView.h
//  Test_1
//
//  Created by double on 2017/8/15.
//  Copyright © 2017年 double. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef NS_ENUM(NSInteger,SceneMode) {
    SceneModeWake,
    SceneModeSleep,
    SceneModeConcentrate,
    SceneModeRelax,
};

@interface TemperatureBottomView : UIView

@property (weak, nonatomic) IBOutlet UILabel *titleLbl;

@property (weak, nonatomic) IBOutlet UIButton *wakeBtn;
@property (weak, nonatomic) IBOutlet UIButton *sleepBtn;
@property (weak, nonatomic) IBOutlet UIButton *concentrateBtn;
@property (weak, nonatomic) IBOutlet UIButton *relaxBtn;

@property(nonatomic,assign) SceneMode mode;

@property(nonatomic,copy) void (^sceneModeBtnEventCallback)(SceneMode sceneMode);

@end
