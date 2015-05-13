//
//  NSMenuItem+FNRepresentedObjectValues.h
//  FNAppKit
//
//  Created by Alexander Rinass on 13/03/14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSMenuItem (FNRepresentedObjectValues)

- (id)valueForClass:(__unsafe_unretained Class)class;
- (id)valuesForClass:(__unsafe_unretained Class)class;

@end
