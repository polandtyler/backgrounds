//
//  NSString+FNUniqueIdentifier.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 20.02.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (FNUniqueIdentifier)

/**
 Creates a UUID string object.
 
 The UUID is created with `CFUUIDCreateString` and has the form:
 `E7071422-36EE-43F9-8CE9-913F00480542`.
 */
+ (id)uniqueIdentifier;
+ (id)stringWithUUID __attribute__((deprecated));

@end
