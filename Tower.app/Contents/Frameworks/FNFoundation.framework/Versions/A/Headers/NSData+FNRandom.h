//
//  NSData+FNRandom.h
//  FNFoundation
//
//  Created by Alexander Rinass on 09.11.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSData (FNRandom)

+ (id)randomDataWithSizeInBytes:(NSUInteger)sizeInBytes;

@end
