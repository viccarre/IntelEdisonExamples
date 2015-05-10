//
//  ViewController.m
//  I.G.R.A.C.
//
//  Created by Victor Carreño on 5/10/15.
//  Copyright (c) 2015 Victor Carreño. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)sendValue:(id)sender {
    
    NSString *agentURL = _URL.text;
    //[NSString stringWithFormat:@"%d",(int)_xPosic.value];
    NSLog([NSString stringWithFormat:@"/message?params=%d,%d,%d",(int)_xPosic.value, (int)_yPosic.value,(int)_zPosic.value]);
    NSURL *url = [NSURL URLWithString:[agentURL stringByAppendingString:[NSString stringWithFormat:@"/message?params=%d,%d,%d",(int)_xPosic.value, (int)_yPosic.value,(int)_zPosic.value]]];
    NSLog(@"%@", url);
    NSLog(@"%d", (int)_xPosic.value);
    NSLog(@"%d", (int)_yPosic.value);
    NSLog(@"%d", (int)_zPosic.value);
    
    NSData *data = [NSData dataWithContentsOfURL:url];
    NSString *ret = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
    NSLog(@"ret=%@", ret);
    
    
}

- (IBAction)gripperSwitch:(id)sender {
    
    if([sender isOn]){
        NSLog(@"Is On");
        NSString *agentURL = _URL.text;
        NSURL *url = [NSURL URLWithString:[agentURL stringByAppendingString:[NSString stringWithFormat:@"/gripper?params=1"]]];
        NSLog([agentURL stringByAppendingString:[NSString stringWithFormat:@"/gripper?params=1"]]);
        NSData *data = [NSData dataWithContentsOfURL:url];
        NSString *ret = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
        NSLog(@"ret=%@", ret);
    }else{
        NSLog(@"Is Off");
        NSString *agentURL = _URL.text;
        NSURL *url = [NSURL URLWithString:[agentURL stringByAppendingString:[NSString stringWithFormat:@"/gripper?params=0"]]];
        NSLog([agentURL stringByAppendingString:[NSString stringWithFormat:@"/gripper?params=0"]]);
        NSData *data = [NSData dataWithContentsOfURL:url];
        NSString *ret = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
        NSLog(@"ret=%@", ret);
    }
}

- (IBAction)xPosiCACTION:(id)sender {
    _xPosicLable.text = [NSString stringWithFormat:@"X Position: %d", (int)_xPosic.value];
}

- (IBAction)yPosicAction:(id)sender {
    _yPosicLabel.text = [NSString stringWithFormat:@"Y Position: %d", (int)_yPosic.value];
}

- (IBAction)zPosicAction:(id)sender {
    _zPosicLabel.text = [NSString stringWithFormat:@"Z Position: %d", (int)_zPosic.value];
}
@end
