//
//  GroupedLightTableViewCell.h
//  ETIDownlights
//
//  Created by Andrea Houg on 4/13/16.
//  Copyright © 2016 Bolutek. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface GroupedLightTableViewCell : UITableViewCell

@property (weak, nonatomic) IBOutlet UIImageView *imageView;
@property (nonatomic) BOOL isSelected;

@end
