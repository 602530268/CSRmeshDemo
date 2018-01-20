//
//  FilesView.h
//  ETIDownlights
//
//  Created by double on 2017/10/11.
//  Copyright © 2017年 Bolutek. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef void(^ChooseFileCallback)(NSString *path);

@interface FilesView : UIView

@property(nonatomic,strong) UITableView *filesTableView;
@property(nonatomic,strong) NSMutableArray *filePaths;

@property(nonatomic,copy) ChooseFileCallback fileCallback;

@end
