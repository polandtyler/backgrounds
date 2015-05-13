//
//  NSObject+FNObjectDescribing.h
//  FNFoundation
//
//  Created by Alexander Rinaß on 09.03.12.
//  Copyright (c) 2012 Fournova GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSObject (FNObjectDescribing)

/**
 Returns a JSON-like description of the value returned by `attributeKeys`,
 pretty printed.
 */
- (NSString *)prettyDescription;

/**
 Returns a JSON-like description of the value returned by `attributeKeys`.
 */
- (NSString *)defaultDescription;

- (NSString *)prettyDescriptionWithItems:(NSArray *)items;
- (NSString *)prettyDescriptionWithDictionary:(NSDictionary *)dictionary;
- (NSString *)prettyDescriptionForObject:(id)object;

@end
