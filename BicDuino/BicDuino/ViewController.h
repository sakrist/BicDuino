//
//  ViewController.h
//  BicDuino
//
//  Created by Volodymyr Boichentsov on 01/06/2015.
//  Copyright (c) 2015 Volodymyr Boichentsov. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "RFduino.h"

@interface ViewController : UIViewController<RFduinoDelegate>

@property(strong, nonatomic) RFduino *rfduino;

@end

