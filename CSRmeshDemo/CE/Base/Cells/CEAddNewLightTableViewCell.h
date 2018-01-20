//
//  CEAddNewLightTableViewCell.h
//  CSRmeshDemo
//
//  Created by double on 2017/7/18.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

#define CEAddNewLightTableViewCellIdentifier @"CEAddNewLightTableViewCellIdentifier"

@interface CEAddNewLightTableViewCell : UITableViewCell
@property (weak, nonatomic) IBOutlet UIImageView *imgView;
@property (weak, nonatomic) IBOutlet UILabel *titleLbl;

@property(nonatomic,assign) BOOL isSelect;  //是否选中状态
@property(nonatomic,assign) BOOL notChoose; //是否不可选状态，YES时将会灰化

@end
