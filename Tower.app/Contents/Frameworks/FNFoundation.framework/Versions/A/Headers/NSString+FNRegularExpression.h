//
//  NSString+FNRegularExpression.h
//  FNFoundation
//
//  Created by Alexander Rinass on 27.06.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (FNRegularExpression)

- (BOOL)isMatchedByRegularExpression:(NSRegularExpression *)regularExpression;
- (NSArray *)componentsMatchedByRegularExpression:(NSRegularExpression *)regularExpression;

@end
