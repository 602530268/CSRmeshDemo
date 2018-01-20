//
//  CELightsTableViewCell.m
//  CSRmeshDemo
//
//  Created by double on 2017/7/19.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "CELightsTableViewCell.h"

@implementation CELightsTableViewCell

- (void)awakeFromNib {
    [super awakeFromNib];
    // Initialization code
    
    self.selectionStyle = UITableViewCellSelectionStyleNone;
    
    self.titleLbl.textColor = [UIColor whiteColor];
    self.detailLbl.textColor = [UIColor lightGrayColor];
    
    [self controlsEventCallback];
}

#pragma mark - Interaction Event 
- (void)controlsEventCallback {
    
    WeakSelf(weakSelf)
    self.switchImgView.switchCallback = ^{
        if (weakSelf.selectDevice && weakSelf.notFindDevice != YES) {
            BOOL power = [UDManager getPowerStateWith:weakSelf.selectDevice.deviceId];
            
            [[CSRDevicesManager sharedInstance] setSelectedDevice:weakSelf.selectDevice];
            [[CommandManager shareInstance] sendPower:!power];
            
            weakSelf.switchImgView.image = [DeviceDataHandle getImageWithDeviceId:weakSelf.selectDevice.deviceId];
        }
    };
}

- (void)setNotFindDevice:(BOOL)notFindDevice {
    _notFindDevice = notFindDevice;
    
    if (_notFindDevice) {
        self.switchImgView.image = [UIImage imageNamed:@"not_in_range"];
        self.detailLbl.text = @"not in range";
    }else {
        self.switchImgView.image = [DeviceDataHandle getImageWithDeviceId:self.selectDevice.deviceId];
        self.detailLbl.text = @"";
//        self.detailLbl.text = [NSString stringWithFormat:@"%@",self.selectDevice.deviceId];
    }
}


- (void)updateUI {
    if (self.selectDevice.deviceId) {
        BOOL onlineState = [UDManager getDeviceOnlingState:self.selectDevice.deviceId];
        self.notFindDevice = !onlineState;
    }
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

@end
