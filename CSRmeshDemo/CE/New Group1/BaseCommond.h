//
//  BaseCommond.h
//  CSRmeshDemo
//
//  Created by double on 2017/6/26.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BaseCommond : NSObject

//获取当前控制器
+ (UIViewController *)getCurrentVC;

//NSData转十六进制字符串
+ (NSString *) converDataToHexString:(NSData *)data;

//十六进制字符串转NSData
+ (NSData *)converHexStrToData:(NSString *)hexString;

//自定义img的尺寸
+ (UIImage *)customImageWith:(UIImage *)image toSize:(CGSize)toSize;

//获取图片上某坐标点对应的像素的color
+ (UIColor *)getPointColorWithImage:(UIImage *)image location:(CGPoint)point;

//获取UIColor对象的RGBA值
+ (NSDictionary *)getRGBDictionaryByColor:(UIColor *)originColor;

//转换成16进制
+ (NSString *)ToHex:(long long int)tmpid :(BOOL)isbool;

//验证是否全中文
+ (BOOL)validateNumber:(NSString*)number;

//获取手机型号
+ (NSString*)deviceString;

//修改image尺寸
+ (UIImage *)scaleFromImage:(UIImage *)image toSize:(CGSize)size;

# pragma mark - 路径类
//获取沙盒根目录
+ (NSString *)pathByHomeDirectory;

//获取document文件路径
+ (NSString *)pathByDocument;

//获取library文件路径
+ (NSString *)pathByLibrary;

//获取library里Caches文件路径
+ (NSString *)pathByCaches;

@end
