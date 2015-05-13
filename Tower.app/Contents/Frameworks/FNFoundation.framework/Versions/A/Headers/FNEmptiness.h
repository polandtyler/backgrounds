//
//  FNUtils.h
//  FNFoundation
//
//  Created by Florian Bürger on 7/30/12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

BOOL FNStringIsEmpty(NSString *string);
BOOL FNURLIsEmpty(NSURL *url);
BOOL FNDataIsEmpty(NSData *data);
BOOL FNArrayIsEmpty(NSArray *array);
BOOL FNDictionaryIsEmpty(NSDictionary *dictionary);
BOOL FNSetIsEmpty(NSSet *set);

BOOL FNIsEmpty(id obj) __deprecated;
BOOL FNIsEmptyString(NSString *obj) __deprecated;
BOOL FNIsNotEmpty(id obj) __deprecated;
BOOL FNIsNotEmptyString(NSString *obj) __deprecated;
