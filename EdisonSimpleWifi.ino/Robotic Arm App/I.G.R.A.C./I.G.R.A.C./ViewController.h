//
//  ViewController.h
//  I.G.R.A.C.
//
//  Created by Victor Carreño on 5/10/15.
//  Copyright (c) 2015 Victor Carreño. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController



@property (strong, nonatomic) IBOutlet UITextField *URL;
@property (strong, nonatomic) IBOutlet UISlider *xPosic;
@property (strong, nonatomic) IBOutlet UISlider *yPosic;
@property (strong, nonatomic) IBOutlet UISlider *zPosic;
- (IBAction)sendValue:(id)sender;
- (IBAction)gripperSwitch:(id)sender;
- (IBAction)xPosiCACTION:(id)sender;
- (IBAction)yPosicAction:(id)sender;
- (IBAction)zPosicAction:(id)sender;
@property (strong, nonatomic) IBOutlet UILabel *xPosicLable;
@property (strong, nonatomic) IBOutlet UILabel *yPosicLabel;
@property (strong, nonatomic) IBOutlet UILabel *zPosicLabel;

@end

