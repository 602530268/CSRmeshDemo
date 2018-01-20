//
//  CELightsTableViewCell.h
//  CSRmeshDemo
//
//  Created by double on 2017/7/19.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SwitchImgView.h"

#define LightsTableViewCellIdentifier @"LightsTableViewCellIdentifier"

@interface CELightsTableViewCell : UITableViewCell
@property (weak, nonatomic) IBOutlet UILabel *titleLbl;
@property (weak, nonatomic) IBOutlet SwitchImgView *switchImgView;
@property (weak, nonatomic) IBOutlet UILabel *detailLbl;

@property(nonatomic,strong) CSRmeshDevice *selectDevice;

@property(nonatomic,assign) BOOL notFindDevice; //没有找到该设备

- (void)updateUI;

@end
