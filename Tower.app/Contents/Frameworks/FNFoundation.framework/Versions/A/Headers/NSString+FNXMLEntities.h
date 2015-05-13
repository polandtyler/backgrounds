//
//  NSString+FNXMLEntities.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 20.02.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (FNXMLEntities)

- (NSString *)stringByEscapingEntities __attribute__((deprecated));
- (NSString *)stringByEscapingXMLEntities;

- (NSString *)stringByUnescapingEntities __attribute__((deprecated));
- (NSString *)stringByUnescapingXMLEntities;

@end
