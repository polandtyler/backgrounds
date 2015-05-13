//
//  NSString+FNFormat.h
//  FNFoundation
//
//  Created by Alexander Rinass on 09/01/14.
//  Copyright (c) 2014 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (FNFormat)

+ (id)stringWithFormat:(NSString *)format arguments:(NSArray *)arguments;

@end
