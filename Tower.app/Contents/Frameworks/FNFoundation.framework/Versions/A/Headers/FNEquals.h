//
//  FNEquals.h
//  FNFoundation
//
//  Created by Patrick Dinger on 06.02.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

BOOL FNEqualStrings(NSString *firstString, NSString *secondString);
BOOL FNEqualNumbers(NSNumber *firstNumber, NSNumber *secondNumer);
BOOL FNEqualDates(NSDate *firstDate, NSDate *secondDate);
BOOL FNEqualValues(NSValue *firstValue, NSValue *secondValue);
BOOL FNEqualObjects(NSObject *firstValue, NSObject *secondValue);
