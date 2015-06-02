//
//  ViewController.m
//  BicDuino
//
//  Created by Volodymyr Boichentsov on 01/06/2015.
//  Copyright (c) 2015 Volodymyr Boichentsov. All rights reserved.
//

#import "ViewController.h"
#import "WMGaugeView.h"

#include "ScanViewController.h"

@interface ViewController ()

@property (strong, nonatomic) IBOutlet WMGaugeView *gaugeView2;

@property (strong, nonatomic) IBOutlet UILabel *speedLabel;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [_rfduino setDelegate:self];
    
    
    _gaugeView2.maxValue = 70;
    _gaugeView2.scaleDivisions = 7;
    _gaugeView2.scaleSubdivisions = 10;
    _gaugeView2.scaleStartAngle = 50;
    _gaugeView2.scaleEndAngle = 310;
    _gaugeView2.innerBackgroundStyle = WMGaugeViewInnerBackgroundStyleFlat;
    _gaugeView2.showScaleShadow = NO;
    _gaugeView2.showScale = YES;
    _gaugeView2.scaleFont = [UIFont fontWithName:@"AvenirNext-Regular" size:0.075];
    _gaugeView2.scalesubdivisionsAligment = WMGaugeViewSubdivisionsAlignmentCenter;
    _gaugeView2.scaleSubdivisionsWidth = 0.002;
    _gaugeView2.scaleSubdivisionsLength = 0.04;
    _gaugeView2.scaleDivisionsWidth = 0.007;
    _gaugeView2.scaleDivisionsLength = 0.07;
    _gaugeView2.needleStyle = WMGaugeViewNeedleStyleFlatThin;
    _gaugeView2.needleWidth = 0.012;
    _gaugeView2.needleHeight = 0.4;
    _gaugeView2.needleScrewStyle = WMGaugeViewNeedleScrewStylePlain;
    _gaugeView2.needleScrewRadius = 0.05;
    
    
    [_speedLabel setFont:[UIFont fontWithName:@"AvenirNext-Regular" size:13]];
    
    
    [NSTimer scheduledTimerWithTimeInterval:2.0
                                     target:self
                                   selector:@selector(gaugeUpdateTimer:)
                                   userInfo:nil
                                    repeats:YES];
    
    // Do any additional setup after loading the view, typically from a nib.
}


-(void)gaugeUpdateTimer:(NSTimer *)timer {
    
    [self setSpeed:rand()%(int)_gaugeView2.maxValue];
}

- (void) setSpeed:(float)speed {
    
    [_gaugeView2 setValue:speed animated:YES duration:1.6 completion:^(BOOL finished) {
//        NSLog(@"gaugeView2 animation complete");
    }];
    
    [_speedLabel setText:[NSString stringWithFormat:@"Speed: %.2f", speed]];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)disconnect:(id)sender
{
    NSLog(@"disconnect pressed");
    
    [_rfduino disconnect];
}

- (void)didReceive:(NSData *)data
{
    float speed = dataFloat(data);
    
    [self setSpeed:speed];
    
}

- (void) stopScan {
    [self dismissViewControllerAnimated:YES completion:^{
        
    }];
}

- (IBAction) openScanView:(id)sender {
    
    ScanViewController *viewController = [[ScanViewController alloc] init];
    
    UINavigationController *navController = [[UINavigationController alloc] initWithRootViewController:viewController];
    viewController.mainViewController = self;
    
    [self presentViewController:navController animated:YES completion:^{
        
    }];
}

@end
