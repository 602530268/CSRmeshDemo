//
//  CEAreasTableViewCell.m
//  CSRmeshDemo
//
//  Created by double on 2017/7/19.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "CEAreasTableViewCell.h"

@implementation CEAreasTableViewCell

- (void)awakeFromNib {
    [super awakeFromNib];
    // Initialization code
    
    self.backgroundColor = BaseBackgroundColor;
    self.selectionStyle = UITableViewCellSelectionStyleNone;
    
    self.titleLbl.textColor = [UIColor whiteColor];
    self.detailLbl.textColor = [UIColor whiteColor];

    [self controlsEventCallback];
}

#pragma mark - Interaction Event
- (void)controlsEventCallback {
    
    WeakSelf(weakSelf)
    self.switchImgView.switchCallback = ^{
        NSNumber *deviceId = nil;
        if (weakSelf.selectArea) {
            CSRmeshDevice *device = weakSelf.selectArea.areaDevice;
            [[CSRDevicesManager sharedInstance] setSelectedDevice:device];
            deviceId = device.deviceId;
        }else {
            [[CSRDevicesManager sharedInstance] setSelectedDevice:nil];
            deviceId = @(0);
        }
        
        BOOL power = [UDManager getPowerStateWith:deviceId];
        [[CommandManager shareInstance] sendPower:!power];
        weakSelf.switchImgView.image = [DeviceDataHandle getImageWithDeviceId:deviceId];
    };
    
}

- (void)updateUI {
    if (self.areaEntity.areaID) {
        BOOL onlineState = [UDManager getDeviceOnlingState:self.areaEntity.areaID];
        self.switchImgView.image = [DeviceDataHandle getImageWithDeviceId:self.areaEntity.areaID];
    }
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

@end
