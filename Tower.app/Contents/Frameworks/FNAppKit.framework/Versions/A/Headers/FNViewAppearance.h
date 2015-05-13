//
//  FNViewAppearance.h
//  FNAppKit
//
//  Created by Alexander Rinass on 25.06.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 This protocol defines a single class method `appearance` which returns
 a specific instance for configuring the view appearance of the class.
 */
@protocol FNViewAppearance <NSObject>
@optional

+ (id)appearance __deprecated;
+ (id)defaultAppearance;

@end

@class FNViewDefaults;
@interface FNViewAppearance : NSObject <FNViewAppearance>
@property (nonatomic, readonly) FNViewDefaults *viewDefaults;
@end
