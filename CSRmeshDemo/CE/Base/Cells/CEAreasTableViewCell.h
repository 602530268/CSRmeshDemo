//
//  CEAreasTableViewCell.h
//  CSRmeshDemo
//
//  Created by double on 2017/7/19.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SwitchImgView.h"

#define AreasTableViewCellIdentifier @"AreasTableViewCellIdentifier"

@interface CEAreasTableViewCell : UITableViewCell

@property (weak, nonatomic) IBOutlet SwitchImgView *switchImgView;
@property (weak, nonatomic) IBOutlet UILabel *titleLbl;
@property (weak, nonatomic) IBOutlet UILabel *detailLbl;

@property(nonatomic,strong) CSRmeshArea *selectArea;

@property(nonatomic,strong) CSRAreaEntity *areaEntity;  

- (void)updateUI;

@end
