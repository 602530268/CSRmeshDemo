//
//  GroupedLightTableViewCell.m
//  ETIDownlights
//
//  Created by Andrea Houg on 4/13/16.
//  Copyright © 2016 Bolutek. All rights reserved.
//

#import "GroupedLightTableViewCell.h"

@implementation GroupedLightTableViewCell

@dynamic imageView;


-(void)setIsSelected:(BOOL)isSelected {
    self.imageView.frame = CGRectMake(28, 8, 44, 44);
    self.imageView.image = isSelected ? [UIImage imageNamed:@"add_selectLight"] : [UIImage imageNamed:@"add_unSelectLight"];
    _isSelected = isSelected;
}

-(void)layoutSubviews {
    [super layoutSubviews];
    self.imageView.frame = CGRectMake(28, 8, 44, 44);
}


@end
