//
//  CESupportVC.m
//  CSRmeshDemo
//
//  Created by double on 2017/10/28.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "CESupportVC.h"

#define KEY_FONT              fontWithName:@"MontSerrat-SemiBold" size:20
#define KEY_FONT1              fontWithName:@"MontSerrat-SemiBold" size:13
#define KEY_FONT2              fontWithName:@"MontSerrat-Regular" size:13

@interface CESupportVC ()

@end

@implementation CESupportVC

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self createUI];
}

#pragma mark - UI
- (void)createUI {
    [self navUI];
    [self createControls];
}

- (void)navUI {
    self.title = @"help & support";
    
    WeakSelf(weakSelf)
    [self customBackBarBtnItemTo:^{
        [weakSelf.navigationController popViewControllerAnimated:YES];
    }];
}

/*
 以下代码摘抄自老项目，懒得用HTML换了
 */
- (void)createControls {
    UIScrollView * scroll = [[UIScrollView alloc] initWithFrame:CGRectMake(0, 0, [UIScreen mainScreen].applicationFrame.size.width, [UIScreen mainScreen].applicationFrame.size.height-44)];
    scroll.contentSize = CGSizeMake([UIScreen mainScreen].applicationFrame.size.width, 10000);
    scroll.showsVerticalScrollIndicator = NO;
    scroll.showsHorizontalScrollIndicator = NO;
    scroll.bounces = NO;
    scroll.backgroundColor = [UIColor whiteColor];
    [self.view addSubview:scroll];
    
    CGFloat navHeight = 0;
    if ([[UIDevice currentDevice].systemVersion floatValue] >= 11.0f) {
        navHeight = StateBarAndNavBarHeight;
    }
    [scroll mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.view).offset(navHeight);
        make.left.right.bottom.equalTo(self.view);
    }];
    
    UILabel * label = [[UILabel alloc] initWithFrame:CGRectMake(0, 05, scroll.frame.size.width, 30)];
    label.text = @"Terms of Use";
    label.textAlignment = NSTextAlignmentCenter;
    label.font = [UIFont KEY_FONT];
    [scroll addSubview:label];
    
    UILabel * label1 = [[UILabel alloc] initWithFrame:CGRectMake(05, 38, scroll.frame.size.width - 10, 30)];
    label1.text = @"Trademarks and Copyrights";
    label1.textAlignment = NSTextAlignmentLeft;
    label1.font = [UIFont KEY_FONT1];
    [scroll addSubview:label1];
    
    UILabel * label2 = [[UILabel alloc] init];
    NSString * string = @"\tTrademarks, logos and service marks displayed on this app are registered and unregistered trademarks of The Home Depot, Igloo Technologies, Inc. and its licensors or content providers, or other third parties. All of these trademarks, logos and service marks are the property of their respective owners. Nothing on this app shall be construed as granting, by implication, estoppel, or otherwise, any license or right to use any trademark, logo or service mark displayed on the app without the owner's prior written permission, except as otherwise described herein. Igloo reserves all rights not expressly granted in and to the app and its content. This app and all of its content, including but not limited to text, design, graphics, interfaces and code, and the selection and arrangement thereof, is protected as a compilation under the copyright laws of the United States and other countries.";
    label2.numberOfLines = 0;
    CGRect r = [string boundingRectWithSize:CGSizeMake(scroll.frame.size.width - 10,10000) options:(NSStringDrawingUsesLineFragmentOrigin) attributes:@{NSFontAttributeName:[UIFont systemFontOfSize:14.f]} context:nil];
    label2.text = string;
    label2.frame = CGRectMake(05, 65, scroll.frame.size.width - 10, r.size.height);
    label2.font = [UIFont KEY_FONT2];
    //    label2.backgroundColor = [UIColor redColor];
    [scroll addSubview:label2];
    
    UILabel * label4 = [[UILabel alloc] initWithFrame:CGRectMake(05, label2.frame.size.height + label2.frame.origin.y, scroll.frame.size.width - 10, 30)];
    label4.text = @"Infringement Notice";
    label4.textAlignment = NSTextAlignmentLeft;
    label4.font = [UIFont KEY_FONT1];
    [scroll addSubview:label4];
    
    UILabel * label5 = [[UILabel alloc] initWithFrame:CGRectMake(05, label4.frame.size.height + label4.frame.origin.y, scroll.frame.size.width - 10, 200)];
    string = @"\tWe respect the intellectual property rights of others and request that you do the same. You are hereby informed that Igloo has adopted and reasonably implemented a policy that provides for the termination in appropriate circumstances of subscribers and account holders of Igloo's system or network who are repeat copyright infringers.\nIgloo is under no obligation to post, forward, transmit, distribute or otherwise provide any material available on this app, including material you provide to us, and so we have an absolute right to remove any material from the app in our sole discretion at any time.";
    label5.numberOfLines = 0;
    r = [string boundingRectWithSize:CGSizeMake(scroll.frame.size.width - 10,10000) options:(NSStringDrawingUsesLineFragmentOrigin) attributes:@{NSFontAttributeName:[UIFont systemFontOfSize:14.f]} context:nil];
    label5.text = string;
    label5.frame = CGRectMake(label5.frame.origin.x, label5.frame.origin.y, label5.frame.size.width, r.size.height);
    label5.textAlignment = NSTextAlignmentLeft;
    label5.font = [UIFont KEY_FONT2];
    //    label5.backgroundColor = [UIColor redColor];
    [scroll addSubview:label5];
    
    UILabel * label6 = [[UILabel alloc] initWithFrame:CGRectMake(05, label5.frame.size.height + label5.frame.origin.y, scroll.frame.size.width - 10, 30)];
    label6.text = @"DISCLAIMERS";
    label6.textAlignment = NSTextAlignmentLeft;
    label6.font = [UIFont KEY_FONT1];
    [scroll addSubview:label6];
    
    UILabel * label7 = [[UILabel alloc] initWithFrame:CGRectMake(05, label6.frame.size.height + label6.frame.origin.y, scroll.frame.size.width - 10, 550)];
    string = @"\tYOUR USE OF THIS APP IS AT YOUR SOLE RISK. THE APP IS PROVIDED ON AN \"AS IS\" AND \"AS AVAILABLE\" BASIS. WE RESERVE THE RIGHT TO RESTRICT OR TERMINATE YOUR ACCESS TO THE APP OR ANY FEATURE OR PART THEREOF AT ANY TIME. IGLOO EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND, WHETHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE AND ANY WARRANTIES THAT MATERIALS ON THE APP ARE NONINFRINGING, AS WELL AS WARRANTIES IMPLIED FROM A COURSE OF PERFORMANCE OR COURSE OF DEALING; THAT ACCESS TO THE APP WILL BE UNINTERRUPTED OR ERROR-FREE; THAT THE APP WILL BE SECURE; THAT THE APP OR THE SERVER THAT MAKES THE APP AVAILABLE WILL BE VIRUS-FREE; OR THAT INFORMATION ON THE APP WILL BE COMPLETE, ACCURATE OR TIMELY. IF YOU DOWNLOAD ANY MATERIALS FROM THIS APP, YOU DO SO AT YOUR OWN DISCRETION AND RISK. YOU WILL BE SOLELY RESPONSIBLE FOR ANY DAMAGE TO YOUR COMPUTER SYSTEM OR LOSS OF DATA THAT RESULTS FROM THE DOWNLOAD OF ANY SUCH MATERIALS. NO ADVICE OR INFORMATION, WHETHER ORAL OR WRITTEN, OBTAINED BY YOU FROM IGLOO OR THROUGH OR FROM THE APP SHALL CREATE ANY WARRANTY OF ANY KIND. IGLOO DOES NOT MAKE ANY WARRANTIES OR REPRESENTATIONS REGARDING THE USE OF THE MATERIALS ON THIS APP IN TERMS OF THEIR COMPLETENESS, CORRECTNESS, ACCURACY, ADEQUACY, USEFULNESS, TIMELINESS, RELIABILITY OR OTHERWISE.\nIN CERTAIN JURISDICTIONS, THE LAW MAY NOT PERMIT THE DISCLAIMER OF WARRANTIES, SO THE ABOVE DISCLAIMER MAY NOT APPLY TO YOU.";
    label7.numberOfLines = 0;
    //    [label2 sizeToFit];
    r = [string boundingRectWithSize:CGSizeMake(scroll.frame.size.width - 10,10000) options:(NSStringDrawingUsesLineFragmentOrigin) attributes:@{NSFontAttributeName:[UIFont systemFontOfSize:13.5f]} context:nil];
    label7.text = string;
    label7.frame = CGRectMake(label7.frame.origin.x, label7.frame.origin.y, label7.frame.size.width, r.size.height);
    label7.textAlignment = NSTextAlignmentLeft;
    label7.font = [UIFont KEY_FONT2];
    //    label7.backgroundColor = [UIColor redColor];
    [scroll addSubview:label7];
    
    label6 = [[UILabel alloc] initWithFrame:CGRectMake(05, label7.frame.size.height + label7.frame.origin.y, scroll.frame.size.width - 10, 30)];
    label6.text = @"LIMITATION OF LIABILITY";
    label6.textAlignment = NSTextAlignmentLeft;
    label6.font = [UIFont KEY_FONT1];
    [scroll addSubview:label6];
    
    label7 = [[UILabel alloc] initWithFrame:CGRectMake(05, label6.frame.size.height + label6.frame.origin.y, scroll.frame.size.width - 10, 890)];
    string = @"\tYOU ACKNOWLEDGE AND AGREE THAT YOU ASSUME FULL RESPONSIBILITY FOR YOUR USE OF THE APP. YOU ACKNOWLEDGE AND AGREE THAT ANY INFORMATION YOU SEND OR RECEIVE DURING YOUR USE OF THE APP MAY NOT BE SECURE AND MAY BE INTERCEPTED BY UNAUTHORIZED PARTIES. YOU ACKNOWLEDGE AND AGREE THAT YOUR USE OF THE APP IS AT YOUR OWN RISK AND THAT THE APP IS MADE AVAILABLE TO YOU AT NO CHARGE. RECOGNIZING SUCH, YOU ACKNOWLEDGE AND AGREE THAT, TO THE FULLEST EXTENT PERMITTED BY APPLICABLE LAW, NEITHER IGLOO NOR ITS AFFILIATES, SUPPLIERS OR THIRD PARTY CONTENT PROVIDERS WILL BE LIABLE FOR ANY DIRECT, INDIRECT, PUNITIVE, EXEMPLARY, INCIDENTAL, SPECIAL, CONSEQUENTIAL OR OTHER DAMAGES ARISING OUT OF OR IN ANY WAY RELATED TO THE APP, OR ANY OTHER SITE YOU ACCESS THROUGH A LINK FROM THIS APP OR FROM ANY ACTIONS WE TAKE OR FAIL TO TAKE AS A RESULT OF COMMUNICATIONS YOU SEND TO US, OR THE DELAY OR INABILITY TO USE THE APP, OR FOR ANY INFORMATION, PRODUCTS OR SERVICES ADVERTISED IN OR OBTAINED THROUGH THE APP, REMOVAL OR DELETION OF ANY MATERIALS SUBMITTED OR POSTED ON ITS APP, OR OTHERWISE ARISING OUT OF THE USE OF THE APP, WHETHER BASED ON CONTRACT, TORT, STRICT LIABILITY OR OTHERWISE, EVEN IF IGLOO, ITS AFFILIATES OR ANY OF ITS SUPPLIERS HAS BEEN ADVISED OF THE POSSIBILITY OF DAMAGES. THIS DISCLAIMER APPLIES, WITHOUT LIMITATION, TO ANY DAMAGES OR INJURY ARISING FROM ANY FAILURE OF PERFORMANCE, ERROR, OMISSION, INTERRUPTION, DELETION, DEFECTS, DELAY IN OPERATION OR TRANSMISSION, COMPUTER VIRUSES, FILE CORRUPTION, COMMUNICATION-LINE FAILURE, NETWORK OR SYSTEM OUTAGE, YOUR LOSS OF PROFITS, OR THEFT, DESTRUCTION, UNAUTHORIZED ACCESS TO, ALTERATION OF, LOSS OR USE OF ANY RECORD OR DATA, AND ANY OTHER TANGIBLE OR INTANGIBLE LOSS. YOU SPECIFICALLY ACKNOWLEDGE AND AGREE THAT NEITHER IGLOO NOR ITS SUPPLIERS SHALL BE LIABLE FOR ANY DEFAMATORY, OFFENSIVE OR ILLEGAL CONDUCT OF ANY USER OF THE APP. YOUR SOLE AND EXCLUSIVE REMEDY FOR ANY OF THE ABOVE CLAIMS OR ANY DISPUTE WITH IGLOO IS TO DISCONTINUE YOUR USE OF THE APP. YOU AND IGLOO AGREE THAT ANY CAUSE OF ACTION ARISING OUT OF OR RELATED TO THE APP MUST COMMENCE WITHIN ONE (1) YEAR AFTER THE CAUSE OF ACTION ACCRUES OR THE CAUSE OF ACTION IS PERMANENTLY BARRED. BECAUSE SOME JURISDICTIONS DO NOT ALLOW LIMITATIONS ON HOW LONG AN IMPLIED WARRANTY LASTS, OR THE EXCLUSION OR LIMITATION OF LIABILITY FOR CONSEQUENTIAL OR INCIDENTAL DAMAGES, ALL OR A PORTION OF THE ABOVE LIMITATION MAY NOT APPLY TO YOU.";
    label7.numberOfLines = 0;
    r = [string boundingRectWithSize:CGSizeMake(scroll.frame.size.width - 10,10000) options:(NSStringDrawingUsesLineFragmentOrigin) attributes:@{NSFontAttributeName:[UIFont systemFontOfSize:13.5f]} context:nil];
    label7.text = string;
    label7.frame = CGRectMake(label7.frame.origin.x, label7.frame.origin.y, label7.frame.size.width, r.size.height);
    label7.textAlignment = NSTextAlignmentLeft;
    label7.font = [UIFont KEY_FONT2];
    //    label7.backgroundColor = [UIColor redColor];
    [scroll addSubview:label7];
    
    label6 = [[UILabel alloc] initWithFrame:CGRectMake(05, label7.frame.size.height + label7.frame.origin.y, scroll.frame.size.width - 10, 30)];
    label6.text = @"Indemnification";
    label6.textAlignment = NSTextAlignmentLeft;
    label6.font = [UIFont KEY_FONT1];
    [scroll addSubview:label6];
    
    label7 = [[UILabel alloc] initWithFrame:CGRectMake(05, label6.frame.size.height + label6.frame.origin.y, scroll.frame.size.width - 10, 300)];
    string = @"\tYou agree to indemnify, defend and hold harmless Igloo and its affiliates and their officers, directors, employees, contractors, agents, licensors, service providers, subcontractors and suppliers from and against any and all losses, liabilities, expenses, damages and costs, including reasonable attorneys' fees and court costs, arising or resulting from your use of the app and any violation of these Terms of Use. If you cause a technical disruption of the app or the systems transmitting the app to you or others, you agree to be responsible for any and all losses, liabilities, expenses, damages and costs, including reasonable attorneys' fees and court costs, arising or resulting from that disruption. Igloo reserves the right, at its own expense, to assume exclusive defense and control of any matter otherwise subject to indemnification by you and, in such case, you agree to cooperate with Igloo in the defense of such matter.";
    label7.numberOfLines = 0;
    r = [string boundingRectWithSize:CGSizeMake(scroll.frame.size.width - 10,10000) options:(NSStringDrawingUsesLineFragmentOrigin) attributes:@{NSFontAttributeName:[UIFont systemFontOfSize:14.f]} context:nil];
    label7.text = string;
    label7.frame = CGRectMake(label7.frame.origin.x, label7.frame.origin.y, label7.frame.size.width, r.size.height);
    label7.textAlignment = NSTextAlignmentLeft;
    label7.font = [UIFont KEY_FONT2];
    //    label7.backgroundColor = [UIColor redColor];
    [scroll addSubview:label7];
    
    label6 = [[UILabel alloc] initWithFrame:CGRectMake(05, label7.frame.size.height + label7.frame.origin.y, scroll.frame.size.width - 10, 30)];
    label6.text = @"Jurisdiction and Applicable Law";
    label6.textAlignment = NSTextAlignmentLeft;
    label6.font = [UIFont KEY_FONT1];
    [scroll addSubview:label6];
    
    label7 = [[UILabel alloc] initWithFrame:CGRectMake(05, label6.frame.size.height + label6.frame.origin.y, scroll.frame.size.width - 10, 300)];
    string = @"\tThe laws of the State of California govern these Terms of Use and your use of the app, and you irrevocably consent to the jurisdiction of the courts located in the County of California for any action arising out of or relating to these Terms of Use. We recognize that it is possible for you to obtain access to this app from any jurisdiction in the world, but we have no practical ability to prevent such access. This app has been designed to comply with the laws of the State of California and of the United States. If any material on this app, or your use of the app, is contrary to the laws of the place where you are when you access it, the app is not intended for you, and we ask you not to use the app. You are responsible for informing yourself of the laws of your jurisdiction and complying with them.";
    label7.numberOfLines = 0;
    r = [string boundingRectWithSize:CGSizeMake(scroll.frame.size.width - 10,10000) options:(NSStringDrawingUsesLineFragmentOrigin) attributes:@{NSFontAttributeName:[UIFont systemFontOfSize:14.f]} context:nil];
    label7.text = string;
    label7.frame = CGRectMake(label7.frame.origin.x, label7.frame.origin.y, label7.frame.size.width, r.size.height);
    label7.textAlignment = NSTextAlignmentLeft;
    label7.font = [UIFont KEY_FONT2];
    //    label7.backgroundColor = [UIColor redColor];
    [scroll addSubview:label7];
    
    label6 = [[UILabel alloc] initWithFrame:CGRectMake(05, label7.frame.size.height + label7.frame.origin.y, scroll.frame.size.width - 10, 30)];
    label6.text = @"Changes to These Terms of Use";
    label6.textAlignment = NSTextAlignmentLeft;
    label6.font = [UIFont KEY_FONT1];
    [scroll addSubview:label6];
    
    label7 = [[UILabel alloc] initWithFrame:CGRectMake(05, label6.frame.size.height + label6.frame.origin.y, scroll.frame.size.width - 10, 300)];
    string = @"\tIgloo reserves the right, at its sole discretion, to change, modify, add or remove any portion of these Terms of Use, in whole or in part, at any time, by posting revised terms on the app. It is your responsibility to check periodically for any changes we make to the Terms of Use. Your continued use of the app after any changes to the Terms of Use or other policies means you accept the changes.";
    label7.numberOfLines = 0;
    r = [string boundingRectWithSize:CGSizeMake(scroll.frame.size.width - 10,10000) options:(NSStringDrawingUsesLineFragmentOrigin) attributes:@{NSFontAttributeName:[UIFont systemFontOfSize:14.f]} context:nil];
    label7.text = string;
    label7.frame = CGRectMake(label7.frame.origin.x, label7.frame.origin.y, label7.frame.size.width, r.size.height);
    label7.textAlignment = NSTextAlignmentLeft;
    label7.font = [UIFont KEY_FONT2];
    //    label7.backgroundColor = [UIColor redColor];
    [scroll addSubview:label7];
    
    label6 = [[UILabel alloc] initWithFrame:CGRectMake(05, label7.frame.size.height + label7.frame.origin.y, scroll.frame.size.width - 10, 30)];
    label6.text = @"Entire Agreement and Admissibility";
    label6.textAlignment = NSTextAlignmentLeft;
    label6.font = [UIFont KEY_FONT1];
    [scroll addSubview:label6];
    
    label7 = [[UILabel alloc] initWithFrame:CGRectMake(05, label6.frame.size.height + label6.frame.origin.y, scroll.frame.size.width - 10, 300)];
    string = @"\tThis agreement and any policies or operating rules posted on this app constitute the entire agreement and understanding between you and Igloo with respect to the subject matter thereof and supersede all prior or contemporaneous communications and proposals, whether oral or written, between the parties with respect to such subject matter. A printed version of these Terms of Use shall be admissible in judicial or administrative proceedings based on or relating to use of the app to the same extent and subject to the same conditions as other business documents and records originally generated and maintained in printed form.";
    label7.numberOfLines = 0;
    r = [string boundingRectWithSize:CGSizeMake(scroll.frame.size.width - 10,10000) options:(NSStringDrawingUsesLineFragmentOrigin) attributes:@{NSFontAttributeName:[UIFont systemFontOfSize:14.f]} context:nil];
    label7.text = string;
    label7.frame = CGRectMake(label7.frame.origin.x, label7.frame.origin.y, label7.frame.size.width, r.size.height);
    label7.textAlignment = NSTextAlignmentLeft;
    label7.font = [UIFont KEY_FONT2];
    //    label7.backgroundColor = [UIColor redColor];
    [scroll addSubview:label7];
    
    label6 = [[UILabel alloc] initWithFrame:CGRectMake(05, label7.frame.size.height + label7.frame.origin.y, scroll.frame.size.width - 10, 30)];
    label6.text = @"Severability";
    label6.textAlignment = NSTextAlignmentLeft;
    label6.font = [UIFont KEY_FONT1];
    [scroll addSubview:label6];
    
    label7 = [[UILabel alloc] initWithFrame:CGRectMake(05, label6.frame.size.height + label6.frame.origin.y, scroll.frame.size.width - 10, 300)];
    string = @"\tIf any provision of this agreement is unlawful, void or unenforceable, the remaining provisions of the agreement will remain in place.";
    label7.numberOfLines = 0;
    r = [string boundingRectWithSize:CGSizeMake(scroll.frame.size.width - 10,10000) options:(NSStringDrawingUsesLineFragmentOrigin) attributes:@{NSFontAttributeName:[UIFont systemFontOfSize:14.f]} context:nil];
    label7.text = string;
    label7.frame = CGRectMake(label7.frame.origin.x, label7.frame.origin.y, label7.frame.size.width, r.size.height);
    label7.textAlignment = NSTextAlignmentLeft;
    label7.font = [UIFont KEY_FONT2];
    //    label7.backgroundColor = [UIColor redColor];
    [scroll addSubview:label7];
    
    label = [[UILabel alloc] initWithFrame:CGRectMake(0, label7.frame.origin.y + label7.frame.size.height, scroll.frame.size.width, 30)];
    label.text = @"Privacy Policy";
    label.textAlignment = NSTextAlignmentCenter;
    label.font = [UIFont KEY_FONT];
    [scroll addSubview:label];
    
    label7 = [[UILabel alloc] initWithFrame:CGRectMake(05, label.frame.size.height + label.frame.origin.y, scroll.frame.size.width - 10, 300)];
    string = @"\tIgloo Technologies, Inc. (“Igloo” or “we”) believes strongly in protecting the privacy of your personal data. We also believe it is important to inform you about how we will use your personal data, and to give you choices, where we can, about how that data will be used. We encourage you to read this Privacy Policy carefully.";
    label7.numberOfLines = 0;
    r = [string boundingRectWithSize:CGSizeMake(scroll.frame.size.width - 10,10000) options:(NSStringDrawingUsesLineFragmentOrigin) attributes:@{NSFontAttributeName:[UIFont systemFontOfSize:14.f]} context:nil];
    label7.text = string;
    label7.frame = CGRectMake(label7.frame.origin.x, label7.frame.origin.y, label7.frame.size.width, r.size.height);
    label7.textAlignment = NSTextAlignmentLeft;
    label7.font = [UIFont KEY_FONT2];
    //    label7.backgroundColor = [UIColor redColor];
    [scroll addSubview:label7];
    
    label6 = [[UILabel alloc] initWithFrame:CGRectMake(05, label7.frame.size.height + label7.frame.origin.y, scroll.frame.size.width - 10, 50)];
    label6.text = @"MOBILE INFORMATION WE COLLECT\nWhich personal data do we collect?";
    label6.numberOfLines = 2;
    label6.textAlignment = NSTextAlignmentLeft;
    label6.font = [UIFont KEY_FONT1];
    [scroll addSubview:label6];
    
    label7 = [[UILabel alloc] initWithFrame:CGRectMake(05, label6.frame.size.height + label6.frame.origin.y, scroll.frame.size.width - 10, 300)];
    string = @"\tThe type of personal data we collect depends on the method of collection.\n•Using the Mobile App, We may collect your:\n◦Name\n◦Email Address\n◦Operational Data (i.e. wattage, voltage, and time of use)\nThis personal data is transferred securely and is then “hashed,” or scrambled into a meaningless string of numbers and letters, before being stored by Igloo.\nPersonally identifiable information (e.g. Name, email address) we collect consists only of what you share with us. For example, certain products may ask for this type of information so that we may contact you by phone or email at your request. You choose what, how, and when you want to share.\nWeb-enabled mobile applications may use cookies or web beacons and other methods to customize your browsing experience.";
    label7.numberOfLines = 0;
    r = [string boundingRectWithSize:CGSizeMake(scroll.frame.size.width - 10,10000) options:(NSStringDrawingUsesLineFragmentOrigin) attributes:@{NSFontAttributeName:[UIFont systemFontOfSize:14.f]} context:nil];
    label7.text = string;
    label7.frame = CGRectMake(label7.frame.origin.x, label7.frame.origin.y, label7.frame.size.width, r.size.height);
    label7.textAlignment = NSTextAlignmentLeft;
    label7.font = [UIFont KEY_FONT2];
    //    label7.backgroundColor = [UIColor redColor];
    [scroll addSubview:label7];
    
    label6 = [[UILabel alloc] initWithFrame:CGRectMake(05, label7.frame.size.height + label7.frame.origin.y, scroll.frame.size.width - 10, 30)];
    label6.text = @"THIRD-PARTY SITES";
    label6.textAlignment = NSTextAlignmentLeft;
    label6.font = [UIFont KEY_FONT1];
    //    label6.backgroundColor = [UIColor redColor];
    [scroll addSubview:label6];
    
    label7 = [[UILabel alloc] initWithFrame:CGRectMake(05, label6.frame.size.height + label6.frame.origin.y, scroll.frame.size.width - 10, 300)];
    string = @"\tUse of 3rd party services (e.g. Home Depot) is governed by the privacy practices of those services. Igloo does not capture or store your login information or other personally identifiable information for these services except for the purpose of pre-populating fields in your account profile; however, session info or cookies may be stored.\nWe may provide links to third-party web sites for your convenience and information. These sites may have their own privacy practices which we recommend you review if you visit any linked web sites. We are not responsible for the content of linked sites or any use of the sites. ";
    label7.numberOfLines = 0;
    r = [string boundingRectWithSize:CGSizeMake(scroll.frame.size.width - 10,10000) options:(NSStringDrawingUsesLineFragmentOrigin) attributes:@{NSFontAttributeName:[UIFont systemFontOfSize:14.5f]} context:nil];
    label7.text = string;
    label7.frame = CGRectMake(label7.frame.origin.x, label7.frame.origin.y, label7.frame.size.width, r.size.height);
    label7.textAlignment = NSTextAlignmentLeft;
    label7.font = [UIFont KEY_FONT2];
    //    label7.backgroundColor = [UIColor redColor];
    [scroll addSubview:label7];
    
    label6 = [[UILabel alloc] initWithFrame:CGRectMake(05, label7.frame.size.height + label7.frame.origin.y, scroll.frame.size.width - 05, 30)];
    label6.text = @"HOW WE USE MOBILE COLLECTED INFORMATION";
    label6.textAlignment = NSTextAlignmentLeft;
    label6.font = [UIFont fontWithName:@"MontSerrat-SemiBold" size:12];
    [scroll addSubview:label6];
    
    label7 = [[UILabel alloc] initWithFrame:CGRectMake(05, label6.frame.size.height + label6.frame.origin.y, scroll.frame.size.width - 10, 300)];
    string = @"\tWe use the information collected to provide customer support, and when applicable, register and administer your account. Additionally, we may use the information you provide to contact you about new products and promotions as well as updates to our services and Privacy Policy.\nInformation you provide may be used to fulfill the service(s) or carry out the transaction(s) you have requested or authorized. For example, if you authorize an online purchase through the website or mobile application, we will use provided information to ship and bill you.";
    label7.numberOfLines = 0;
    r = [string boundingRectWithSize:CGSizeMake(scroll.frame.size.width - 10,10000) options:(NSStringDrawingUsesLineFragmentOrigin) attributes:@{NSFontAttributeName:[UIFont systemFontOfSize:14.5f]} context:nil];
    label7.text = string;
    label7.frame = CGRectMake(label7.frame.origin.x, label7.frame.origin.y, label7.frame.size.width, r.size.height);
    label7.textAlignment = NSTextAlignmentLeft;
    label7.font = [UIFont KEY_FONT2];
    //    label7.backgroundColor = [UIColor redColor];
    [scroll addSubview:label7];
    
    label6 = [[UILabel alloc] initWithFrame:CGRectMake(05, label7.frame.size.height + label7.frame.origin.y, scroll.frame.size.width - 10, 30)];
    label6.text = @"INFORMATION WE TRANSFER";
    label6.textAlignment = NSTextAlignmentLeft;
    label6.font = [UIFont KEY_FONT1];
    [scroll addSubview:label6];
    
    label7 = [[UILabel alloc] initWithFrame:CGRectMake(05, label6.frame.size.height + label6.frame.origin.y, scroll.frame.size.width - 10, 300)];
    string = @"\tWe reserve the right to transfer any information we have about you in the event we sell or transfer all or a portion of our business or assets. Should such a sale or transfer occur, we will use reasonable efforts to direct the transferee to use the data you have provided through the website and mobile app in a manner that is consistent with your previous relationship with Igloo and with this Privacy Policy.\nWe may transfer the data we store to other countries where we do business for the purposes described above. We will use reasonable methods to protect the data as described here unless otherwise required by applicable laws.\nIn the event you instruct us or have otherwise provided consent to transfer your data to a third party, the specific data transferred to such third party shall be at our discretion. Data transferred to a third party shall be pursuant to that third party's privacy practices which we strongly recommend you review prior to transfer. We are not responsible for the treatment or use of your data transferred to a third party pursuant to your instruction or consent even if such data originated with a device manufactured or sold by Commercial Electric or Hampton Bay.";
    label7.numberOfLines = 0;
    r = [string boundingRectWithSize:CGSizeMake(scroll.frame.size.width - 10,10000) options:(NSStringDrawingUsesLineFragmentOrigin) attributes:@{NSFontAttributeName:[UIFont systemFontOfSize:13.5f]} context:nil];
    label7.text = string;
    label7.frame = CGRectMake(label7.frame.origin.x, label7.frame.origin.y, label7.frame.size.width, r.size.height);
    label7.textAlignment = NSTextAlignmentLeft;
    label7.font = [UIFont KEY_FONT2];
    //    label7.backgroundColor = [UIColor redColor];
    [scroll addSubview:label7];
    
    label6 = [[UILabel alloc] initWithFrame:CGRectMake(05, label7.frame.size.height + label7.frame.origin.y, scroll.frame.size.width - 10, 30)];
    label6.text = @"HOW WE PROTECT DATA";
    label6.textAlignment = NSTextAlignmentLeft;
    label6.font = [UIFont KEY_FONT1];
    [scroll addSubview:label6];
    
    label7 = [[UILabel alloc] initWithFrame:CGRectMake(05, label6.frame.size.height + label6.frame.origin.y, scroll.frame.size.width - 10, 300)];
    string = @"\tWe maintain administrative, technical and physical safeguards designed to protect against unauthorized disclosure, use, alteration or destruction of the data you provide.";
    label7.numberOfLines = 0;
    r = [string boundingRectWithSize:CGSizeMake(scroll.frame.size.width - 10,10000) options:(NSStringDrawingUsesLineFragmentOrigin) attributes:@{NSFontAttributeName:[UIFont systemFontOfSize:14.f]} context:nil];
    label7.text = string;
    label7.frame = CGRectMake(label7.frame.origin.x, label7.frame.origin.y, label7.frame.size.width, r.size.height);
    label7.textAlignment = NSTextAlignmentLeft;
    label7.font = [UIFont KEY_FONT2];
    //    label7.backgroundColor = [UIColor redColor];
    [scroll addSubview:label7];
    
    label6 = [[UILabel alloc] initWithFrame:CGRectMake(05, label7.frame.size.height + label7.frame.origin.y, scroll.frame.size.width - 10, 30)];
    label6.text = @"UPDATES TO OUR PRIVACY POLICY";
    label6.textAlignment = NSTextAlignmentLeft;
    label6.font = [UIFont KEY_FONT1];
    [scroll addSubview:label6];
    
    label7 = [[UILabel alloc] initWithFrame:CGRectMake(05, label6.frame.size.height + label6.frame.origin.y, scroll.frame.size.width - 10, 300)];
    string = @"\tThis Privacy Policy may be updated periodically to reflect changes in our online information practices. In the event of a material change to this Privacy Policy, such as substantive changes in the handling of information, new types of data being collected, or the use of a different method for the sharing of information with third parties from what is outlined in this Privacy Policy, Igloo will communicate these changes via the mobile application and indicate at the top of the statement when it was most recently updated.";
    label7.numberOfLines = 0;
    r = [string boundingRectWithSize:CGSizeMake(scroll.frame.size.width - 10,10000) options:(NSStringDrawingUsesLineFragmentOrigin) attributes:@{NSFontAttributeName:[UIFont systemFontOfSize:13.5f]} context:nil];
    label7.text = string;
    label7.frame = CGRectMake(label7.frame.origin.x, label7.frame.origin.y, label7.frame.size.width, r.size.height);
    label7.textAlignment = NSTextAlignmentLeft;
    label7.font = [UIFont KEY_FONT2];
    //    label7.backgroundColor = [UIColor redColor];
    [scroll addSubview:label7];
    
    scroll.contentSize = CGSizeMake(scroll.frame.size.width, label7.frame.origin.y + label7.frame.size.height + 10);
}

#pragma mark - Data

#pragma mark - Interaction Event

#pragma mark - Trigger Event

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
