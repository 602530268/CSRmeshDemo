//
//  CEAddNewLightTableViewCell.m
//  CSRmeshDemo
//
//  Created by double on 2017/7/18.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "CEAddNewLightTableViewCell.h"

@implementation CEAddNewLightTableViewCell

- (void)awakeFromNib {
    [super awakeFromNib];
    // Initialization code
    
    self.backgroundColor = [UIColor clearColor];
    self.selectionStyle = UITableViewCellSelectionStyleNone;
    
    self.imgView.image = [UIImage imageNamed:@"add_unSelectLight"];
    self.titleLbl.textColor = [UIColor whiteColor];
}

- (void)setIsSelect:(BOOL)isSelect {
    if (isSelect) {
        self.imgView.image = [UIImage imageNamed:@"add_selectLight"];
    }else {
        self.imgView.image = [UIImage imageNamed:@"add_unSelectLight"];
    }
}

- (void)setNotChoose:(BOOL)notChoose {
    if (notChoose) {
        self.titleLbl.textColor = [UIColor lightGrayColor];
        self.imgView.tintColor = [UIColor lightGrayColor];
        self.imgView.image = [self.imgView.image imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
    }else {
        self.titleLbl.textColor = [UIColor whiteColor];
        self.imgView.tintColor = [UIColor clearColor];
        self.imgView.image = [self.imgView.image imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal];
    }
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

@end
