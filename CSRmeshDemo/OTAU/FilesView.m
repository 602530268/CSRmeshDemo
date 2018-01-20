//
//  FilesView.m
//  ETIDownlights
//
//  Created by double on 2017/10/11.
//  Copyright © 2017年 Bolutek. All rights reserved.
//

#import "FilesView.h"
#import "Masonry.h"

static NSString *FilesTableViewCellIdentifier = @"FilesTableViewCellIdentifier";

@interface FilesView ()<UITableViewDataSource,UITableViewDelegate>
{
    NSString *_choosePath;
}

@end

@implementation FilesView

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        
        _filesTableView = [[UITableView alloc] initWithFrame:CGRectZero style:UITableViewStylePlain];
        _filesTableView.delegate = self;
        _filesTableView.dataSource = self;
        _filesTableView.tableFooterView = [[UIView alloc] init];
        [self addSubview:_filesTableView];
        [_filesTableView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.center.equalTo(self);
            make.size.equalTo(self);
        }];
        
        [_filesTableView registerClass:[UITableViewCell class] forCellReuseIdentifier:FilesTableViewCellIdentifier];
        
        NSArray *files = [[NSBundle mainBundle] pathsForResourcesOfType:@".xuv" inDirectory:@"./"];
        _filePaths = files.mutableCopy;
    }
    return self;
}

#pragma mark - UITableViewDataSource
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return _filePaths.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:FilesTableViewCellIdentifier forIndexPath:indexPath];
    
    NSString *path = _filePaths[indexPath.row];
    
    NSString *fileName = [[path lastPathComponent] stringByDeletingPathExtension];
    
    //文件命名不允许存在 '/'，这里进行处理
    if ([fileName isEqualToString:@"56\" Color Changing Downlight"]) {
        fileName = @"5/6\" Color Changing Downlight";
    }
    
//    NSString *fullName = [NSString stringWithFormat:@"%@.xuv",fileName];
    cell.textLabel.text = fileName;
    
    return cell;
}

#pragma mark - UITableViewDelegate
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
    _choosePath = _filePaths[indexPath.row];
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.2 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        if (_fileCallback) {
            _fileCallback(_filePaths[indexPath.row]);
        }
    });

}


@end
