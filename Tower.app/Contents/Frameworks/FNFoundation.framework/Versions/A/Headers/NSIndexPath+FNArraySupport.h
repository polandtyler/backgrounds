//
//  NSIndexPath+FNArraySupport.h
//  FNFoundation
//
//  Created by Alexander Rinass on 25.07.13.
//  Copyright (c) 2013 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSIndexPath (FNArraySupport)

/**
 Creates an index path with a given array, e.g. @[ @1, @2, @3 ] will create
 an index path “1.2.3“.
 */
+ (id)indexPathWithArray:(NSArray *)indexes;

- (NSArray *)indexes;

@end
